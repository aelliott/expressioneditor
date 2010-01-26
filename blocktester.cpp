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

#include "blocktester.hpp"

BlockTester::BlockTester(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    text_ = new QTextEdit(this);
    highlighter = new BlockHighlighter(text_);
    layout->addWidget(text_);

    setLayout(layout);
}

QString BlockTester::text() const
{
    return text_->toPlainText();
}

void BlockTester::updateExpression(QString exp)
{
    highlighter->updateExpression(exp);
    text_->setText(text());
}

void BlockTester::setText(QString testString)
{
    text_->setText(testString);
}

void BlockTester::setFormat(int type)
{
    highlighter->setRegexpFormat(type);
    text_->setText(text());
}
