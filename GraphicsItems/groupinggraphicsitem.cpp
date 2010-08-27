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

#include "groupinggraphicsitem.hpp"

/*!
 * Creates a new GroupingGraphicsItem
 *
 * \param   brackets    Determines whether this grouping
 *                      has parenteheses around it
 * \param   outer   True if the item should graphically have
 *                  outer padding
 * \param   capturing   True if this is a capturing group
 * \param   parent  This item's parent item
 */
GroupingGraphicsItem::GroupingGraphicsItem(bool brackets, bool outer, bool capturing, QGraphicsItem *parent) : QGraphicsObject(parent), hasBrackets(brackets), isCapturing(capturing)
{
    setOuterGroup(outer);
    dragEvent = false;
    setAcceptDrops(true);
    updateData();
}

/*!
 * Returns the geometry of the graphical object
 *
 * \return  Returns a QRectF containing the object's geometry
 */
QRectF GroupingGraphicsItem::boundingRect() const
{
    double height = 0;
    double width = 0;
    for(int i = 0; i < childItems().size(); ++i)
    {
        QRectF rect = childItems().at(i)->boundingRect();
        if(rect.height() > height)
            height = rect.height();
        width += rect.width() + itemSpacing;
    }
    if(width > 0 && !outerGroup)
        width -= itemSpacing;
    else
        width += itemSpacing;
    return QRectF(0, 0, width, height);
}

/*!
 * Paints the object on the canvas and lays out child items
 *
 * \param   painter The QPainter used to draw the graphics item
 * \param   option  Unused
 * \param   widget  Unused
 */
void GroupingGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    dropZones.clear();

    // Lay out items
    double offset = 0;
    double height = boundingRect().height();
    for(int i = 0; i < childItems().size(); ++i)
    {
        // Get the geometry of the child item
        QRectF rect = childItems().at(i)->boundingRect();

        // If there is currently a drag event, draw the valid
        // drop zones and add their geometry to dropZones
        if(dragEvent && (outerGroup || offset > 0))
        {
            QRectF dropZone(offset, 0, itemSpacing, height);
            dropZones.push_back(dropZone);
            QBrush brush(Qt::lightGray, Qt::BDiagPattern);
            painter->setBrush(brush);
            painter->setPen(Qt::NoPen);
            painter->drawRect(dropZone);
        }

        // If we're between items or at either end of an outer
        // group add padding
        if(offset > 0 || outerGroup)
            offset += itemSpacing;

        // Align the item centrally along the vertical axis
        double verticalOffset = (height/2)-(rect.height()/2);
        if(!childItems().at(i)->isSelected())
            childItems().at(i)->setPos(offset, verticalOffset);

        // Add the item's width to the offset to prevent overlap
        // of elements
        offset += rect.width();
    }

    // If this is an outer group then draw the valid drop zones
    // at either end of the item and add those to dropZones
    if(dragEvent && outerGroup)
    {
        QRectF dropZone(offset, 0, itemSpacing, height);
        dropZones.push_back(dropZone);
        QBrush brush(Qt::lightGray, Qt::BDiagPattern);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawRect(dropZone);
    }
}

/*!
 * Adds an item to be a child of the group
 *
 * \param   item    The item to add as a new child
 * \param   updateFlag  False if we do not want to update the object's
 *                      internal data with this addition (to prevent the
 *                      change being overwritten in some circumstances)
 */
void GroupingGraphicsItem::addChildItem(QGraphicsObject *item, bool updateFlag)
{
    item->setParentItem(this);
    connect(item, SIGNAL(dataChanged()), this, SLOT(updateData()));
    connect(item, SIGNAL(editComplete()), this, SLOT(editCompleted()));
    connect(item, SIGNAL(removeItem(QGraphicsObject*)), this, SLOT(removeChild(QGraphicsObject*)));
    if(updateFlag)
        updateData();
}

/*!
 * Set a name for the capture group
 *
 * \param   name    The new name of the capturing group
 */
void GroupingGraphicsItem::setCapturingName(QString name)
{
    capturingName = name;
    updateData();
}

/*!
 * True if this group should have no horizontal padding (for layout reasons)
 *
 * \param   outer   Determines whether the item should graphically have
 *                  horizontal spacing around it
 */
void GroupingGraphicsItem::setOuterGroup(bool outer)
{
    outerGroup = outer;
}

/*!
 * Determines whether this group is capturing (default) or non-capturing
 *
 * \param   capturing   Determines whether this is a capturing group or a
 *                      a non-capturing group
 */
void GroupingGraphicsItem::setCapturing(bool capturing)
{
    isCapturing = capturing;
    updateData();
}

/*!
 * Determines whether the data returned should have parentheses.  This is
 * used to provide a horizontal grouping of regexp items without filling
 * the visualisation-generated regexp with unnecessary parens.
 *
 * \param   brackets    Determines whether this grouping has parentheses
 *                      around it
 */
void GroupingGraphicsItem::setBrackets(bool brackets)
{
    hasBrackets = brackets;
}

/*!
 * Sets up the item for a drag/drop, and painting of valid drop-zones
 *
 * \param   event   The drag event captured
 */
void GroupingGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    dragEvent = true;
    update();
}

