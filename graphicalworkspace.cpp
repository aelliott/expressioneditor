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

#include "graphicalworkspace.hpp"

GraphicalWorkspace::GraphicalWorkspace(QWidget *parent) : QGraphicsView(parent)
{
    factory = new RegexFactory();

    setDragMode(QGraphicsView::RubberBandDrag);
    setRubberBandSelectionMode(Qt::IntersectsItemShape);

    scene = new QGraphicsScene;
    scene->setBackgroundBrush(QColor(247, 247, 247));
    setScene(scene);
    connect(scene, SIGNAL(changed(QList<QRectF>)), this, SLOT(sceneChanged()));
    editingStarted = false;
    welcomeMessage = new QGraphicsTextItem;
    welcomeMessage->setHtml(tr("To begin editing drag an item from the toolkit <br>"
                               "on the left or start typing in the text field below."));
    scene->addItem(welcomeMessage);
}

QString GraphicalWorkspace::getErrorString() const
{
    return errorString;
}

/**
 * Public slots
 */
bool GraphicalWorkspace::updateExpression(QString newExpression)
{
    RegexBase *rx = factory->factory(newExpression);
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
        scene->removeItem(visualisation);
    expression = newExpression;
    visualisation = new GraphicalExpression(newExpression);
    scene->addItem(visualisation);
    QRectF sceneArea = scene->itemsBoundingRect();
    sceneArea.adjust(-10, -10, 20, 20);
    setSceneRect(sceneArea);
    return true;
}

QPixmap GraphicalWorkspace::exportToImage()
{
    QPixmap image(scene->width(), scene->height());
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    painter.end();

    return image;
}

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

void GraphicalWorkspace::setFormat(int type)
{
    factory->setType(type);
}
