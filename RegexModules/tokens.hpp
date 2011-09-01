/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#ifndef TOKENS_HPP
#define TOKENS_HPP

/*!
 * This enum defines constants for each required regular expression token
 */
enum RegexpToken
{
    // Basic regexp features
    T_LITERAL, // abcde
    T_ALTERNATION, // | or \| in emacs
    T_GROUPING_OPEN,  // ( or \( in BRE
    T_GROUPING_CLOSE, // ) or \) in BRE
    T_REPEAT_ZERO_OR_ONE, // ?
    T_REPEAT_ANY_NUMBER,  // *
    T_REPEAT_ONE_OR_MORE, // +
    T_REPEAT_SPECIFIED, // {m,n} or \{m,n\} in BRE
    T_ANY_CHARACTER, // .
    T_BRACKET_EXPRESSION_OPEN,  // [
    T_BRACKET_EXPRESSION_CLOSE, // ]
    T_BRACKET_EXPRESSION_RANGE, // a-z A-Z 0-9
    T_NEGATED_BRACKET_EXPRESSION_OPEN, // [^
    T_STARTING_POSITION, // ^
    T_ENDING_POSITION, // $
    T_BACKREFERENCE, // \0 ... \9

    // Further regexp features
    T_REVERSED_CAPTURING_GROUPING_OPEN, // (?:
    T_NAMED_GROUPING_OPEN, // (?P<name> or (?<name> or (?'name'
    T_COMMENT_OPEN, // (?#
    T_COMMENT_CLOSE, // )
    T_ATOMIC_MATCH_OPEN, // (?>
    T_ATOMIC_MATCH_CLOSE, // )
    T_POSITIVE_LOOKAHEAD_ASSERTION_OPEN, // (?=
    T_NEGATIVE_LOOKAHEAD_ASSERTION_OPEN, // (?!
    T_POSITIVE_LOOKBEHIND_ASSERTION_OPEN, // (?<=
    T_NEGATIVE_LOOKBEHIND_ASSERTION_OPEN, // (?<!
    T_ASSERTION_CLOSE, // )
    T_CONDITIONAL_OPEN, // (?
    T_CONDITIONAL_THEN, // after the "if" portion
    T_CONDITIONAL_ELSE, // | after the "then" portion
    T_CONDITIONAL_CLOSE, // )
    T_NAMED_BACKREFERENCE, // (?P=name) or \g<name> or \g{name} or \g<name> or \g'name' or \k<name> or \k'name'
    T_REPEAT_ZERO_OR_ONE_NONGREEDY, // ??
    T_REPEAT_ANY_NUMBER_NONGREEDY, // *?
    T_REPEAT_ONE_OR_MORE_NONGREEDY, // +?
    T_REPEAT_SPECIFIED_NONGREEDY, // {m,n}?
    T_REPEAT_ZERO_OR_ONE_POSESSIVE, // ?+
    T_REPEAT_ANY_NUMBER_POSESSIVE, // *+
    T_REPEAT_ONE_OR_MORE_POSESSIVE, // ++
    T_REPEAT_SPECIFIED_POSESSIVE, // {m,n}+
    T_QUOTE_SEQUENCE_OPEN, // \Q
    T_QUOTE_SEQUENCE_CLOSE, // \E
    T_FIRST_MATCHING_POSITION, // \G
    T_START_OF_STRING, // \A \`
    T_END_OF_STRING, // \Z \'
    T_END_OF_STRING_WITH_CLOSING_EOL, // \z

    // POSIX-style character classes
    T_ALNUM, // [:alnum:]
    T_WORD,  // [:word:]  \w
    T_ALPHA, // [:alpha:]
    T_BLANK, // [:blank:]
    T_CNTRL, // [:cntrl:]
    T_DIGIT, // [:digit:] \d
    T_GRAPH, // [:graph:]
    T_LOWER, // [:lower:] \l \L
    T_PRINT, // [:print:]
    T_PUNCT, // [:punct:]
    T_SPACE, // [:space:] \s
    T_UPPER, // [:upper:] \u \U
    T_XDIGIT, // [:xdigit:]

    // Perl-style character classes
    T_NOT_WORD, // \W
    T_NOT_DIGIT, // \D
    T_NOT_SPACE, // \S
    T_WORD_BOUNDARY, // \b
    T_NOT_WORD_BOUNDARY, // \B
    T_HORIZONTAL_WHITESPACE, // \h
    T_NOT_HORIZONTAL_WHITESPACE, // \H
    T_VERTICAL_WHITESPACE, // \v
    T_NOT_VERTICAL_WHITESPACE, // \V
    T_UNICODE_PROPERTY, // \p{Unicode Property Name} or \P{Unicode Property Name}

    // Special character matches
    T_BELL, // \a
    T_BACKSPACE, // \b
    T_ESCAPE, // \e
    T_FORM_FEED, // \f
    T_LINE_FEED, // \n
    T_CARRIAGE_RETURN, // \r
    T_HORIZONTAL_TAB, // \t
    T_VERTICAL_TAB, // \v
    T_ASCII_CONTROL_CHAR, // \cA ... \cZ
    T_UNICODE_NEWLINE, // \R
    T_BYTE, // \C
    T_OCTAL_CHAR, // \ooo or \0ooo
    T_HEXADECIMAL_CHAR, // \xHH or \xHHHH or \x{HHHH}
    T_UNICODE_CHAR, // \uHHHH or \UHHHHHHHH
    T_UNICODE_NAMED_CHAR, // \N{Unicode Character Name}
    T_GRAPHEME_CLUSTER, // \X

    // Behaviour flags
    T_FLAGS_OPEN, // (?
    T_FLAGS_CLOSE, // )
    T_FLAGS_NEGATION, // -

    // ICU, PCRE & Perl flags
    T_FLAG_CASELESS, // i
    T_FLAG_DOTALL, // s
    T_FLAG_MULTILINE, // m
    T_FLAG_EXTENDED, // x

    // ICU-specific flags
    T_FLAG_UWORD, // w

    // PCRE-specific flags
    T_FLAG_PCRE_EXTRA, // X
    T_FLAG_ANCHORED, // A
    T_FLAG_UNGREEDY, // U

    // Perl-specific flags
    T_FLAG_PRESERVE_MATCH, // p
    T_FLAG_GLOBAL_MATCH, // g
    T_FLAG_KEEP_CURRENT_POSITION, // c
    T_FLAG_LOCALE_RULES, // l
    T_FLAG_UNICODE_RULES, // u
    T_FLAG_UNICODE_RULES_ASCII_ONLY, // a
    T_FLAG_DEFAULT_RULES, // d

    // Final catch-all
    T_ERROR
};

#endif // TOKENS_HPP
