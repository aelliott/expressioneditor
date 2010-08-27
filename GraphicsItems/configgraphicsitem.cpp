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

#include "configgraphicsitem.hpp"

/*!
 * Produces a new ConfigGraphicsItem
 *
 * \param   confFlag    The configuration flag set (i.e. "i"
 *                      for (?i))
 * \param   parent      The item's parent
 */
ConfigGraphicsItem::ConfigGraphicsItem(QString confFlag, QGraphicsItem *parent) : RegexGraphicsItem(parent)
{
    setFlag(confFlag);
    backgroundColour = QColor(230, 230, 230);
    updateData();
}

/*!
 * Setter, sets the configuration flag (i, m, etc)
 *
 * \param   confFlag    The configuration flag set (i.e. "i"
 *                      for (?i))
 */
void ConfigGraphicsItem::setFlag(QString confFlag)
{
    flag = confFlag;
    if(flag == "i")
        displayText = "Case Insensitive";
    else if(flag == "s")
        displayText = "\".\" matches all";
    else if(flag == "x")
        displayText = "PCRE_EXTENDED";
    else if(flag == "X")
        displayText = "PCRE_EXTRA";
    else if(flag == "m")
        displayText = "Multiline Matching";
    else if(flag == "U")
        displayText = "Ungreedy Capturing";
    else
        displayText = "Unrecognised Flag";
}

/*!
 * Returns the geometry of the graphical object
 *
 * \return  Returns a QRectF containing the object's geometry
 */
QRectF ConfigGraphicsItem::boundingRect() const
{
    QFont boldFont = qApp->font();
    boldFont.setBold(true);
    QFontMetrics bold(boldFont);
    int height = 3*verticalPadding + 2*qApp->fontMetrics().height();
    int width  = 2*horizontalPadding + qMax(qApp->fontMetrics().width(tr("Configuration Flag")), bold.width(displayText));

    return QRectF(0, 0, width, height);
}

/*!
 * Paints the object on the canvas and lays out child items
 *
 * \param   painter The QPainter used to draw the graphics item
 * \param   option  Unused
 * \param   widget  Unused
 */
void ConfigGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(210, 210, 210));
    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);

    painter->drawText(horizontalPadding, 2.5*verticalPadding, tr("Configuration Flag"));

    QFont bold = painter->font();
    bold.setBold(true);
    painter->setFont(bold);
    painter->drawText(horizontalPadding, boundingRect().height()-(1.5*verticalPadding), displayText);
}

/*!
 * Hover over listener, triggers the hover state (colour change)
 *
 * \param   event   The hover event that has been triggered
 */
void ConfigGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(220, 220, 220);
    update();
}

/*!
 * Hover exit listener, triggers a return to the normal state
 *
 * \param   event   The hover event that has been triggered
 */
void ConfigGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(230, 230, 230);
    update();
}

/*!
 * Update the object's internal data, trigger dataChanged on any changes
 * in state.
 */
void ConfigGraphicsItem::updateData()
{
    QString data = QString("(?") + flag + ")";
    setData(expressionData, QVariant(data));
    emit dataChanged();
}
