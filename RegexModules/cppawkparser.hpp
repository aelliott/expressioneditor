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
#ifndef CPPAWKPARSER_HPP
#define CPPAWKPARSER_HPP

#include "RegexModules/posixparser.hpp"

/*!
 * Quote from: http://pubs.opengroup.org/onlinepubs/009604499/utilities/awk.html#tag_04_06_13_04
 *
 * "The awk utility shall make use of the extended regular expression notation
 * (see the Base Definitions volume of IEEE Std 1003.1-2001, Section 9.4,
 * Extended Regular Expressions) except that it shall allow the use of
 * C-language conventions for escaping special characters within the EREs, as
 * specified in the table in the Base Definitions volume of IEEE Std
 * 1003.1-2001, Chapter 5, File Format Notation ( '\\\\', '\\a', '\\b', '\\f', '\\n',
 * '\\r', '\\t' , '\\v' ) and the following table; these escape sequences shall be
 * recognized both inside and outside bracket expressions. Note that records
 * need not be separated by <newline>s and string constants can contain
 * <newline>s, so even the "\\n" sequence is valid in awk EREs. Using a slash
 * character within an ERE requires the escaping shown in the following table."
 *
 * Therefore we will derive this from a PosixParser initialised to ERE format
 * and make the necessary alterations.
 */
class CppAwkParser : public PosixParser
{
    Q_OBJECT

public:
    explicit CppAwkParser(QString expression = QString(), QObject *parent = 0);
};

#endif // CPPAWKPARSER_HPP
