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

BracketExpressionGraphicsItem::BracketExpressionGraphicsItem(bool negated, QGraphicsItem *parent)
    : QGraphicsWidget(parent)
    , _negated(negated)
{
    _text = new QGraphicsTextItem(this);
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
        QString chars = "Any one of: ";
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

    QString text;
    if(_negated)
        text = "Any Character Except:";
    else
        text = "Any One Of:";

    for(stringIter = items.begin(); stringIter != items.end(); ++stringIter)
    {
        text += QString("<br>  - ") + (*stringIter);
    }

    _text->setHtml(text);
}

QRectF BracketExpressionGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/BracketExpression/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/BracketExpression/VerticalPadding", 5.0).toDouble();

    QRectF textRect = _text->boundingRect();

    return QRectF(0, 0, textRect.width() + 2*horizontalPadding, textRect.height() + 2*verticalPadding);
}

void BracketExpressionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/BracketExpression/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/BracketExpression/VerticalPadding", 5.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/BracketExpression/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/BracketExpression/Color", QColor(225,225,255)).value<QColor>();

    painter->setBrush(bgColor);
    painter->setPen(Qt::black);

    painter->drawRoundedRect(boundingRect(), cornerRadius, cornerRadius);

    _text->setPos(horizontalPadding, verticalPadding);
}

QSizeF BracketExpressionGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
