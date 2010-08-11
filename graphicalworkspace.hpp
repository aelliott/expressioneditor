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
/*!
 * \brief   The Workspace is a subclass of QGraphicsView and contains the
 *          scene on which the visualisation is drawn.
 */

#ifndef GRAPHICALWORKSPACE_HPP
#define GRAPHICALWORKSPACE_HPP

#include <QGraphicsView>
#include <QDebug>
#include "regexfactory.hpp"
#include "graphicalexpression.hpp"

class GraphicalWorkspace : public QGraphicsView
{
    Q_OBJECT;

public:
    //! Creates a new GraphicalWorkspace
    explicit GraphicalWorkspace(QWidget *parent = 0);

    //! Get the error string from the regexp backend
    QString getErrorString() const;

signals:
    //! Signal triggered whenever the expression is graphically altered
    void expressionChanged(QString newExpression);

public slots:
    //! Update the expression
    bool updateExpression(QString expression);

    //! React to the a scene change
    void sceneChanged();

    //! Return a QPixmap representation of the current visualisation
    QPixmap exportToImage();

    //! Set the current regexp format in use
    void setRegexpFormat(int type);

private:
    RegexFactory *factory;
    QString expression;
    QString errorString;
    bool editingStarted;
    QGraphicsScene *scene;
    QGraphicsTextItem *welcomeMessage;
    GraphicalExpression *visualisation;
};

#endif // GRAPHICALWORKSPACE_HPP
