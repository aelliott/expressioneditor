/*!
 * \file
 *
 * Copyright (c) 2011,2012 Alex Elliott <alex@alex-elliott.co.uk>
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Expression editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Expression editor.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "expressiongraphicsitem.hpp"

ExpressionGraphicsItem::ExpressionGraphicsItem(QString expression, RegexFactory::RegexFormat format, QGraphicsItem *parent)
    : QGraphicsWidget(parent)
    , _expression(expression)
    , _pos(0)
{
    QSettings settings;
    _itemSpacing = settings.value("Visualisation/HorizontalSpacing", 8.0).toDouble();

    _factory = new RegexFactory(format);

    Parser *parser = _factory->regexpParser();
    parser->parse(_expression);

    _tokens = parser->tokens();
    _root = new QGraphicsLinearLayout(Qt::Horizontal);
    _root->setSpacing(_itemSpacing);

    for(_iter = _tokens.begin(); _iter != _tokens.end();)
    {
        _incremented = false;

        _root = handleToken(**_iter, _root);

        // The iterator can be incremented from within handleToken, so we must
        // ensure we do not run over the end
        if(_iter != _tokens.end() && !_incremented)
        {
            ++_iter;
            ++_pos;
        }
    }
    _root->setContentsMargins(10, 10, 10, 10);
    setLayout(_root);

    delete parser;
}

ExpressionGraphicsItem::~ExpressionGraphicsItem()
{
    delete _factory;
}

QGraphicsLinearLayout *ExpressionGraphicsItem::handleToken(Token token, QGraphicsLinearLayout *currentLayout)
{
    RegexGraphicsItem *newItem;
    RepeatGraphicsItem *repeat;
    QGraphicsLinearLayout *newLayout;
    bool defaultCapturing = true;
    bool named = false;
    _incremented = false;

    switch(token.type())
    {
    case T_LITERAL:
        newItem = new LiteralGraphicsItem(*_iter, _pos);
        currentLayout->addItem(newItem);
        //currentLayout->setAlignment(newItem, Qt::AlignVCenter | Qt::AlignLeft);
        _lastItem = newItem;
        break;
    case T_ALTERNATION:
    {
        // This is a bit nasty, but it works
        int start = static_cast<RegexGraphicsItem *>(currentLayout->itemAt(0))->tokenPos();
        AlternationGraphicsItem *alternation = new AlternationGraphicsItem(currentLayout, *_iter, start);
        currentLayout = new QGraphicsLinearLayout(Qt::Horizontal);
        currentLayout->setSpacing(_itemSpacing);
        currentLayout->addItem(alternation);
        ++_iter;
        ++_pos;
        _incremented = true;
        while(_iter != _tokens.end() && (*_iter)->type() != T_GROUPING_CLOSE)
        {
            _incremented = false;

            if((*_iter)->type() == T_ALTERNATION)
            {
                alternation->newBranch();
                alternation->linearLayout()->setSpacing(_itemSpacing);
            }
            else
                handleToken(**_iter, alternation->linearLayout());

            if(_iter != _tokens.end() && !_incremented)
            {
                ++_iter;
                ++_pos;
                _incremented = true;
            }
        }
        alternation->setEndPos(_pos-1);
        _lastItem = alternation;
    }
        break;
    case T_NAMED_GROUPING_OPEN:
    case T_GROUPING_OPEN:
    case T_REVERSED_CAPTURING_GROUPING_OPEN:
    {
        GroupingGraphicsItem *grouping = new GroupingGraphicsItem(*_iter, _pos, defaultCapturing);
        currentLayout->addItem(grouping);
        //currentLayout->setAlignment(grouping, Qt::AlignVCenter | Qt::AlignLeft);
        ++_iter;
        ++_pos;
        _incremented = true;
        newLayout = new QGraphicsLinearLayout(Qt::Horizontal);
        newLayout->setSpacing(_itemSpacing);
        while(_iter != _tokens.end() && (*_iter)->type() != T_GROUPING_CLOSE)
        {
            _incremented = false;

            newLayout = handleToken(**_iter, newLayout);

            if(_iter != _tokens.end() && !_incremented)
            {
                ++_iter;
                ++_pos;
                _incremented = true;
            }
        }
        if((*_iter)->type() == T_GROUPING_CLOSE)
        {
            ++_iter;
            ++_pos;
            _incremented = true;
        }
        grouping->setLinearLayout(newLayout);
        grouping->setEndPos(_pos-1);
        _lastItem = grouping;
    }
        break;
    case T_BRACKET_EXPRESSION_OPEN:
    case T_NEGATED_BRACKET_EXPRESSION_OPEN:
    {
        BracketExpressionGraphicsItem *bracketExpression = new BracketExpressionGraphicsItem(*_iter, _pos);
        currentLayout->addItem(bracketExpression);

        ++_iter;
        ++_pos;
        _incremented = true;

        while(_iter != _tokens.end() && (*_iter)->type() != T_BRACKET_EXPRESSION_CLOSE)
        {
            bracketExpression->addToken(*_iter);
            ++_iter;
            ++_pos;
        }

        if((*_iter)->type() == T_BRACKET_EXPRESSION_CLOSE)
        {
            ++_iter;
            ++_pos;
        }

        bracketExpression->setEndPos(_pos-1);
        _lastItem = bracketExpression;
    }
        break;
    case T_STARTING_POSITION:
    case T_ENDING_POSITION:
        newItem = new AnchorGraphicsItem(*_iter, _pos);
        currentLayout->addItem(newItem);
        _lastItem = newItem;
        break;
    case T_WORD:
    case T_NOT_WORD:
    case T_DIGIT:
    case T_NOT_DIGIT:
    case T_SPACE:
    case T_NOT_SPACE:
        newItem = new CharacterClassItem(*_iter, _pos);
        currentLayout->addItem(newItem);
        _lastItem = newItem;
        break;
    case T_ANY_CHARACTER:
    case T_BELL:
    case T_BACKSPACE:
    case T_ESCAPE:
    case T_FORM_FEED:
    case T_LINE_FEED:
    case T_CARRIAGE_RETURN:
    case T_HORIZONTAL_TAB:
    case T_VERTICAL_TAB:
    case T_ASCII_CONTROL_CHAR:
    case T_UNICODE_NEWLINE:
    case T_BYTE:
    case T_OCTAL_CHAR:
    case T_HEXADECIMAL_CHAR:
    case T_UNICODE_CHAR:
    case T_UNICODE_NAMED_CHAR:
    case T_GRAPHEME_CLUSTER:
        newItem = new SpecialCharGraphicsItem(*_iter, _pos);
        currentLayout->addItem(newItem);
        _lastItem = newItem;
        break;
    case T_REPEAT_ZERO_OR_ONE:
    case T_REPEAT_ANY_NUMBER:
    case T_REPEAT_ONE_OR_MORE:
    case T_REPEAT_SPECIFIED:
        currentLayout->removeItem(_lastItem);
        repeat = new RepeatGraphicsItem(*_iter, _lastItem->tokenPos(), _lastItem);
        repeat->setEndPos(_pos);
        currentLayout->addItem(repeat);
        _lastItem = repeat;
        break;
    case T_COMMENT_OPEN:
        newItem = new CommentGraphicsItem(*_iter, _pos);
        ++_iter;
        ++_pos;
        _incremented = true;

        if(_iter != _tokens.end() && (*_iter)->type() == T_LITERAL)
        {
            currentLayout->addItem(newItem);
            ++_iter;
            ++_pos;
            if(_iter != _tokens.end() && (*_iter)->type() == T_COMMENT_CLOSE)
            {
                ++_iter;
                ++_pos;
            }
        }
        else if(_iter != _tokens.end() && (*_iter)->type() == T_COMMENT_CLOSE)
        {
            currentLayout->addItem(newItem);
            ++_iter;
            ++_pos;
        }
        newItem->setEndPos(_pos-1);
        _lastItem = newItem;
        break;
    default:
        newItem = new ErrorGraphicsItem(*_iter, _pos);
        currentLayout->addItem(newItem);
        //currentLayout->setAlignment(newItem, Qt::AlignVCenter | Qt::AlignLeft);
        _lastItem = newItem;
    }

    _lastItem->setGeometry(_lastItem->boundingRect());
    currentLayout->setAlignment(_lastItem, Qt::AlignVCenter | Qt::AlignLeft);
    currentLayout->setGeometry(QRectF(0, 0, currentLayout->sizeHint(Qt::PreferredSize).width(),
                               currentLayout->sizeHint(Qt::PreferredSize).height()));

    return currentLayout;
}

QRectF ExpressionGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, _root->geometry().width()+20, _root->geometry().height() + 20 );
}

QSizeF ExpressionGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
