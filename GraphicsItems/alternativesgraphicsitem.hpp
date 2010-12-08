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
 * \brief   This class represents an alternation "|" in a regexp.
 *
 * This class is used to produce the graphical represntation of an alternation
 * by vertically stacking each possible alternation path.
 */

#ifndef ALTERNATIVESGRAPHICSITEM_HPP
#define ALTERNATIVESGRAPHICSITEM_HPP

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QDebug>
#include "regexgraphicsitem.hpp"

class AlternativesGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT;

public:
    AlternativesGraphicsItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addChildItem(QGraphicsObject *item);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

public slots:
    void updateData();

private:
    static const int horizontalPadding = 10;
    static const int verticalPadding = 8;
    QColor backgroundColour;
};

#endif // ALTERNATIVESGRAPHICSITEM_HPP
