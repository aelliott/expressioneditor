/*!
 * \file
 *
 * Copyright (c) 2009,2010,2011 Alex Elliott <alex@alex-elliott.co.uk>
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

/*!
 * \brief   ExpressionHighlighter provides syntax highlighting for
 *          regular expressions
 *
 * Regular expressions are highlighted by multi-pass pattern matching
 * heuristics, fittingly perhaps implemented with regular expressions.
 */
class ExpressionHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit ExpressionHighlighter(QTextEdit *parent = 0);
    void highlightBlock(const QString &text);

private:
    //! Vector keeping track of all escaped characters (such as "\.")
    QVector<int> _escapedChars;

    //! Vector keeping track of all character ranges
    QVector<int> _characterRanges;
};

#endif // EXPRESSIONHIGHLIGHTER_HPP
