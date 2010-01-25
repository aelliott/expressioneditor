/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2010 Alex Elliott <alex@alex-elliott.co.uk>
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

#ifndef BLOCKHIGHLIGHTER_HPP
#define BLOCKHIGHLIGHTER_HPP

#include <QSyntaxHighlighter>
#include "regexfactory.hpp"

class BlockHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT;

public:
    explicit BlockHighlighter(QTextEdit *parent = 0);
    void highlightBlock(const QString &text);

public slots:
    void updateExpression(QString exp);
    void setRegexpFormat(int type);

private:
    RegexFactory *factory;
    RegexBase *rx;
};

#endif // BLOCKHIGHLIGHTER_HPP
