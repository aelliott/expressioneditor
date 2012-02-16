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
#ifndef EXPRESSIONGRAPHICSSCENE_HPP
#define EXPRESSIONGRAPHICSSCENE_HPP

#include <QGraphicsScene>

class ExpressionGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ExpressionGraphicsScene(QObject *parent = 0);

signals:

public slots:

};

#endif // EXPRESSIONGRAPHICSSCENE_HPP
