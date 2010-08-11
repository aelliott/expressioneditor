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
 * \brief   The ExpressionEditor class is the main editing widget for
 *          the application, containing the visualisation, text input
 *          and testing widgets.
 *
 * This class contains the main elements of expressioneditor and marshals
 * communications between the various segments.
 */

#ifndef EXPRESSIONEDITOR_HPP
#define EXPRESSIONEDITOR_HPP

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QSplitter>
#include "graphicaleditor.hpp"
#include "expressiontester.hpp"
#include "expressionhighlighter.hpp"

class ExpressionEditor : public QWidget
{
    Q_OBJECT

public:
    //! Creates a new ExpressionEditor widget
    explicit ExpressionEditor(QWidget *parent = 0);

    //! Get the expression that is currently in use
    QString getExpression();

    //! Get the test strings from the testing widget
    QStringList getTestStrings();

protected:
    //! Reimplemented resize handler, triggers a height update of the regexp text input
    void resizeEvent(QResizeEvent *event);

public slots:
    //! Slots for any updates to the regular expression
    void updateExpression();
    //! Slots for any updates to the regular expression
    void updateExpression(QString regex);

    //! Adds a test string to the expression test widget
    void addTestString(QString testString);

    //! Sets the regexp format
    void setRegexpFormat(int type);

    //! Produces a QPixmap of the expression visualisation to export to PNG
    QPixmap exportToImage();

private:
    //! Updates the height of the regexp text input to fit the expression.
    void updateInputHeight();
    QVBoxLayout *mainLayout;
    QSplitter *splitter;
    QVBoxLayout *subLayout;
    QTextEdit *expressionInput;
    QLabel *validIndicator;
    ExpressionTester *tester;
    ExpressionHighlighter *highlighter;
    GraphicalEditor *graphicalEditor;
};

#endif // EXPRESSIONEDITOR_HPP
