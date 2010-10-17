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

#include "graphicalexpression.hpp"

/*!
 * Creates a new GraphicalExpression
 *
 * \param   The expression to parse and create a visualisation for
 */
GraphicalExpression::GraphicalExpression(QString expression)
{
    // The actual work is done here
    updateExpression(expression);
}

/*!
 * Returns the geometry of the graphical object
 *
 * \return The dimensions of the regular expression visualisation
 */
QRectF GraphicalExpression::boundingRect() const
{
    // Calculate the height of the expression by iterating over all of the
    // objects inside the visualisation and taking the maximum
    double height = 0;
    for(int i = 0; i < childItems().size(); ++i)
        if(childItems().at(i)->boundingRect().height() > height)
            height = childItems().at(i)->boundingRect().height();

    // Calculate the width by summing the width of the child items plus the
    // item spacing between them
    double width = 0;
    for(int i = 0; i < childItems().size(); ++i)
        width += childItems().at(i)->boundingRect().width()+itemSpacing;
    width += 2*itemSpacing;

    // Return the calculated dimensions
    return QRectF(0, 0, width, height);
}

/*!
 * This method simply sets the positions of the various objects as they should
 * be in the visualisation, the painting of those objects is left to their own
 * implementations
 *
 * \param   painter Unused
 * \param   option  Unused
 * \param   widget  Unused
 */
void GraphicalExpression::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Lay out items
    double offset = 0;
    double height = boundingRect().height();
    for(int i = 0; i < childItems().size(); ++i)
    {
        offset += itemSpacing;
        double verticalOffset = (height/2)-(childItems().at(i)->boundingRect().height()/2);
        if(!childItems().at(i)->isSelected())
            childItems().at(i)->setPos(offset, verticalOffset);
        offset += childItems().at(i)->boundingRect().width();
    }
}

/*!
 * Adds an item to be a regexp element
 *
 * \param   item    The graphical object to add to the visualisation
 */
void GraphicalExpression::addChildItem(QGraphicsObject *item)
{
    connect(item, SIGNAL(editComplete()), this, SLOT(expressionChanged()));
    item->setParentItem(this);
}

/*!
 * Root of the parsing process (internal)
 *
 * \param   expression  The regular expression to use to produce a visualisation
 */
void GraphicalExpression::parseExpression(QString expression)
{
    int offset = 0;
    addChildItem(parseSection(expression, offset, false, true));
}

/*!
 * Parses out a full section of regexp (usually a capture group or an
 * alternation)
 *
 * \param   expression      The expression we are working on
 * \param   offset          A reference to the offset we have reached in the
 *                          expression
 * \param   inAlternatives  Determines whether we are in an alternation or not
 * \param   outerFlag       Specifies the case in which this is an outer group
 *                          and thus should have horizontal padding
 * \return  A pointer to a QGraphicsObject we can add to the scene
 */
