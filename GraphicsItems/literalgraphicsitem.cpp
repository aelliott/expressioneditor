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
#include "literalgraphicsitem.hpp"
#include <QApplication>
#include <QFontMetrics>

LiteralGraphicsItem::LiteralGraphicsItem(Token *token, int tokenPos, QGraphicsItem *parent)
    : RegexGraphicsItem(token, tokenPos, parent)
{
    QString text = token->value();
    _literal = text;
    // Do not display escaped characters in the literal graphics item
    for(int i = 0; i < text.length(); ++i)
    {
        if(QString(text.at(i)) == QString("\\"))
            text.remove(i, 1);
    }

    _text = text;
}

QRectF LiteralGraphicsItem::boundingRect() const
{
    QSettings settings;
    double horizontalPadding = settings.value("Visualisation/Literal/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Literal/VerticalPadding", 5.0).toDouble();

    return QRectF(0, 0, _metrics.width(_text) + 2*horizontalPadding + 1, _metrics.height() + 2*verticalPadding);
}

void LiteralGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    _font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    double horizontalPadding = settings.value("Visualisation/Literal/HorizontalPadding", 6.0).toDouble();
    double verticalPadding   = settings.value("Visualisation/Literal/VerticalPadding", 5.0).toDouble();
    double cornerRadius   = settings.value("Visualisation/Literal/CornerRadius", 5.0).toDouble();
    QColor bgColor = settings.value("Visualisation/Literal/Color", QColor(220,255,220)).value<QColor>();

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
                          drawRect.height() - 2*verticalPadding),
                      Qt::AlignCenter,
                      _text);
}

QSizeF LiteralGraphicsItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which)
    Q_UNUSED(constraint)

    QRectF rect = boundingRect();
    return QSizeF(rect.width(), rect.height());
}
