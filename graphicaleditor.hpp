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

#ifndef GRAPHICALEDITOR_HPP
#define GRAPHICALEDITOR_HPP

#include <QWidget>
#include <QHBoxLayout>
#include "graphicaltoolkit.hpp"
#include "graphicalworkspace.hpp"

class GraphicalEditor : public QWidget
{
Q_OBJECT
public:
    explicit GraphicalEditor(QWidget *parent = 0);
    QString getExpression();

signals:
    void expressionChanged(QString newExpression);

public slots:
    void updateExpression(QString newExpression);
    void sceneChanged(QString newExpression);
    QPixmap exportToImage();
    void setFormat(int type);

private:
    QString expression;
    QHBoxLayout *layout;
    GraphicalToolkit *toolkit;
    GraphicalWorkspace *workspace;
};

#endif // GRAPHICALEDITOR_HPP
