#include "drawobjects.h"
#include <QtDebug>

RobotDraw::RobotDraw(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    team_color.resize(3);
    role_color.resize(3);
}

QRectF RobotDraw::boundingRect() const
{
    return QRectF(0, 0, radius, radius);
}

void RobotDraw::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int i, size = team_contour.size(), size1 = role_contour.size();
    QPainterPath team_shape, role_shape;
    QBrush team_brush(QColor(team_color[2], team_color[1], team_color[0]));
    QBrush role_brush(QColor(role_color[2], role_color[1], role_color[0]));

    if(size > 0){
        team_shape.moveTo(team_contour[0].x, team_contour[0].y);

        for(i = 1; i < size; i++){
            team_shape.lineTo(team_contour[i].x, team_contour[i].y);
        }
        team_shape.closeSubpath();
    }
    if(size1 > 0){
        role_shape.moveTo(role_contour[0].x, role_contour[0].y);
        for(i = 1; i < size1; i++){
            role_shape.lineTo(role_contour[i].x, role_contour[i].y);
        }
        role_shape.closeSubpath();
    }

    painter->setBrush(Qt::green);
    if(pos == Point(-1, -1)){
        pos = Point(1, 1);
    }

    painter->setBrush(team_brush);
    painter->drawPath(team_shape);
    painter->setBrush(role_brush);
    painter->drawPath(role_shape);
}

QPainterPath RobotDraw::shape()
{
    int i, size = team_contour.size(), size1 = role_contour.size();
    QPainterPath shape;

    shape.moveTo(team_contour[0].x, team_contour[0].y);

    for(i = 1; i < size; i++){
        shape.lineTo(team_contour[i].x, team_contour[i].y);
    }
    shape.moveTo(role_contour[0].x, role_contour[0].y);
    for(i = 1; i < size1; i++){
        shape.lineTo(role_contour[i].x, role_contour[i].y);
    }
    shape.closeSubpath();

    return shape;
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
        fieldPath.lineTo(fieldPoints[i].x, fieldPoints[i].y);
    }
    fieldPath.closeSubpath();

    return fieldPath;
}

BallDraw::BallDraw(QGraphicsItem *parent)
{
    color.resize(3, 0);
}

QRectF BallDraw::boundingRect() const
{
    return QRectF(0, 0, radius, radius);
}

void BallDraw::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath obj = shape();
    QBrush brush(QColor(color[2],color[1],color[0]));

    painter->setBrush(brush);
    painter->drawPath(obj);
}

QPainterPath BallDraw::shape()
{
    int i = 0, size = contour.size();
    QPainterPath shape;

    if(size > 0){
        shape.moveTo(contour[i].x, contour[i].y);

        for(i = 1; i < size; i++){
            shape.lineTo(contour[i].x, contour[i].y);
        }
        shape.closeSubpath();
    }

    return shape;
}

Enemy::Enemy(QGraphicsItem *parent)
{

}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, 0, radius, radius);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush red_brush(Qt::red);

    painter->setBrush(red_brush);
    painter->drawEllipse(pos.x, pos.y, radius, radius);
}
