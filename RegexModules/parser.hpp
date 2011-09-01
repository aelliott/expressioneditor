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
#ifndef PARSER_HPP
#define PARSER_HPP

#include <QObject>
#include <QRegExp>
#include <QDebug>
#include <vector>
#include <map>

#include "RegexModules/token.hpp"

class Parser : public QObject
{
    Q_OBJECT

public:
    explicit Parser(QString pattern = QString(), QObject *parent = 0);
    virtual ~Parser();

public slots:
    virtual bool parse(QString pattern = QString()) = 0;
    virtual void handleToken(RegexpToken token) = 0;

    QString expression() const;
    std::vector<Token *> tokens() const;

    void setExpression(QString pattern);

protected:
    RegexpToken findMatch();

    QString _expression;
    int _pos;
    int _matchLength;
    int _bracketCount;
    bool _inCharacterClass;
    bool _inFlags;
    std::vector<Token *> _tokens;
    std::map<RegexpToken, QString> _syntax;
};

#endif // PARSER_HPP
