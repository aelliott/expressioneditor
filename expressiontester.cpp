/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2010 Alex Elliott <alex@alex-elliott.co.uk>
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

#include "expressiontester.hpp"

ExpressionTester::ExpressionTester(QWidget *parent) : QTabWidget(parent)
{
    multiline = new MultilineTester(this);
    addTab(multiline, tr("Test Inputs"));

    block = new BlockTester(this);
    addTab(block, tr("Text Block"));

    searchReplace = new SearchReplaceTester(this);
    addTab(searchReplace, tr("Search / Replace"));
}

QString ExpressionTester::getExpression()
{
    return multiline->getExpression();
}

QStringList ExpressionTester::getTestStrings()
{
    return multiline->getTestStrings();
}

void ExpressionTester::updateExpression(QString exp)
{
    multiline->updateExpression(exp);
    block->updateExpression(exp);
    searchReplace->updateExpression(exp);
}

void ExpressionTester::addTestString(QString testString)
{
    multiline->addTestString(testString);
}

void ExpressionTester::setFormat(int type)
{
    multiline->setFormat(type);
    block->setFormat(type);
    searchReplace->setFormat(type);
}
