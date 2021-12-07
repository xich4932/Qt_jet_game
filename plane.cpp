#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QDebug>
#include <QPixmap>
#include <QList>
#include "plane.h"
#include "bar.h"

//80*339

const int Bullet::speed [4] = {19, 19, 19, 19};
const int Bullet::width_[4] = {10, 25, 15, 11}; //{50, 15, 20};
const int Bullet::height_[4] ={10, 43, 57, 50}; // {15, 57, 37};
const std::string Bullet::rec_path_[4] = {":/plane/img/missile.png",":/plane/img/missile23.png", ":/plane/img/missile.png", ":/plane/img/enemymissile.png"};
const std::string Enemy::path_enemy[3] = {":/plane/img/ufo1.png", ":/plane/img/ufo2.png",":/plane/img/boss.png" };
const int Bullet::enemy_bullet_poi[3] = {85, 255, 395};
const int Enemy::width_[3] = {50,50,341 };
const int Enemy::height_[3] = {32,33,206 };
const int Enemy::default_hp [3] = {100, 500,80000};

int Enemy::bullet_idx = 0;
/*
void Player::init_bullet(){

    for(int i = 0; i < bullet_size; i++){
        all_bullets[i].set_x(this->x_);
        all_bullets[i].set_y(this->y_);
    }

}
*/

Player::Player(){
    pix_map.load(":/plane/img/jet.png");
    //pix_map.fill(Qt::transparent);
    x_ = 150;
    y_ = 461;
    //init_bullet();
}



Player::Player(int x, int y) : x_(x), y_(y){
    pix_map.load(":/plane/img/jet.png");
   // pix_map.fill(Qt::transparent);
   // init_bullet();
}

QRectF Player::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

// define the actual shape of the object
QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

// called by Qt to actually display the point
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->boundingRect();
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    //painter->drawImage(QRectF(this->x_, this->y_,width_,height_),QImage(":/plane/img/player.png"));
    painter->drawPixmap(this->x_, this->y_, this->width_, this->height_, pix_map);
    prepareGeometryChange();
    //painter->drawRect(this->x_, this->y_, this->width_, this->height_);
    update();
}

void Player::shooting(){
   // all_bullets->selfMovement();

    //all_bullets[(right_bullet + 1) % bullet_size].set_finished(1);
    //edge case: when bullet are all running in the sky, it will reset the olest bullet

    right_bullet = (right_bullet + 1) % bullet_size;
    if( ! all_bullets[right_bullet].get_finished()) all_bullets[right_bullet].set_finished(1);
   // bool activate_one = 0;
    for(int i = 0; i < bullet_size ; i ++){
      //  qDebug() << all_bullets[i].get_x() <<" "<< all_bullets[i].get_y();
        if(all_bullets[i].get_finished()){
            all_bullets[i].selfMovement();
        }else{
            all_bullets[i].set_x(this->x_);
            all_bullets[i].set_y(this->y_ - 30);
        }
    }

}

void Player::upgrade_power(enum type t){
    for(int b = 0; b < bullet_size; b++)
        all_bullets[b].b_type = t;
}


Bullet::Bullet(){
    x_= 150, y_ = 461, dir = -1;
    b_type = type::normal;
    bullet_rec.load(QString::fromStdString(rec_path_[b_type]));
   // bullet_rec.fill(Qt::transparent);
}

Bullet::Bullet(int x, int y, int d,enum type t): x_(x), y_(y), dir(d), b_type(t){
    bullet_rec.load(QString::fromStdString(rec_path_[b_type]));
    //bullet_rec.fill(Qt::transparent);
}

QRectF Bullet::boundingRect() const {
    return QRectF(x_, y_, width_[b_type], height_[b_type]);
}

