/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#ifndef EXPRESSIONEDIT_HPP
#define EXPRESSIONEDIT_HPP

#include <QApplication>
#include <QTextEdit>
#include <QKeyEvent>
#include <QSettings>

#include "expressionhighlighter.hpp"

class ExpressionEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ExpressionEdit(QWidget *parent = 0);
    ~ExpressionEdit();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void setRegexFactory(RegexFactory *factory);

public slots:
    void rehash();
    void recalculateHeight();

private:
    bool _highlighting;
    RegexFactory *_factory;
    ExpressionHighlighter *_highlighter;
};

#endif // EXPRESSIONEDIT_HPP
