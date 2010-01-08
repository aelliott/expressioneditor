/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2010 Alex Elliott <alex@alex-elliott.co.uk>
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

#include "configgraphicsitem.hpp"

ConfigGraphicsItem::ConfigGraphicsItem(QString confFlag, QGraphicsItem *parent) : RegexGraphicsItem(parent)
{
    setFlag(confFlag);
    backgroundColour = QColor(230, 230, 230);
    updateData();
}

void ConfigGraphicsItem::setFlag(QString confFlag)
{
    flag = confFlag;
    if(flag == "i")
        displayText = "PCRE_CASELESS";
    else if(flag == "s")
        displayText = "PCRE_DOTALL";
    else if(flag == "x")
        displayText = "PCRE_EXTENDED";
    else if(flag == "X")
        displayText = "PCRE_EXTRA";
    else if(flag == "m")
        displayText = "PCRE_MULTILINE";
    else if(flag == "U")
        displayText = "PCRE_UNGREEDY";
    else
        displayText = "Unrecognised Flag";
}

QRectF ConfigGraphicsItem::boundingRect() const
{
    QFont boldFont = qApp->font();
    boldFont.setBold(true);
    QFontMetrics bold(boldFont);
    int height = 3*verticalPadding + 2*qApp->fontMetrics().height();
    int width  = 2*horizontalPadding + qMax(qApp->fontMetrics().width(tr("PCRE Flag")), bold.width(displayText));

    return QRectF(0, 0, width, height);
}

void ConfigGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(210, 210, 210));
    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    painter->drawText(horizontalPadding, 2.5*verticalPadding, tr("PCRE Flag"));
    QFont bold = painter->font();
    bold.setBold(true);
    painter->setFont(bold);
    painter->drawText(horizontalPadding, boundingRect().height()-(1.5*verticalPadding), displayText);
}

void ConfigGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(220, 220, 220);
    update();
}

void ConfigGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(230, 230, 230);
    update();
}

void ConfigGraphicsItem::updateData()
{
    QString data = QString("(?") + flag + ")";
    setData(expressionData, QVariant(data));
    emit dataChanged();
}
