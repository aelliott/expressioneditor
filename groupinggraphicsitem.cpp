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

#include "groupinggraphicsitem.hpp"

GroupingGraphicsItem::GroupingGraphicsItem(bool capturing, QGraphicsItem *parent) : QGraphicsObject(parent)
{
    isCapturing = capturing;
    updateData();
}

QRectF GroupingGraphicsItem::boundingRect() const
{
    double height = 0;
    double width = 0;
    for(int i = 0; i < childItems().size(); ++i)
    {
        QRectF rect = childItems().at(i)->boundingRect();
        if(rect.height() > height)
            height = rect.height();
        width += rect.width() + itemSpacing;
    }
    if(width > 0)
        width -= itemSpacing;
    return QRectF(0, 0, width, height);
}

void GroupingGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Lay out items
    double offset = 0;
    double height = boundingRect().height();
    for(int i = 0; i < childItems().size(); ++i)
    {
        QRectF rect = childItems().at(i)->boundingRect();
        if(offset > 0)
            offset += itemSpacing;
        double verticalOffset = (height/2)-(rect.height()/2);
        if(!childItems().at(i)->isSelected())
            childItems().at(i)->setPos(offset, verticalOffset);
        offset += rect.width();
    }
}

void GroupingGraphicsItem::addChildItem(QGraphicsObject *item)
{
    item->setParentItem(this);
    connect(item, SIGNAL(dataChanged()), this, SLOT(updateData()));
    updateData();
}

void GroupingGraphicsItem::setCapturingName(QString name)
{
    capturingName = name;
    updateData();
}

/**
 * Private methods
 */
void GroupingGraphicsItem::updateData()
{
    QString expression;
    QStringList elements;
    for(int i = 0; i < childItems().size(); ++i)
        elements << childItems().at(i)->data(expressionData).toString();
    if(isCapturing)
    {
        if(!capturingName.isEmpty())
            expression = QString("(?<") + capturingName + ">" + elements.join("") + ")";
        else
            expression = QString("(") + elements.join("") + ")";
    }
    else
        expression = elements.join("");
    setData(expressionData, QVariant(expression));
    emit dataChanged();
}
