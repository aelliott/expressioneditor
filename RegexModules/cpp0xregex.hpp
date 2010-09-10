/*!
 * \file
 * \author Alex Elliott <alex@alex-elliott.co.uk>
 * \version 0.1pre
 *
 * \section LICENSE
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009,2010 Alex Elliott <alex@alex-elliott.co.uk>
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
/*!
 * \brief   This class provides an interface to the C++0x regular expression
 *          implementation
 *
 * The class inherits RegexBase and provides a polymorphic class providing the
 * same access functions and behavior for C++0x features as for the other
 * regular expression libraries.
 *
 * This feature is currently opt-in only due to C++0x not being fully supported
 * or part of a full standard yet, making it hard to rely on it being present
 * in target systems, in those that do support C++0x drafts however it can be
 * activated (at least on GCC) by providing WITH_CPP0X to CMake.
 *
 * As of now most GCC versions do not seem to have a complete implementation of
 * regular expressions as part of tr1 or c++0x
 */

#ifndef CPP0XREGEXP_HPP
#define CPP0XREGEXP_HPP

#include "regexbase.hpp"
#include <regex>
#include <string>

class Cpp0xRegex : public RegexBase
{
    Q_OBJECT;

public:
    explicit Cpp0xRegex(QString expression = QString(), QObject *parent = 0);

    // Getters
    QString getExpression() const;
    QString getErrorString() const;
    QString cap(int offset = 0);
    int captureCount() const;
    QStringList capturedTexts();
    int indexIn(QString string, int offset = 0);
    int lastIndexIn(QString string, int offset = -1);
    int matchedLength() const;
    int pos(int offset = 0);

    // Logic tests
    bool isEmpty() const;
    bool isValid() const;
    bool exactMatch(const QString &string);

    // Setters
    void setExpression(QString expr);
    void setOptions(RegexpOptions options);
    void setCaseSensitivity(bool caseSensitivity);

    // Helpers
    QString escape();
    QString escape(const QString expr);

private:
    QString expression;
    bool valid;
    std::regex *regexp;
};

#endif // CPP0XREGEXP_HPP
