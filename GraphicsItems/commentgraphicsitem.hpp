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
 * \brief   This class represents a comment block (?#...) in a regexp.
 *
 * This class is used to produce the graphical represntation of a comment block
 * within the regexp visualisation.
 */

#ifndef COMMENTGRAPHICSITEM_HPP
#define COMMENTGRAPHICSITEM_HPP

#include <QApplication>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include "regexgraphicsitem.hpp"

class CommentGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT;

public:
    explicit CommentGraphicsItem(QString comment = QString(), QGraphicsItem *parent = 0);
    void setComment(QString comment);
    void appendText(QString append);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    //! Signal triggered when the value of this item has changed.
    void dataChanged();

public slots:
    void updateData();

private:
    QString commentString;
    QColor backgroundColour;
    static const int horizontalPadding = 10;
    static const int verticalPadding = 6;
};

#endif // COMMENTGRAPHICSITEM_HPP
