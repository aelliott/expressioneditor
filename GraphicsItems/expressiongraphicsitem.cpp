/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
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
            ++_iter;
    }
    setLayout(_root);

    delete parser;
}

ExpressionGraphicsItem::~ExpressionGraphicsItem()
{
    delete _factory;
}

QGraphicsLinearLayout *ExpressionGraphicsItem::handleToken(Token token, QGraphicsLinearLayout *currentLayout)
{
    QGraphicsWidget *newItem;
    GroupingGraphicsItem *grouping;
    RepeatGraphicsItem *repeat;
    AlternationGraphicsItem *alternation;
    BracketExpressionGraphicsItem *bracketExpression;
    QGraphicsLinearLayout *newLayout;
    bool capturing = true;
    bool named = false;
    bool negated = true;
    _incremented = false;

    switch(token.type())
    {
    case T_LITERAL:
        newItem = new LiteralGraphicsItem(token.value());
        currentLayout->addItem(newItem);
        //currentLayout->setAlignment(newItem, Qt::AlignVCenter | Qt::AlignLeft);
        _lastItem = newItem;
        break;
    case T_ALTERNATION:
        alternation = new AlternationGraphicsItem(currentLayout);
        currentLayout = new QGraphicsLinearLayout(Qt::Horizontal);
        currentLayout->setSpacing(_itemSpacing);
        currentLayout->addItem(alternation);
        ++_iter;
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
                _incremented = true;
            }
        }
        _lastItem = alternation;
        break;
    case T_NAMED_GROUPING_OPEN:
    case T_GROUPING_OPEN:
    case T_REVERSED_CAPTURING_GROUPING_OPEN:
        grouping = new GroupingGraphicsItem(token, capturing);
        currentLayout->addItem(grouping);
        //currentLayout->setAlignment(grouping, Qt::AlignVCenter | Qt::AlignLeft);
        ++_iter;
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
                _incremented = true;
            }
        }
        if((*_iter)->type() == T_GROUPING_CLOSE)
        {
            ++_iter;
            _incremented = true;
        }
        grouping->setLinearLayout(newLayout);
        _lastItem = grouping;
        break;
    case T_BRACKET_EXPRESSION_OPEN:
        negated = !negated;
    case T_NEGATED_BRACKET_EXPRESSION_OPEN:
        bracketExpression = new BracketExpressionGraphicsItem(negated);
        currentLayout->addItem(bracketExpression);

        ++_iter;
        _incremented = true;

        while(_iter != _tokens.end() && (*_iter)->type() != T_BRACKET_EXPRESSION_CLOSE)
        {
            bracketExpression->addToken(*_iter);
            ++_iter;
        }

        if((*_iter)->type() == T_BRACKET_EXPRESSION_CLOSE)
            ++_iter;

        _lastItem = bracketExpression;
        break;
    case T_STARTING_POSITION:
    case T_ENDING_POSITION:
        newItem = new AnchorGraphicsItem(token.type());
        currentLayout->addItem(newItem);
        _lastItem = newItem;
        break;
    case T_WORD:
    case T_NOT_WORD:
    case T_DIGIT:
    case T_NOT_DIGIT:
    case T_SPACE:
    case T_NOT_SPACE:
        newItem = new CharacterClassItem(token.type());
        currentLayout->addItem(newItem);
        _lastItem = newItem;
        break;
    case T_REPEAT_ZERO_OR_ONE:
    case T_REPEAT_ANY_NUMBER:
    case T_REPEAT_ONE_OR_MORE:
    case T_REPEAT_SPECIFIED:
        currentLayout->removeItem(_lastItem);
        repeat = new RepeatGraphicsItem(token, _lastItem);
        currentLayout->addItem(repeat);
        _lastItem = repeat;
        break;
    case T_COMMENT_OPEN:
        ++_iter;
        _incremented = true;

        if(_iter != _tokens.end() && (*_iter)->type() == T_LITERAL)
        {
            newItem = new CommentGraphicsItem((*_iter)->value());
            currentLayout->addItem(newItem);
            ++_iter;
            if(_iter != _tokens.end() && (*_iter)->type() == T_COMMENT_CLOSE)
                ++_iter;
        }
        else if(_iter != _tokens.end() && (*_iter)->type() == T_COMMENT_CLOSE)
        {
            newItem = new CommentGraphicsItem("");
            currentLayout->addItem(newItem);
            ++_iter;
        }
        _lastItem = newItem;
        break;
    default:
        newItem = new ErrorGraphicsItem(token.value());
        currentLayout->addItem(newItem);
        //currentLayout->setAlignment(newItem, Qt::AlignVCenter | Qt::AlignLeft);
        _lastItem = newItem;
    }

    currentLayout->setAlignment(_lastItem, Qt::AlignVCenter | Qt::AlignLeft);

    return currentLayout;
}
