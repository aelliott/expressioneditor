/*!
 * \file
 *
 * Copyright (c) 2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "testinputswidget.hpp"

TestInputsWidget::TestInputsWidget(QWidget *parent)
    : QTableWidget(parent)
    , _factory(0)
    , _expression("")
{
    setColumnCount(4);
    addTestRows(4);

    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateRows(QTableWidgetItem*)));
}

void TestInputsWidget::addTestRows(int rows)
{
    // Simple convenience, add n rows
    for(int i = 0; i < rows; ++i)
        addTestRow();
}

void TestInputsWidget::addTestRow()
{
    // Get a new row
    setRowCount(rowCount()+1);

    // Only the first item is editable, the rest are application controlled
    for(int i = 0; i < 4; ++i)
    {
        // Editable first column, special case
        if(i == 0)
        {
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable
                           | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled
                           | Qt::ItemIsDragEnabled);
            setItem(rowCount()-1, i, item);
            continue;
        }

        // General case, application editable only
        QTableWidgetItem *newItem = new QTableWidgetItem("");
        newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        setItem(rowCount()-1, i, newItem);
    }
}

void TestInputsWidget::updateRows(QTableWidgetItem *item)
{
    // Only update results when the item that has changed is an input
    if(item->column() == 0)
        updateResults();
}

void TestInputsWidget::updateResults()
{
    // Ensure we are ready to proceed
    if(_factory == 0)
        return;

    RegexBase *regexp = _factory->regexpEngine(_expression);

    // If it's invalid do nothing
    // NOTE: In the future it would probably make more sense if this cleared
    // the current results
    if(!regexp->isValid())
        return;

    for(int i = 0; i < rowCount(); ++i)
    {
        // If there is no item here, don't segfault, that is generally bad
        if(item(i,0) == 0)
            continue;

        QString input = item(i, 0)->text();
        if(!input.isEmpty())
        {
            bool exact = regexp->exactMatch(input);
            int partial = regexp->indexIn(input);

            if(exact)
            {
                item(i, 1)->setText("Exact Match");
                item(i, 2)->setText("0");
            }

            if(!exact && partial > -1)
            {
                item(i, 1)->setText("Partial Match");
                item(i, 2)->setText(QVariant(partial).toString());
            }

            if(exact || partial > -1)
            {
                // If it's an exact match run it again to make sure we caught
                // everything for the capture groups
                if(exact)
                    regexp->exactMatch(input);

                QStringList matches = regexp->capturedTexts();
                QString matchString = "";
                for(int j = 0; j < matches.length(); ++j)
                {
                    matchString += QString("[") + QVariant(j).toString()
                                + "] " + matches.at(j);
                    if(j != (matches.length()-1))
                        matchString += QString(", \n");
                }
                item(i, 3)->setText(matchString);
            }
            else
            {
                item(i, 1)->setText("No Match");
                item(i, 2)->setText("N/A");
                item(i, 3)->setText("");
            }
        }

        resizeRowToContents(i);
    }

    // Also, if there is text in the last row insert a new one so people
    // can continue to provide test inputs
    if(item(rowCount()-1, 0) != 0)
        setRowCount(rowCount()+1);
}

void TestInputsWidget::setRegexFactory(RegexFactory *factory)
{
    _factory = factory;
}

void TestInputsWidget::updateExpression(QString expression)
{
    _expression = expression;
    updateResults();
}
