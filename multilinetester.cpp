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

#include "multilinetester.hpp"

/*!
 * Create and set up a new MultilineTester widget
 *
 * \param   parent  This widget's parent widget
 */
MultilineTester::MultilineTester(QWidget *parent) : QWidget(parent)
{
    factory = new RegexFactory();
    rx = factory->factory();

    mainLayout = new QVBoxLayout(this);

    //QLabel *testHeading = new QLabel(tr("Test Inputs:"), this);

    table = new QTableWidget(0, 4, this);
    QStringList headings;
    headings << "Input" << "Match" << "Index" << "Captured Text";
    table->setAlternatingRowColors(true);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setHorizontalHeaderLabels(headings);
        connect(table, SIGNAL(cellChanged(int,int)), this, SLOT(updateTestCase(int,int)));

    for(int i = 0; i < MultilineTester::initialRows; ++i)
        addRow();

    //mainLayout->addWidget(testHeading);
    mainLayout->addWidget(table);
}

/*!
 * If a new empty row is required in the table, add a new one below all of the
 * existing rows
 */
void MultilineTester::addRow()
{
    table->setRowCount(table->rowCount()+1);
    int row = table->rowCount()-1;
    QTableWidgetItem *testCase = new QTableWidgetItem;
    table->setItem(row, 0, testCase);
    for(int i = 1; i < 4; ++i)
    {
        QTableWidgetItem *tmp = new QTableWidgetItem;
        tmp->setFlags(Qt::ItemIsSelectable);
        table->setItem(row, i, tmp);
    }
    table->resizeRowsToContents();
    table->resizeColumnToContents(0);
}

/*!
 * Return the current regular expression in the regexp backend
 *
 * \return  The current regular expression in use
 */
QString MultilineTester::getExpression()
{
    return rx->getExpression();
}

/*!
 * Get all of the test strings stored in the table (for saving along with the
 * expression)
 *
 * \return  A list of all of the test strings
 */
QStringList MultilineTester::getTestStrings()
{
    QStringList testStrings;
    for(int i = 0; i < table->rowCount(); ++i)
        if(!table->item(i, 0)->text().isEmpty())
            testStrings.push_back(table->item(i, 0)->text());
    return testStrings;
}

/*!
 * Update the current regular expression to use
 *
 * \param   exp The new expression to use
 */
void MultilineTester::updateExpression(QString exp)
{
    delete rx;
    rx = factory->factory(exp);
    for(int i = 0; i < table->rowCount(); ++i)
        updateRow(i);
}

/*!
 * Update the data cells for the specfied row
 *
 * \param   row The row to update
 */
void MultilineTester::updateRow(int row)
{
    if(rx->isEmpty() || table->item(row, 0)->text().isEmpty())
        return;

    // Test for exact match
    QTableWidgetItem *match = new QTableWidgetItem;
    match->setFlags(Qt::ItemIsSelectable);
    if(rx->exactMatch(table->item(row, 0)->text()))
        match->setText(tr("Exact Match"));
    else if(rx->indexIn(table->item(row, 0)->text()) > -1)
        match->setText(tr("Partial Match"));
    else
        match->setText(tr("No"));
    table->setItem(row, 1, match);

    // Test for index
    QTableWidgetItem *index = new QTableWidgetItem;
    index->setFlags(Qt::ItemIsSelectable);
    int foundIndex;
    if((foundIndex = rx->indexIn(table->item(row, 0)->text())) > -1)
        index->setText(QVariant(foundIndex).toString());
    else
        index->setText(tr("None"));
    table->setItem(row, 2, index);

    // Get any captured strings
    if(!rx->exactMatch(table->item(row, 0)->text()))
        rx->indexIn(table->item(row, 0)->text(), 0);
    QTableWidgetItem *captured = new QTableWidgetItem;
    captured->setFlags(Qt::ItemIsSelectable);
    QString texts;
    if(rx->captureCount() > 0)
    {
        for(int i = 0; i <= rx->captureCount(); ++i)
            texts += QString("[") + QVariant(i).toString() + "] \"" + rx->cap(i) + "\"\n";
        captured->setText(texts);
    }
    else
        captured->setText(tr("None"));
    table->setItem(row, 3, captured);
    table->resizeRowsToContents();
    table->resizeColumnToContents(0);
}

/*!
 * Add a new test string to the table (usually used when importing from a saved
 * file)
 *
 * \param   testString  The test string to add to the table
 */
void MultilineTester::addTestString(QString testString)
{
    QTableWidgetItem *newTestString = new QTableWidgetItem;
    newTestString->setText(testString);
    for(int i = 0; i < table->rowCount(); ++i)
    {
        if(table->item(i, 0)->text().isEmpty())
        {
            table->setItem(i, 0, newTestString);
            updateTestCase(i, 0);
            return;
        }
    }
}

/*!
 * Set the regular expression backend to use
 *
 * \param   type    The regular expression backend to use
 */
void MultilineTester::setRegexpFormat(int type)
{
    // Update the factory and recreate the backend
    factory->setRegexpFormat(type);
    updateExpression(rx->getExpression());
}

/*!
 * Catch any edits made to the table cells, only the test strings are editable
 * directly so we only need to care about edits make to column 0
 *
 * If an edit has been made to a test string input, then update the row to
 * reflect the new matching situation and if necessary add a new row to the
 * table
 *
 * \param   row     The index of the edited row
 * \param   column  The index of the edited column
 */
void MultilineTester::updateTestCase(int row, int column)
{
    // We're only interested in changes to input
    if(column != 0) return;

    updateRow(row);

    // If this was the last row, and it is now not empty, add a new row below it
    if((row+1) == table->rowCount() && !table->item(row, 0)->text().isEmpty())
        addRow();
}
