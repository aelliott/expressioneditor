/*!
 * \file
 *
 * Copyright (c) 2009-2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#ifndef CPP11REGEXP_HPP
#define CPP11REGEXP_HPP

#include "regexbase.hpp"
#include <regex>
#include <string>
#include <QDebug>

/*!
 * \brief   This class provides an interface to the C++11 regular expression
 *          implementation
 *
 * The class inherits RegexBase and provides a polymorphic class providing the
 * same access functions and behavior for C++11 features as for the other
 * regular expression libraries.
 */
class Cpp11Regex : public RegexBase
{
    Q_OBJECT

public:
    explicit Cpp11Regex(QString expression = QString(), int format = -1, QObject *parent = 0);

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

private:
    void parseResults(std::smatch &results);

    QString _regexp;
    int _matchLength;
    bool _valid;
    std::vector<int> _capturePositions;
    std::regex _re;
    QString _error;
    std::regex_constants::syntax_option_type _type;
};

#endif // CPP11REGEXP_HPP