QGraphicsObject* GraphicalExpression::parseSection(
        QString expression,
        int &offset,
        bool inAlternatives,
        bool outerFlag
        )
{
    // Create a grouping item to add children to as encountered
    GroupingGraphicsItem *group = new GroupingGraphicsItem;

    // Use the bool flags to determine whether this is an outer group
    if(outerFlag || inAlternatives)
        group->setOuterGroup(true);

    // Declare a set of useful regular expressions for matching various
    // sections of... regular expressions.  How meta.
    QRegExp character("[^[\\\\$\\.|?*+()^]|\\\\[^bBwWdDsSnt]");
    QRegExp repeats("\\{(\\d+),?(\\d+)?\\}|\\{,(\\d+)?\\}|\\+\\??|\\?|\\*\\??");
    QRegExp special("\\.|\\^|\\$|\\\\[bBwWdDsSntafrv]|\\\\x[0-9a-fA-F]{2,4}|\\\\0[1-3]?[0-7]{2}|\\\\[1-9][0-9]*");
    QRegExp pcre_config("\\(\\?(i|s|x|X|m|U)\\)");

    // Loop until there is nothing more we can do
    bool workDone;
    do
    {
        // Set to false, will be set to true if anything is done
        workDone = false;

        // Look for a PCRE configuration flag, such as (?i) for
        // case-insensitive matching
        if(!workDone && pcre_config.indexIn(expression, offset) == offset)
        {
            // Retrieve the character determining what option has been set
            QString flag = QString(expression.at(offset+2));

            // Add the configuration item
            group->addChildItem(new ConfigGraphicsItem(flag));

            // Move along the offset and then begin a new loop iteration
            offset += pcre_config.matchedLength();
            workDone = true;
        }

        // Look for a regular expression comment (?#...)
        if(!workDone && QRegExp("\\(\\?#").indexIn(expression, offset) == offset)
        {
            // Increase offset for the opening of the comment
            offset += 3;

            // Create a comment item to work with
            CommentGraphicsItem *tmp = new CommentGraphicsItem;

            // While the comment is not closed
            while(QRegExp("[^)]").indexIn(expression, offset) == offset)
            {
                tmp->appendText(QString(expression.at(offset)));
                ++offset;
            }

            // We've reached the end of the comment, increase the offset to
            // consume the final closing )
            ++offset;

            // Add the comment item
            group->addChildItem(tmp);
            workDone = true;
        }

        // Check for a grouping being started
        if(!workDone && QRegExp("\\(").indexIn(expression, offset) == offset)
        {
            // Pass this along to the parseCapture method and return to this
            // method when it has completed its work
            group->addChildItem(parseCapture(expression, ++offset));
            workDone = true;
        }

        // Check for a special character such as \w or \S
        if(!workDone && special.indexIn(expression, offset) == offset)
        {
            // Create a special character item based on what has been found
            SpecialCharGraphicsItem *tmp = new SpecialCharGraphicsItem(special.cap(0));
            offset += special.cap(0).length();

            // Check if there is a repeat quantifier after the special character
            // and if there is apply it, otherwise just add the special
            // character item
            if(repeats.indexIn(expression, offset) == offset)
            {
                group->addChildItem(parseRepeat(repeats.cap(0), tmp));
                offset += repeats.cap(0).length();
            }
            else
                group->addChildItem(tmp);

            workDone = true;
        }

        // Check for a regular/literal character string
        if(!workDone && character.indexIn(expression, offset) == offset)
        {
            // Read in as many consecutive characters as possible
            QStringList characters;

            // While we have come across a character and not a special char or
            // a repeat char.
            // NOTE: Check for special should probably not be necessary
            while(repeats.indexIn(expression, offset) != offset
                  && special.indexIn(expression, offset) != offset
                  && character.indexIn(expression, offset) == offset
                  )
            {
                // Append the character to the collection
//                if(character.cap(0).length() == 2)
//                    characters << QString(character.cap(0).at(1));
//                else
                    characters << character.cap(0);
                offset += character.cap(0).length();
            }

            // Check for repeat characters that would catch the
            // last character.
            if(repeats.indexIn(expression, offset) == offset)
            {
                // Retrieve the last character, removing it from the string
                QString last = characters.back();
                characters.pop_back();

                // If there are still characters in the string (i.e. there was
                // more than one character there) then add that string to the
                // visualisation
                if(characters.size() > 0)
                    group->addChildItem(new TextGraphicsItem(characters.join("")));

                // Parse the repeat for the last character and add the repeat
                // item to the visualisation
                QString repeat = repeats.cap(0);
                group->addChildItem(parseRepeat(repeat, new TextGraphicsItem(last)));

                offset += repeats.cap(0).length();
            }
            else
                // No repeat, just add the string we found to the visualisation
                group->addChildItem(new TextGraphicsItem(characters.join("")));

            workDone = true;
        }

        // Check for the start of a character range/set/class [...]
        if(!workDone && QRegExp("\\[").indexIn(expression, offset) == offset)
        {
            // Consume characters until we get to the end ]
            QRegExp content("((\\\\.)+|[^]\\\\]|\\[:[a-z]+:\\])+");
            ++offset;
            QString charRangeContents = "";

            // If we've started with ^] or ] take that
            QRegExp notBrace("((\\^)?\\])");
            if(notBrace.indexIn(expression, offset) == offset)
            {
                charRangeContents = notBrace.cap(1);
                offset += notBrace.cap(0).length();
            }

            // Check for all other regular contents
            if(content.indexIn(expression, offset) == offset)
            {
                charRangeContents += content.cap(0);
                offset += content.cap(0).length();
            }

            // Increment the offset since we should have reached the closing ]
            // now
            ++offset;

            // If we have found something at all here
            if(!charRangeContents.isEmpty())
            {
                // Create a char range item for it
                CharRangeGraphicsItem *tmp = new CharRangeGraphicsItem(charRangeContents);

                // Check for a repeat and if found apply it
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

        // Check for an alternation, if we do find one then check if we are
        // already in alternation (in which case this is just an inner branch)
        // and if not set up for alternation
        if(!workDone && QRegExp("\\|").indexIn(expression, offset) == offset)
        {
            if(!inAlternatives)
            {
                // Create a new item to return (as the current one is going to
                // end up inside an alternatives item
                GroupingGraphicsItem *newGroup = new GroupingGraphicsItem;
                if(outerFlag)
                {
                    //newGroup->setOuterGroup(true);
                    newGroup->setBrackets(true);
                }
                group->setOuterGroup(true);
                AlternativesGraphicsItem *alts = parseAlternatives(expression, offset, group);
                newGroup->addChildItem(alts);
                return newGroup;
            }
            else
                return group;
        }
    }
    while(workDone);

    return group;
}

/*!
 * Parses a repeated section, one with a quantifier (? + * etc)
 *
 * \param   repeatString    The repeat quantifer present
 * \param   repeatItem      The graphical item being repeated (will become a
 *                          child of the repeat item
 * \return  Returns a repeat item containing the provided repeat item
 */
RepeatGraphicsItem* GraphicalExpression::parseRepeat(QString repeatString, QGraphicsObject *repeatItem)
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
    else if(repeatString == "+?")
    {
        repeat = new RepeatGraphicsItem(RepeatGraphicsItem::OneOrMore);
        repeat->setGreedy(false);
    }
    else if(repeatString == "?")
        repeat = new RepeatGraphicsItem(RepeatGraphicsItem::ZeroOrOne);
    else if(repeatString == "*")
        repeat = new RepeatGraphicsItem(RepeatGraphicsItem::ZeroOrMore);
    else if(repeatString == "*?")
    {
        repeat = new RepeatGraphicsItem(RepeatGraphicsItem::ZeroOrMore);
        repeat->setGreedy(false);
    }

    repeat->setChildItem(repeatItem);
    return repeat;
}

/*!
 * Parses a single capture group
 *
 * \param   expression  The expression we're working on
 * \param   offset      A reference to the position reached in the string
 * \return  A Grouping item for this capture group
 */
QGraphicsObject* GraphicalExpression::parseCapture(QString expression, int &offset)
{
    GroupingGraphicsItem *group = new GroupingGraphicsItem(true);

    // Regular expression to check if this is a named capture group
    // NOTE: Should be more comprehensive
    QRegExp named("\\?P<([^>]+)>");

    // Check for non-capturing, etc.
    // NOTE: Since this flips capturing, we should know whether the default is
    // capturing or non-capturing really
    if(QRegExp("\\?:").indexIn(expression, offset) == offset)
    {
        offset += 2;
        group->setCapturing(false);
    }
    else if(named.indexIn(expression, offset) == offset)
    {
        // We have a capturing name;
        offset += named.matchedLength();
        group->setCapturingName(named.cap(1));
    }

    // Parse out the section inside the capture group
    QGraphicsObject *tmp = parseSection(expression, offset);

    // Increment the count for the closing )
    if(QRegExp("\\)").indexIn(expression, offset) == offset)
        ++offset;

    // Add the item to the capturing group
    group->addChildItem(tmp);

    // Check if this group is repeated, if so apply the repeat quantifier
    QRegExp repeats("\\{(\\d+)?,?(\\d+)?\\}|\\+\\??|\\?|\\*\\??");
    if(repeats.indexIn(expression, offset) == offset)
    {
        RepeatGraphicsItem *repeat = parseRepeat(repeats.cap(0), group);
        offset += repeats.cap(0).length();
        return repeat;
    }
    else
        return group;
}

/*!
 * Parses an alternation
 *
 * \param   expression  The expression we're working on
 * \param   offset      A reference to the position reached in the string
 * \param   firstItem   A grouping item which was being worked on when the
 *                      alternation was found
 * \return  An alternatives item
 */
AlternativesGraphicsItem* GraphicalExpression::parseAlternatives(
        QString expression,
        int &offset,
        QGraphicsObject *firstItem
        )
{
    // Create an alternatives item and add the initial item to it
    AlternativesGraphicsItem *alternatives = new AlternativesGraphicsItem;
    alternatives->addChildItem(firstItem);

    bool more = false;
    do
    {
        // Add a further alternation branch to the alternatives item
        alternatives->addChildItem(parseSection(expression, ++offset, true));

        // Check if there is another branch
        more = (QRegExp("\\|").indexIn(expression, offset) == offset);
    }
    while(more);
    return alternatives;
}

/*!
 * Updates the expression and forces a recalculation of the visualisation
 *
 * \param   The new expression
 */
void GraphicalExpression::updateExpression(QString expression)
{
    // Parse out a new expression
    parseExpression(expression);
}

/*!
 * Gets the current expression from the GraphicalExpression
 *
 * \return  The expression according to the visualisation built as a composite
 *          of the data members of the children of this item.  This should
 *          be equal to the string used to build the visualisation in most cases
 *          other than a graphical edit
 */
QString GraphicalExpression::getExpression() const
{
    QStringList expression;
    for(int i = 0; i < childItems().size(); ++i)
    {
        expression << childItems().at(i)->data(expressionData).toString();
    }
    return expression.join("");
}

/*!
 * Slot triggered when the expression has changed
 */
void GraphicalExpression::expressionChanged()
{
    emit dataChanged();
}
