#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTime>
#include <QKeyEvent>
#include <QRect>
#include <vector>
#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plane.h"
#include "bar.h"

#define window_width 341
#define window_height 511
#define player_width 50
#define player_height 50

const int MainWindow::posi[4] = {0, 77, 154, 231};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //hp graphic scene
    scene_power = new  QGraphicsScene;
    QGraphicsView * view_power = ui->power_bar_1;
    view_power->setScene(scene_power);
    view_power->setSceneRect(0,0,view_power->frameSize().width(),view_power->frameSize().height());
   // power_null = nullptr;
   // PowerBar * power_ = new PowerBar(0, 190,360);
    scene_power->addItem(power_);
   // view_power->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view_power->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //initial rand seed
    srand(static_cast<unsigned>(QTime::currentTime().msec()));

    player_->set_x(120);  player_->set_y(461);
    //player_[1]->set_x(180);  player_[1]->set_y(461);

    scene_health = new  QGraphicsScene;
    QGraphicsView * view_health = ui->health_bar_1;
    view_health->setScene(scene_health);
    view_health->setSceneRect(0,0,view_health->frameSize().width(),view_health->frameSize().height());
    //health_null = nullptr;
   // HealthBar * health_ = new HealthBar(0, - 170,360);
    scene_health->addItem(health_);
    //view_heal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view_power->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene_sky = new  QGraphicsScene;
    QGraphicsView * view_sky = ui->sky;


    view_sky->setScene(scene_sky);
    view_sky->setSceneRect(0,0,view_sky->frameSize().width(),view_sky->frameSize().height());
    //view_sky->setSceneRect(0,0,9999,9999);

   // Bullet *test_bullet_1 = new Bullet(player_->get_x(),player_->get_y() - 200,-1,type::missile);
    //scene_sky->addItem(test_bullet_1);
    scene_sky->addItem(player_);
    scene_sky->addItem(boss);

    setFocus();
    this->setFocusPolicy(Qt::StrongFocus);

    timer->setInterval(50);
    enemy_showup->setInterval(1000);

    for(int i = 0; i < bullet_size; i++){
        scene_sky->addItem(&player_->all_bullets[i]);
        scene_sky->addItem(&boss->enemy_bullet[i]);
    }

    for(int e = 0; e < 10; e++){
        scene_sky->addItem(&enemy_[e]);
        enemy_[e].setEnabled(0);
    }

   connect(timer,&QTimer::timeout,this,&MainWindow::timer_event);
   connect(enemy_showup,&QTimer::timeout,this,&MainWindow::enemy_event);
   update();
}

void MainWindow::collide_detection(){
    for(int b = 0; b < bullet_size; b++){
        if(! player_->all_bullets[b].get_finished()) continue;
        for(int e = 0; e < 10; e++){
            if(player_->all_bullets[b].get_finished() && enemy_[e].check_finished() && player_->all_bullets[b].boundingRect().intersects(enemy_[e].boundingRect())){
                enemy_[e].decre_hp(demage[player_->all_bullets[e].b_type]);
                player_->all_bullets[b].set_finished(0);
                if(! enemy_[e].check_alive()){
                    enemy_[e].set_finished(0);
                    enemy_[e].restore();
                    power_->set_height(5);
                    reward();
                    update_score_label();
                }
            }
            if(enemy_[e].check_finished() && enemy_[e].boundingRect().intersects(player_->boundingRect())){
                health_->set_height(5);
                enemy_[e].set_finished(0);
                enemy_[e].restore();
            }
            if(boss_showup){

                if(player_->all_bullets[b].get_finished() && player_->all_bullets[b].boundingRect().intersects(boss->boundingRect())){
                    boss->decre_hp(demage[player_->all_bullets[e].b_type]);
                }
            }
        }
    }

}

void MainWindow::update_score_label(){
    score += 100;
    ui->score_number_1->setText(QString::number(score));
}

void MainWindow::checking_event(){
    double power_percent = power_->get_percent();
    if(power_percent >= 100){
        //player_->upgrade_power(missile);
        if(upgradable < 2){
            ui->text_1->setText("press space");
        }else{
            ui->text_1->setText("");
        }

    }else if(power_percent >= 50){
        //player_->upgrade_power(big_missile);
        if(upgradable < 1){
            ui->text_1->setText("press space");
        }else{
            ui->text_1->setText("");
        }

    }                                                       //2000
    if(!boss_showup && ui->score_number_1->text().toInt() >= 2000){
        //scene_sky->addItem(boss);
        boss->set_finished(1);
        boss_showup = 1;
    }
    end_game();
    //if(boss_showup && )
}

