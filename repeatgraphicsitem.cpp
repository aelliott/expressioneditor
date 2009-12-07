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

#include "repeatgraphicsitem.hpp"

RepeatGraphicsItem::RepeatGraphicsItem(RepeatGraphicsItem::Type type, int minimum, int maximum, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    switch(type)
    {
        case RepeatGraphicsItem::ZeroOrOne:
            title = "Included At Most Once";
            break;
        case RepeatGraphicsItem::ZeroOrMore:
            title = "Repeated 0+ Times";
            break;
        case RepeatGraphicsItem::OneOrMore:
            title = "Repeated At Least Once";
            break;
        case RepeatGraphicsItem::ExactValue:
            title = "Repeated Exactly " + QVariant(minimum).toString() + " Times";
            break;
        case RepeatGraphicsItem::SpecifiedRange:
            if(maximum == -1)
                title = "Repeated At Least " + QVariant(minimum).toString() + " Times";
            else
                title = "Repeated Between " + QVariant(minimum).toString() + " And " + QVariant(maximum).toString() + " Times";
            break;
    }

    setType = type;
    setMinimum = minimum;
    setMaximum = maximum;

    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    backgroundColour = QColor(255, 230, 230);
}

void RepeatGraphicsItem::setChildItem(QGraphicsItem *item)
{
    // There can only be one child item
    if(childItems().size() > 0)
        delete childItems().at(0);
    item->setParentItem(this);
    double verticalOffset = qApp->fontMetrics().height() + 1.5*verticalPadding;
    double horizontalOffset = (boundingRect().width()/2)-(item->boundingRect().width()/2);
    item->setPos(horizontalOffset, verticalOffset);
}

QRectF RepeatGraphicsItem::boundingRect() const
{
    double width = 0;
    double height = 0;
    if(childItems().size() > 0)
    {
        if(childItems().at(0)->boundingRect().width() > qApp->fontMetrics().width(title))
            width  = childItems().at(0)->boundingRect().width()  + 2*horizontalPadding;
        else
            width = qApp->fontMetrics().width(title) + 2*horizontalPadding;
        height = childItems().at(0)->boundingRect().height() + qApp->fontMetrics().height() + 2.5*verticalPadding;
    }
    return QRectF(0, 0, width, height);
}

void RepeatGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(235, 210, 210));

    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    painter->drawText(horizontalPadding, 0.5*qApp->fontMetrics().height()+verticalPadding, title);
}

void RepeatGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(245, 220, 220);
    update();
}

void RepeatGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(255, 230, 230);
    update();
}
