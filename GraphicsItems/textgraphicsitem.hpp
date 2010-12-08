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
 * \brief   This class represents a plain text segment within a regexp.
 *
 * This class is used to represent a plain literal string within the regular
 * expression visualisation.
 */

#ifndef TEXTGRAPHICSITEM_HPP
#define TEXTGRAPHICSITEM_HPP

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include "regexgraphicsitem.hpp"
#include "texteditdialog.hpp"

class TextGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT;

public:
    TextGraphicsItem(QString text = QString(), QGraphicsItem * parent = 0);
    void setText(QString text);
    void appendText(QString append);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    void updateData();
    QString textString;
    QString displayText;
    QColor backgroundColour;
    static const int horizontalPadding = 10;
    static const int verticalPadding = 6;
};

#endif // TEXTGRAPHICSITEM_HPP
