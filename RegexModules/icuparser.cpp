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
#include "icuparser.hpp"

IcuParser::IcuParser(QString pattern, QObject *parent)
    : Parser(pattern, parent)
{
    _syntax.insert(std::pair<RegexpToken, QString>(T_LITERAL,
                                                   "([^\\\\[\\]()|?*+{}\\.^$]|\\\\[^a-zA-Z0-9])+"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_ALTERNATION,
                   "\\|"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_GROUPING_OPEN,
                   "\\("));
    _syntax.insert(std::pair<RegexpToken, QString>(T_GROUPING_CLOSE,
                   "\\)"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ZERO_OR_ONE,
                   "\\?"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ANY_NUMBER,
                   "\\*"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ONE_OR_MORE,
                   "\\+"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_SPECIFIED,
                   "\\{\\d+\\}|\\{\\d+,\\}|\\{,\\d+\\}|\\{\\d+,\\d+\\}"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_ANY_CHARACTER,
                   "\\."));
    _syntax.insert(std::pair<RegexpToken, QString>(T_BRACKET_EXPRESSION_OPEN,
                   "\\["));
    _syntax.insert(std::pair<RegexpToken, QString>(T_BRACKET_EXPRESSION_CLOSE,
                   "\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_BRACKET_EXPRESSION_RANGE,
                   "[a-z]-[a-z]|[A-Z]-[A-Z]|\\d-\\d"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NEGATED_BRACKET_EXPRESSION_OPEN,
                   "\\[\\^"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_STARTING_POSITION,
                   "\\^"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_ENDING_POSITION,
                   "\\$"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_BACKREFERENCE,
                   "\\\\\\d"));

    _syntax.insert(std::pair<RegexpToken, QString>(T_REVERSED_CAPTURING_GROUPING_OPEN,
                   "\\(\\?:"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NAMED_GROUPING_OPEN,
                   "\\(\\?<[\\w\\d]+>|\\(\\?P<[\\w\\d]+>|\\(\\?P'[\\w\\d]+'"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_COMMENT_OPEN,
                   "\\(\\?#"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_COMMENT_CLOSE,
                   "\\)"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_POSITIVE_LOOKAHEAD_ASSERTION_OPEN,
                   "\\(\\?="));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NEGATIVE_LOOKAHEAD_ASSERTION_OPEN,
                   "\\(\\?!"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_POSITIVE_LOOKBEHIND_ASSERTION_OPEN,
                   "\\(\\?<="));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NEGATIVE_LOOKBEHIND_ASSERTION_OPEN,
                   "\\(\\?<!"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_ASSERTION_CLOSE,
                   "\\)"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NAMED_BACKREFERENCE,
                   "\\(\\?<P=[\\w\\d]+>\\)"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ZERO_OR_ONE_NONGREEDY,
                   "\\?\\?"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ANY_NUMBER_NONGREEDY,
                   "\\*\\?"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ONE_OR_MORE_NONGREEDY,
                   "\\+\\?"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_SPECIFIED_NONGREEDY,
                   "\\{(\\d+|\\d+,|,\\d+|\\d+,\\d+)\\}\\?"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ZERO_OR_ONE_POSSESSIVE,
                   "\\?\\+"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ANY_NUMBER_POSSESSIVE,
                   "\\*\\+"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_ONE_OR_MORE_POSSESSIVE,
                   "\\+\\+"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_REPEAT_SPECIFIED_POSSESSIVE,
                   "\\{(\\d+|\\d+,|,\\d+|\\d+,\\d+)\\}\\+"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_QUOTE_SEQUENCE_OPEN,
                   "\\\\Q"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_QUOTE_SEQUENCE_CLOSE,
                   "\\\\E"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FIRST_MATCHING_POSITION,
                   "\\\\G"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_START_OF_STRING,
                   "\\\\[A`]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_END_OF_STRING,
                   "\\\\[Z']"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_END_OF_STRING_WITH_CLOSING_EOL,
                   "\\\\z"));

    _syntax.insert(std::pair<RegexpToken, QString>(T_ALNUM,
                   "\\[\\[:alnum:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_WORD,
                   "\\\\w|\\[\\[:word:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_WORD,
                   "\\\\W"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_ALPHA,
                   "\\[\\[:alpha:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_BLANK,
                   "\\[\\[:blank:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_CNTRL,
                   "\\[\\[:cntrl:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_DIGIT,
                   "\\\\d|\\[\\[:digit:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_DIGIT,
                   "\\\\D"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_GRAPH,
                   "\\[\\[:graph:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_LOWER,
                   "\\\\l|\\\\L|\\[\\[:lower:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_PRINT,
                   "\\[\\[:print:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_PUNCT,
                   "\\[\\[:punct:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_SPACE,
                   "\\\\s|\\[\\[:space:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_SPACE,
                   "\\\\S"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_UPPER,
                   "\\\\u|\\\\U|\\[\\[:upper:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_WORD_BOUNDARY,
                   "\\\\b"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_WORD_BOUNDARY,
                   "\\\\B"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_XDIGIT,
                   "\\[\\[:xdigit:\\]\\]"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_VERTICAL_WHITESPACE,
                   "\\\\v"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_VERTICAL_WHITESPACE,
                   "\\\\V"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_HORIZONTAL_WHITESPACE,
                   "\\\\h"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_HORIZONTAL_WHITESPACE,
                   "\\\\H"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_UNICODE_PROPERTY,
                   "\\\\(p|P)\\{[^}]*\\}"));

    _syntax.insert(std::pair<RegexpToken, QString>(T_BELL,
                   "\\\\a"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_BACKSPACE,
                   "\\\\b"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_ESCAPE,
                   "\\\\e"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FORM_FEED,
                   "\\\\f"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_LINE_FEED,
                   "\\\\n"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_HORIZONTAL_TAB,
                   "\\\\t"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_OCTAL_CHAR,
                   "\\\\[0-7]{3}"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_HEXADECIMAL_CHAR,
                   "\\\\x\\{([0-9a-f]{2}|[0-9a-f]{4})\\}|\\\\x([0-9a-f]{2}|[0-9a-f]{4})"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_UNICODE_CHAR,
                   "\\\\u\\{([0-9a-f]{4}|[0-9a-f]{8})\\}|\\\\u([0-9a-f]{4}|[0-9a-f]{8})"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_UNICODE_NAMED_CHAR,
                   "\\\\N\\{[^}]*\\}"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_GRAPHEME_CLUSTER,
                   "\\\\X"));

    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAGS_OPEN,
                   "\\(\\?"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAGS_CLOSE,
                   "\\)"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAGS_NEGATION,
                   "-"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAG_CASELESS,
                   "i"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAG_DOTALL,
                   "s"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAG_MULTILINE,
                   "m"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAG_EXTENDED,
                   "x"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_FLAG_UWORD,
                   "w"));
}

