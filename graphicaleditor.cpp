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

#include "graphicaleditor.hpp"

/*!
 * Creates a new GraphicalEditor
 *
 * \param   parent  This item's parent
 */
GraphicalEditor::GraphicalEditor(QWidget *parent) : QWidget(parent)
{
    expression = "";

    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    toolkit = new GraphicalToolkit(this);
    toolkit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    workspace = new GraphicalWorkspace(this);
    connect(workspace, SIGNAL(expressionChanged(QString)), this, SLOT(sceneChanged(QString)));

    layout->addWidget(toolkit);
    layout->addWidget(workspace);
}

/*!
 * Retrieves the current regular expression
 *
 * \return  The current regular expression
 */
QString GraphicalEditor::getExpression()
{
    return expression;
}

/*!
 * Retrieves any error string from the regular expression backend
 *
 * \return  The current error string (if any) from the regular expression engine
 */
QString GraphicalEditor::getErrorString() const
{
    return workspace->getErrorString();
}

/*!
 * Udpates the regular expression when a new one is available
 *
 * \param   newExpression   The new regular expression
 * \return  Returns true if a new regular expression has been set, false
 *          otherwise
 */
bool GraphicalEditor::updateExpression(QString newExpression)
{
    expression = newExpression;
    return workspace->updateExpression(newExpression);
}

/*!
 * Internal slot which recieves data when the QGraphicsScene has changed,
 * meaning a graphical edit of the current regular expression has taken place.
 * This signal should be passed up the chain to be properly handled along with
 * the regular expression that the graphical editor now contains.
 *
 * \param   newExpression   The new regular expression from the graphical editor
 */
void GraphicalEditor::sceneChanged(QString newExpression)
{
    emit expressionChanged(newExpression);
}

/*!
 * Return a QPixmap of the current regular expression's visualisation for and
 * export into an image format.
 *
 * \return A QPixmap of the current regular expression's visualisation
 */
QPixmap GraphicalEditor::exportToImage()
{
    return workspace->exportToImage();
}

/*!
 * Sets which regular expression backend should be use in the graphical editor
 *
 * \param   type    The regular expression format to use
 */
void GraphicalEditor::setRegexpFormat(int type)
{
    workspace->setRegexpFormat(type);
}
