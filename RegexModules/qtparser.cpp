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
#include "qtparser.hpp"

QtParser::QtParser(QString pattern, QObject *parent)
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
                   "[a-zA-Z]-[a-zA-Z]|\\d-\\d"));
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
    _syntax.insert(std::pair<RegexpToken, QString>(T_POSITIVE_LOOKAHEAD_ASSERTION_OPEN,
                   "\\(\\?="));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NEGATIVE_LOOKAHEAD_ASSERTION_OPEN,
                   "\\(\\?!"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_ASSERTION_CLOSE,
                   "\\)"));

    _syntax.insert(std::pair<RegexpToken, QString>(T_WORD,
                   "\\\\w"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_WORD,
                   "\\\\W"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_DIGIT,
                   "\\\\d"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_DIGIT,
                   "\\\\D"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_SPACE,
                   "\\\\s"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_SPACE,
                   "\\\\S"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_WORD_BOUNDARY,
                   "\\\\b"));
    _syntax.insert(std::pair<RegexpToken, QString>(T_NOT_WORD_BOUNDARY,
                   "\\\\B"));

    _syntax.insert(std::pair<RegexpToken, QString>(T_OCTAL_CHAR,
                   "\\\\[0-7]{3}"));
}

void QtParser::handleToken(RegexpToken token)
{
    QRegExp groupingClose(_syntax[T_GROUPING_CLOSE]);
    QRegExp assertionClose(_syntax[T_ASSERTION_CLOSE]);
    QRegExp bracketExpressionLiteral("[^\\\\[\\]()|?*+{}\\.^$]|\\\\[^a-zA-Z0-9]");
    QRegExp bracketExpressionRange(_syntax[T_BRACKET_EXPRESSION_RANGE]);
    QRegExp bracketExpressionClose(_syntax[T_BRACKET_EXPRESSION_CLOSE]);
    QRegExp characterClass("");
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
        _tokens.push_back(new Token(token, _expression.mid(_pos, _matchLength)));
        _pos += _matchLength;
        break;
    case T_GROUPING_OPEN:
    case T_REVERSED_CAPTURING_GROUPING_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        while(groupingClose.indexIn(_expression, _pos) != _pos && _pos < _expression.length())
            handleToken(findMatch());

        if(groupingClose.indexIn(_expression, _pos) == _pos)
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

        // Look for a "[]...]" or "[^]...]" including a literal close bracket in
        // the first position of the bracket expression
        if(bracketExpressionClose.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_LITERAL, _expression.mid(_pos, bracketExpressionClose.matchedLength())));
            _pos += bracketExpressionClose.matchedLength();
        }

        while(bracketExpressionClose.indexIn(_expression, _pos) != _pos && _pos < _expression.length())
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

        if(bracketExpressionClose.indexIn(_expression, _pos) == _pos)
        {
            _tokens.push_back(new Token(T_BRACKET_EXPRESSION_CLOSE,
                                        _expression.mid(_pos, bracketExpressionClose.matchedLength()))
                              );
            _pos += bracketExpressionClose.matchedLength();
        }
        else
            openingToken->setType(T_ERROR);

        break;
    case T_POSITIVE_LOOKAHEAD_ASSERTION_OPEN:
    case T_NEGATIVE_LOOKAHEAD_ASSERTION_OPEN:
        openingToken = new Token(token, _expression.mid(_pos, _matchLength));
        _tokens.push_back(openingToken);
        _pos += _matchLength;

        while(assertionClose.indexIn(_expression, _pos) != _pos && _pos < _expression.length())
            handleToken(findMatch());

        if(assertionClose.indexIn(_expression, _pos) == _pos)
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
        switch(_tokens[_tokens.size()-1]->type())
        {
        case T_REPEAT_ZERO_OR_ONE:
        case T_REPEAT_ANY_NUMBER:
        case T_REPEAT_ONE_OR_MORE:
        case T_REPEAT_SPECIFIED:
            _tokens.push_back(new Token(T_ERROR, _expression.mid(_pos, _matchLength)));
            _pos += _matchLength;
            break;
        case T_LITERAL:
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
            break;
        }
        break;
    default:
        qDebug() << "Unknown token at position " << _pos << ": " << token;
        qDebug() << "Value: " << _expression.mid(_pos, _matchLength);
        _tokens.push_back(new Token(T_ERROR, _expression.mid(_pos, _matchLength)));
        _pos += _matchLength;
    }
}
