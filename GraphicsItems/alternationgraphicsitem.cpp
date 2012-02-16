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
#include "alternationgraphicsitem.hpp"

AlternationGraphicsItem::AlternationGraphicsItem(QGraphicsLinearLayout *initialLayout, Token *token, int tokenPos, QGraphicsItem *parent)
    : RegexGraphicsItem(token, tokenPos, parent)
{
    QSettings settings;
    double itemSpacing       = settings.value("Visualisation/VerticalSpacing", 12.0).toDouble();
    double horizontalPadding = settings.value("Visualisation/Alternation/HorizontalPadding", 8.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Alternation/VerticalPadding", 6.0).toDouble();

    _title = new QGraphicsTextItem("Alternation", this);
    _title->setPos(horizontalPadding, verticalPadding);

    _mainLayout = new QGraphicsLinearLayout(Qt::Vertical);
    _mainLayout->setContentsMargins(horizontalPadding, 2*verticalPadding + _title->boundingRect().height(), horizontalPadding, verticalPadding);
    _mainLayout->setSpacing(itemSpacing);
    setLayout(_mainLayout);

    _mainLayout->addItem(initialLayout);

    _mainLayout->setAlignment(initialLayout, Qt::AlignTop | Qt::AlignHCenter);

    newBranch();
}

void AlternationGraphicsItem::newBranch()
{
    _currentLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    _mainLayout->addItem(_currentLayout);
    _mainLayout->setAlignment(_currentLayout, Qt::AlignTop | Qt::AlignHCenter);
}

QGraphicsLinearLayout *AlternationGraphicsItem::linearLayout() const
{
    return _currentLayout;
}

QRectF AlternationGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Alternation/HorizontalPadding", 8.0).toDouble();
    QSizeF childrenRect = _mainLayout->sizeHint(Qt::PreferredSize);

    return QRectF(0, 0, qMax(childrenRect.width(), 2*horizontalPadding + _title->boundingRect().width()), childrenRect.height());
}

void AlternationGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    double itemSpacing       = settings.value("Visualisation/VerticalSpacing", 12.0).toDouble();
    double horizontalPadding = settings.value("Visualisation/Alternation/HorizontalPadding", 8.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Alternation/VerticalPadding", 6.0).toDouble();
    double cornerRadius      = settings.value("Visualisation/Alternation/CornerRadius", 5.0).toDouble();
    QColor bgColor           = settings.value("Visualisation/Alternation/Color", QColor(255,255,225)).value<QColor>();

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

    double offset = 2*verticalPadding + _title->boundingRect().height();
    for(int i = 0; (i+1) < _mainLayout->count(); ++i)
    {
        if(i > 0)
            offset += itemSpacing/2;
        QGraphicsLayoutItem *item = _mainLayout->itemAt(i);
        offset += item->contentsRect().height() + itemSpacing/2;

        if(qRound(offset) == offset)
            offset += 0.5;

        if(item->contentsRect().height() == 0)
            continue;

        painter->drawLine(QPointF(horizontalPadding, offset),
                          QPointF(boundingRect().width()-horizontalPadding, offset));
    }
}

QSizeF AlternationGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
