/*!
 * \file
 * \author Alex Elliott <alex@alex-elliott.co.uk>
 * \version 0.1pre
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009,2010 Alex Elliott <alex@alex-elliott.co.uk>
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

#include "specialchargraphicsitem.hpp"

SpecialCharGraphicsItem::SpecialCharGraphicsItem(QGraphicsItem *parent)
{
    SpecialCharGraphicsItem("", parent);
}

SpecialCharGraphicsItem::SpecialCharGraphicsItem(QString text, QGraphicsItem *parent) : RegexGraphicsItem(parent)
{
    contents = new QGraphicsTextItem;
    contents->setParentItem(this);
    setContents(text);
    backgroundColour = QColor(255, 220, 255);
}

void SpecialCharGraphicsItem::setContents(QString text)
{
    plainContents = text;
    if(!text.isEmpty())
        contents->setHtml(parseString(text));
    else
        contents->setHtml(text);

    updateData();
}

QString SpecialCharGraphicsItem::parseString(QString text)
{
    if(text == ".")
        return tr("Matches<br>any character");
    if(text == "^")
        return tr("Line<br>start");
    if(text == "$")
        return tr("Line<br>end");
    if(text == "\\d")
        return tr("Digit<br>character");
    if(text == "\\b")
        return tr("Word<br>boundary");
    if(text == "\\w")
        return tr("Word<br>character");
    if(text == "\\s")
        return tr("Whitespace<br>character");
    if(text == "\\D")
        return tr("Non-digit<br>character");
    if(text == "\\B")
        return tr("Non-word<br>boundary");
    if(text == "\\W")
        return tr("Non-word<br>character");
    if(text == "\\S")
        return tr("Non-whitespace<br>character");
    if(text == "\\n")
        return tr("Line<br>break");
    if(text == "\\t")
        return tr("Tab<br>character");
    if(text == "\\a")
        return tr("Bell<br>character");
    if(text == "\\f")
        return tr("Form<br>feed");
    if(text == "\\r")
        return tr("Carraige<br>return");
    if(text == "\\v")
        return tr("Vertical<br>tab");

    QRegExp unicode("\\\\x([0-9a-fA-F]{2,4})");
    if(unicode.exactMatch(text))
        return tr("Unicode<br>char ") + unicode.cap(1) + " \"" + QString(QChar(unicode.cap(1).toInt(0, 16))) + "\"";

    QRegExp octal("\\\\(0?[0-3][0-7]{2})");
    if(octal.exactMatch(text))
        return tr("Octal<br>char ") + octal.cap(1) + " \"" + QString(QChar::fromAscii(octal.cap(1).toInt(0, 8))) + "\"";

    QRegExp backreference("\\\\([1-9][0-9]*)");
    if(backreference.exactMatch(text))
        return tr("Backreference<br>#") + backreference.cap(1);

    return "";
}

QRectF SpecialCharGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, contents->boundingRect().width()+2*horizontalPadding, contents->boundingRect().height()+2*verticalPadding);
}

void SpecialCharGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(235, 200, 235));

    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    contents->setPos(horizontalPadding, verticalPadding);
}

void SpecialCharGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(245, 210, 245);
    update();
}

void SpecialCharGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(255, 220, 255);
    update();
}

void SpecialCharGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    SpecialCharEditDialog dialog(plainContents);
    int response = dialog.exec();

    if(response == QDialog::Rejected)
        return;
}

/**
 * Private methods
 */
void SpecialCharGraphicsItem::updateData()
{
    setData(expressionData, QVariant(plainContents));
    emit dataChanged();
}
