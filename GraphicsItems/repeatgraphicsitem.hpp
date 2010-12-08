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
 * \brief   This class represents a repeated item within a regexp.
 *
 * This class is used to produce the graphical representation of a repeat
 * within a regular expression.  For example (foo)+ is (foo) repeated
 * "one or more" times.
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
    /*!
     * This enumerates the different types of repeats
     * allowed by the RepeatGraphicsItem
     */
    enum Type
    {
        ZeroOrOne, //!< Zero or one repeats - ?
        ZeroOrMore, //!< Zero or more repeats - *
        OneOrMore, //!< One or more repeats - +
        ExactValue, //!< An exact value of repeats - {n}
        SpecifiedRange //!< A specified range of repeats - {n,m}
    };

    RepeatGraphicsItem(RepeatGraphicsItem::Type type, int minimum = -1, int maximum = -1, QGraphicsItem *parent = 0);
    void setRepeat(RepeatGraphicsItem::Type type, int minimum = -1, int maximum = -1);
    void setGreedy(bool newGreedy);
    void setChildItem(QGraphicsObject *item);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void updateData();
    void removeChild(QGraphicsObject *item);

private:
    static const int horizontalPadding = 10;
    static const int verticalPadding = 8;
    QColor backgroundColour;
    QString title;
    RepeatGraphicsItem::Type setType;
    bool greedy;
    int setMinimum;
    int setMaximum;
};

#endif // REPEATGRAPHICSITEM_HPP
