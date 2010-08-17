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

#ifndef SPECIALCHARGRAPHICSITEM_HPP
#define SPECIALCHARGRAPHICSITEM_HPP

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "regexgraphicsitem.hpp"
#include "specialchareditdialog.hpp"

class SpecialCharGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT;

public:
    SpecialCharGraphicsItem(QGraphicsItem *parent = 0);
    SpecialCharGraphicsItem(QString text, QGraphicsItem *parent = 0);
    void setContents(QString text);
    static QString parseString(QString text);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void dataChanged();

private:
    void updateData();
    QString plainContents;
    QGraphicsTextItem *contents;
    QColor backgroundColour;
    static const int horizontalPadding = 10;
    static const int verticalPadding = 6;
};

#endif // SPECIALCHARGRAPHICSITEM_HPP
