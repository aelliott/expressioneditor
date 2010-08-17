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
 * \brief   GraphicalExpression represents a full regexp within the QGraphicsScene
 *
 * The class takes a regular expression and parses it out into its component parts
 * then uses those to construct the displayed visualisation.
 */

#ifndef GRAPHICALEXPRESSION_HPP
#define GRAPHICALEXPRESSION_HPP

#include <QGraphicsItemGroup>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QDebug>
#include "GraphicsItems/groupinggraphicsitem.hpp"
#include "GraphicsItems/alternativesgraphicsitem.hpp"
#include "GraphicsItems/charrangegraphicsitem.hpp"
#include "GraphicsItems/commentgraphicsitem.hpp"
#include "GraphicsItems/configgraphicsitem.hpp"
#include "GraphicsItems/repeatgraphicsitem.hpp"
#include "GraphicsItems/specialchargraphicsitem.hpp"
#include "GraphicsItems/textgraphicsitem.hpp"

class GraphicalExpression : public QGraphicsObject
{
    Q_OBJECT;

public:
    //! Creates a new GraphicalExpression
    GraphicalExpression(QString expression = QString());

    //! Updates the expression and forces a recalculation of the visualisation
    void updateExpression(QString expression);

    //! Gets the current expression from the GraphicalExpression
    QString getExpression() const;

    //! Returns the geometry of the graphical object
    QRectF boundingRect() const;

    //! Paints the object on the canvas and lays out child items
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! Adds an item to be a regexp element
    void addChildItem(QGraphicsObject *item);

    //! Parses out a full section of regexp (usually a capture group or an alternation)
    static QGraphicsObject* parseSection(QString expression, int &offset, bool inAlternatives = false, bool outerFlag = false);

    //! Parses a repeated section, one with a quantifier (? + * etc)
    static RepeatGraphicsItem* parseRepeat(QString repeatString, QGraphicsObject* repeatItem);

    //! Parses a single capture group
    static QGraphicsObject* parseCapture(QString expression, int &offset);

    //! Parses an alternation
    static AlternativesGraphicsItem* parseAlternatives(QString expression, int &offset, QGraphicsObject* firstItem);

public slots:
    //! Slot triggered when the expression has changed
    void expressionChanged();

signals:
    //! Signal sent when the expression has changed
    void dataChanged();

private:
    //! Root of the parsing process (internal)
    void parseExpression(QString expression);
    static const int expressionData = 0;
    static const int itemSpacing = 8;
};

#endif // GRAPHICALEXPRESSION_HPP
