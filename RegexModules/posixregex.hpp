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
#ifndef POSIXREGEX_HPP
#define POSIXREGEX_HPP

#include <QDebug>
#include <vector>
#include "capturedstring.hpp"
#include "regexbase.hpp"
#include <regex.h>

/*!
 * \brief   This class provides an interface to the POSIX regular expression
 *          implementation
 *
 * The class inherits RegexBase and provides a polymorphic class providing the
 * same access functions and behavior for POSIX features as for the other
 * regular expression libraries.
 */
class PosixRegex : public RegexBase
{
    Q_OBJECT

private:
    regex_t _posix;
    bool _failed;
    bool _valid;
    QString _errorString;
    std::vector<CapturedString> _captured;
    void parseCaptures(QString str, regmatch_t captures[]);

public:
    explicit PosixRegex(QString expression = QString(), int format = -1, QObject *parent = 0);
    ~PosixRegex();

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

    // Helpers
    QString escape();
    QString escape(const QString expression);
};

#endif // POSIXREGEX_HPP