/*
void MainWindow::paintEvent(QPaintEvent *event){
    QPainter new_painter (this);
   // Bullet test_b(50,100,1,type::normal);
   // new_painter.drawPixmap(test_b.get_x(), test_b.get_y(), 50, 50, test_b.bullet_rec);
    //new_painter.drawPixmap(player_->get_x(), player_->get_y(),100,100,player_->pix_map);
    //scene_sky->addItem(player_);

   // new_painter.drawPixmap(150,250,50,50, player_->pix_map );
   // qDebug() << "print";
    player_->all_bullets[(right_bullet + 1) % bullet_size].set_finished(1);
    right_bullet ++;
    /*
    for(int i = 0; i < bullet_size; i++){
        //if(! player_->all_bullets[i].get_finished()){
            player_->all_bullets[i].selfMovement();
            if(! player_->all_bullets[i].get_finished()){
                new_painter.drawPixmap(player_->all_bullets[i].get_x(), player_->all_bullets[i].get_y(),
                                       50, 50,
                                       player_->all_bullets[i].bullet_rec);
                qDebug() <<"print bullet " << right_bullet;
           // }
            }

    }
    */



void MainWindow::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Up){
        player_->incre_y(-10);
    }else if(event->key() == Qt::Key_Down){
        player_->incre_y(10);
    }else if(event->key() == Qt::Key_Left){
        player_->incre_x(-10);
    }else if(event->key() == Qt::Key_Right){
        player_->incre_x(10);
    }else if(event->key() == Qt::Key_Space){
        double pow_per = power_->get_percent();
        if(pow_per >= 100){
            upgradable ++;
            player_->upgrade_power(missile);
        }else if(pow_per >= 50){
            upgradable ++;
            player_->upgrade_power(big_missile);
        }
    }

    scene_sky->update();
}

void MainWindow::timer_event(){
    player_->shooting();
    scene_sky->update();
    scene_power->update();
    scene_health->update();
    if(boss_showup)
        boss->shooting();
    checking_event();
}

void MainWindow::end_game(){
    if(health_->get_percent() <= 0){
        //enemy_showup->stop();
        on_canvasButton_clicked();
        ui->text_1->setText("you lose");
        //timer->stop();
        qDebug() <<"you die";
    }else if(boss_showup && ! boss->check_alive()){
        on_canvasButton_clicked();
        ui->text_1->setText("you win");
        qDebug() <<"you win";
    }
}

void MainWindow::reward(){
    power_->set_height(5);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player_;
}

void MainWindow::enemy_event(){
    enemyTurn();
    enemyStrategy();
    collide_detection();
    boss_shooting_detection();
}

void MainWindow::on_canvasButton_clicked()
{

    if(! start_flag ){
        timer->start();
        enemy_showup->start();
        //ui->canvasButton
        ui->canvasButton->setText("pause");
    }else{
        timer->stop();
        enemy_showup->stop();
        ui->canvasButton->setText("play");
    }
    start_flag = 1 - start_flag;
}


void MainWindow::enemyStrategy(){
    for(int i = 0; i < 10; i++){
        if(enemy_[i].check_finished()){
                enemy_[i].incre_y(60);
        }
    }
}

void MainWindow::boss_shooting_detection(){
    if(! boss_showup) return;
    for(int b = 0; b < bullet_size; b++){
        if(boss->enemy_bullet[b].get_finished() && boss->enemy_bullet[b].boundingRect().intersects(player_->boundingRect())){
            health_->set_height(7);
        }
    }

}

//each turn, 30% chance for a inactive enemy to be active
void MainWindow::enemyTurn(){
    right_enemy = (right_enemy + 1) % 10;
    if(! enemy_[right_enemy].check_finished()){
        if(rand() % 9 > 3 ){
            right_enemy = (right_enemy + 1) % 10;
            //when score is over 600, there 2/3 another enemy will show up
            if(ui->score_number_1->text().toInt() > 600 && rand() % 3 > 1){
                enemy_[right_enemy].E_type = ufo2;
                enemy_[right_enemy].restore_hp();
            }
            enemy_[right_enemy].set_finished(1);
            enemy_[right_enemy].setEnabled(1);
            enemy_[right_enemy].set_x_y(posi[rand()% 4] ,0);
        }
    }
}
