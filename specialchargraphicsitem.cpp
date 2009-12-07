/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009 Alex Elliott <alex@alex-elliott.co.uk>
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
 *
 */

#include "specialchargraphicsitem.hpp"

SpecialCharGraphicsItem::SpecialCharGraphicsItem(QGraphicsItem *parent)
{
    SpecialCharGraphicsItem("", parent);
}

SpecialCharGraphicsItem::SpecialCharGraphicsItem(QString text, QGraphicsItem *parent)
{
    contents = new QGraphicsTextItem;
    contents->setParentItem(this);
    setContents(text);
    backgroundColour = QColor(255, 220, 255);
}

void SpecialCharGraphicsItem::setContents(QString text)
{
    if(!text.isEmpty())
    {
        if(text == ".")
            contents->setHtml("Matches<br>any character");
        if(text == "^")
            contents->setHtml("Line<br>start");
        if(text == "$")
            contents->setHtml("Line<br>end");
        if(text == "\\d")
            contents->setHtml("Digit<br>character");
        if(text == "\\b")
            contents->setHtml("Word<br>boundary");
        if(text == "\\w")
            contents->setHtml("Word<br>character");
    }
    else contents->setHtml(text);
}

QRectF SpecialCharGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, contents->boundingRect().width()+2*horizontalPadding, contents->boundingRect().height()+2*verticalPadding);
}

void SpecialCharGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(235, 200, 235));

    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    contents->setPos(horizontalPadding, verticalPadding);
}

void SpecialCharGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(245, 210, 245);
    update();
}

void SpecialCharGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(255, 220, 255);
    update();
}
