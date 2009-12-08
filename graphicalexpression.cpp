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

#include "graphicalexpression.hpp"

GraphicalExpression::GraphicalExpression()
{
    GraphicalExpression("");
}

GraphicalExpression::GraphicalExpression(QString expression)
{
    updateExpression(expression);
}

QRectF GraphicalExpression::boundingRect() const
{
    // Return the size of the whole expression
    double height = 0;
    for(int i = 0; i < childItems().size(); ++i)
        if(childItems().at(i)->boundingRect().height() > height)
            height = childItems().at(i)->boundingRect().height();
    double width = 0;
    for(int i = 0; i < childItems().size(); ++i)
        width += childItems().at(i)->boundingRect().width();
    return QRectF(0, 0, width, height);
}

void GraphicalExpression::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void GraphicalExpression::addChildItem(QGraphicsItem *item)
{
    item->setParentItem(this);
    // Lay out items
    double offset = 0;
    double height = boundingRect().height();
    for(int i = 0; i < childItems().size(); ++i)
    {
        if(offset > 0)
            offset += itemSpacing;
        double verticalOffset = (height/2)-(childItems().at(i)->boundingRect().height()/2);
        childItems().at(i)->setPos(offset, verticalOffset);
        offset += childItems().at(i)->boundingRect().width();
    }
}

void GraphicalExpression::parseExpression(QString expression)
{
    int offset = 0;
    addChildItem(parseSection(expression, offset));
}

QGraphicsItem* GraphicalExpression::parseSection(QString expression, int &offset, bool inAlternatives)
{
    GroupingGraphicsItem *group = new GroupingGraphicsItem;

    QRegExp character("[^[\\\\$.|?*+()^{}]|\\\\[[\\\\$.|?*+()^{}]");
    QRegExp repeats("\\{(\\d+)?,?(\\d+)?\\}|\\+|\\?|\\*");
    QRegExp special("\\.|\\^|\\$|\\\\[bBwWdDsSnt]");

    bool workDone = true;
    while(workDone)
    {
        workDone = false;

        if(QRegExp("\\(").indexIn(expression, offset) == offset)
        {
            group->addChildItem(parseCapture(expression, offset));
            workDone = true;
        }

        if(!workDone && character.indexIn(expression, offset) == offset)
        {
            // Read in as many consecutive characters as possible
            QStringList characters;

            while(character.indexIn(expression, offset) == offset)
            {
                if(character.cap(0).length() == 2)
                    characters << QString(character.cap(0).at(1));
                else
                    characters << character.cap(0);
                offset += character.cap(0).length();
            }

            // Check for repeat characters that would catch the
            // last character.
            if(repeats.indexIn(expression, offset) == offset)
            {
                QString last = characters.back();
                characters.pop_back();
                if(characters.size() > 0)
                    group->addChildItem(new TextGraphicsItem(characters.join("")));

                QString repeat = repeats.cap(0);
                group->addChildItem(parseRepeat(repeat, new TextGraphicsItem(last)));

                offset += repeats.cap(0).length();
            }
            else
                group->addChildItem(new TextGraphicsItem(characters.join("")));

            workDone = true;
        }

        if(!workDone && QRegExp("\\[").indexIn(expression, offset) == offset)
        {
            // Consume characters until we get to the end ]
            QRegExp content("((\\\\[^]]){0,}|[^]\\\\])+");
            ++offset;
            if(content.indexIn(expression, offset) == offset)
            {
                CharRangeGraphicsItem *tmp = new CharRangeGraphicsItem(content.cap(0));
                offset += content.cap(0).length()+1;
                if(repeats.indexIn(expression, offset) == offset)
                {
                    group->addChildItem(parseRepeat(repeats.cap(0), tmp));
                    offset += repeats.cap(0).length();
                }
                else
                    group->addChildItem(tmp);
            }

            workDone = true;
        }

        if(!workDone && special.indexIn(expression, offset) == offset)
        {
            SpecialCharGraphicsItem *tmp = new SpecialCharGraphicsItem(special.cap(0));
            offset += special.cap(0).length();
            if(repeats.indexIn(expression, offset) == offset)
            {
                group->addChildItem(parseRepeat(repeats.cap(0), tmp));
                offset += repeats.cap(0).length();
            }
            else
                group->addChildItem(tmp);

            workDone = true;
        }

        if(!workDone && QRegExp("\\|").indexIn(expression, offset) == offset)
        {
            if(!inAlternatives)
                return parseAlternatives(expression, offset, group);
            else
                return group;
        }
    }

    return group;
}

RepeatGraphicsItem* GraphicalExpression::parseRepeat(QString repeatString, QGraphicsItem *repeatItem)
{
    RepeatGraphicsItem *repeat;
    QRegExp range("\\{(\\d+)?,?(\\d+)?\\}");
    if(range.exactMatch(repeatString))
    {
        if(!range.cap(2).isEmpty())
            if(range.cap(1).isEmpty() && repeatString.contains(","))
                repeat = new RepeatGraphicsItem(RepeatGraphicsItem::SpecifiedRange, -1, range.cap(2).toInt());
            else
                repeat = new RepeatGraphicsItem(RepeatGraphicsItem::SpecifiedRange, range.cap(1).toInt(), range.cap(2).toInt());
        else if(repeatString.contains(","))
            repeat = new RepeatGraphicsItem(RepeatGraphicsItem::SpecifiedRange, range.cap(1).toInt());
        else
            repeat = new RepeatGraphicsItem(RepeatGraphicsItem::ExactValue, range.cap(1).toInt());
    }
    else if(repeatString == "+")
        repeat = new RepeatGraphicsItem(RepeatGraphicsItem::OneOrMore);
    else if(repeatString == "?")
        repeat = new RepeatGraphicsItem(RepeatGraphicsItem::ZeroOrOne);
    else if(repeatString == "*")
        repeat = new RepeatGraphicsItem(RepeatGraphicsItem::ZeroOrMore);

    repeat->setChildItem(repeatItem);
    return repeat;
}

QGraphicsItem* GraphicalExpression::parseCapture(QString expression, int &offset)
{
    GroupingGraphicsItem *group = new GroupingGraphicsItem(true);
    ++offset;
    QGraphicsItem *tmp = parseSection(expression, offset);

    if(QRegExp("\\)").indexIn(expression, offset) == offset)
        ++offset;

    group->addChildItem(tmp);

    QRegExp repeats("\\{(\\d+)?,?(\\d+)?\\}|\\+|\\?|\\*");
    if(repeats.indexIn(expression, offset) == offset)
    {
        RepeatGraphicsItem *repeat = parseRepeat(repeats.cap(0), group);
        offset += repeats.cap(0).length();
        return repeat;
    }
    else
        return group;
}

AlternativesGraphicsItem* GraphicalExpression::parseAlternatives(QString expression, int &offset, QGraphicsItem *firstItem)
{
    AlternativesGraphicsItem *alternatives = new AlternativesGraphicsItem;
    alternatives->addChildItem(firstItem);
    bool more = false;
    do
    {
        alternatives->addChildItem(parseSection(expression, ++offset, true));
        more = (QRegExp("\\|").indexIn(expression, offset) == offset);
    }
    while(more);
    return alternatives;
}

void GraphicalExpression::updateExpression(QString expression)
{
    parseExpression(expression);
}

QString GraphicalExpression::getExpression() const
{
    QStringList expression;
    for(int i = 0; i < childItems().size(); ++i)
        expression << childItems().at(i)->data(expressionData).toString();
    return expression.join("");
}
