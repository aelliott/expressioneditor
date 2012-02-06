/*!
 * \file
 *
 * Copyright (c) 2009,2010,2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "anchorgraphicsitem.hpp"

AnchorGraphicsItem::AnchorGraphicsItem(RegexpToken token, QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    _text = new QGraphicsTextItem(this);

    switch(token)
    {
    case T_STARTING_POSITION:
        _text->setHtml("<center>Starting<br>Position");
        break;
    case T_ENDING_POSITION:
        _text->setHtml("<center>Ending<br>Position");
        break;
    }

    _text->setTextWidth(_text->boundingRect().width());
}

QRectF AnchorGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Anchor/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Anchor/VerticalPadding", 5.0).toDouble();

    QRectF textRect = _text->boundingRect();

    return QRectF(0, 0, textRect.width() + 2*horizontalPadding, textRect.height() + 2*verticalPadding);
}

void AnchorGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Anchor/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Anchor/VerticalPadding", 5.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/Anchor/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/Anchor/Color", QColor(220,255,255)).value<QColor>();

    painter->setBrush(bgColor);
    painter->setPen(Qt::black);

    QRectF drawRect = boundingRect();
    // Align the rect to the pixel grid
    if(qRound(scenePos().x()) == scenePos().x())
    {
        drawRect.setX(0.5);
        drawRect.setWidth(drawRect.width()-.5);
    }
    if(qRound(scenePos().y()) == scenePos().y())
    {
        drawRect.setHeight(drawRect.height()-.5);
        drawRect.setY(0.5);
    }
    painter->drawRoundedRect(drawRect, cornerRadius, cornerRadius);

    _text->setPos(horizontalPadding, verticalPadding);
}

QSizeF AnchorGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