/*!
 * Updates state based on current co-ordinates of mouse within the item.
 * If the mouse is currently not within a valid drop zone the event will
 * be ignored providing an "invalid" cursor.
 *
 * \param   event   The drag event captured
 */
void GroupingGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if(validDropZone(event->pos()))
        event->acceptProposedAction();
    else
        event->ignore();
}

/*!
 * Returns the item to its previous state
 *
 * \param   event   The drag event captured
 */
void GroupingGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
    dragEvent = false;
    update();
}

/*!
 * Handles a drag drop event, checks if it has been dropped in
 * a valid drop zone, and if so checks to see if the visualisation
 * should be altered.
 *
 * \param   event   The drop event captured
 */
void GroupingGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    // If this isn't in a valid drop zone ignore the event
    if(!validDropZone(event->pos()))
        event->ignore();

    int offset;
    // Should be unnecessary due to the previous check, but
    // nonetheless make sure we have an offset to determine
    // where in the expression the drop has occured
    if((offset = dropZoneOffset(event->pos())) >= 0)
    {
        QGraphicsObject *item;

        // If this is a regexp element that has been dropped
        if(event->mimeData()->hasFormat("text/x-regexp"))
        {
            event->acceptProposedAction();
            // Get the regexp data, if there isn't any then leave
            QString fragment = event->mimeData()->data("text/x-regexp");
            if(fragment.isEmpty())
                return;

            int regexpoffset = 0;
            // Produce a regexp element from the regexp string
            item = GraphicalExpression::parseSection(fragment, regexpoffset, false, true);
            addChildItem(item, false);
        }
        else if(event->mimeData()->hasFormat("message/x-droptype"))
        {
            event->acceptProposedAction();
            qDebug() << "Drop Type: " << event->mimeData()->data("message/x-droptype");
            // handle each droptype with a specified dialog handler, then
            // use parseSection as above.
            return;
        }
        else
        {
            qDebug() << "Unexpected drop action";
            dragEvent = false;
            update();
            updateData();
            return;
        }

        // Normalise the offsets between outer groups and non-outer groups
        if(!outerGroup)
            ++offset;

        if(offset < childItems().size())
        {
            // Note: item is required to be intialised for this, which is
            // currently the only possible output (the other options return before
            // this), some logic to check for initialisation would be sensible
            item->stackBefore(childItems().at(offset));
        }

        // Now that there has been a drop the drag event must be over.
        // Update now redrawing the area without drop zones and including the newly
        // dropped fragment
        dragEvent = false;
        update();
        updateData();
    }
}

/*!
 * Removes a given child item
 *
 * \param   item    Pointer to the item to delete
 */
void GroupingGraphicsItem::removeChild(QGraphicsObject *item)
{
    // Check if we have ownership of this pointer
    if(isAncestorOf(item))
        delete item;

    // Update the data without this child
    updateData();

    // If the item is now empty, remove this item as well
    if(data(expressionData).toString() == "()" || data(expressionData).toString() == "")
        emit removeItem(this);
    else
        editCompleted();
}

/*!
 * Updates the item's data
 */
void GroupingGraphicsItem::updateData()
{
    QString expression;

    // Build a QStringList containing all of the child item's
    // regexp strings.
    QStringList elements;
    for(int i = 0; i < childItems().size(); ++i)
        elements << childItems().at(i)->data(expressionData).toString();

    // If this expression has parens this gets a bit more complex
    if(hasBrackets)
    {
        // Check for a capturing name
        //NOTE: This currently only handles (?P<name>...) format
        // the others should be added here
        if(!capturingName.isEmpty())
            expression = QString("(?P<") + capturingName + ">" + elements.join("") + ")";
        //NOTE: When there is a QSettings option reversing the meaning of capturing
        //      and non-capturing groups this will need to be changed to accomodate it.
        else if(isCapturing)
            expression = QString("(") + elements.join("") + ")";
        else
            expression = QString("(?:") + elements.join("") + ")";
    }
    else
        expression = elements.join("");

    // Set the data to what we've generated and emit a signal to indicate we have
    // finished updating
    setData(expressionData, QVariant(expression));
    emit dataChanged();
}


/*!
 * Slot which passes on an editComplete() signal
 */
void GroupingGraphicsItem::editCompleted()
{
    emit editComplete();
}

/*!
 * Returns true if the mouse position returned by QDragEvent
 * is in a valid drop-zone (an area imbetween regexp elements)
 *
 * \param   position    The position of the mouse
 * \return  True if an item can be dropped here, false otherwise
 */
bool GroupingGraphicsItem::validDropZone(QPointF position)
{
    for(int i = 0; i < dropZones.size(); ++i)
        if(dropZones.at(i).contains(position))
            return true;
    return false;
}

/*!
 * Returns an integer which represents which drop zone
 * (starting at 0) if any the mouse position is hovering over
 *
 * \param   position    The position of the mouse
 * \return  The integer offset determining which drop zone is
 *          being hovered over (starting at 0)
 */
int GroupingGraphicsItem::dropZoneOffset(QPointF position)
{
    for(int i = 0; i < dropZones.size(); ++i)
        if(dropZones.at(i).contains(position))
            return i;
    return -1;
}
