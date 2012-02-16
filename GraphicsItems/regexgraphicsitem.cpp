/*!
 * \file
 *
 * Copyright (c) 2012 Alex Elliott <alex@alex-elliott.co.uk>
 *
 * \section LICENSE
 * This file is part of Expression editor
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
#include "regexgraphicsitem.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QFont>

RegexGraphicsItem::RegexGraphicsItem(Token *token, int tokenPos, QGraphicsItem *parent)
    : QGraphicsWidget(parent)
    , _token(token)
    , _tokenPos(tokenPos)
    , _endPos(tokenPos)
    , _metrics(QFont())
{
    QSettings settings;
    _font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    _metrics = QFontMetrics(_font);

    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
}

Token *RegexGraphicsItem::token() const
{
    return _token;
}

int RegexGraphicsItem::tokenPos() const
{
    return _tokenPos;
}

int RegexGraphicsItem::endPos() const
{
    return _endPos;
}

void RegexGraphicsItem::setEndPos(int endPos)
{
    _endPos = endPos;
}

void RegexGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
}

void RegexGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Check if we have moved the mouse enough to start a drag event
    if (QLineF(
                event->screenPos(),
                event->buttonDownScreenPos(Qt::LeftButton)
                ).length() < QApplication::startDragDistance())
        return;

    // Create a new drag event with some mime data
    QDrag *drag = new QDrag(event->widget());
    QMimeData *mime = new QMimeData;

    // Attach the necessary information to handle the event, the position of
    // this element in the token sequence, and the end of this token slice (if
    // different)
    mime->setData("text/x-regexp-start-pos", QVariant(tokenPos()).toByteArray());
    mime->setData("text/x-regexp-end-pos", QVariant(endPos()).toByteArray());
    drag->setMimeData(mime);

    // Create a scaled down image of the regexp item being dragged and use
    // that as the pixmap image to drag around (so it's clear what element
    // is attached to the drag event)
    QPixmap image(this->boundingRect().width()*0.75, this->boundingRect().height()*0.75);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene()->render(&painter, QRectF(), this->sceneBoundingRect());
    painter.end();

    // Attach the scaled down image to the drag event
    drag->setPixmap(image);

    // Execute the drag event
    drag->exec();
}

void RegexGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
