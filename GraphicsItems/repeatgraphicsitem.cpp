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

RepeatGraphicsItem::RepeatGraphicsItem(Token *token, int tokenPos, QGraphicsWidget *childWidget, QGraphicsItem *parent)
    : RegexGraphicsItem(token, tokenPos, parent)
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Repeat/HorizontalPadding", 8.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Repeat/VerticalPadding", 6.0).toDouble();

    parseToken(*token);

    _layout = new QGraphicsLinearLayout(Qt::Horizontal);
    _layout->setContentsMargins(horizontalPadding, 2*verticalPadding + _metrics.height(), horizontalPadding, verticalPadding);
    setLayout(_layout);
    _layout->setGeometry(boundingRect());

    if(childWidget == 0)
        _child = new QGraphicsWidget(this);
    else
        _child = childWidget;
    _layout->addStretch();
    _layout->addItem(_child);
    _layout->addStretch();
    _layout->setAlignment(_child, Qt::AlignTop | Qt::AlignHCenter);
}

void RepeatGraphicsItem::setWidget(QGraphicsWidget *widget)
{
    _layout->removeItem(_child);
    delete _child;
    _child = widget;
    for(int i = 0; i < _layout->count(); ++i)
        _layout->removeAt(0);
    _layout->addStretch();
    _layout->addItem(_child);
    _layout->addStretch();
    _layout->setAlignment(_child, Qt::AlignBottom | Qt::AlignHCenter);
}

QRectF RepeatGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Repeat/HorizontalPadding", 8.0).toDouble();
    QSizeF childrenRect = _layout->sizeHint(Qt::PreferredSize);

    return QRectF(0, 0, qMax(static_cast<double>(childrenRect.width()), 2*horizontalPadding + _metrics.width(_title)), childrenRect.height());
}

void RepeatGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    _font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    double horizontalPadding = settings.value("Visualisation/Repeat/HorizontalPadding", 8.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Repeat/VerticalPadding", 6.0).toDouble();
    double cornerRadius = settings.value("Visualisation/Repeat/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/Repeat/Color", QColor(255,255,225)).value<QColor>();

    painter->setFont(_font);
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

    painter->drawText(QRectF(
                          horizontalPadding,
                          verticalPadding,
                          drawRect.width() - 2*horizontalPadding,
                          _metrics.height()),
                      Qt::AlignVCenter | Qt::AlignLeft,
                      _title);
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
        _title = tr("Repeat 0 or 1 Time(s)");
        break;
    case T_REPEAT_ANY_NUMBER:
        _title = tr("Repeat 0+ Time(s)");
        break;
    case T_REPEAT_ONE_OR_MORE:
        _title = tr("Repeat 1+ Time(s)");
        break;
    case T_REPEAT_SPECIFIED:
        if(fixed.exactMatch(repeatToken.value()))
            _title = tr("Repeat ") + fixed.cap(1) + tr(" Time(s)");
        else if(lowerLimit.exactMatch(repeatToken.value()))
            _title = tr("Repeat ") + lowerLimit.cap(1) + tr("+ Time(s)");
        else if(upperLimit.exactMatch(repeatToken.value()))
            _title = tr("Repeat Up To ") + upperLimit.cap(1) + tr(" Time(s)");
        else if(limits.exactMatch(repeatToken.value()))
            _title = tr("Repeat Between ") + limits.cap(1) + tr(" and ") + limits.cap(2) + tr(" Time(s)");
        break;
    default:
        _title = tr("Unknown Repeat Syntax");
    }
}
