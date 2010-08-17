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
/*!
 * \brief   This class represents a capture group within a regexp
 *
 * This class encapsulates a grouping graphics item (...) by default
 * this has no visual appearance of itself within the regexp
 */

#ifndef GROUPINGGRAPHICSITEM_HPP
#define GROUPINGGRAPHICSITEM_HPP

#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QMimeData>
#include "graphicalexpression.hpp"

class GroupingGraphicsItem : public QGraphicsObject
{
    Q_OBJECT;

public:
    //! Creates a new GroupingGraphicsItem
    GroupingGraphicsItem(bool brackets = false, bool outer = false, bool capturing = true, QGraphicsItem *parent = 0);

    //! Returns the geometry of the graphical object
    QRectF boundingRect() const;

    //! Paints the object on the canvas and lays out child items
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! Adds an item to be a child of the group
    void addChildItem(QGraphicsObject *item, bool updateFlag = true);

    //! Set a name for the capture group
    void setCapturingName(QString name);

    //! True if this group should have no horizontal padding (for layout reasons)
    void setOuterGroup(bool outer);

    //! Determines whether this group is capturing (default) or non-capturing
    void setCapturing(bool capturing);

    //! Determines whether the data returned should have parentheses
    void setBrackets(bool brackets);

    //! Sets up the item for a drag/drop, and painting of valid drop-zones
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

    //! Updates state based on current co-ordinates of mouse within the item
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

    //! Returns the item to its previous state
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);

    //! Handles a drop event
    void dropEvent(QGraphicsSceneDragDropEvent *event);

signals:
    //! Signal sent if any items have changed
    void dataChanged();

    //! Sends a signal to remove an item
    void removeItem(QGraphicsObject *item);

    //! Signal sent when it's safe to update the visualisation
    void editComplete();

public slots:
    //! Updates the item's data
    void updateData();

    //! Removes a given child item
    void removeChild(QGraphicsObject *item);

    //! Uh... I should remember this...
    void editCompleted();

private:
    bool validDropZone(QPointF position);
    int dropZoneOffset(QPointF position);
    static const int expressionData = 0;
    static const int itemSpacing = 8;
    bool outerGroup;
    bool hasBrackets;
    bool isCapturing;
    bool dragEvent;
    QString capturingName;
    QVector<QRectF> dropZones;
};

#endif // GROUPINGGRAPHICSITEM_HPP
