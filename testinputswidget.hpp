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
#ifndef TESTINPUTSWIDGET_HPP
#define TESTINPUTSWIDGET_HPP

#include <QTableWidget>
#include <QDebug>

#include "regexfactory.hpp"

class TestInputsWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit TestInputsWidget(QWidget *parent = 0);

    void addTestRows(int rows);
    void addTestRow();

public slots:
    void updateRows(QTableWidgetItem *item);
    void updateResults();

    void setRegexFactory(RegexFactory *factory);
    void updateExpression(QString expression);

private:
    RegexFactory *_factory;
    QString _expression;
};

#endif // TESTINPUTSWIDGET_HPP
