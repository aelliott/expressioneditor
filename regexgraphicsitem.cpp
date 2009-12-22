#include "regexgraphicsitem.hpp"

RegexGraphicsItem::RegexGraphicsItem(QGraphicsItem *parent) : QGraphicsObject(parent)
{
}

void RegexGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void RegexGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(event->widget());
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(this->data(expressionData).toString());
    drag->setMimeData(mimeData);

    QPixmap image(this->boundingRect().width()*0.75, this->boundingRect().height()*0.75);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene()->render(&painter, QRectF(), this->sceneBoundingRect());
    painter.end();

    drag->setPixmap(image);

    Qt::DropAction dropAction = drag->exec();
    Q_UNUSED(dropAction);
}
