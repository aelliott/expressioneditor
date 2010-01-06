/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2010 Alex Elliott <alex@alex-elliott.co.uk>
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

#include "commentgraphicsitem.hpp"

CommentGraphicsItem::CommentGraphicsItem(QString comment, QGraphicsItem *parent) : RegexGraphicsItem(parent), commentString(comment)
{
    backgroundColour = QColor(230, 230, 230);
    updateData();
}

void CommentGraphicsItem::setComment(QString comment)
{
    commentString = comment;
    updateData();
}

void CommentGraphicsItem::appendText(QString append)
{
    commentString += append;
    updateData();
}

QRectF CommentGraphicsItem::boundingRect() const
{
    int width = 2*horizontalPadding + qApp->fontMetrics().width(commentString);
    int height = 2*verticalPadding + qApp->fontMetrics().height();
    return QRectF(0, 0, width, height);
}

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

void CommentGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(220, 220, 220);
    update();
}

void CommentGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(230, 230, 230);
    update();
}

/**
 * Private methods
 */
void CommentGraphicsItem::updateData()
{
    QString text = QString("(?#") + commentString + ")";
    setData(expressionData, QVariant(text));
    emit dataChanged();
}
