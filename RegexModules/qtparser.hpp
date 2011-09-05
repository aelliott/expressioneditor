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
#ifndef QTPARSER_HPP
#define QTPARSER_HPP

#include "RegexModules/parser.hpp"

class QtParser : public Parser
{
    Q_OBJECT

public:
    explicit QtParser(QString pattern = QString(), QObject *parent = 0);

public slots:
    //bool parse(QString pattern = QString());
    void handleToken(RegexpToken token);
};

#endif // QTPARSER_HPP