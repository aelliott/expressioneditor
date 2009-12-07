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

#include "graphicaleditor.hpp"

GraphicalEditor::GraphicalEditor(QWidget *parent) : QWidget(parent)
{
    expression = "";

    layout = new QHBoxLayout(this);

    toolkit = new GraphicalToolkit(this);
    toolkit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    workspace = new GraphicalWorkspace(this);

    layout->addWidget(toolkit);
    layout->addWidget(workspace);
}

QString GraphicalEditor::getExpression()
{
    return expression;
}

/**
 * Public Slots
 */
void GraphicalEditor::updateExpression(QString newExpression)
{
    expression = newExpression;
    workspace->updateExpression(newExpression);
}

QPixmap GraphicalEditor::exportToImage()
{
    return workspace->exportToImage();
}
