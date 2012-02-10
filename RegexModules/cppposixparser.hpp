/*!
 * \file
 *
 * Copyright (c) 2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#ifndef CPPPOSIXPARSER_HPP
#define CPPPOSIXPARSER_HPP

#include "RegexModules/posixparser.hpp"

/*!
 * This class exists as a guard against any discrepancy between POSIX's regex.h
 * from C and the POSIX format from C++11 - as of now I don't know any concerns
 * which should be addressed, but if any present themselves then this would be
 * the obvious place to handle them.
 */
class CppPosixParser : public PosixParser
{
    Q_OBJECT

public:
    CppPosixParser(QString pattern = QString(), bool extended = true, QObject *parent = 0);
};

#endif // CPPPOSIXPARSER_HPP
