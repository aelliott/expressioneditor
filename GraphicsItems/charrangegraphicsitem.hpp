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
 * \brief   This class represents a character range [a-zAC...etc] in a regexp.
 *
 * This class is used to produce the graphical representation of a character range -
 * parsing the contents to produce a list of all of the characters accepted by the
 * character range.
 */

#ifndef CHARRANGEGRAPHICSITEM_HPP
#define CHARRANGEGRAPHICSITEM_HPP

#include <QApplication>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QDebug>
#include "regexfactory.hpp"
#include "regexgraphicsitem.hpp"
#include "specialchargraphicsitem.hpp"

class CharRangeGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT;

public:
    //! Creates a new CharRangeGraphicsItem
    CharRangeGraphicsItem(QString initContents = QString(), int regexType = 0, QGraphicsItem *parent = 0);

    //! Cleans up dynamically allocated memory
    ~CharRangeGraphicsItem();

    /*!
     * \brief   Parses the contents of the character range to produce a neat list of
     *          the allowed characters.
     *
     * This method parses out any ranges (a-z, etc), special characters (\w etc),
     * POSIX character classes ([:alpha:] etc), and anything not treated as a literal
     * and places all left-over characters in a simple stringlist to produce a final
     * comma-delimited list of characters allowed in addition to the special chars.
     */
    void parseContents(QString string);

    //! Returns the geometry of the graphical object
    QRectF boundingRect() const;

    //! Paints the object on the canvas and lays out child items
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! Hover over listener, triggers the hover state (colour change)
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    //! Hover exit listener, triggers a return to the normal state
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    //! Mouse double-click listener.  Produces a GUI editing dialog for the regexp element.
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    //! Signal triggered when the value of this item has changed.
    void dataChanged();

public slots:
    /*!
     * \brief   Update the object's internal data, trigger dataChanged on any changes
     *          in state.
     */
    void updateData();

private:
    static const int horizontalPadding = 10;
    static const int verticalPadding = 6;
    QColor backgroundColour;
    QString contents;
    int regexFormat;
    bool initialised;
    QGraphicsTextItem *contentsItem;
};

#endif // CHARRANGEGRAPHICSITEM_HPP
