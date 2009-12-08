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

#ifndef CHARRANGEGRAPHICSITEM_HPP
#define CHARRANGEGRAPHICSITEM_HPP

#include <QApplication>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsTextItem>
#include "specialchargraphicsitem.hpp"

class CharRangeGraphicsItem : public QGraphicsItem
{
public:
    CharRangeGraphicsItem(QGraphicsItem *parent = 0);
    CharRangeGraphicsItem(QString initContents, QGraphicsItem *parent = 0);
    void parseContents(QString string);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    void updateData();
    static const int expressionData = 0;
    static const int horizontalPadding = 10;
    static const int verticalPadding = 6;
    QColor backgroundColour;
    QString contents;
    bool initialised;
    QGraphicsTextItem *contentsItem;
};

#endif // CHARRANGEGRAPHICSITEM_HPP
