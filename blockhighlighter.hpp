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
#ifndef BLOCKHIGHLIGHTER_HPP
#define BLOCKHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include "regexfactory.hpp"

/*!
 * \brief This class highlights all matched sections of a block of text
 *        against the current regular expression.
 *
 * The class uses the current defined regular expression type, and the current
 * regular expression to highlight all matches within the QTextEdit containing
 * the block of text we are using to test against.
 */
class BlockHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit BlockHighlighter(RegexFactory *factory, QTextEdit *parent = 0);
    ~BlockHighlighter();
    void highlightBlock(const QString &text);

public slots:
    void updateExpression(QString exp);

private:
    RegexFactory *_factory;
    QString _pattern;
};

#endif // BLOCKHIGHLIGHTER_HPP
