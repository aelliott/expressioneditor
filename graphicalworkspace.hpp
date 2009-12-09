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

#ifndef GRAPHICALWORKSPACE_HPP
#define GRAPHICALWORKSPACE_HPP

#include <QGraphicsView>
#include <QDebug>
#include "graphicalexpression.hpp"

class GraphicalWorkspace : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicalWorkspace(QWidget *parent = 0);

signals:
    void expressionChanged(QString newExpression);

public slots:
    void updateExpression(QString expression);
    void sceneChanged();
    QPixmap exportToImage();

private:
    QString expression;
    bool editingStarted;
    QGraphicsScene *scene;
    QGraphicsTextItem *welcomeMessage;
    GraphicalExpression *visualisation;
};

#endif // GRAPHICALWORKSPACE_HPP
