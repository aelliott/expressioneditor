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
 * \brief   This testing widget allows the testing of a regular expression
 *          search and replace including the capability to reference captured
 *          groups in the replacement text
 */

#ifndef SEARCHREPLACETESTER_HPP
#define SEARCHREPLACETESTER_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include "blockhighlighter.hpp"
#include "regexfactory.hpp"

class SearchReplaceTester : public QWidget
{
    Q_OBJECT;

public:
    explicit SearchReplaceTester(QWidget *parent = 0);
    QString getText() const;

public slots:
    void updateExpression(QString exp);
    void updateReplacedText();
    void setText(QString testString);
    void setRegexpFormat(int newType);

private:
    QVBoxLayout *layout;
    QHBoxLayout *replaceLayout;
    QLabel *replaceLabel;
    QLineEdit *replaceInput;
    QSplitter *splitter;
    QTextEdit *testText;
    QTextEdit *replacedText;
    BlockHighlighter *highlighter;
    QString expression;
    int type;

};

#endif // SEARCHREPLACETESTER_HPP
