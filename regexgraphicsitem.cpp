/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009 Alex Elliott <alex@alex-elliott.co.uk>
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

#include "regexgraphicsitem.hpp"

RegexGraphicsItem::RegexGraphicsItem(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    setCursor(Qt::OpenHandCursor);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

void RegexGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void RegexGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(this->data(expressionData).toString());
    drag->setMimeData(mimeData);

    QPixmap image(this->boundingRect().width()*0.75, this->boundingRect().height()*0.75);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene()->render(&painter, QRectF(), this->sceneBoundingRect());
    painter.end();

    drag->setPixmap(image);

    Qt::DropAction dropAction = drag->exec();

    if(dropAction == Qt::MoveAction)
        emit removeItem(this);
}

/**
 * Public slots
 */
void RegexGraphicsItem::removeChild(QGraphicsObject *item)
{
    if(isAncestorOf(item))
        delete item;
}