void IcuParser::handleToken(RegexpToken token)
{
    QRegExp rx;
    QRegExp characterClass;
    QRegExp bracketExpressionLiteral("[^\\\\[\\]()|?*+{}\\.$]|\\\\[^a-zA-Z0-9]");
    QRegExp bracketExpressionRange(_syntax[T_BRACKET_EXPRESSION_RANGE]);
    QRegExp flagClose;
    Token *openingToken;
    QString character;
    QString tmp;

    switch(token)
    {
    case T_LITERAL:
    case T_ALTERNATION:
    case T_ANY_CHARACTER:
    case T_STARTING_POSITION:
    case T_ENDING_POSITION:
    case T_BACKREFERENCE:
    case T_WORD:
    case T_NOT_WORD:
    case T_DIGIT:
    case T_NOT_DIGIT:
    case T_SPACE:
    case T_NOT_SPACE:
    case T_WORD_BOUNDARY:
    case T_NOT_WORD_BOUNDARY:
    case T_OCTAL_CHAR:
    case T_NAMED_BACKREFERENCE:
    case T_FIRST_MATCHING_POSITION:
    case T_START_OF_STRING:
    case T_END_OF_STRING:
    case T_END_OF_STRING_WITH_CLOSING_EOL:
    case T_ALNUM:
    case T_ALPHA:
    case T_BLANK:
    case T_CNTRL:
    case T_GRAPH:
    case T_LOWER:
    case T_PRINT:
    case T_PUNCT:
    case T_UPPER:
    case T_XDIGIT:
    case T_HORIZONTAL_WHITESPACE:
    case T_NOT_HORIZONTAL_WHITESPACE:
    case T_VERTICAL_WHITESPACE:
    case T_NOT_VERTICAL_WHITESPACE:
    case T_BELL:
    case T_BACKSPACE:
    case T_ESCAPE:
    case T_FORM_FEED:
    case T_LINE_FEED:
    case T_HORIZONTAL_TAB:
    case T_HEXADECIMAL_CHAR:
    case T_UNICODE_PROPERTY:
    case T_UNICODE_NEWLINE:
    case T_UNICODE_CHAR:
    case T_UNICODE_NAMED_CHAR:
    case T_GRAPHEME_CLUSTER:
        _tokens.push_back(new Token(token, _expression.mid(_pos, _matchLength)));
        _pos += _matchLength;
        break;
    case T_GROUPING_OPEN:
    case T_REVERSED_CAPTURING_GROUPING_OPEN:
    case T_NAMED_GROUPING_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        rx.setPattern(_syntax[T_GROUPING_CLOSE]);

        while(rx.indexIn(_expression, _pos) != _pos && _pos < _expression.length())
            handleToken(findMatch());

        if(rx.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_GROUPING_CLOSE, _expression.mid(_pos, 1)));
            _pos += 1;
        }
        else
            openingToken->setType(T_ERROR);
        break;
    case T_BRACKET_EXPRESSION_OPEN:
    case T_NEGATED_BRACKET_EXPRESSION_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        rx.setPattern(_syntax[T_BRACKET_EXPRESSION_CLOSE]);
        // Look for a "[]...]" or "[^]...]" including a literal close bracket in
        // the first position of the bracket expression
        if(rx.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_LITERAL, _expression.mid(_pos, rx.matchedLength())));
            _pos += rx.matchedLength();
        }

        while(rx.indexIn(_expression, _pos) != _pos && _pos < _expression.length())
        {
            bool matched = false;
            if(matched == false && bracketExpressionRange.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_BRACKET_EXPRESSION_RANGE, _expression.mid(_pos, bracketExpressionRange.matchedLength())));
                _pos += bracketExpressionRange.matchedLength();
            }

            if(matched == false && bracketExpressionLiteral.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_LITERAL, _expression.mid(_pos, bracketExpressionLiteral.matchedLength())));
                _pos += bracketExpressionLiteral.matchedLength();
            }

            characterClass.setPattern(_syntax[T_WORD]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_WORD, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            characterClass.setPattern(_syntax[T_NOT_WORD]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_NOT_WORD, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            characterClass.setPattern(_syntax[T_DIGIT]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_DIGIT, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            characterClass.setPattern(_syntax[T_NOT_DIGIT]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_NOT_DIGIT, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            characterClass.setPattern(_syntax[T_SPACE]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_SPACE, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            characterClass.setPattern(_syntax[T_NOT_SPACE]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_NOT_SPACE, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            characterClass.setPattern(_syntax[T_WORD_BOUNDARY]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_WORD_BOUNDARY, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            characterClass.setPattern(_syntax[T_NOT_WORD_BOUNDARY]);
            if(matched == false && characterClass.indexIn(_expression, _pos) == _pos)
            {
                matched = true;
                _tokens.push_back(new Token(T_NOT_WORD_BOUNDARY, _expression.mid(_pos, characterClass.matchedLength())));
                _pos += characterClass.matchedLength();
            }

            if(!matched)
            {
                _tokens.push_back(new Token(T_ERROR, _expression.mid(_pos, 1)));
                ++_pos;
            }
        }

        if(rx.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_BRACKET_EXPRESSION_CLOSE,
                                        _expression.mid(_pos, rx.matchedLength()))
                              );
            _pos += rx.matchedLength();
        }
        else
            openingToken->setType(T_ERROR);

        break;
    case T_POSITIVE_LOOKAHEAD_ASSERTION_OPEN:
    case T_NEGATIVE_LOOKAHEAD_ASSERTION_OPEN:
    case T_POSITIVE_LOOKBEHIND_ASSERTION_OPEN:
    case T_NEGATIVE_LOOKBEHIND_ASSERTION_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        rx.setPattern(_syntax[T_ASSERTION_CLOSE]);
        while(rx.indexIn(_expression, _pos) != _pos && _pos < _expression.length())
            handleToken(findMatch());

        if(rx.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_ASSERTION_CLOSE, _expression.mid(_pos, 1)));
            _pos += 1;
        }
        else
            openingToken->setType(T_ERROR);
        break;
    case T_REPEAT_ZERO_OR_ONE:
    case T_REPEAT_ANY_NUMBER:
    case T_REPEAT_ONE_OR_MORE:
    case T_REPEAT_SPECIFIED:
    case T_REPEAT_ZERO_OR_ONE_NONGREEDY:
    case T_REPEAT_ANY_NUMBER_NONGREEDY:
    case T_REPEAT_ONE_OR_MORE_NONGREEDY:
    case T_REPEAT_SPECIFIED_NONGREEDY:
    case T_REPEAT_ZERO_OR_ONE_POSSESSIVE:
    case T_REPEAT_ANY_NUMBER_POSSESSIVE:
    case T_REPEAT_ONE_OR_MORE_POSSESSIVE:
    case T_REPEAT_SPECIFIED_POSSESSIVE:
        switch(_tokens[_tokens.size()-1]->type())
        {
        case T_POSITIVE_LOOKAHEAD_ASSERTION_OPEN:
        case T_NEGATIVE_LOOKAHEAD_ASSERTION_OPEN:
        case T_POSITIVE_LOOKBEHIND_ASSERTION_OPEN:
        case T_NEGATIVE_LOOKBEHIND_ASSERTION_OPEN:
        case T_REPEAT_ZERO_OR_ONE:
        case T_REPEAT_ANY_NUMBER:
        case T_REPEAT_ONE_OR_MORE:
        case T_REPEAT_SPECIFIED:
        case T_REPEAT_ZERO_OR_ONE_NONGREEDY:
        case T_REPEAT_ANY_NUMBER_NONGREEDY:
        case T_REPEAT_ONE_OR_MORE_NONGREEDY:
        case T_REPEAT_SPECIFIED_NONGREEDY:
        case T_REPEAT_ZERO_OR_ONE_POSSESSIVE:
        case T_REPEAT_ANY_NUMBER_POSSESSIVE:
        case T_REPEAT_ONE_OR_MORE_POSSESSIVE:
        case T_REPEAT_SPECIFIED_POSSESSIVE:
        case T_GROUPING_OPEN:
        case T_REVERSED_CAPTURING_GROUPING_OPEN:
        case T_NAMED_GROUPING_OPEN:
            _tokens.push_back(new Token(T_ERROR, _expression.mid(_pos, _matchLength)));
            _pos += _matchLength;
            break;
        case T_LITERAL:
            // Requires a bit of extra work to separate the last character from
            // the literal
            character = _tokens[_tokens.size()-1]->value().right(1);
            tmp = _tokens[_tokens.size()-1]->value();
            if(tmp.size() > 1)
            {
                tmp.truncate(tmp.length() - 1);
                _tokens[_tokens.size()-1]->setValue(tmp);
                _tokens.push_back(new Token(T_LITERAL, character));
            }
        default:
            _tokens.push_back(new Token(token, _expression.mid(_pos, _matchLength)));
            _pos += _matchLength;
        }
        break;
    case T_COMMENT_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        // Comments contain one literal comment message lasting up until the
        // next closing paren
        rx.setMinimal(true);
        rx.setPattern(QString(".*(?=") + _syntax[T_COMMENT_CLOSE] + ")");
        if(rx.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_LITERAL, _expression.mid(_pos, rx.matchedLength())));
            _pos += rx.matchedLength();
        }

        rx.setPattern(_syntax[T_COMMENT_CLOSE]);
        if(rx.indexIn(_expression, _pos) != _pos)
            openingToken->setType(T_ERROR);
        else
        {
            _tokens.push_back(new Token(T_COMMENT_CLOSE, _expression.mid(_pos, rx.matchedLength())));
            _pos += rx.matchedLength();
        }
        break;
    case T_QUOTE_SEQUENCE_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        // Quote sequences are literal up until a closing \E
        rx.setMinimal(true);
        rx.setPattern(QString(".*(?=") + _syntax[T_QUOTE_SEQUENCE_CLOSE] + ")");
        if(rx.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_LITERAL, _expression.mid(_pos, rx.matchedLength())));
            _pos += rx.matchedLength();
        }

        rx.setPattern(_syntax[T_QUOTE_SEQUENCE_CLOSE]);
        if(rx.indexIn(_expression, _pos) != _pos)
            openingToken->setType(T_ERROR);
        else
        {
            _tokens.push_back(new Token(T_QUOTE_SEQUENCE_CLOSE, _expression.mid(_pos, rx.matchedLength())));
            _pos += rx.matchedLength();
        }
        break;
    case T_FLAGS_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        // Flag sections can contain a-zA-Z- characters and end with a close
        // paren, if we encounter anything else then we'll stop trying to match
        // it as a flag and mark the opening as an error
        rx.setMinimal(true);
        rx.setPattern(QString("[a-zA-Z-]*") + _syntax[T_FLAGS_CLOSE]);
        if(rx.indexIn(_expression, _pos) != _pos)
            openingToken->setType(T_ERROR);
        else
        {
            flagClose.setPattern(_syntax[T_FLAGS_CLOSE]);
            while(flagClose.indexIn(_expression, _pos) != _pos)
            {
                bool matched = false;

                rx.setPattern(_syntax[T_FLAGS_NEGATION]);
                if(!matched && rx.indexIn(_expression, _pos) == _pos)
                {
                    _tokens.push_back(new Token(T_FLAGS_NEGATION, _expression.mid(_pos, rx.matchedLength())));
                    _pos += rx.matchedLength();
                    matched = true;
                }

                rx.setPattern(_syntax[T_FLAG_CASELESS]);
                if(!matched && rx.indexIn(_expression, _pos) == _pos)
                {
                    _tokens.push_back(new Token(T_FLAG_CASELESS, _expression.mid(_pos, rx.matchedLength())));
                    _pos += rx.matchedLength();
                    matched = true;
                }

                rx.setPattern(_syntax[T_FLAG_DOTALL]);
                if(!matched && rx.indexIn(_expression, _pos) == _pos)
                {
                    _tokens.push_back(new Token(T_FLAG_DOTALL, _expression.mid(_pos, rx.matchedLength())));
                    _pos += rx.matchedLength();
                    matched = true;
                }

                rx.setPattern(_syntax[T_FLAG_MULTILINE]);
                if(!matched && rx.indexIn(_expression, _pos) == _pos)
                {
                    _tokens.push_back(new Token(T_FLAG_MULTILINE, _expression.mid(_pos, rx.matchedLength())));
                    _pos += rx.matchedLength();
                    matched = true;
                }

                rx.setPattern(_syntax[T_FLAG_EXTENDED]);
                if(!matched && rx.indexIn(_expression, _pos) == _pos)
                {
                    _tokens.push_back(new Token(T_FLAG_EXTENDED, _expression.mid(_pos, rx.matchedLength())));
                    _pos += rx.matchedLength();
                    matched = true;
                }

                rx.setPattern(_syntax[T_FLAG_UWORD]);
                if(!matched && rx.indexIn(_expression, _pos) == _pos)
                {
                    _tokens.push_back(new Token(T_FLAG_UWORD, _expression.mid(_pos, rx.matchedLength())));
                    _pos += rx.matchedLength();
                    matched = true;
                }

                if(!matched)
                {
                    _tokens.push_back(new Token(T_ERROR, _expression.mid(_pos, 1)));
                    ++_pos;
                }
            }

            _tokens.push_back(new Token(T_FLAGS_CLOSE, _expression.mid(_pos, flagClose.matchedLength())));
            _pos += flagClose.matchedLength();
        }
        break;
    default:
        qDebug() << "Unknown token at position " << _pos << ": " << token;
        qDebug() << "Value: " << _expression.mid(_pos, _matchLength);
        _tokens.push_back(new Token(T_ERROR, _expression.mid(_pos, _matchLength)));
        _pos += _matchLength;
    }
}
