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
/*!
 * \brief   Contains expressioneditor's testing widgets
 *
 * This widget subclasses QTabWidget and provides a testing widget in
 * each tab for different test criteria.
 */

#ifndef EXPRESSIONTESTER_HPP
#define EXPRESSIONTESTER_HPP

#include <QTabWidget>
#include "multilinetester.hpp"
#include "blocktester.hpp"
#include "searchreplacetester.hpp"


class ExpressionTester : public QTabWidget
{
    Q_OBJECT;

public:
    //! Creates a new ExpressionTester
    explicit ExpressionTester(QWidget *parent = 0);

    //! Getter, gets the expression being tested against
    QString getExpression();

    //! Getter, retrieves the test strings used in testing
    QStringList getTestStrings();

public slots:
    //! Setter, sets the expression to the new content
    void updateExpression(QString exp);

    //! Adds a test string to the testing widget
    void addTestString(QString testString);

    //! Setter, updates the regexp format in use
    void setRegexpFormat(int type);

private:
    //! Multi-input testing widget, provides detail on what matches and doesn't
    MultilineTester *multiline;

    //! Highlights all instances of matches within a block of text
    BlockTester *block;

    //! Shows the results of the expression used as a search/replace
    SearchReplaceTester *searchReplace;
};

#endif // EXPRESSIONTESTER_HPP
