/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2010 Alex Elliott <alex@alex-elliott.co.uk>
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
 *
 */

#ifndef REGEXBASE_HPP
#define REGEXBASE_HPP

#include <QObject>
#include <QStringList>

class RegexBase : public QObject
{
    Q_OBJECT;

protected:
    enum RegexpOptions
    {
        CaseInsensitive = 0x01,
        MultiLine = 0x02,
        UnGreedy = 0x04,
        NoCapture = 0x08,
        UTF8 = 0x10
    };

    QString regexp;
    int matchLength;
    QStringList captured;

public:
    /*
     * The public interface is largely modelled on QRegExp with some
     * alterations to make it fit more with the rest of the application
     */
    explicit RegexBase(QString expression = QString(), QObject *parent = 0);
    virtual ~RegexBase(){}

    // Getters
    QString getExpression() const;
    virtual QString getErrorString() const = 0;
    virtual QString cap(int offset = 0) = 0;
    virtual int captureCount() const = 0;
    virtual QStringList capturedTexts() = 0;
    virtual int indexIn(QString string, int offset = 0) = 0;
    virtual int lastIndexIn(QString string, int offset = -1) = 0;
    virtual int matchedLength() const = 0;
    virtual int pos(int offset = 0) = 0;

    // Logic tests
    bool isEmpty() const;
    virtual bool isValid() const = 0;
    virtual bool exactMatch(const QString &string) = 0;

    // Setters
    virtual void setExpression(QString expression) = 0;
    virtual void setOptions(RegexpOptions options) = 0;
    virtual void setCaseSensitivity(bool caseSensitivity) = 0;

    // Helpers
    virtual QString escape() = 0;
    virtual QString escape(const QString expression) = 0;
};

#endif // REGEXBASE_HPP
