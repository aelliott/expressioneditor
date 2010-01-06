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

GroupingGraphicsItem::GroupingGraphicsItem(bool brackets, bool outer, bool capturing, QGraphicsItem *parent) : QGraphicsObject(parent), hasBrackets(brackets), isCapturing(capturing)
{
    setOuterGroup(outer);
    dragEvent = false;
    setAcceptDrops(true);
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
    if(width > 0 && !outerGroup)
        width -= itemSpacing;
    else
        width += itemSpacing;
    return QRectF(0, 0, width, height);
}

void GroupingGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    dropZones.clear();

    // Lay out items
    double offset = 0;
    double height = boundingRect().height();
    for(int i = 0; i < childItems().size(); ++i)
    {
        QRectF rect = childItems().at(i)->boundingRect();
        if(dragEvent && (outerGroup || offset > 0))
        {
            QRectF dropZone(offset, 0, itemSpacing, height);
            dropZones.push_back(dropZone);
            QBrush brush(Qt::lightGray, Qt::BDiagPattern);
            painter->setBrush(brush);
            painter->setPen(Qt::NoPen);
            painter->drawRect(dropZone);
        }
        if(offset > 0 || outerGroup)
            offset += itemSpacing;
        double verticalOffset = (height/2)-(rect.height()/2);
        if(!childItems().at(i)->isSelected())
            childItems().at(i)->setPos(offset, verticalOffset);
        offset += rect.width();
    }

    if(dragEvent && outerGroup)
    {
        QRectF dropZone(offset, 0, itemSpacing, height);
        dropZones.push_back(dropZone);
        QBrush brush(Qt::lightGray, Qt::BDiagPattern);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawRect(dropZone);
    }
}

void GroupingGraphicsItem::addChildItem(QGraphicsObject *item, bool updateFlag)
{
    item->setParentItem(this);
    connect(item, SIGNAL(dataChanged()), this, SLOT(updateData()));
    connect(item, SIGNAL(removeItem(QGraphicsObject*)), this, SLOT(removeChild(QGraphicsObject*)));
    if(updateFlag)
        updateData();
}

void GroupingGraphicsItem::setCapturingName(QString name)
{
    capturingName = name;
    updateData();
}

void GroupingGraphicsItem::setOuterGroup(bool outer)
{
    outerGroup = outer;
}

void GroupingGraphicsItem::setCapturing(bool capturing)
{
    isCapturing = capturing;
}

void GroupingGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    dragEvent = true;
    update();
}

void GroupingGraphicsItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if(validDropZone(event->pos()))
        event->acceptProposedAction();
    else
        event->ignore();
}

void GroupingGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
    dragEvent = false;
    update();
}

void GroupingGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    int offset;
    if((offset = dropZoneOffset(event->pos())) >= 0)
    {
        QGraphicsObject *item;

        if(event->mimeData()->hasFormat("text/x-regexp"))
        {
            event->acceptProposedAction();
            QString fragment = event->mimeData()->data("text/x-regexp");
            if(fragment.isEmpty())
                return;

            int regexpoffset = 0;
            item = GraphicalExpression::parseSection(fragment, regexpoffset);
            addChildItem(item, false);
        }
        else if(event->mimeData()->hasFormat("message/x-droptype"))
        {
            event->acceptProposedAction();
            qDebug() << "Drop Type: " << event->mimeData()->data("message/x-droptype");
            // handle each droptype with a specified dialog handler, then
            // use parseSection as above.
        }
        else
        {
            qDebug() << "Unexpected drop action";
            dragEvent = false;
            update();
            updateData();
            return;
        }

        if(!outerGroup)
            ++offset;
        if(offset < childItems().size())
        {
            item->stackBefore(childItems().at(offset));
        }

        dragEvent = false;
        update();
        updateData();
    }
}

/**
 * Public slots
 */
void GroupingGraphicsItem::removeChild(QGraphicsObject *item)
{
    if(isAncestorOf(item))
        delete item;
    updateData();
}

void GroupingGraphicsItem::updateData()
{
    QString expression;
    QStringList elements;
    for(int i = 0; i < childItems().size(); ++i)
        elements << childItems().at(i)->data(expressionData).toString();
    if(hasBrackets)
    {
        if(!capturingName.isEmpty())
            expression = QString("(?<") + capturingName + ">" + elements.join("") + ")";
        else if(isCapturing)
            expression = QString("(") + elements.join("") + ")";
        else
            expression = QString("(?:") + elements.join("") + ")";
    }
    else
        expression = elements.join("");
    setData(expressionData, QVariant(expression));
    emit dataChanged();
}

/**
 * Private methods
 */
bool GroupingGraphicsItem::validDropZone(QPointF position)
{
    for(int i = 0; i < dropZones.size(); ++i)
        if(dropZones.at(i).contains(position))
            return true;
    return false;
}

int GroupingGraphicsItem::dropZoneOffset(QPointF position)
{
    for(int i = 0; i < dropZones.size(); ++i)
        if(dropZones.at(i).contains(position))
            return i;
    return -1;
}
