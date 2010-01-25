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
    QString text() const;

public slots:
    void updateExpression(QString exp);
    void setText(QString testString);
    void setFormat(int type);

private:
    QVBoxLayout *layout;
    QTextEdit *text_;
    BlockHighlighter *highlighter;
};

#endif // BLOCKTESTER_HPP
