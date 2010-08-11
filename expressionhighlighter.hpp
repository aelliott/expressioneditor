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
 * \brief   ExpressionHighlighter provides syntax highlighting for
 *          regular expressions
 *
 * Regular expressions are highlighted by multi-pass pattern matching
 * heuristics, fittingly perhaps implemented with regular expressions.
 */

#ifndef EXPRESSIONHIGHLIGHTER_HPP
#define EXPRESSIONHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include <QStringList>
#include <QString>
#include <QRegExp>
#include <QTextCharFormat>
#include <QVector>
#include <QFont>
#include <QDebug>

class ExpressionHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT;

public:
    //! Creates an ExpressionHighlighter highlighting the provided QTextEdit
    explicit ExpressionHighlighter(QTextEdit *parent = 0);

    //! Reimplemented method, highlights blocks of the regexp
    void highlightBlock(const QString &text);

private:
    //! Vector keeping track of all escaped characters \.
    QVector<int> escapedChars;

    //! Vector keeping track of all character ranges
    QVector<int> characterRanges;
};

#endif // EXPRESSIONHIGHLIGHTER_HPP
