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

#ifndef REPEATGRAPHICSITEM_HPP
#define REPEATGRAPHICSITEM_HPP

#include <QApplication>
#include "regexgraphicsitem.hpp"
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

class RepeatGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT;

public:
    enum Type
    {
        ZeroOrOne,
        ZeroOrMore,
        OneOrMore,
        ExactValue,
        SpecifiedRange
    };

    RepeatGraphicsItem(RepeatGraphicsItem::Type type, int minimum = -1, int maximum = -1, QGraphicsItem *parent = 0);
    void setRepeat(RepeatGraphicsItem::Type type, int minimum = -1, int maximum = -1);
    void setChildItem(QGraphicsObject *item);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void dataChanged();

public slots:
    void updateData();
    void removeChild(QGraphicsObject *item);

private:
    static const int horizontalPadding = 10;
    static const int verticalPadding = 8;
    QColor backgroundColour;
    QString title;
    RepeatGraphicsItem::Type setType;
    int setMinimum;
    int setMaximum;
};

#endif // REPEATGRAPHICSITEM_HPP
