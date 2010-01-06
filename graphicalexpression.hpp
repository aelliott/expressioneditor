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

#ifndef GRAPHICALEXPRESSION_HPP
#define GRAPHICALEXPRESSION_HPP

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include "groupinggraphicsitem.hpp"
#include "alternativesgraphicsitem.hpp"
#include "charrangegraphicsitem.hpp"
#include "commentgraphicsitem.hpp"
#include "repeatgraphicsitem.hpp"
#include "specialchargraphicsitem.hpp"
#include "textgraphicsitem.hpp"

class GraphicalExpression : public QGraphicsItem
{
public:
    GraphicalExpression();
    GraphicalExpression(QString expression);
    void updateExpression(QString expression);
    QString getExpression() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void addChildItem(QGraphicsItem *item);
    static QGraphicsObject* parseSection(QString expression, int &offset, bool inAlternatives = false, bool outerFlag = false);
    static RepeatGraphicsItem* parseRepeat(QString repeatString, QGraphicsObject* repeatItem);
    static QGraphicsObject* parseCapture(QString expression, int &offset);
    static AlternativesGraphicsItem* parseAlternatives(QString expression, int &offset, QGraphicsObject* firstItem);

private:
    void parseExpression(QString expression);
    static const int expressionData = 0;
    static const int itemSpacing = 8;
};

#endif // GRAPHICALEXPRESSION_HPP
