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
#ifndef EXPRESSIONGRAPHICSITEM_HPP
#define EXPRESSIONGRAPHICSITEM_HPP

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include <QPainter>
#include "regexfactory.hpp"

#include "GraphicsItems/alternationgraphicsitem.hpp"
#include "GraphicsItems/anchorgraphicsitem.hpp"
#include "GraphicsItems/bracketexpressiongraphicsitem.hpp"
#include "GraphicsItems/characterclassitem.hpp"
#include "GraphicsItems/commentgraphicsitem.hpp"
#include "GraphicsItems/errorgraphicsitem.hpp"
#include "GraphicsItems/groupinggraphicsitem.hpp"
#include "GraphicsItems/literalgraphicsitem.hpp"
#include "GraphicsItems/repeatgraphicsitem.hpp"

class ExpressionGraphicsItem : public QGraphicsWidget
{
    Q_OBJECT

public:
    explicit ExpressionGraphicsItem(QString expression, RegexFactory::RegexFormat format, QGraphicsItem *parent = 0);
    ~ExpressionGraphicsItem();

    QGraphicsLinearLayout *handleToken(Token token, QGraphicsLinearLayout *currentLayout);

signals:
    void expressionChanged(QString);

public slots:

private:
    QString _expression;
    RegexFactory *_factory;
    QGraphicsLinearLayout *_root;
    QGraphicsWidget *_lastItem;
    std::vector<Token *> _tokens;
    std::vector<Token *>::iterator  _iter;
    bool _incremented;

    double _itemSpacing;
};

#endif // EXPRESSIONGRAPHICSITEM_HPP
