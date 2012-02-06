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
#include "groupinggraphicsitem.hpp"

GroupingGraphicsItem::GroupingGraphicsItem(Token token, bool defaultCapturing, QGraphicsItem *parent)
    : QGraphicsWidget(parent)
    , _token(token)
    , _defaultCapturing(defaultCapturing)
{
    if(token.type() == T_REVERSED_CAPTURING_GROUPING_OPEN)
        _capturing = !_defaultCapturing;
    else
        _capturing = _defaultCapturing;

    if(token.type() == T_NAMED_GROUPING_OPEN)
    {
        QRegExp rx("<([^>]+)>|'([^']+)'");
        if(rx.indexIn(token.value()) != -1)
        {
            _name = rx.cap(1);
            _title = new QGraphicsTextItem(QString("Grouping \"") + _name + "\"", this);
        }
    }

    _layout = new QGraphicsLinearLayout(Qt::Horizontal);

    setLinearLayout(_layout);
}

void GroupingGraphicsItem::addWidget(QGraphicsWidget *widget)
{
    _layout->addItem(widget);
}

QGraphicsLinearLayout *GroupingGraphicsItem::linearLayout() const
{
    return _layout;
}

void GroupingGraphicsItem::setLinearLayout(QGraphicsLinearLayout *layout)
{
    QSettings settings;
    int displayOptions = settings.value("Visualisation/Grouping/DisplayOptions", (DisplayCapturing | DisplayNamed)).toInt();

    double horizontalPadding = 0.0;
    double verticalPadding   = 0.0;
    if((_capturing && (displayOptions & DisplayCapturing))
            || (!_capturing && (displayOptions & DisplayNonCapturing))
            || (!_name.isEmpty() && (displayOptions & DisplayNamed))
            )
    {
        horizontalPadding = settings.value("Visualisation/Grouping/HorizontalPadding", 8.0).toDouble();
        verticalPadding   = settings.value("Visualisation/Grouping/VerticalPadding", 6.0).toDouble();
    }

    if(!_name.isEmpty() && (displayOptions & DisplayNamed))
        _layout->setContentsMargins(horizontalPadding, 2*verticalPadding + _title->boundingRect().height(), horizontalPadding, verticalPadding);
    else
        _layout->setContentsMargins(horizontalPadding, verticalPadding, horizontalPadding, verticalPadding);

    _layout = layout;
    setLayout(layout);
}

QRectF GroupingGraphicsItem::boundingRect() const
{
    QSettings settings;
    int displayOptions = settings.value("Visualisation/Grouping/DisplayOptions", (DisplayCapturing | DisplayNamed)).toInt();

    double horizontalPadding = 0.0;
    double verticalPadding   = 0.0;
    if((_capturing && (displayOptions & DisplayCapturing))
            || (!_capturing && (displayOptions & DisplayNonCapturing))
            || (!_name.isEmpty() && (displayOptions & DisplayNamed))
            )
    {
        horizontalPadding = settings.value("Visualisation/Grouping/HorizontalPadding", 8.0).toDouble();
        verticalPadding   = settings.value("Visualisation/Grouping/VerticalPadding", 6.0).toDouble();
    }
    if(!_name.isEmpty() && (displayOptions & DisplayNamed))
        _layout->setContentsMargins(horizontalPadding, 2*verticalPadding + _title->boundingRect().height(), horizontalPadding, verticalPadding);
    else
        _layout->setContentsMargins(horizontalPadding, verticalPadding, horizontalPadding, verticalPadding);
    QSizeF childrenRect = _layout->sizeHint(Qt::PreferredSize);

    if(!_name.isEmpty() && (displayOptions & DisplayNamed))
        return QRectF(0,
                      0,
                      qMax(childrenRect.width(), _title->boundingRect().width() + 2*horizontalPadding),
                      qMax(childrenRect.height(), _title->boundingRect().height() + 2*verticalPadding));
    else
        return QRectF(0, 0, childrenRect.width(), childrenRect.height());
}

void GroupingGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    int displayOptions = settings.value("Visualisation/Grouping/DisplayOptions", (DisplayCapturing | DisplayNamed)).toInt();
    double horizontalPadding = settings.value("Visualisation/Grouping/HorizontalPadding", 8.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Grouping/VerticalPadding", 6.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/Grouping/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/Grouping/Color", QColor(245,245,245)).value<QColor>();

    painter->setBrush(bgColor);
    painter->setPen(Qt::black);

    if((_capturing && (displayOptions & DisplayCapturing))
            || (!_capturing && (displayOptions & DisplayNonCapturing))
            || (!_name.isEmpty() && (displayOptions & DisplayCapturing))
            )
    {
        if(!_name.isEmpty())
            _title->setPos(horizontalPadding, verticalPadding);

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
}

QSizeF GroupingGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
