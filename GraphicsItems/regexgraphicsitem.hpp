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
 * \brief   The base class for graphical regexp visualisation items.
 *
 * This class is a common base class for all elements of the graphical
 * visualisation, providing all of the common functionality required.
 */
#ifndef REGEXGRAPHICSITEM_HPP
#define REGEXGRAPHICSITEM_HPP

#include <QApplication>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsScene>

class RegexGraphicsItem : public QGraphicsObject
{
    Q_OBJECT;

public:
    explicit RegexGraphicsItem(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    //! Sends a signal to remove an item
    void removeItem(QGraphicsObject *item);

    //! Signal sent if any items have changed
    void editComplete();

    //! Signal sent if the data stored inside has changed
    void dataChanged();

public slots:
    virtual void removeChild(QGraphicsObject *item);
    void editCompleted();

protected:
    virtual void updateData();
    /*!
     * The offset at which expression data should be stored via setData() and
     * data()
     */
    static const int expressionData = 0;

    /*!
     * The point at which the mouse was first clicked inside the graphics item,
     * used to determine if the mouse has moved far enough to start a drag
     */
    QPointF dragStartPosition;
};

#endif // REGEXGRAPHICSITEM_HPP
