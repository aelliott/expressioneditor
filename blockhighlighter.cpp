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

#include "blockhighlighter.hpp"

BlockHighlighter::BlockHighlighter(QTextEdit *parent) : QSyntaxHighlighter(parent)
{
    factory = new RegexFactory();
    rx = factory->factory(QString());
}

void BlockHighlighter::highlightBlock(const QString &text)
{
    if(!rx->isValid())
        return;

    QTextCharFormat red;
    red.setForeground(Qt::red);
    QTextCharFormat blue;
    blue.setForeground(Qt::blue);
    int offset = 0;
    bool isRed = true;
    while((offset = rx->indexIn(text, offset)) != -1)
    {
        int length = rx->matchedLength();
        if(isRed)
            setFormat(offset, length, red);
        else
            setFormat(offset, length, blue);
        isRed = !isRed;
        offset += length;
    }
}

void BlockHighlighter::updateExpression(QString exp)
{
    rx = factory->factory(exp);
}

void BlockHighlighter::setRegexpFormat(int type)
{
    factory->setType(type);
    updateExpression(rx->getExpression());
}
