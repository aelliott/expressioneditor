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

#include "expressiontester.hpp"

/*!
 * Creates a new ExpressionTester, populating it with all of the available
 * test widgets
 *
 * \param   parent  This widget's parent widget
 */
ExpressionTester::ExpressionTester(QWidget *parent) : QTabWidget(parent)
{
    multiline = new MultilineTester(this);
    addTab(multiline, tr("Test Inputs"));

    block = new BlockTester(this);
    addTab(block, tr("Text Block"));

    searchReplace = new SearchReplaceTester(this);
    addTab(searchReplace, tr("Search / Replace"));
}

/*!
 * Getter, gets the expression being tested against
 *
 * \return  The current expression in the test widgets
 */
QString ExpressionTester::getExpression()
{
    // Relying on an assumed invariant that all test widgets contain the same
    // expression at all times (barring mid-update)
    return multiline->getExpression();
}

/*!
 * Getter, retrieves the test strings used in testing
 *
 * \return  Returns the test strings used in the multiline test widget
 */
QStringList ExpressionTester::getTestStrings()
{
    return multiline->getTestStrings();
}

/*!
 * Setter, sets the expression to the new content
 *
 * \param   exp The new regular expression to test against
 */
void ExpressionTester::updateExpression(QString exp)
{
    multiline->updateExpression(exp);
    block->updateExpression(exp);
    searchReplace->updateExpression(exp);
}

/*!
 * Adds a test string to the testing widget
 *
 * \param   testString  The test string to add to the multiline testing widget
 */
void ExpressionTester::addTestString(QString testString)
{
    multiline->addTestString(testString);
}

/*!
 * Setter, updates the regexp format in use
 *
 * \param   type    The format of regular expressions to use when testing
 */
void ExpressionTester::setRegexpFormat(int type)
{
    multiline->setRegexpFormat(type);
    block->setRegexpFormat(type);
    searchReplace->setRegexpFormat(type);
}
