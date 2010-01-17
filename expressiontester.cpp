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

#include "expressiontester.hpp"

ExpressionTester::ExpressionTester(QWidget *parent) : QWidget(parent)
{
    factory = new RegexFactory();
    rx = factory->factory();

    mainLayout = new QVBoxLayout(this);

    QLabel *testHeading = new QLabel(tr("Test Inputs:"), this);

    table = new QTableWidget(0, 4, this);
    QStringList headings;
    headings << "Input" << "Match" << "Index" << "Captured Text";
    table->setAlternatingRowColors(true);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setHorizontalHeaderLabels(headings);
        connect(table, SIGNAL(cellChanged(int,int)), this, SLOT(updateTestCase(int,int)));

    for(int i = 0; i < ExpressionTester::initialRows; ++i)
        addRow();

    mainLayout->addWidget(testHeading);
    mainLayout->addWidget(table);
}

void ExpressionTester::addRow()
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

QString ExpressionTester::getExpression()
{
    return rx->getExpression();
}

QStringList ExpressionTester::getTestStrings()
{
    QStringList testStrings;
    for(int i = 0; i < table->rowCount(); ++i)
        if(!table->item(i, 0)->text().isEmpty())
            testStrings.push_back(table->item(i, 0)->text());
    return testStrings;
}

/**
 * Public slots
 */
void ExpressionTester::updateExpression(QString exp)
{
    delete rx;
    rx = factory->factory(exp);
    for(int i = 0; i < table->rowCount(); ++i)
        updateRow(i);
}

void ExpressionTester::updateRow(int row)
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

void ExpressionTester::addTestString(QString testString)
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

void ExpressionTester::setFormat(int type)
{
    factory->setType(type);
    updateExpression(rx->getExpression());
}

/**
 * Private slots
 */
void ExpressionTester::updateTestCase(int row, int column)
{
    // We're only interested in changes to input
    if(column != 0) return;

    updateRow(row);

    if((row+1) == table->rowCount() && !table->item(row, 0)->text().isEmpty())
        addRow();
}
