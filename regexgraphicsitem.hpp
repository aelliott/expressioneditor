#ifndef REGEXGRAPHICSITEM_HPP
#define REGEXGRAPHICSITEM_HPP

#include <QApplication>
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsScene>

class RegexGraphicsItem : public QGraphicsObject
{
    Q_OBJECT;

public:
    explicit RegexGraphicsItem(QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

protected:
    static const int expressionData = 0;
    QPointF dragStartPosition;
};

#endif // REGEXGRAPHICSITEM_HPP
