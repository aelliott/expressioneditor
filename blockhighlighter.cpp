/*!
 * \file
 *
 * Copyright (c) 2009,2010,2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "blockhighlighter.hpp"

/*!
 * Creates a new BlockHighlighter acting on the given QTextEdit if one
 * has been provided.
 *
 * \param   parent  The QTextEdit to highlight
 */
BlockHighlighter::BlockHighlighter(RegexFactory *factory, QTextEdit *parent)
    : QSyntaxHighlighter(parent)
    , _factory(factory)
    , _expression(QString())
{
}

/*!
 * Cleans up dynamically allocated memory
 */
BlockHighlighter::~BlockHighlighter()
{
}

/*!
 * Reimplemented method, takes a block of text (usually a paragraph of
 * the block) and applies highlighting rules to it.
 *
 * The method uses the current expression and regular expression type to
 * accurate find all of the matched text segments within the block it has
 * been given and highlights them in alternating blue/red text.
 *
 * NOTE: because the blocks passed in are not the whole text of the
 * QTextEdit the alternation can only be block (and thus paragraph)
 * consistent.  At each paragraph the highlighting resets to lead with red.
 *
 * \param   text    The text block to highlight (not the whole text)
 */
void BlockHighlighter::highlightBlock(const QString &text)
{
    RegexBase *rx = _factory->regexpEngine(_expression);

    // If it's invalid we have nothing to do
    if(!rx->isValid())
        return;

    // Define the two alternating text formats we're going to use
    QTextCharFormat red;
    red.setForeground(Qt::red);
    QTextCharFormat blue;
    blue.setForeground(Qt::blue);

    int offset = 0;
    bool isRed = true;

    while((offset = rx->indexIn(text, offset)) != -1)
    {
        int length = rx->matchedLength();
        // Fix for infinite looping
        if(length == 0)
            return;

        if(isRed)
            setFormat(offset, length, red);
        else
            setFormat(offset, length, blue);

        isRed = !isRed;
        offset += length;
    }

    delete rx;
}

/*!
 * Slot to receive any changes to the current expression
 *
 * \param   exp The new expression string
 */
void BlockHighlighter::updateExpression(QString exp)
{
    _expression = exp;
    rehighlight();
}
