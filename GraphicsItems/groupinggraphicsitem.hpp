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
    GroupingGraphicsItem(bool brackets = false, bool outer = false, bool capturing = true, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addChildItem(QGraphicsObject *item, bool updateFlag = true);
    void setCapturingName(QString name);
    void setOuterGroup(bool outer);
    void setCapturing(bool capturing);
    void setBrackets(bool brackets);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

signals:
    //! Signal sent if any items have changed
    void dataChanged();

    //! Sends a signal to remove an item
    void removeItem(QGraphicsObject *item);

    //! Signal sent when it's safe to update the visualisation
    void editComplete();

public slots:
    void updateData();
    void removeChild(QGraphicsObject *item);
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
