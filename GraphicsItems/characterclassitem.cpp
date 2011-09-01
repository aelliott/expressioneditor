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
#include "characterclassitem.hpp"

CharacterClassItem::CharacterClassItem(RegexpToken token, QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    _text = new QGraphicsTextItem(this);

    switch(token)
    {
    case T_WORD:
        _text->setHtml("<center>Word<br>Character");
        break;
    case T_NOT_WORD:
        _text->setHtml("<center>Non-word<br>Character");
        break;
    case T_DIGIT:
        _text->setHtml("<center>Digit<br>Character");
        break;
    case T_NOT_DIGIT:
        _text->setHtml("<center>Non-digit<br>Character");
        break;
    case T_SPACE:
        _text->setHtml("<center>Space<br>Character");
        break;
    case T_NOT_SPACE:
        _text->setHtml("<center>Non-space<br>Character");
        break;
    }

    _text->setTextWidth(_text->boundingRect().width());
}

QRectF CharacterClassItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/CharacterClass/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/CharacterClass/VerticalPadding", 5.0).toDouble();

    QRectF textRect = _text->boundingRect();

    return QRectF(0, 0, textRect.width() + 2*horizontalPadding, textRect.height() + 2*verticalPadding);
}

void CharacterClassItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/CharacterClass/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/CharacterClass/VerticalPadding", 5.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/CharacterClass/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/CharacterClass/Color", QColor(255,220,255)).value<QColor>();

    painter->setBrush(bgColor);
    painter->setPen(Qt::black);

    painter->drawRoundedRect(boundingRect(), cornerRadius, cornerRadius);

    _text->setPos(horizontalPadding, verticalPadding);
}

QSizeF CharacterClassItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
