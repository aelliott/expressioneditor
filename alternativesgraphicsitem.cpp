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

#include "alternativesgraphicsitem.hpp"

AlternativesGraphicsItem::AlternativesGraphicsItem(QGraphicsItem *parent) : RegexGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    backgroundColour = QColor(255, 255, 210);
    updateData();
}

QRectF AlternativesGraphicsItem::boundingRect() const
{
    // Items are stacked vertically
    double width = 0;
    double height = 0;
    for(int i = 0; i < childItems().size(); ++i)
    {
        QRectF rect = childItems().at(i)->boundingRect();
        if((rect.width() + 2*horizontalPadding) > width)
            width = rect.width();
        height += rect.height() + 2*verticalPadding;
    }
    // Width of heading
    if(qApp->fontMetrics().width(tr("Alternatives")) > width)
        width = qApp->fontMetrics().width(tr("Alternatives"));
    // Height of heading:
    height += qApp->fontMetrics().height() + verticalPadding;
    width +=  2*horizontalPadding;
    return QRectF(0, 0, width, height);
}

void AlternativesGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(245, 245, 180));
    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);

    // Draw heading
    double lineHeight = verticalPadding+(painter->fontMetrics().height()/2);
    painter->drawText(horizontalPadding, lineHeight, tr("Alternatives"));

    lineHeight += verticalPadding;
    double width = boundingRect().width();
    double verticalOffset = 2*verticalPadding+(qApp->fontMetrics().height()/2);

    for(int i = 0; i < childItems().size(); ++i)
    {
        QRectF rect = childItems().at(i)->boundingRect();

        // Draw lines
        if(i != childItems().size()-1)
        {
            lineHeight += rect.height();
            lineHeight += verticalPadding;
            painter->drawLine(horizontalPadding, lineHeight, width-horizontalPadding, lineHeight);
            lineHeight += verticalPadding;
        }

        // Lay out items
        childItems().at(i)->setPos((width/2)-(rect.width()/2), verticalOffset);
        verticalOffset += rect.height() + 2*verticalPadding;
    }
}

void AlternativesGraphicsItem::addChildItem(QGraphicsObject *item)
{
    item->setParentItem(this);
    connect(item, SIGNAL(dataChanged()), this, SLOT(updateData()));

    updateData();
}

void AlternativesGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(250, 250, 190);
    update();
}

void AlternativesGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(255, 255, 210);
    update();
}

/**
 * Private methods
 */
void AlternativesGraphicsItem::updateData()
{
    QStringList expression;
    for(int i = 0; i < childItems().size(); ++i)
        expression << childItems().at(i)->data(expressionData).toString();
    setData(expressionData, QVariant(expression.join("|")));
    emit dataChanged();
}
