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

#include "expressionhighlighter.hpp"

ExpressionHighlighter::ExpressionHighlighter(QTextEdit *parent) : QSyntaxHighlighter(parent)
{
}

void ExpressionHighlighter::highlightBlock(const QString &text)
{
    // Set the general format, monospace in black.
    //QFont highlightedFont("Liberation Mono", 9);

    QTextCharFormat normal;
    normal.setForeground(Qt::black);
    //normal.setFont(highlightedFont);
    setFormat(0, text.size(), normal);

    // A format for errors found
    QTextCharFormat errorFormat;
    errorFormat.setForeground(Qt::red);
    //errorFormat.setFont(highlightedFont);

    // Clear vectors
    escapedChars.clear();
    characterRanges.clear();

    // So, the idea is we collect all of the characters that are
    // escaped with a \ and keep track of the indexes which are
    // because of that not special characters, we can then check
    // other characters to see if they are escaped, and if not
    // parse them normally.
    QStringList specialchars;
    specialchars << "\\" << "[" << "]" << "(" << ")" << "*" << "^" << "$" << "." << "|" << "?" << "+" << "{" << "}";

    QTextCharFormat escapedFormat;
    escapedFormat.setForeground(Qt::darkGray);
    //escapedFormat.setFont(highlightedFont);
    escapedFormat.setFontWeight(QFont::Bold);

    QString pattern = QString("\\\\\\") + specialchars.join("|\\\\\\");
    QRegExp escaped(pattern);

    int startOffset = text.indexOf(escaped);
    while(startOffset >= 0)
    {
        setFormat(startOffset, 2, escapedFormat);
        escapedChars.push_back(startOffset);
        escapedChars.push_back(++startOffset);
        startOffset = text.indexOf(escaped, ++startOffset);
    }

    // Now that we have identified the escaped characters, we
    // should identify character ranges since other characters
    // inside those are also not special.
    QTextCharFormat braceFormat;
    braceFormat.setForeground(Qt::darkGreen);
    //braceFormat.setFont(highlightedFont);
    //braceFormat.setFontWeight(QFont::Bold);

    QRegExp bracePattern("\\[|\\]");
    int openingSquareBraces = 0;
    int closingSquareBraces = 0;
    int lastOpeningBrace = -1;
    setCurrentBlockState(0);
    startOffset = text.indexOf(bracePattern, 0);
    while(startOffset >= 0)
    {
        if(!escapedChars.contains(startOffset) && !characterRanges.contains(startOffset))
        {
            if(QString(text.at(startOffset)) == "[")
            {
                if(currentBlockState() == 0)
                {
                    ++openingSquareBraces;
                    lastOpeningBrace = startOffset;
                    setCurrentBlockState(1);
                    setFormat(startOffset, 1, braceFormat);
                }
                // if the block state was 1 then it's a literal [
            }
            if(QString(text.at(startOffset)) == "]")
            {
                if(currentBlockState() == 1)
                {
                    ++closingSquareBraces;
                    // we can set the range of the character set
                    // here from lastOpeningBrace to startOffset.
                    for(int i = lastOpeningBrace; i <= startOffset; ++i)
                        characterRanges.push_back(i);
                    setCurrentBlockState(0);
                    setFormat(startOffset, 1, braceFormat);
                }
                else if(currentBlockState() == 0)
                {
                    // Unmatched closing brace
                    setFormat(startOffset, 1, errorFormat);
                }
            }
        }
        startOffset = text.indexOf(bracePattern, ++startOffset);
    }

    if(openingSquareBraces != closingSquareBraces)
    {
        // Unmatched opening brace
        setFormat(lastOpeningBrace, 1, errorFormat);
    }

    // Next lets find the parentheses in the pattern
    QTextCharFormat parenFormat;
    parenFormat.setForeground(Qt::darkYellow);
    //parenFormat.setFont(highlightedFont);
    //parenFormat.setFontWeight(QFont::Bold);

    QRegExp parenPattern("\\(|\\)");
    int openingParens = 0;
    int closingParens = 0;
    int lastOpeningParen = -1;
    setCurrentBlockState(0);
    startOffset = text.indexOf(parenPattern, 0);
    while(startOffset >= 0)
    {
        if(!escapedChars.contains(startOffset))
        {
            if(QString(text.at(startOffset)) == "(")
            {
                ++openingParens;
                lastOpeningParen = startOffset;
                setCurrentBlockState(currentBlockState()+1);
                setFormat(startOffset, 1, parenFormat);
            }
            if(QString(text.at(startOffset)) == ")")
            {
                if(currentBlockState() > 0)
                {
                    ++closingParens;
                    setCurrentBlockState(currentBlockState()-1);
                    setFormat(startOffset, 1, parenFormat);
                }
                else if(currentBlockState() == 0)
                {
                    // Unmatched closing parenthesis
                    setFormat(startOffset, 1, errorFormat);
                }
            }
        }
        startOffset = text.indexOf(parenPattern, ++startOffset);
    }

    if(openingParens != closingParens)
    {
        // Unmatched opening parenthesis
        setFormat(lastOpeningParen, 1, errorFormat);
    }

    // Highlight the specified number of repeats {n} and {n,n}
    QTextCharFormat repeatFormat;
    repeatFormat.setForeground(Qt::darkMagenta);
    //repeatFormat.setFont(highlightedFont);

    QRegExp repeatPattern("\\{|\\}");
    startOffset = text.indexOf(repeatPattern, 0);
    while(startOffset >= 0)
    {
        if(!escapedChars.contains(startOffset) && !characterRanges.contains(startOffset))
        {
            if(QString(text.at(startOffset)) == "{")
            {
                QRegExp rx("\\{\\d+,(\\d+)?\\}|\\{\\d+\\}");
                if(text.indexOf(rx, startOffset-1) == startOffset)
                {
                    setFormat(startOffset, 1, repeatFormat);
                    if(text.indexOf(",", startOffset+1) != -1 && text.indexOf(",", startOffset+1) < text.indexOf("}", startOffset+1))
                    {
                        startOffset = text.indexOf(",", ++startOffset);
                        setFormat(startOffset, 1, repeatFormat);
                    }
                    startOffset = text.indexOf("}", ++startOffset);
                    setFormat(startOffset, 1, repeatFormat);
                }
                else
                    setFormat(startOffset, 1, errorFormat);
            }
            else
                setFormat(startOffset, 1, errorFormat);
        }
        startOffset = text.indexOf(repeatPattern, ++startOffset);
    }

    // Locate the remaining special characters and bold them
    QTextCharFormat specialFormat;
    specialFormat.setForeground(Qt::blue);
    //specialFormat.setFont(highlightedFont);

    QStringList remaining;
    remaining << "*" << "^" << "$" << "." << "|" << "?" << "+";
    pattern = QString("\\") + remaining.join("|\\");
    QRegExp remainingPattern(pattern);
    startOffset = text.indexOf(remainingPattern, 0);
    while(startOffset >= 0)
    {
        if(!escapedChars.contains(startOffset) && !characterRanges.contains(startOffset))
            setFormat(startOffset, 1, specialFormat);
        startOffset = text.indexOf(remainingPattern, ++startOffset);
    }
}
