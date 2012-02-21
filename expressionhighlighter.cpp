/*!
 * \file
 *
 * Copyright (c) 2009-2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "expressionhighlighter.hpp"

/*!
 * Creates an ExpressionHighlighter highlighting the provided QTextEdit
 *
 * \param   parent  The QTextEdit to highlight
 */
ExpressionHighlighter::ExpressionHighlighter(RegexFactory *factory, QTextEdit *parent)
    : QSyntaxHighlighter(parent)
    , _factory(factory)
{
}

/*!
 * Reimplemented method, highlights blocks of the regexp
 *
 * \param   text    The block of text to highlight
 */
void ExpressionHighlighter::highlightBlock(const QString &text)
{
    // Set the general format
    QTextCharFormat normal;
    normal.setForeground(Qt::black);
    setFormat(0, text.length(), normal);

    if(_factory == 0)
        return;

    Parser *parser = _factory->regexpParser();
    parser->parse(text);

    // Escaped characters
    QTextCharFormat escapedFormat;
    escapedFormat.setForeground(Qt::darkGray);
    escapedFormat.setFontWeight(QFont::Bold);
    // Errors (T_ERROR)
    QTextCharFormat errorFormat;
    errorFormat.setForeground(Qt::red);
    errorFormat.setBackground(QColor(255, 0, 0, 50));
    // Special characters
    QTextCharFormat specialFormat;
    specialFormat.setForeground(Qt::blue);
    // Curly braces and bracket expressions
    QTextCharFormat braceFormat;
    braceFormat.setForeground(Qt::darkGreen);
    // Parentheses
    QTextCharFormat parenFormat;
    parenFormat.setForeground(Qt::darkYellow);
    // Repeat format
    QTextCharFormat repeatFormat;
    repeatFormat.setForeground(Qt::darkMagenta);

    std::vector<Token *> tokens = parser->tokens();
    std::vector<Token *>::iterator iter;
    int pos = 0;
    for(iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        Token *token = *iter;
        QString value = token->value();
        Q_ASSERT((pos + value.length()) <= text.length());
        switch(token->type())
        {
        case T_WORD:
        case T_NOT_WORD:
        case T_DIGIT:
        case T_NOT_DIGIT:
        case T_SPACE:
        case T_NOT_SPACE:
            setFormat(pos, value.length(), escapedFormat);
            break;
        case T_ALTERNATION:
        case T_STARTING_POSITION:
        case T_ENDING_POSITION:
        case T_ANY_CHARACTER:
        case T_BELL:
        case T_BACKSPACE:
        case T_ESCAPE:
        case T_FORM_FEED:
        case T_LINE_FEED:
        case T_CARRIAGE_RETURN:
        case T_HORIZONTAL_TAB:
        case T_VERTICAL_TAB:
        case T_ASCII_CONTROL_CHAR:
        case T_UNICODE_NEWLINE:
        case T_BYTE:
        case T_OCTAL_CHAR:
        case T_HEXADECIMAL_CHAR:
        case T_UNICODE_CHAR:
        case T_UNICODE_NAMED_CHAR:
        case T_GRAPHEME_CLUSTER:
            setFormat(pos, value.length(), specialFormat);
            break;
        case T_BRACKET_EXPRESSION_OPEN:
        case T_NEGATED_BRACKET_EXPRESSION_OPEN:
        case T_BRACKET_EXPRESSION_CLOSE:
            setFormat(pos, value.length(), braceFormat);
            break;
        case T_GROUPING_OPEN:
        case T_REVERSED_CAPTURING_GROUPING_OPEN:
        case T_GROUPING_CLOSE:
            setFormat(pos, value.length(), parenFormat);
            break;
        case T_REPEAT_ZERO_OR_ONE:
        case T_REPEAT_ANY_NUMBER:
        case T_REPEAT_ONE_OR_MORE:
        case T_REPEAT_ZERO_OR_ONE_NONGREEDY:
        case T_REPEAT_ANY_NUMBER_NONGREEDY:
        case T_REPEAT_ONE_OR_MORE_NONGREEDY:
        case T_REPEAT_ZERO_OR_ONE_POSSESSIVE:
        case T_REPEAT_ANY_NUMBER_POSSESSIVE:
        case T_REPEAT_ONE_OR_MORE_POSSESSIVE:
            setFormat(pos, value.length(), repeatFormat);
            break;
        case T_REPEAT_SPECIFIED:
        case T_REPEAT_SPECIFIED_NONGREEDY:
        case T_REPEAT_SPECIFIED_POSSESSIVE:
            setFormat(pos, 1, braceFormat);
            setFormat(pos + value.length() - 1, 1, braceFormat);
            break;
        case T_ERROR:
            setFormat(pos, value.length(), errorFormat);
            break;
        default:
            setFormat(pos, value.length(), normal);
        }

        pos += value.length();
    }

    delete parser;
}
