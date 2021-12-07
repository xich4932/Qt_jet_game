#ifndef BAR_H
#define BAR_H

#include<QColor>
#include<QGraphicsItem>
// 80 * 339

class Bar : public QObject, public QGraphicsItem {
public:
    Bar() {}
    //Bar(int x, int y, int w, int h): x_(x), y_(y),width_(w),height_(h),full_height(h){}
    virtual int get_x() = 0;
    virtual int get_y() = 0;
    //virtual int get_height() = 0;
    virtual void set_height()= 0;
    virtual double get_percent() = 0;
    double step = 3;
};

class PowerBar : public Bar {
public:
    PowerBar(){}
    PowerBar(int x, int y, int h ): power_x(x), power_y(y), full_height(h){
        five_percent = full_height / 20;
    }
       //five_percent = full_height / 20;

    int get_x() {return power_x;}
    int get_y() {return power_y;}
    int get_height() {return height_;}
    void set_height() {height_ += five_percent; power_y -= five_percent;}
    double get_percent() {return (full_height/2 - power_y) * 100 / full_height;}
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    int power_x;
    int power_y;
    int height_ = 0;
    int full_height = 360;
    double five_percent = full_height / 20;
    int width_ = 80;
    QColor qc_;
};

class HealthBar : public Bar {
public:
    HealthBar() {}
    HealthBar(int x, int y, int h): health_x(x), health_y(y), height_(h), full_height(h){
        five_percent = full_height / 20;
    }


    int get_x() {return health_x;}
    int get_y() {return health_y;}
    //int get_height() {return height_;}
    void set_height() { height_ -= five_percent; health_y += five_percent;}
    double get_percent() {return (full_height/2 - health_y) * 100 / full_height ;}

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    int health_x;
    int health_y;
    int height_;
    int width_ = 80;
    int full_height = 370;
    double five_percent = 370 / 20;
    QColor qc_;

};

#endif
