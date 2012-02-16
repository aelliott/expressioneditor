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
#ifndef BRACKETEXPRESSIONGRAPHICSITEM_HPP
#define BRACKETEXPRESSIONGRAPHICSITEM_HPP

#include "GraphicsItems/regexgraphicsitem.hpp"

#include <QDebug>

class BracketExpressionGraphicsItem : public RegexGraphicsItem
{
    Q_OBJECT

public:
    explicit BracketExpressionGraphicsItem(Token *token, int tokenPos, QGraphicsItem *parent = 0);

    void addToken(Token *token);
    void readTokens();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;

private:
    std::vector<Token *> _tokens;
    QGraphicsTextItem *_text;
    bool _negated;
};

#endif // BRACKETEXPRESSIONGRAPHICSITEM_HPP
