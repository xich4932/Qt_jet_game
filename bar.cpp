#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "bar.h"
//80 * 339

QRectF PowerBar::boundingRect() const
{
    return QRectF(power_x, power_y, width_, height_);
}

// define the actual shape of the object
QPainterPath PowerBar::shape() const
{
    QPainterPath path;
    path.addRect(power_x, power_y, width_, height_);
    return path;
}

// called by Qt to actually display the point
void PowerBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    qc_ = QColor(24,123,254);
    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setPen(qc_);
    painter->setBrush(QBrush(qc_));
    //qDebug() << this->x_ <<" " << this->y_ << " " << this->width_ << " "<<this->height_;
    painter->drawRect(QRect(this->power_x, this->power_y, this->width_, this->height_));
    painter->setBrush(b);
}



QRectF HealthBar::boundingRect() const
{
    return QRectF(health_x, health_y, width_, height_);
}

// define the actual shape of the object
QPainterPath HealthBar::shape() const
{
    QPainterPath path;
    path.addRect(health_x, health_y, width_, height_);
    return path;
}

// called by Qt to actually display the point
void HealthBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    double rate = this->get_percent();
   // qDebug() << rate ;
    if(rate > 66){
        qc_ = Qt::green;
    }else if(rate > 33){
        qc_ = QColor(255,140,0);
    }else{
        qc_ = Qt::red;
    }
   // qc_ = QColor(24,123,254);
    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setPen(qc_);
    painter->setBrush(QBrush(qc_));
    //qDebug() << this->x_ <<" " << this->y_ << " " << this->width_ << " "<<this->height_;
    painter->drawRect(QRect(this->health_x, this->health_y, this->width_, this->height_));
    painter->setBrush(b);
}



