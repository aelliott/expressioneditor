/*!
 * \file
 *
 * Copyright (c) 2012 Alex Elliott <alex@alex-elliott.co.uk>
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
#include "testblockwidget.hpp"

TestBlockWidget::TestBlockWidget(QWidget *parent)
    : QTextEdit(parent)
    , _blockHighlighter(0)
    , _factory(0)
{
}

TestBlockWidget::~TestBlockWidget()
{
}

void TestBlockWidget::setRegexFactory(RegexFactory *factory)
{
    _factory = factory;
    _blockHighlighter = new BlockHighlighter(factory, this);
}

void TestBlockWidget::updateExpression(QString expression)
{
    _blockHighlighter->updateExpression(expression);
}
