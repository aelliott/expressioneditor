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
 * \brief   This class provides an interface to an implementation which attempts
 * to provide a "Perl style" regular expression backend via the use of PCRE - in
 * a very similar way to how PHP handles regular expressions via the preg_*
 * family of functions
 *
 * The class inherits RegexBase and provides a polymorphic class providing the
 * same access functions and behavior for perl features as for the other regular
 * expression libraries.
 */

#ifndef PERLREGEX_H
#define PERLREGEX_H

#include "pcreregex.hpp"

class PerlRegex : public PcreRegex
{
    Q_OBJECT;

private:
    bool _valid;

public:
    explicit PerlRegex(QString expression = QString(), QObject *parent = 0);
    QString parseExpression(QString expression);
    bool isValid() const;
    void setExpression(QString expression);
};

#endif // PERLREGEX_H
