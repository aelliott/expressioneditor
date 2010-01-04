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

#ifndef EXPRESSIONTESTER_HPP
#define EXPRESSIONTESTER_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegExp>
#include <QTableWidget>
#include <QString>
#include <QStringList>
#include <QHeaderView>
#include <QLabel>
#include <QDebug>
#include "regexfactory.hpp"

class ExpressionTester : public QWidget
{
Q_OBJECT
public:
    explicit ExpressionTester(QWidget *parent = 0);
    QString getExpression();
    QStringList getTestStrings();

signals:

public slots:
    void updateExpression(QString exp);
    void updateRow(int row);
    void addTestString(QString testString);

private:
    static const int initialRows = 4;
    void addRow();
    QVBoxLayout *mainLayout;
    RegexFactory *factory;
    RegexBase *rx;
    QTableWidget *table;

private slots:
    void updateTestCase(int row, int column);
};

#endif // EXPRESSIONTESTER_HPP
