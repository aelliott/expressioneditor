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

#include "blocktester.hpp"

/*!
 * Creates a new BlockTester
 *
 * \param   parent  The parent of the widget
 */
BlockTester::BlockTester(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    text = new QTextEdit(this);
    highlighter = new BlockHighlighter(text);
    layout->addWidget(text);

    setLayout(layout);
}


/*!
 * Access method, allows access to the plain text being tested against
 *
 * \return  Returns the block of text being tested against
 */
QString BlockTester::getText() const
{
    return text->toPlainText();
}

/*!
 * Slot to receive any changes to the current expression, passes along the
 * signal to the BlockHighlighter highlighting the object and triggers the
 * highlighter to highlight the object again.
 *
 * \param   exp The new expression
 */
void BlockTester::updateExpression(QString exp)
{
    highlighter->updateExpression(exp);
    highlighter->rehighlight();
}

/*!
 * Slot to update the block of text being tested against, used in file
 * loading.
 *
 * \param   testString  The block of text to test matches against
 */
void BlockTester::setText(QString testString)
{
    text->setText(testString);
}

/*!
 * Slot to receive any changes to the regular expression format used.
 * Sets the regexp format in the highlighter and triggers a full
 * rehighlight of the text.
 *
 * \param   type    The regular expression format to use
 */
void BlockTester::setRegexpFormat(int type)
{
    highlighter->setRegexpFormat(type);
    highlighter->rehighlight();
}
