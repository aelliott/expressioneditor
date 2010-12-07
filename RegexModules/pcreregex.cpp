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

#include "pcreregex.hpp"

/*!
 * Create a new PcreRegex backend
 *
 * \param   expression  The expression to compile and use
 * \param   parent      This object's parent object
 */
PcreRegex::PcreRegex(QString expression, QObject *parent)
    : RegexBase(expression, parent)
    , pcre(expression.toStdString())
{
}

QString PcreRegex::getErrorString() const
{
    return QString(pcre.error().c_str());
}

QString PcreRegex::cap(int offset)
{
    return QString(pcre.cap(offset).c_str());
}

int PcreRegex::captureCount() const
{
    return pcre.capturingCount();
}

QStringList PcreRegex::capturedTexts()
{
    QStringList strings;
    for(int i = 0; i <= captureCount(); ++i)
        strings << QString(pcre.cap(i).c_str());
    return strings;
}

int PcreRegex::indexIn(QString string, int offset)
{
    if(pcre.PartialMatch(string.toStdString(), offset))
        return pcre.startPos(0);
    else
        return -1;
}

int PcreRegex::lastIndexIn(QString string, int offset)
{
    if(pcre.PartialMatch(string.toStdString(), offset))
    {
        int result = -1;
        for(int i = 0; pcre.startPos(i) != -1; ++i)
            result = pcre.startPos(i);
        return result;
    }
    else
        return -1;
}

int PcreRegex::matchedLength() const
{
    return pcre.matchedLength();
}

int PcreRegex::pos(int offset)
{
    return pcre.startPos(offset);
}

bool PcreRegex::isValid() const
{
    return pcre.isValid();
}

bool PcreRegex::exactMatch(const QString &string)
{
    return pcre.ExactMatch(string.toStdString());
}

void PcreRegex::setExpression(QString expression)
{
    pcre.setExpression(expression.toStdString());
}

void PcreRegex::setOptions(RegexpOptions options)
{

}

void PcreRegex::setCaseSensitivity(bool caseSensitivity)
{

}

QString PcreRegex::escape()
{
    return QString(pcre.escape().c_str());
}

QString PcreRegex::escape(QString expression)
{
    return QString(pcre.escape(expression.toStdString()).c_str());
}
