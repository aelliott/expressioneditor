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
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>

class RepeatGraphicsItem : public QGraphicsItem
{
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
    void setChildItem(QGraphicsItem *item);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

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
