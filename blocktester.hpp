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
 * \brief   BlockTester is a testing widget which takes a block of text and shows
 *          all matched strings within it.
 *
 * This class is part of the testing framework within ExpressionEditor
 * it implements a testing widget which shows what sections of a block of
 * text are marked by a given regular expression using a given regular
 * expression engine.
 */

#ifndef BLOCKTESTER_HPP
#define BLOCKTESTER_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <blockhighlighter.hpp>

class BlockTester : public QWidget
{
    Q_OBJECT;

public:
    explicit BlockTester(QWidget *parent = 0);
    QString getText() const;

public slots:
    void updateExpression(QString exp);
    void setText(QString testString);
    void setRegexpFormat(int type);

private:
    QVBoxLayout *layout;
    QTextEdit *text;
    BlockHighlighter *highlighter;
};

#endif // BLOCKTESTER_HPP
