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

#include "charrangegraphicsitem.hpp"

CharRangeGraphicsItem::CharRangeGraphicsItem(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    CharRangeGraphicsItem("", parent);
}

CharRangeGraphicsItem::CharRangeGraphicsItem(QString initContents, QGraphicsItem *parent)
{
    initialised = false;
    contents = initContents;
    parseContents(contents);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    backgroundColour = QColor(240, 240, 255);
}

void CharRangeGraphicsItem::parseContents(QString string)
{
    if(initialised)
        delete contentsItem;
    else
        initialised = true;
    contentsItem = new QGraphicsTextItem;

    // Parse into sections:
    QStringList characters;
    QVector<QString> elements;

    // Parsing logic
    //TODO: Actually parse the string ;)
    characters << string;

    // Add characters to elements
    elements.push_front(characters.join(", "));

    QString htmlContents = QObject::tr("Any one of: ");
    for(int i = 0; i < elements.size(); ++i)
        htmlContents += QString("<br> - ") + elements.at(i);

    contentsItem->setHtml(htmlContents);
}

QRectF CharRangeGraphicsItem::boundingRect() const
{
    double width = contentsItem->boundingRect().width()+2*horizontalPadding;
    double height = contentsItem->boundingRect().height()+2*verticalPadding;
    return QRectF(0, 0, width, height);
}

void CharRangeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(220, 220, 235));

    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);

    contentsItem->setParentItem(this);
    contentsItem->setPos(horizontalPadding, verticalPadding);
}

void CharRangeGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(230, 230, 245);
    update();
}

void CharRangeGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(240, 240, 255);
    update();
}
