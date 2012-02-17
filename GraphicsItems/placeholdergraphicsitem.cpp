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
#include "placeholdergraphicsitem.hpp"

#include <QSettings>
#include <QObject>

PlaceholderGraphicsItem::PlaceholderGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , _metrics(QFont())
{
    _msg = QObject::tr("Drop an Item From the Left\nor Begin Typing Below");

    QSettings settings;
    QFont font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    font.setPointSize(font.pointSize()+1);
    _metrics = QFontMetrics(font);
}

QRectF PlaceholderGraphicsItem::boundingRect() const
{
    double horizontalPadding = 12.0;
    double verticalPadding   = 10.0;

    int lines = _msg.count("\n")+1;
    double textWidth = 0.0;
    QStringList words = _msg.split("\n");
    for(int i = 0; i < words.size(); ++i)
        if(_metrics.width(words.at(i)) > textWidth)
            textWidth = _metrics.width(words.at(i));
    // To prevent a rounding error causing a cut-off later, just add an extra pixel now
    textWidth++;

    return QRectF(0.5, 0.5, textWidth + 2*horizontalPadding, lines*_metrics.height() + 2*verticalPadding);
}

void PlaceholderGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QSettings settings;
    QFont font = settings.value("Visualisation/Font", QFont("sans-serif", 10)).value<QFont>();
    font.setPointSize(font.pointSize()+1);
    double horizontalPadding = 12.0;
    double verticalPadding   = 10.0;
    double cornerRadius = 5.0;

    painter->setFont(font);
    painter->setBrush(Qt::white);
    painter->setPen(Qt::black);

    QRectF drawRect = boundingRect();
    painter->drawRoundedRect(drawRect, cornerRadius, cornerRadius);

    painter->drawText(QRectF(
                          horizontalPadding,
                          verticalPadding,
                          drawRect.width() - 2*horizontalPadding,
                          drawRect.height() - 2*verticalPadding),
                      Qt::AlignCenter,
                      _msg);
}
