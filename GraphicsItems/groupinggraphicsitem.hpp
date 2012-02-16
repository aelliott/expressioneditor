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
#ifndef GROUPINGGRAPHICSITEM_HPP
#define GROUPINGGRAPHICSITEM_HPP

#include "GraphicsItems/regexgraphicsitem.hpp"
#include <QGraphicsLinearLayout>

class GroupingGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT
public:
    enum GroupingDisplayOptions
    {
        DisplayNone = 0x0,
        DisplayCapturing = 0x1,
        DisplayNonCapturing = 0x2,
        DisplayNamed = 0x4,
        DisplayAll = (DisplayCapturing | DisplayNonCapturing)
    };

    explicit GroupingGraphicsItem(Token *token, int tokenPos, bool defaultCapturing = true, QGraphicsItem *parent = 0);

    void addWidget(QGraphicsWidget *widget);
    QGraphicsLinearLayout *linearLayout() const;
    void setLinearLayout(QGraphicsLinearLayout *layout);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;

private:
    QGraphicsLinearLayout *_layout;
    bool _capturing;
    bool _defaultCapturing;
    QString _name;
    QGraphicsTextItem *_title;
};

#endif // GROUPINGGRAPHICSITEM_HPP
