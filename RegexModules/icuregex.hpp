/*!
 * \file
 *
 * Copyright (c) 2009,2010,2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#ifndef ICUREGEX_HPP
#define ICUREGEX_HPP

#include <QList>
#include <QDebug>
#include <unicode/regex.h>
#include <unicode/ucnv.h>
#include "regexbase.hpp"

/*!
 * \brief   This class provides an interface to the ICU regular expression
 *          implementation
 *
 * The class inherits RegexBase and provides a polymorphic class providing the
 * same access functions and behavior for ICU features as for the other regular
 * expression libraries.
 */
class IcuRegex : public RegexBase
{
    Q_OBJECT

private:
    RegexMatcher *_matcher;
    UErrorCode _status;
    bool _valid;
    char *_patternStr;
    UnicodeString _pattern;
    UnicodeString _targetString;

public:
    explicit IcuRegex(QString expression = QString(), QObject *parent = 0);
    ~IcuRegex();

    // Getters
    QString getErrorString() const;
    QString cap(int offset = 0);
    int captureCount() const;
    QStringList capturedTexts();
    int indexIn(QString string, int offset = 0);
    int lastIndexIn(QString string, int offset = -1);
    int matchedLength() const;
    int pos(int offset = 0);

    // Logic tests
    bool isValid() const;
    bool exactMatch(const QString &string);

    // Setters
    void setExpression(QString expression);
    void setOptions(RegexpOptions options);
    void setCaseSensitivity(bool caseSensitivity);
};

#endif // ICUREGEX_HPP
