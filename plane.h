#ifndef PLANE_H
#define PLANE_H

#include<QColor>
#include<QGraphicsItem>
#include<vector>
#include<iostream>
#include<QPixmap>

#define bullet_size 40

class Plane : public QObject, public QGraphicsItem {
public:
    QPixmap pix_map;
    Plane() {}
    virtual void shooting() = 0;
   // virtual void collisionDetection() = 0;

};


enum type {normal, missile, big_missile};
const int demage[4] = {20, 50,100};


class Bullet : public QObject, public QGraphicsItem {
public:
    Bullet();
    Bullet(int, int, int ,enum type t);
   // ~Bullet();
    QPixmap bullet_rec;//.load(:/plane/img/enemy_1.png);
    int get_x() {return x_;}
    int get_y() {return y_;}
    bool get_finished() {return finished;}
    void set_x(int x) { x_ = x;}
    void set_y(int y) { y_ = y;}
    void set_finished(bool b) {finished = b;}
    //positive direction right up
    void incre_x(int x) { x_ += x;}
    void incre_y(int y) { y_ += y;}

    void selfMovement( );

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static const int speed [3]; //= {19, 30, 30};
    static const int width_[3]; //= {15, 15, 20};
    static const int height_[3];// = {15, 57, 37};
    static const std::string rec_path_[3];

    enum type b_type = type::normal;
private:
    int x_;
    int y_;
    int demage;
    int dir;//(1,-1) //player's direction be positive, enemy be negative
    bool finished = 0; // 0 = ready to shoot, 1 = is running
};

class Player : public Plane{
public:
    Player();
    //QPixmap pix_map;

    Player(int, int);
    //positive direction right up
    void incre_x(int x) { x_ += x;}
    void incre_y(int y) { y_ += y;}

    void set_x(int x) {x_ = x;}
    void set_y(int y) {y_ = y;}
    int get_x() {return x_;}
    int get_y() {return y_;}
   // void decrease_hp(int);
   // void increase_power(int);
    void shooting() override;
    void upgrade_power(enum type);
    //void collisionDetection() override ;
    //attack();
    Bullet all_bullets [bullet_size];

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    void init_bullet();
    int left_bullet = 0;
    int right_bullet = 0;
private:
    int x_;
    int y_;
    int width_ = 50;
    int height_ = 50;
    QColor Qc_;

};

enum Enemy_type {ufo1,ufo2, boss_ufo};

class Enemy : public QObject, public QGraphicsItem{
public:
    //static const std::string path_enemy[2];
    static const int default_hp [3];
    static const std::string path_enemy[3];
    //static const int posi[6];
    Enemy();
    Enemy(int, int,enum Enemy_type);
    int get_x() {return x_;}
    int get_y() {return y_;}
    void set_x_y(int a, int b){x_ = a; y_ = b;}
    bool check_finished() {return is_finished;}
    void set_finished(bool b) {is_finished = b;}
    void incre_x(int x);// {x_ += x;}
    void incre_y(int y);// {y_ += y;}
    void restore();
    void decre_hp(int );
    bool check_alive();
    void shooting() ;
    //void set_type(enum Enemy_type ) { b}

    QPixmap enemy_pix;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    enum Enemy_type E_type;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    static const int width_[3];
    static const int height_[3];
private:
    int x_;
    int y_;
    int hp;
    //enum Enemy_type;
    bool is_finished = 0;
    bool is_alive = 0;
};

#endif
