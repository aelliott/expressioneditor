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

#include "commentgraphicsitem.hpp"

/*!
 * Produces a new CommentGraphicsItem
 *
 * \param   comment The regexp comment string to represent
 * \param   parent  The item's parent
 */
CommentGraphicsItem::CommentGraphicsItem(QString comment, QGraphicsItem *parent) : RegexGraphicsItem(parent), commentString(comment)
{
    backgroundColour = QColor(230, 230, 230);
    updateData();
}

/*!
 * Setter method, sets the comment string
 *
 * \param   comment Comment string to set
 */
void CommentGraphicsItem::setComment(QString comment)
{
    commentString = comment;
    updateData();
}

/*!
 * Convenience method, appends a string on to the end of
 * the existing comment string
 *
 * \param   append  String to append onto the existing
 *                  comment string.
 */
void CommentGraphicsItem::appendText(QString append)
{
    commentString += append;
    updateData();
}

/*!
 * Returns the geometry of the graphical object
 *
 * \return  Returns a QRectF containing the object's geometry
 */
QRectF CommentGraphicsItem::boundingRect() const
{
    int width = 2*horizontalPadding + qApp->fontMetrics().width(commentString);
    int height = 2*verticalPadding + qApp->fontMetrics().height();
    return QRectF(0, 0, width, height);
}

/*!
 * Paints the object on the canvas and lays out child items
 *
 * \param   painter The QPainter used to draw the graphics item
 * \param   option  Unused
 * \param   widget  Unused
 */
void CommentGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(210, 210, 210));
    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    painter->drawText(horizontalPadding, boundingRect().height()-(1.5*verticalPadding), commentString);
}

/*!
 * Hover over listener, triggers the hover state (colour change)
 *
 * \param   event   The hover event that has been triggered
 */
void CommentGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(220, 220, 220);
    update();
}

/*!
 * Hover exit listener, triggers a return to the normal state
 *
 * \param   event   The hover event that has been triggered
 */
void CommentGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(230, 230, 230);
    update();
}

/*!
 * Update the object's internal data, trigger dataChanged on any changes
 * in state.
 */
void CommentGraphicsItem::updateData()
{
    QString text = QString("(?#") + commentString + ")";
    setData(expressionData, QVariant(text));
    emit dataChanged();
}
