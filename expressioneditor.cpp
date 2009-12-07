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

#include "expressioneditor.hpp"

ExpressionEditor::ExpressionEditor(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    graphicalEditor = new GraphicalEditor(this);

    splitter = new QSplitter(Qt::Vertical, this);

    QWidget *textInput = new QWidget(this);
    QHBoxLayout *textLayout = new QHBoxLayout(textInput);
    QLabel *inputLabel = new QLabel(tr("Expression: "));
    inputLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    expressionInput = new QTextEdit;
    expressionInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    expressionInput->setFixedHeight(28);

    highlighter = new ExpressionHighlighter(expressionInput);

    textLayout->addWidget(inputLabel);
    textLayout->addWidget(expressionInput);

    tester = new ExpressionTester(this);
        connect(expressionInput, SIGNAL(textChanged()), this, SLOT(updateExpression()));

    QWidget *workspaceLayout = new QWidget(this);
    subLayout = new QVBoxLayout(workspaceLayout);
    subLayout->addWidget(graphicalEditor);
    subLayout->addWidget(textInput);

    splitter->addWidget(workspaceLayout);
    splitter->addWidget(tester);

    mainLayout->addWidget(splitter);
}

QString ExpressionEditor::getExpression()
{
    return expressionInput->toPlainText();
}

QStringList ExpressionEditor::getTestStrings()
{
    return tester->getTestStrings();
}

/**
 * Public Slots
 */
void ExpressionEditor::updateExpression()
{
    if(getExpression() != tester->getExpression())
        updateExpression(getExpression());
}

void ExpressionEditor::updateExpression(QString regex)
{
    tester->updateExpression(regex);
    graphicalEditor->updateExpression(regex);
    if(getExpression() != regex)
        expressionInput->setText(regex);
}

void ExpressionEditor::addTestString(QString testString)
{
    tester->addTestString(testString);
}

QPixmap ExpressionEditor::exportToImage()
{
    return graphicalEditor->exportToImage();
}
