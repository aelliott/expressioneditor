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

#ifndef CMAKECONFIG_HPP_IN
//! File header guard
#define CMAKECONFIG_HPP_IN

//! Compiles out support for POSIX (regex.h)
#define NO_POSIX
//! Compiles out support for PCRE
#define NO_PCRE
//! Compiles out support for ICU
#define NO_ICU
//! Compiles in support for C++11
#define NO_CPP11

#endif // CMAKECONFIG_HPP_IN