QPainterPath Bullet::shape() const {
    QPainterPath path;
    if(b_type == normal){
        path.addEllipse(x_, y_, width_[b_type], width_[b_type]);
    }else{
        path.addRect(x_, y_, width_[b_type], height_[b_type]);
    }
    return path;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);
    prepareGeometryChange();
    bullet_rec.load(QString::fromStdString(rec_path_[b_type]));
    if(finished){
        if(b_type == normal){
            QColor qc_ = QColor(96,8,71);
            QBrush b = painter->brush();
            painter->setBrush(QBrush(qc_));
            painter->drawEllipse(QRect(this->x_, this->y_, width_[b_type], height_[b_type]));
            painter->setBrush(b);
        }else if(b_type == missile){
            painter->setRenderHint(QPainter::SmoothPixmapTransform);
            //painter->drawImage(QRectF(this->x_, this->y_,width_[b_type], width_[b_type]),QImage(":/plane/img/missile.png"));
            painter->drawPixmap(this->x_, this->y_,width_[1], height_[1],bullet_rec);
        }else{
            painter->setRenderHint(QPainter::SmoothPixmapTransform);
            //painter->drawImage(QRectF(this->x_, this->y_,width_[b_type], width_[b_type]),QImage(":/plane/img/missile_2.png"));
            painter->drawPixmap(this->x_, this->y_,width_[2], height_[2],bullet_rec);
        }
       // painter->drawRect(this->x_, this->y_, width_[b_type], height_[b_type]);
    }
}



void Bullet::selfMovement(){
  // if( finished ) return;
   // for(int i = 0; i < bullet_size; i++){

    y_ += (speed[b_type] * dir);
  //  }
    if(y_ > 511 || y_< 0) finished = 0;
}

void Enemy::init_bullet(){
    for(int i = 0; i < bullet_size; i++){
        enemy_bullet[i].set_dir(1);
        enemy_bullet[i].set_x(Bullet::enemy_bullet_poi[i % 3]);
        enemy_bullet[i].b_type = enemy_missile;
       // enemy_bullet[i].bullet_rec.load(":/plane/img/enemymissile.png");
    }


}

Enemy::Enemy(){
    x_ = 0;
    y_ = 0;
    hp = default_hp[ufo1];
    E_type = ufo1;
    //is_boss = 0;
    //enemy_pix.load(QString::fromStdString(path_enemy[ufo]));
    enemy_pix.load(":/plane/img/enemy_1.png");
    init_bullet();
}

Enemy::Enemy(int a, int b,enum Enemy_type t):x_(a), y_(b),E_type(t){
   // enemy_pix.load(QString::fromStdString(path_enemy[t]));
    hp = default_hp[t];
    enemy_pix.load(QString::fromStdString(path_enemy[E_type]));
    init_bullet();
    
}

void Enemy::shooting(){
    bullet_idx = (bullet_idx + 1) % bullet_size;
    if(!enemy_bullet[bullet_idx].get_finished())
        enemy_bullet[bullet_idx].set_finished(1);
        //enemy_bullet[bullet_idx].selfMovement();
    for(int i = 0; i < bullet_size ; i ++){
      //  qDebug() << "shooting";
      //  qDebug() << all_bullets[i].get_x() <<" "<< all_bullets[i].get_y();
        if(enemy_bullet[i].get_finished()){
            enemy_bullet[i].selfMovement();
        }else{
            //enemy_bullet[i].set_x(this->x_);
            enemy_bullet[i].set_y(this->y_ + 30);
        }
    }
}

void Enemy::decre_hp(int de){
    hp -= de;
}

bool Enemy::check_alive(){
    if(hp <= 0)
        return 0;
    return 1;
}

QRectF Enemy::boundingRect() const {
    return QRectF(x_, y_, width_[E_type], height_[E_type]);
}

QPainterPath Enemy::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_[E_type], height_[E_type]);
    return path;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(widget);
    enemy_pix.load(QString::fromStdString(path_enemy[E_type]));
    if(is_finished){
        prepareGeometryChange();
        painter->setRenderHint(QPainter::SmoothPixmapTransform);
        painter->drawPixmap(this->x_, this->y_,width_[E_type], height_[E_type], enemy_pix);
    }
}

void Enemy::incre_x(int x){
    x_ += x;
    if(x_ < 0 || x> 341)
       restore();

}
    // {x_ += x;}
void Enemy::incre_y(int y){
    y_ += y;
    if(y_ < 0 || y_ > 511) restore();
}

void Enemy::restore(){
    hp = default_hp[E_type];
    is_finished = 0;
}







