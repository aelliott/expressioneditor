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
 * \brief   This class implements an interface to the various regular expression
 *          implementations supported by Expression Editor
 *
 * The class provides a polymorphic base class giving a uniform interface with
 * which to access the specific underlying regular expression backends
 */

#ifndef REGEXBASE_HPP
#define REGEXBASE_HPP

#include <QObject>
#include <QStringList>

class RegexBase : public QObject
{
    Q_OBJECT;

protected:
    /*!
     * This enum contains the various settable options within regular expression
     * backends (some may not be implemented in some backends)
     */
    enum RegexpOptions
    {
        //! Determines whether the match should be case sensitive or not
        CaseInsensitive = 0x01,
        //! Determines whether the matcher should include \\n and \\r\\n line breaks or treat lines individually
        MultiLine = 0x02,
        //! Inverts the greediness behaviour to ungreedy by default
        UnGreedy = 0x04,
        //! Inverts the capturing behaviour of the backend to default to non-capturing groups
        NoCapture = 0x08,
        //! Determines whether the matcher should use UTF8 encoding or not
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

    /*!
     * Get the error string provided by the regex backend if the last attempt
     * to compile the provided regular expression failed
     *
     * \return  A descriptive string representation of the last error
     */
    virtual QString getErrorString() const = 0;

    /*!
     * Return the capture group at the provided offset
     *
     * \param   offset  The capture group to return
     * \return  The returned capture group at the given offset
     */
    virtual QString cap(int offset = 0) = 0;

    /*!
     * Returns the number of capture groups
     *
     * \return  The number of capture groups in the compiled expression
     */
    virtual int captureCount() const = 0;

    /*!
     * Returns a QStringList containing all of the matched capture groups from
     * the last use of the regular expression match
     *
     * \return  A list of captured strings
     */
    virtual QStringList capturedTexts() = 0;

    /*!
     * Finds the index of a match in the provided string starting at the provided
     * offset, returns -1 if there is no match
     *
     * \param   string  The string to apply the regular expression to
     * \param   offset  The offset to start matching from within the string
     * \return  The integer offset of the first match or -1 on no match
     */
    virtual int indexIn(QString string, int offset = 0) = 0;

    /*!
     * Finds the index of the last match in the provided string starting at the
     * provided offset, returns -1 if there is no match
     *
     * \param   string  The string to apply the regular expression to
     * \param   offset  The offset to start matching from within the string
     * \return  The integer offset of the last match or -1 on no match
     */
    virtual int lastIndexIn(QString string, int offset = -1) = 0;

    /*!
     * Returns the length of the matched text (the full match, capture group 0)
     *
     * \return  The length of the text matched
     */
    virtual int matchedLength() const = 0;

    /*!
     * Returns the position of the last match within the string
     *
     * \return  The position at which the last match begins
     */
    virtual int pos(int offset = 0) = 0;

    // Logic tests
    bool isEmpty() const;

    /*!
     * Returns true if the regular expression provided was compiled correctly
     * by the regular expression backend, and false if there were any errors
     *
     * \return  True if the regular expression compiled with no errors, false
     *          otherwise
     */
    virtual bool isValid() const = 0;

    /*!
     * Attempts to match the entire string provided against the current
     * regular expression, returns true if a full match is present and false
     * if a full match cannot be found.  Partial matches are not accepted
     *
     * \return  True if the regular expression has a full match for the entire
     *          string provided, false otherwise
     */
    virtual bool exactMatch(const QString &string) = 0;

    // Setters
    /*!
     * Set or reset the regular expression used by the matcher
     *
     * \param   expression  The regular expression to compile and use
     */
    virtual void setExpression(QString expression) = 0;

    /*!
     * Set regular expression options (i.e. case-insensitive matching)
     *
     * \param   options Bitmask of available options
     */
    virtual void setOptions(RegexpOptions options) = 0;

    /*!
     * Set the case sensitivity individually
     *
     * This option can also be set as part of setOptions
     *
     * \param   caseSensitivity True if the match should be case sensitive, false
     *                          otherwise
     */
    virtual void setCaseSensitivity(bool caseSensitivity) = 0;

    // Helpers
    /*!
     * Escape special characters to return a string which the regular expression
     * backend will interpret as a literal string matching the string provided
     *
     * \param   expression  The expression or fragment of an expression to escape
     * \return  An escaped version of the provided string
     */
    virtual QString escape() = 0;

    /*!
     * Escape special characters in the expression currently in use within the
     * regexp backend
     *
     * \return  An escaped version of the current regular expression
     */
    virtual QString escape(const QString expression) = 0;
};

#endif // REGEXBASE_HPP
