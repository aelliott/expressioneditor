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

#include "textgraphicsitem.hpp"

/*!
 * Creates a new TextGraphicsItem with the specified text
 *
 * \param   text    The text content of the item
 * \param   parent  This item's parent item
 */
TextGraphicsItem::TextGraphicsItem(QString text, QGraphicsItem *parent)
    : RegexGraphicsItem(parent)
{
    setText(text);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    backgroundColour = QColor(220,255,220);
}

/*!
 * Sets the text content of the graphics item and creates a "display safe"
 * internal string for use in drawing
 */
void TextGraphicsItem::setText(QString text)
{
    textString = text;
    displayText = textString;
    displayText.replace(QRegExp("\\\\([^bBwWdDsSnt])"),"\\1");
    updateData();
}

/*!
 * Appends the given string to the currently stored string
 *
 * \param   append  The string to append
 */
void TextGraphicsItem::appendText(QString append)
{
    setText(textString + append);
}

/*!
 * Returns the geometry of the graphical object
 *
 * \return  Returns a QRectF containing the object's geometry
 */
QRectF TextGraphicsItem::boundingRect() const
{
    double width = qApp->fontMetrics().width(displayText)+(2*horizontalPadding);
    double height = qApp->fontMetrics().height()+(2*verticalPadding);
    return QRectF(0, 0, width, height);
}

/*!
 * Paints the object on the canvas and lays out child items
 *
 * \param   painter The QPainter used to draw the graphics item
 * \param   option  Unused
 * \param   widget  Unused
 */
void TextGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(180,225,180));
    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    painter->drawText(horizontalPadding, boundingRect().height()-(1.5*verticalPadding), displayText);
}

/*!
 * Hover over listener, triggers the hover state (colour change)
 *
 * \param   event   The hover event that has been triggered
 */
void TextGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(200,240,200);
    update();
}

/*!
 * Hover exit listener, triggers a return to the normal state
 *
 * \param   event   The hover event that has been triggered
 */
void TextGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(220,255,220);
    update();
}

/*!
 * Double click event handler, present a dialog allowing GUI editing of the
 * regexp element
 *
 * \param   event   The double click event captured
 */
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

/*!
 * Update the object's internal data, trigger dataChanged on any changes
 * in state.
 */
void TextGraphicsItem::updateData()
{
//    QStringList specialchars;
//    specialchars << "\\\\" << "[" << "]" << "(" << ")" << "*" << "^" << "$" << "." << "|" << "?" << "+" << "{" << "}";
//    QString pattern = QString("(\\") + specialchars.join("|\\") + ")";
//    QString expression = textString;
//    expression.replace(QRegExp(pattern), "\\\\1");
    setData(expressionData, QVariant(textString));
    emit dataChanged();
}
