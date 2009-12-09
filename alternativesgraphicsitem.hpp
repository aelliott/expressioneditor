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

#ifndef ALTERNATIVESGRAPHICSITEM_HPP
#define ALTERNATIVESGRAPHICSITEM_HPP

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QDebug>

class AlternativesGraphicsItem : public QGraphicsObject
{
    Q_OBJECT;

public:
    AlternativesGraphicsItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addChildItem(QGraphicsObject *item);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void dataChanged();

public slots:
    void updateData();

private:
    static const int expressionData = 0;
    static const int horizontalPadding = 10;
    static const int verticalPadding = 8;
    QColor backgroundColour;
};

#endif // ALTERNATIVESGRAPHICSITEM_HPP
