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
 * \brief   GraphicalEditor contains the elements used to graphically
 *          represent and edit the current regular expression.
 *
 * Specifically it contains a GraphicalWorkspace which contains and drives
 * the regexp visualisation, and a GraphicalToolkit which contains elements
 * to be dragged and dropped into the regular expression being worked on.
 */

#ifndef GRAPHICALEDITOR_HPP
#define GRAPHICALEDITOR_HPP

#include <QWidget>
#include <QHBoxLayout>
#include "graphicaltoolkit.hpp"
#include "graphicalworkspace.hpp"

class GraphicalEditor : public QWidget
{
    Q_OBJECT;

public:
    //! Creates a new GraphicalEditor
    explicit GraphicalEditor(QWidget *parent = 0);

    //! Getter, retrieves the expression
    QString getExpression();

    //! Getter, retrieves any error string from the regexp backend
    QString getErrorString() const;

signals:
    //! Signal triggered whenever the expression has changed somehow
    void expressionChanged(QString newExpression);

public slots:
    //! Slot which udpates the expression when a new one is available
    bool updateExpression(QString newExpression);

    //! Slot which recieves data when the QGraphicsScene has changed, meaning a graphical edit
    void sceneChanged(QString newExpression);

    //! Slot returning a QPixmap of the current regexp visualisation
    QPixmap exportToImage();

    //! Setter, sets the regexp format
    void setRegexpFormat(int type);

private:
    QString expression;
    QHBoxLayout *layout;
    GraphicalToolkit *toolkit;
    GraphicalWorkspace *workspace;
};

#endif // GRAPHICALEDITOR_HPP
