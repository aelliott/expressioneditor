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

#include "textgraphicsitem.hpp"

TextGraphicsItem::TextGraphicsItem(QGraphicsItem * parent)
{
    TextGraphicsItem("", parent);
}

TextGraphicsItem::TextGraphicsItem(QString text, QGraphicsItem * parent) : QGraphicsObject(parent)
{
    setText(text);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    backgroundColour = QColor(220,255,220);
}

void TextGraphicsItem::setText(QString text)
{
    textString = text;
    displayText = textString;
    displayText.replace(QRegExp("\\\\([^bBwWdDsSnt])"),"\\1");
    updateData();
}

void TextGraphicsItem::appendText(QString append)
{
    setText(textString + append);
}

QRectF TextGraphicsItem::boundingRect() const
{
    double width = qApp->fontMetrics().width(displayText)+(2*horizontalPadding);
    double height = qApp->fontMetrics().height()+(2*verticalPadding);
    return QRectF(0, 0, width, height);
}

void TextGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(180,225,180));
    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    painter->drawText(horizontalPadding, boundingRect().height()-(1.5*verticalPadding), displayText);
}

void TextGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(200,240,200);
    update();
}

void TextGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(220,255,220);
    update();
}

void TextGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    TextEditDialog dialog(displayText);
    int response = dialog.exec();

    if(response == QDialog::Rejected)
        return;

    setText(dialog.getText());
    update();
}

/**
 * Private methods
 */
void TextGraphicsItem::updateData()
{
    QStringList specialchars;
    specialchars << "\\\\" << "[" << "]" << "(" << ")" << "*" << "^" << "$" << "." << "|" << "?" << "+" << "{" << "}";
    QString pattern = QString("(\\") + specialchars.join("|\\") + ")";
    QString expression = textString;
    expression.replace(QRegExp(pattern), "\\\\1");
    setData(expressionData, QVariant(expression));
    emit dataChanged();
}
