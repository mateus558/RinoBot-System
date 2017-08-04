#include "drawobjects.h"
#include <QtDebug>

RobotDraw::RobotDraw(QGraphicsItem *parent) : QGraphicsItem(parent)
{

}

QRectF RobotDraw::boundingRect() const
{
    return QRectF(0, 0, radius, radius);
}

void RobotDraw::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(pos.x, pos.y, radius, radius);
}

FieldDraw::FieldDraw(QGraphicsItem *parent) : QGraphicsItem(parent)
{

}

QRectF FieldDraw::boundingRect() const
{
    return QRectF(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
}

void FieldDraw::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x = fieldPoints[0].x, y = (fieldPoints[0].y + fieldPoints[9].y)/2;
    int i;
    QPen pen(Qt::white, 4);
    QPainterPath fieldPath = shape(), atkPath, defPath;

    defPath.moveTo(defPoints[0].x, defPoints[0].y);
    atkPath.moveTo(atkPoints[0].x, atkPoints[0].y);
    for(i = 1; i < defPoints.size(); i++){   
        defPath.lineTo(defPoints[i].x, defPoints[i].y);
    }
    for(i = 1; i < atkPoints.size(); i++){
        atkPath.lineTo(atkPoints[i].x, atkPoints[i].y);
    }
    defPath.closeSubpath();
    atkPath.closeSubpath();

    painter->setPen(pen);
    painter->drawPath(fieldPath);
    painter->drawPath(defPath);
    painter->drawPath(atkPath);
    painter->drawLine(fieldPoints[0].x, fieldPoints[0].y, fieldPoints[9].x, fieldPoints[9].y);
    painter->drawLine(defPoints[2].x, defPoints[2].y, defPoints[5].x, defPoints[5].y);
    painter->drawLine(atkPoints[2].x, atkPoints[2].y, atkPoints[5].x, atkPoints[5].y);
    painter->drawEllipse(x-50, y-50, 100, 100);
}

QPainterPath FieldDraw::shape()
{
    QPainterPath fieldPath;
    int i, n = fieldPoints.size();

    fieldPath.moveTo(fieldPoints[0].x, fieldPoints[0].y);

    for(i = 1; i < n; i++){
        qDebug() << "Point:" << fieldPoints[i].x << " " << fieldPoints[i].y;
        fieldPath.lineTo(fieldPoints[i].x, fieldPoints[i].y);
    }
    fieldPath.closeSubpath();

    return fieldPath;
}

BallDraw::BallDraw(QGraphicsItem *parent)
{

}

QRectF BallDraw::boundingRect() const
{
    return QRectF(0, 0, radius, radius);
}

void BallDraw::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush orangeBrush(QColor(255,165,0));

    painter->setBrush(orangeBrush);
    painter->drawEllipse(pos.x, pos.y, radius, radius);
}
