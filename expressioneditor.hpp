/**
 * This file is part of Expression editor
 *
 * Expression editor is Copyright 2009 Alex Elliott <alex@alex-elliott.co.uk>
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

#ifndef EXPRESSIONEDITOR_HPP
#define EXPRESSIONEDITOR_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QSplitter>
#include "graphicaleditor.hpp"
#include "expressiontester.hpp"
#include "expressionhighlighter.hpp"

class ExpressionEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ExpressionEditor(QWidget *parent = 0);
    QString getExpression();
    QStringList getTestStrings();

signals:

public slots:
    void updateExpression();
    void updateExpression(QString regex);
    void addTestString(QString testString);
    QPixmap exportToImage();

private:
    QVBoxLayout *mainLayout;
    QSplitter *splitter;
    QVBoxLayout *subLayout;
    QTextEdit *expressionInput;
    ExpressionTester *tester;
    ExpressionHighlighter *highlighter;
    GraphicalEditor *graphicalEditor;
};

#endif // EXPRESSIONEDITOR_HPP
