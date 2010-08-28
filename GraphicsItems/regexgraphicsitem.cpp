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

#include "regexgraphicsitem.hpp"

/*!
 * Creates a new RegexGraphicsItem
 *
 * \param   parent  The item's parent item
 */
RegexGraphicsItem::RegexGraphicsItem(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    setCursor(Qt::OpenHandCursor);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

/*!
 * Handle a mouse click on this item
 *
 * \param   event   The mouse click event captured
 */
void RegexGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // If we've been clicked with the left mouse button register the
    // location to check against when initiating a drag event.
    if(event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

/*!
 * Handle a mouse move event to check if a drag event should
 * be initiated
 *
 * \param   event   The mouse move event captured
 */
void RegexGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Check if the left mouse button is being held with the movement,
    // if not we can safely ignore it.
    if (!(event->buttons() & Qt::LeftButton))
        return;

    // Check if the mouse has moved sufficiently far to initiate a drag
    // event, if not we can ignore it for now
    if ((event->pos() - dragStartPosition).manhattanLength()
            < QApplication::startDragDistance())
        return;

    // The mouse has moved far enough, create a new drag event and attach
    // this item's details to it
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mimeData = new QMimeData;

    // Attach the data associated with this element as a text/x-regexp
    mimeData->setData("text/x-regexp", this->data(expressionData).toByteArray());
    drag->setMimeData(mimeData);

    // Create a scaled down image of the regexp item being dragged and use
    // that as the pixmap image to drag around (so it's clear what element
    // is attached to the drag event)
    QPixmap image(this->boundingRect().width()*0.75, this->boundingRect().height()*0.75);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene()->render(&painter, QRectF(), this->sceneBoundingRect());
    painter.end();

    // Attach the scaled down image to the drag event
    drag->setPixmap(image);

    // Execute the drag event
    Qt::DropAction dropAction = drag->exec();

    // If the action is accepted then this element has moved and this item
    // should remove itself from its current location
    if(dropAction == Qt::MoveAction)
        emit removeItem(this);
}

/*!
 * Update the item's internal data, this is expected to be overridden
 * in the derived classes
 */
void RegexGraphicsItem::updateData(){ }

/*!
 * Removes the specified item from the item.  Can be overridden in the
 * derived class
 *
 * \param   item    The item to be deleted
 */
void RegexGraphicsItem::removeChild(QGraphicsObject *item)
{
    // Check if we have ownership of this pointer
    if(isAncestorOf(item))
        delete item;
    update();
    updateData();
    editCompleted();
}

/*!
 * Slot triggering an editComplete() signal
 */
void RegexGraphicsItem::editCompleted()
{
    emit editComplete();
}
