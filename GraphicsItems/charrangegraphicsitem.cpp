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

#include "charrangegraphicsitem.hpp"

/*!
 * Creates a new CharRangeGraphicsItem
 *
 * \param   initContents    String of the contents to initialise with
 * \param   regexType       The type of regular expression in use
 * \param   parent          This item's parent item
 */
CharRangeGraphicsItem::CharRangeGraphicsItem(QString initContents, int regexType, QGraphicsItem *parent)
    : RegexGraphicsItem(parent)
    , regexFormat(regexType)
    , initialised(false)
    , contents(initContents)
{
    parseContents(contents);

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptHoverEvents(true);
    backgroundColour = QColor(240, 240, 255);
}

/*!
 * Cleans up dynamically allocated memory
 */
CharRangeGraphicsItem::~CharRangeGraphicsItem()
{
    if(initialised)
        delete contentsItem;
}

/*!
 * Parses the contents of the character range to produce a neat list of
 * the allowed characters.
 *
 * This method parses out any ranges (a-z, etc), special characters (\\w etc),
 * POSIX character classes ([:alpha:] etc), and anything not treated as a literal
 * and places all left-over characters in a simple stringlist to produce a final
 * comma-delimited list of characters allowed in addition to the special chars.
 *
 * \param   string  The string contents of the character range (that between [
 *                  and a closing ])
 */
void CharRangeGraphicsItem::parseContents(QString string)
{
    // If we already have a QGraphicsTextItem then we need to free
    // the memory before we create a new one
    if(initialised)
        delete contentsItem;
    else
        initialised = true;
    contentsItem = new QGraphicsTextItem(this);

    // Parse into sections:
    QStringList characters;
    QVector<QString> elements;

    QString charRegex = "((\\\\x[0-9a-fA-F]{2,4}|\\\\.|[^]\\\\]))";
    QRegExp charPattern(charRegex);
    QRegExp rangePattern(charRegex+"\\-"+charRegex);
    QRegExp charClass("\\[:(alnum|word|alpha|blank|cntrl|digit|graph|lower|print|punct|space|upper|xdigit):\\]");

    // Parsing logic
    bool negated = false;
    int offset = 0;
    // Check if we're negating the following characters
    if(string.startsWith("^"))
    {
        negated = true;
        ++offset;
        // "[^]...]" is allowed, will match anything but "]" and any
        // further contents
        if(QString(string.at(offset)) == "]")
        {
            characters << "]";
            ++offset;
        }
    }

    // Loop while there are still characters to read in
    bool workDone = true;
    while(workDone)
    {
        workDone = false;

        // Match POSIX character classes (like [:alpha:])
        if(!workDone && charClass.indexIn(string, offset) == offset)
        {
            elements.push_back(charClass.cap(0) + " POSIX Class");
            offset += charClass.cap(0).length();
            workDone = true;
        }

        // Match a range (like a-z)
        if(!workDone && rangePattern.indexIn(string, offset) == offset)
        {
            elements.push_back(rangePattern.cap(0));
            offset += rangePattern.cap(0).length();
            workDone = true;
        }

        // Match anything else, including escaped strings or special characters
        if(!workDone && charPattern.indexIn(string, offset) == offset)
        {
            if(QRegExp("\\.|\\\\[bBwWdDsSntafrv]|\\\\x[0-9a-fA-F]{4}|\\\\0?[0-3][0-7]{2}|\\\\[1-9][0-9]*").exactMatch(charPattern.cap(0)))
                elements.push_back(SpecialCharGraphicsItem::parseString(charPattern.cap(0)).replace("<br>"," "));
            else if(charPattern.cap(0).length() == 2)
                characters << QString(charPattern.cap(0).at(1));
            else
                characters << charPattern.cap(0);
            offset += charPattern.cap(0).length();
            workDone = true;
        }
    }

    // Add characters to elements
    if(characters.size() > 0)
        elements.push_front(characters.join(", "));

    QString htmlContents;
    if(negated)
        htmlContents = tr("All characters except: ");
    else
        htmlContents = tr("Any one of: ");
    for(int i = 0; i < elements.size(); ++i)
        htmlContents += QString("<br> - ") + elements.at(i);

    contentsItem->setHtml(htmlContents);

    updateData();
}


/*!
 * Returns the geometry of the graphical object
 *
 * \return  A QRectF describing the dimensions of the object
 */
QRectF CharRangeGraphicsItem::boundingRect() const
{
    // The height and width of this item depend entirely on the height and width
    // of the QGraphicsTextItem child item
    double width = contentsItem->boundingRect().width()+2*horizontalPadding;
    double height = contentsItem->boundingRect().height()+2*verticalPadding;
    return QRectF(0, 0, width, height);
}


/*!
 * Paints the object on the canvas and lays out child items
 *
 * \param   painter QPainter used to paint the scene
 * \param   option Unused
 * \param   widget  Unused
 */
void CharRangeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(220, 220, 235));

    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);

    contentsItem->setParentItem(this);
    contentsItem->setPos(horizontalPadding, verticalPadding);
}

/*!
 * Hover over listener, triggers the hover state (colour change)
 *
 * \param   event   The hover event received
 */
void CharRangeGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(230, 230, 245);
    update();
}

/*!
 * Hover exit listener, triggers a return to the normal state
 *
 * \param   event   The hover event received
 */
void CharRangeGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(240, 240, 255);
    update();
}

/*!
 * Mouse double-click listener.  Produces a GUI editing dialog for the regexp element.
 *
 * NOTE: this method is incomplete as there is not currently a CharRangeEditDialog
 *
 * \param   event   The mouse click event received
 */
void CharRangeGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    qDebug() << "CharRange: I've been double clicked";
}

/*!
 * Update the object's internal data, trigger dataChanged on any changes
 * in state.
 */
void CharRangeGraphicsItem::updateData()
{
    QString expression = QString("[") + contents + "]";
    setData(expressionData, QVariant(expression));
    emit dataChanged();
}
