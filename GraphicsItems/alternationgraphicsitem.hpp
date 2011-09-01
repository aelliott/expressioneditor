/*!
 * \file
 *
 * Copyright (c) 2011 Alex Elliott <alex@alex-elliott.co.uk>
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
#ifndef ALTERNATIONGRAPHICSITEM_HPP
#define ALTERNATIONGRAPHICSITEM_HPP

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QPainter>
#include <QSettings>

class AlternationGraphicsItem : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit AlternationGraphicsItem(QGraphicsLinearLayout *initialLayout, QGraphicsItem *parent = 0);

    void newBranch();
    QGraphicsLinearLayout *linearLayout() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;

private:
    QGraphicsLinearLayout *_mainLayout;
    QGraphicsLinearLayout *_currentLayout;
    QGraphicsTextItem *_title;
};

#endif // ALTERNATIONGRAPHICSITEM_HPP
