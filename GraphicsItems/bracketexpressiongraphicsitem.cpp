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
#include "bracketexpressiongraphicsitem.hpp"

BracketExpressionGraphicsItem::BracketExpressionGraphicsItem(Token *token, int tokenPos, QGraphicsItem *parent)
    : RegexGraphicsItem(token, tokenPos, parent)
{
    _negated = (token->type() == T_NEGATED_BRACKET_EXPRESSION_OPEN);
}

void BracketExpressionGraphicsItem::addToken(Token *token)
{
    _tokens.push_back(token);
    readTokens();
}

void BracketExpressionGraphicsItem::readTokens()
{
    std::vector<Token *>::iterator iter;
    QStringList characters;
    QStringList items;

    for(iter = _tokens.begin(); iter != _tokens.end(); ++iter)
    {
        Token *token = *iter;
        switch(token->type())
        {
        case T_LITERAL:
            if(token->value().length() == 2 && QString("\\") == QString(token->value()[0]))
                characters.push_back(QString(token->value()[1]));
            else
                characters.push_back(token->value());
            break;
        case T_BRACKET_EXPRESSION_RANGE:
            items.push_back(token->value());
            break;
        case T_WORD:
            items.push_back(QString("Word Character"));
            break;
        case T_NOT_WORD:
            items.push_back(QString("Not Word Character"));
            break;
        case T_DIGIT:
            items.push_back(QString("Digit Character"));
            break;
        case T_NOT_DIGIT:
            items.push_back(QString("Not Digit Character"));
            break;
        case T_SPACE:
            items.push_back(QString("Space Character"));
            break;
        case T_NOT_SPACE:
            items.push_back(QString("Not Space Character"));
            break;
        case T_WORD_BOUNDARY:
            items.push_back(QString("Word Boundary"));
            break;
        case T_NOT_WORD_BOUNDARY:
            items.push_back(QString("Not Word Boundary"));
            break;
        default:
            qDebug() << "Unhandled token in bracket expression: " << token->value();
        }
    }

    characters.removeDuplicates();
    QStringList::iterator stringIter;

    if(characters.length() > 0)
    {
        QString chars = "Characters: ";
        bool first = true;
        for(stringIter = characters.begin(); stringIter != characters.end(); ++stringIter)
        {
            if(!first)
                chars += QString(", ") + (*stringIter);
            else
            {
                chars += (*stringIter);
                first = false;
            }
        }
        items.push_back(chars);
    }

    if(_negated)
        _heading = "Any Character Except:";
    else
        _heading = "Any One Of:";

    _text = "";
    bool first = true;
    for(stringIter = items.begin(); stringIter != items.end(); ++stringIter)
    {
        if(first)
        {
            _text = QString(" - ") + (*stringIter);
            first = false;
        }
        else
            _text += QString("\n - ") + (*stringIter);
    }
}

QRectF BracketExpressionGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/BracketExpression/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/BracketExpression/VerticalPadding", 5.0).toDouble();

    // +2 in this case because of the extra heading in paint()
    // This also means 3 sets of vertical padding
    int lines = _text.count("\n")+2;
    double textWidth = 0.0;
    QStringList words = _text.split("\n");
    for(int i = 0; i < words.size(); ++i)
        if(_metrics.width(words.at(i)) > textWidth)
            textWidth = _metrics.width(words.at(i));
    textWidth = qMax(textWidth, static_cast<double>(_metrics.width(_heading)));

    return QRectF(0, 0, textWidth + 2*horizontalPadding, lines*_metrics.height() + 3*verticalPadding);
}

void BracketExpressionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    _font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    double horizontalPadding = settings.value("Visualisation/BracketExpression/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/BracketExpression/VerticalPadding", 5.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/BracketExpression/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/BracketExpression/Color", QColor(225,225,255)).value<QColor>();

    painter->setFont(_font);
    painter->setBrush(bgColor);
    painter->setPen(Qt::black);

    QRectF drawRect = boundingRect();
    // Align the rect to the pixel grid
    if(qRound(scenePos().x()) == scenePos().x())
    {
        drawRect.setX(0.5);
        drawRect.setWidth(drawRect.width()-.5);
    }
    if(qRound(scenePos().y()) == scenePos().y())
    {
        drawRect.setHeight(drawRect.height()-.5);
        drawRect.setY(0.5);
    }
    painter->drawRoundedRect(drawRect, cornerRadius, cornerRadius);

    int lines = _text.count("\n")+1;
    double textWidth = 0.0;
    QStringList words = _text.split("\n");
    for(int i = 0; i < words.size(); ++i)
        if(_metrics.width(words.at(i)) > textWidth)
            textWidth = _metrics.width(words.at(i));
    textWidth = qMax(textWidth, static_cast<double>(_metrics.width(_heading)));

    painter->drawText(QRectF(
                          horizontalPadding,
                          verticalPadding,
                          textWidth,
                          _metrics.height()),
                      Qt::AlignCenter,
                      _heading);

    painter->drawText(QRectF(
                          horizontalPadding,
                          _metrics.height() + 2*verticalPadding,
                          textWidth,
                          lines*_metrics.height()),
                      Qt::AlignVCenter | Qt::AlignLeft | Qt::TextWordWrap,
                      _text);
}

QSizeF BracketExpressionGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
