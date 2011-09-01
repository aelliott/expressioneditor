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
#include "expressionedit.hpp"

ExpressionEdit::ExpressionEdit(QWidget *parent)
    : QTextEdit(parent)
{
    QSettings settings;
    _highlighting = settings.value("Editor/Highlighting", true).toBool();

    if(_highlighting)
        _highlighter = new ExpressionHighlighter(this);
}

ExpressionEdit::~ExpressionEdit()
{
    if(_highlighting)
        delete _highlighter;
}

void ExpressionEdit::keyPressEvent(QKeyEvent *e)
{
    QTextEdit::keyPressEvent(e);

    QSettings settings;
    bool autocompletion = settings.value("Editor/Autocompletion", false).toBool();
    if(!autocompletion)
        return;

    if(e->key() == Qt::Key_ParenLeft)
    {
        QKeyEvent *parenPress = new QKeyEvent(QEvent::KeyPress, Qt::Key_ParenRight, e->modifiers(), ")");
        this->keyPressEvent(parenPress);
    }
}

void ExpressionEdit::keyReleaseEvent(QKeyEvent *e)
{
    QTextEdit::keyPressEvent(e);

    QSettings settings;
    bool autocompletion = settings.value("Editor/Autocompletion", false).toBool();
    if(!autocompletion)
        return;

    if(e->key() == Qt::Key_ParenLeft)
    {
        QKeyEvent *parenRelease = new QKeyEvent(QEvent::KeyRelease, Qt::Key_ParenRight, e->modifiers());
        this->keyPressEvent(parenRelease);
        QKeyEvent *leftPress = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
        this->keyPressEvent(leftPress);
        QKeyEvent *leftRelease = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Left, Qt::NoModifier);
        this->keyPressEvent(leftRelease);
    }
}

void ExpressionEdit::rehash()
{
    QSettings settings;
    bool previous = _highlighting;
    _highlighting = settings.value("Editor/Highlighting", true).toBool();

    if(previous && !_highlighting)
    {
        // Stop highlighting
        delete _highlighter;
    }
    else if(!previous && _highlighting)
    {
        // Start highlighting
        _highlighter = new ExpressionHighlighter(this);
    }
}
