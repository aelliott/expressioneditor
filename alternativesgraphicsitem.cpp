/*!
 * \file
 * \author Alex Elliott <alex@alex-elliott.co.uk>
 * \version 0.1pre
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009,2010 Alex Elliott <alex@alex-elliott.co.uk>
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

#include "alternativesgraphicsitem.hpp"

/*!
 * Creates a new AlternativesGraphicsItem
 *
 * \param   parent  The item's parent
 */
AlternativesGraphicsItem::AlternativesGraphicsItem(QGraphicsItem *parent) : RegexGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    backgroundColour = QColor(255, 255, 210);
    updateData();
}

/*!
 * Returns the geometry of the graphical object
 */
QRectF AlternativesGraphicsItem::boundingRect() const
{
    // Items are stacked vertically
    double width = 0;
    double height = 0;

    // The size of this element depends on its children, we must calculate:
    //  - the sum of the item heights plus title height and padding/spacing
    //  - the maximum width of the items plus padding
    for(int i = 0; i < childItems().size(); ++i)
    {
        QRectF rect = childItems().at(i)->boundingRect();
        if((rect.width() + 2*horizontalPadding) > width)
            width = rect.width();
        height += rect.height() + 2*verticalPadding;
    }

    // If the heading is wider than any of the elements then we'll take that
    // width instead.
    if(qApp->fontMetrics().width(tr("Alternatives")) > width)
        width = qApp->fontMetrics().width(tr("Alternatives"));

    // Height of heading:
    height += qApp->fontMetrics().height() + verticalPadding;
    width +=  2*horizontalPadding;

    return QRectF(0, 0, width, height);
}

/*!
 * Paints the object on the canvas and lays out child items
 *
 * \param   painter QPainter used to draw the item
 * \param   option  Unused
 * \param   widget  Unused
 */
void AlternativesGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // If we're not currently selecting this object use the stored
    // background colour.
    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(245, 245, 180));

    // Draw the main item background
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

        // Draw lines between the child items
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

/*!
 * This method adds a new alternation (and a new item) to the
 * AlternativesGraphicsItem, this will be maintained as a new
 * vertically stacked item within the visualisation
 *
 * \param   item    A regular expression segment
 */
void AlternativesGraphicsItem::addChildItem(QGraphicsObject *item)
{
    item->setParentItem(this);
    connect(item, SIGNAL(dataChanged()), this, SLOT(updateData()));
    connect(item, SIGNAL(editComplete()), this, SLOT(editCompleted()));
    connect(item, SIGNAL(removeItem(QGraphicsObject*)), this, SLOT(removeChild(QGraphicsObject*)));

    updateData();
}

/*!
 * Hover over listener, triggers the hover state (colour change)
 *
 * \param   event   The hover event
 */
void AlternativesGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(250, 250, 190);
    update();
}

/*!
 * Hover exit listener, triggers a return to the normal state
 *
 * \param   event   The hover event
 */
void AlternativesGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(255, 255, 210);
    update();
}

/*!
 * Update the object's internal data, trigger dataChanged on any changes
 * in state.
 */
void AlternativesGraphicsItem::updateData()
{
    QStringList expression;
    for(int i = 0; i < childItems().size(); ++i)
        expression << childItems().at(i)->data(expressionData).toString();
    setData(expressionData, QVariant(expression.join("|")));
    emit dataChanged();
}
