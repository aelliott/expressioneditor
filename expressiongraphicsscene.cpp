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
#include <QSettings>
#include <QDebug>

ExpressionGraphicsScene::ExpressionGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void ExpressionGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QSettings settings;
    double itemSpacing = settings.value("Visualisation/HorizontalSpacing", 8.0).toDouble();

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

        QColor dropZoneColour(210, 210, 255, 80);
        QBrush brush(dropZoneColour);
        QPen pen(dropZoneColour);

        QPointF topLeft = itemPos;
        topLeft.setY(itemPos.y()-itemSpacing);

        QGraphicsRectItem *topLabel = new QGraphicsRectItem(0, 0, bounds.width(), itemSpacing);
        topLabel->setPen(pen);
        topLabel->setBrush(brush);
        topLabel->setPos(topLeft);
        addItem(topLabel);
        _dropZoneLabels.append(topLabel);

        topLeft = itemPos;
        topLeft.setX(itemPos.x()-itemSpacing);

        QGraphicsRectItem *leftLabel = new QGraphicsRectItem(0, 0, itemSpacing, bounds.height());
        leftLabel->setPen(pen);
        leftLabel->setBrush(brush);
        leftLabel->setPos(topLeft);
        addItem(leftLabel);
        _dropZoneLabels.append(leftLabel);

        topLeft = itemPos;
        topLeft.setY(itemPos.y()+bounds.height());

        QGraphicsRectItem *bottomLabel = new QGraphicsRectItem(0, 0, bounds.width(), itemSpacing);
        bottomLabel->setPen(pen);
        bottomLabel->setBrush(brush);
        bottomLabel->setPos(topLeft);
        addItem(bottomLabel);
        _dropZoneLabels.append(bottomLabel);

        topLeft = itemPos;
        topLeft.setX(itemPos.x()+bounds.width());

        QGraphicsRectItem *rightLabel = new QGraphicsRectItem(0, 0, itemSpacing, bounds.height());
        rightLabel->setPen(pen);
        rightLabel->setBrush(brush);
        rightLabel->setPos(topLeft);
        addItem(rightLabel);
        _dropZoneLabels.append(rightLabel);
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
