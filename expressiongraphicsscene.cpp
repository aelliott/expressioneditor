/*!
 * \file
 *
 * Copyright (c) 2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "expressiongraphicsscene.hpp"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QDebug>

ExpressionGraphicsScene::ExpressionGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void ExpressionGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    while(_dropZoneLabels.size() > 0)
    {
        removeItem(_dropZoneLabels.at(0));
        _dropZoneLabels.removeAt(0);
    }

    QList<QGraphicsItem *> itemList = items();
    for(int i = 0; i < itemList.size()-1; ++i)
    {
        QGraphicsItem *item = itemList.at(i);
        QPointF itemPos = item->scenePos();
        QRectF bounds = item->boundingRect();

        qDebug() << itemPos;
        qDebug() << bounds;

        QPointF topLeft = itemPos;
        topLeft.setY(itemPos.y()-8.0);

        QPointF bottomRight = itemPos;
        bottomRight.setX(itemPos.x()+bounds.width());

        QGraphicsRectItem *dropZoneLabel = new QGraphicsRectItem(0, 0, bounds.width(), 8.0);
        dropZoneLabel->setPos(topLeft);
        addItem(dropZoneLabel);
        _dropZoneLabels.append(dropZoneLabel);

        qDebug() << dropZoneLabel->boundingRect();
    }

    event->accept();
}

void ExpressionGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void ExpressionGraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    while(_dropZoneLabels.size() > 0)
    {
        removeItem(_dropZoneLabels.at(0));
        _dropZoneLabels.removeAt(0);
    }

    event->accept();
}

void ExpressionGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    while(_dropZoneLabels.size() > 0)
    {
        removeItem(_dropZoneLabels.at(0));
        _dropZoneLabels.removeAt(0);
    }

    event->accept();

    const QMimeData *mime = event->mimeData();
    int startPos = QVariant(mime->data("text/x-regexp-start-pos")).toInt();
    int endPos = QVariant(mime->data("text/x-regexp-end-pos")).toInt();

    //qDebug() << "Drop Accepted from: " << startPos << " to " << endPos;

    // Must now decide how to handle this drop
}
