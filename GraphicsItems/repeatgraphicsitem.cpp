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

#include "repeatgraphicsitem.hpp"
#include "repeateditdialog.hpp"

RepeatGraphicsItem::RepeatGraphicsItem(RepeatGraphicsItem::Type type, int minimum, int maximum, QGraphicsItem *parent) : RegexGraphicsItem(parent), greedy(true)
{
    setRepeat(type, minimum, maximum);

    updateData();

    backgroundColour = QColor(255, 230, 230);
}

void RepeatGraphicsItem::setRepeat(RepeatGraphicsItem::Type type, int minimum, int maximum)
{
    setType = type;
    setMinimum = minimum;
    setMaximum = maximum;
    switch(type)
    {
        case RepeatGraphicsItem::ZeroOrOne:
            title = tr("Included At Most Once");
            break;
        case RepeatGraphicsItem::ZeroOrMore:
            title = tr("Repeated 0+ Times");
            if(!greedy)
                title += tr(" (non-greedy)");
            break;
        case RepeatGraphicsItem::OneOrMore:
            title = tr("Repeated At Least Once");
            if(!greedy)
                title += tr(" (non-greedy)");
            break;
        case RepeatGraphicsItem::ExactValue:
            title = tr("Repeated Exactly ") + QVariant(minimum).toString() + tr(" Times");
            break;
        case RepeatGraphicsItem::SpecifiedRange:
            if(maximum == -1)
                title = tr("Repeated At Least ") + QVariant(minimum).toString() + tr(" Times");
            else if(minimum == -1)
                title = tr("Repeated At Most ") + QVariant(maximum).toString() + tr(" Times");
            else
                title = tr("Repeated Between ") + QVariant(minimum).toString() + tr(" And ") + QVariant(maximum).toString() + tr(" Times");
            break;
    }
}

void RepeatGraphicsItem::setGreedy(bool newGreedy)
{
    greedy = newGreedy;
    setRepeat(setType, setMinimum, setMaximum);
}

void RepeatGraphicsItem::setChildItem(QGraphicsObject *item)
{
    // There can only be one child item
    if(childItems().size() > 0)
        delete childItems().at(0);
    item->setParentItem(this);
    connect(item, SIGNAL(dataChanged()), this, SLOT(updateData()));
    connect(item, SIGNAL(removeItem(QGraphicsObject*)), this, SLOT(removeChild(QGraphicsObject*)));
    updateData();
}

QRectF RepeatGraphicsItem::boundingRect() const
{
    double width = 0;
    double height = 0;
    if(childItems().size() > 0)
    {
        if(childItems().at(0)->boundingRect().width() > qApp->fontMetrics().width(title))
            width  = childItems().at(0)->boundingRect().width()  + 2*horizontalPadding;
        else
            width = qApp->fontMetrics().width(title) + 2*horizontalPadding;
        height = childItems().at(0)->boundingRect().height() + qApp->fontMetrics().height() + 2.5*verticalPadding;
    }
    return QRectF(0, 0, width, height);
}

void RepeatGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!isSelected())
        painter->setBrush(backgroundColour);
    else
        painter->setBrush(QColor(235, 210, 210));

    painter->drawRoundedRect(boundingRect(), 8.0, 8.0);
    painter->drawText(horizontalPadding, 0.5*qApp->fontMetrics().height()+verticalPadding, title);

    if(childItems().size() > 0 && !childItems().at(0)->isSelected())
    {
        double verticalOffset = qApp->fontMetrics().height() + 1.5*verticalPadding;
        double horizontalOffset = (boundingRect().width()/2)-(childItems().at(0)->boundingRect().width()/2);
        childItems().at(0)->setPos(horizontalOffset, verticalOffset);
    }
}

void RepeatGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(245, 220, 220);
    update();
}

void RepeatGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->accept();
    backgroundColour = QColor(255, 230, 230);
    update();
}

void RepeatGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    RepeatEditDialog dialog(setType, setMinimum, setMaximum);
    int response = dialog.exec();

    if(response == QDialog::Rejected)
        return;

    setRepeat(dialog.getType(), dialog.getMinimum(), dialog.getMaximum());
    updateData();
    update();
}

/**
 * Public slots
 */
void RepeatGraphicsItem::updateData()
{
    QString expression = "";
    if(childItems().size() > 0)
    {
        expression = childItems().at(0)->data(expressionData).toString();

        switch(setType)
        {
        case RepeatGraphicsItem::ZeroOrOne:
            expression += "?";
            break;
        case RepeatGraphicsItem::ZeroOrMore:
            expression += "*";
            if(!greedy)
                expression += "?";
            break;
        case RepeatGraphicsItem::OneOrMore:
            expression += "+";
            if(!greedy)
                expression += "?";
            break;
        case RepeatGraphicsItem::ExactValue:
            expression += "{" + QVariant(setMinimum).toString() + "}";
            break;
        case RepeatGraphicsItem::SpecifiedRange:
            if(setMaximum == -1)
                expression += "{" + QVariant(setMinimum).toString() + ",}";
            else if(setMinimum == -1)
                expression += "{," + QVariant(setMaximum).toString() + "}";
            else
                expression += "{" + QVariant(setMinimum).toString() + "," + QVariant(setMaximum).toString() + "}";
            break;
        }
    }

    setData(expressionData, QVariant(expression));
    emit dataChanged();
}

void RepeatGraphicsItem::removeChild(QGraphicsObject *item)
{
    if(isAncestorOf(item))
        delete item;
    // Since the repeat item can only have one child, this is now empty
    emit removeItem(this);
}
