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

#include "graphicalworkspace.hpp"

/*!
 * Creates a new GraphicalWorkspace
 *
 * \param   parent  This item's parent widget
 */
GraphicalWorkspace::GraphicalWorkspace(QWidget *parent) : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    factory = new RegexFactory();

    setDragMode(QGraphicsView::RubberBandDrag);
    setRubberBandSelectionMode(Qt::IntersectsItemShape);

    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QColor(247, 247, 247));
    setScene(scene);
    //connect(scene, SIGNAL(changed(QList<QRectF>)), this, SLOT(sceneChanged()));
    editingStarted = false;
    welcomeMessage = new QGraphicsTextItem;
    welcomeMessage->setHtml(tr("To begin editing drag an item from the toolkit <br>"
                               "on the left or start typing in the text field below."));
    scene->addItem(welcomeMessage);
}

/*!
 * Get the error string from the regexp backend
 *
 * \return  The regular expression backend's reported error string
 */
QString GraphicalWorkspace::getErrorString() const
{
    return errorString;
}

/*!
 * Update the expression
 *
 * \param   newExpression   The new regular expression to use
 * \return  True if the new expression has been accepted, false otherwise
 */
bool GraphicalWorkspace::updateExpression(QString newExpression)
{
    RegexBase *rx = factory->factory(newExpression);

    if(rx->getExpression().isEmpty())
        return false;

    expression = rx->getExpression();

    if(!rx->isValid())
    {
        errorString = rx->getErrorString();
        delete rx;
        return false;
    }
    delete rx;

    if(!editingStarted)
    {
        scene->removeItem(welcomeMessage);
        editingStarted = true;
    }
    else
    {
        //scene->removeItem(visualisation);
        delete visualisation;
    }
    visualisation = new GraphicalExpression(expression);
    connect(visualisation, SIGNAL(dataChanged()), this, SLOT(sceneChanged()));
    scene->addItem(visualisation);
    QRectF sceneArea = scene->itemsBoundingRect();
    sceneArea.adjust(-10, -10, 20, 20);
    setSceneRect(sceneArea);
    return true;
}

/*!
 * Return a QPixmap representation of the current visualisation
 *
 * \return  The exported QPixmap from the graphics scene
 */
QPixmap GraphicalWorkspace::exportToImage()
{
    QPixmap image(scene->width(), scene->height());
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    painter.end();

    return image;
}

/*!
 * React to the a scene change, check if the expression has been modified and if
 * it has propagate the change via the expressionChanged() signal
 */
void GraphicalWorkspace::sceneChanged()
{
    if(editingStarted)
    {
        QString newExpression = visualisation->getExpression();
        if(expression != newExpression)
        {
            expression = newExpression;
            emit expressionChanged(newExpression);
        }
    }
}

/*!
 * Set the current regexp format in use
 *
 * \param   type    The regular expression format to use
 */
void GraphicalWorkspace::setRegexpFormat(int type)
{
    factory->setRegexpFormat(type);
}
