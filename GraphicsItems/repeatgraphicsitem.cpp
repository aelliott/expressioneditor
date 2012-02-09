/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "repeatgraphicsitem.hpp"

RepeatGraphicsItem::RepeatGraphicsItem(Token repeatToken, QGraphicsWidget *childWidget, QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Repeat/HorizontalPadding", 8.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Repeat/VerticalPadding", 6.0).toDouble();

    _title = new QGraphicsTextItem("Repeat", this);
    _title->setPos(horizontalPadding, verticalPadding);
    parseToken(repeatToken);

    _layout = new QGraphicsLinearLayout(Qt::Vertical);
    _layout->setContentsMargins(horizontalPadding, 2*verticalPadding + _title->boundingRect().height(), horizontalPadding, verticalPadding);
    setLayout(_layout);
    _layout->setGeometry(boundingRect());

    if(childWidget == 0)
        _child = new QGraphicsWidget(this);
    else
        _child = childWidget;
    _layout->addItem(_child);
    _layout->setAlignment(_child, Qt::AlignTop | Qt::AlignHCenter);
}

void RepeatGraphicsItem::setWidget(QGraphicsWidget *widget)
{
    _layout->removeItem(_child);
    delete _child;
    _child = widget;
    _layout->addItem(_child);
    _layout->setAlignment(_child, Qt::AlignBottom | Qt::AlignHCenter);
}

QRectF RepeatGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Repeat/HorizontalPadding", 8.0).toDouble();
    QSizeF childrenRect = _layout->sizeHint(Qt::PreferredSize);

    return QRectF(0, 0, qMax(static_cast<double>(childrenRect.width()), 2*horizontalPadding + _title->boundingRect().width()), childrenRect.height());
}

void RepeatGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    double cornerRadius   = settings.value("Visualisation/Repeat/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/Repeat/Color", QColor(255,255,225)).value<QColor>();

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
}

QSizeF RepeatGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}

void RepeatGraphicsItem::parseToken(Token repeatToken)
{
    QRegExp fixed("\\{(\\d+)\\}");
    QRegExp lowerLimit("\\{(\\d+),\\}");
    QRegExp upperLimit("\\{,(\\d+)\\}");
    QRegExp limits("\\{(\\d+),(\\d+)\\}");

    switch(repeatToken.type())
    {
    case T_REPEAT_ZERO_OR_ONE:
        _title->setHtml("Repeat 0 or 1 Time(s)");
        break;
    case T_REPEAT_ANY_NUMBER:
        _title->setHtml("Repeat 0+ Time(s)");
        break;
    case T_REPEAT_ONE_OR_MORE:
        _title->setHtml("Repeat 1+ Time(s)");
        break;
    case T_REPEAT_SPECIFIED:
        if(fixed.exactMatch(repeatToken.value()))
            _title->setHtml(QString("Repeat ") + fixed.cap(1) + " Time(s)");
        else if(lowerLimit.exactMatch(repeatToken.value()))
            _title->setHtml(QString("Repeat ") + lowerLimit.cap(1) + "+ Time(s)");
        else if(upperLimit.exactMatch(repeatToken.value()))
            _title->setHtml(QString("Repeat Up To ") + upperLimit.cap(1) + " Time(s)");
        else if(limits.exactMatch(repeatToken.value()))
            _title->setHtml(QString("Repeat Between ") + limits.cap(1) + " and " + limits.cap(2) + " Time(s)");
        break;
    default:
        _title->setHtml("Unknown Repeat Syntax");
    }
}
