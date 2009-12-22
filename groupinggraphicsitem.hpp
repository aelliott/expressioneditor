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
    GroupingGraphicsItem(bool capturing = false, bool outer = false, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addChildItem(QGraphicsObject *item);
    void setCapturingName(QString name);
    void setOuterGroup(bool outer);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

signals:
    void dataChanged();

public slots:
    void updateData();

private:
    bool validDropZone(QPointF position);
    static const int expressionData = 0;
    static const int itemSpacing = 8;
    bool outerGroup;
    bool isCapturing;
    bool dragEvent;
    QString capturingName;
    QVector<QRectF> dropZones;
};

#endif // GROUPINGGRAPHICSITEM_HPP
