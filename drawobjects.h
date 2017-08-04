#ifndef DRAWOBJECTS_H
#define DRAWOBJECTS_H

#include <QPainter>
#include <QGraphicsItem>
#include <opencv2/core.hpp>
#include <vector>

#include "utils.h"

class BallDraw : public QGraphicsItem
{
public:
    int radius = 15;
    cv::Point pos;
    BallDraw(QGraphicsItem* parent = NULL);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class RobotDraw : public QGraphicsItem
{
public:
    int radius = 25;
    double angle = 0;
    cv::Point pos;
    RobotDraw(QGraphicsItem* parent = NULL);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   // QPainterPath shape();
};

class FieldDraw : public QGraphicsItem
{
public:
    std::vector<cv::Point> fieldPoints;
    std::vector<cv::Point> atkPoints;
    std::vector<cv::Point> defPoints;

    FieldDraw(QGraphicsItem* parent = NULL);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape();
};

#endif // DRAWOBJECTS_H
