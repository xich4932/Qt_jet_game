#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "bar.h"
#include "plane.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void paintEvent(QPaintEvent *event);
    void collide_detection();
    void timer_event();
    void reward();
    Bullet * test = new Bullet(150,200,-1,missile);
    Enemy  enemy_[10];
    Enemy *boss = new Enemy(0,0, Enemy_type::boss_ufo);
    int right_bullet = 0;
    void enemyStrategy();
    void enemyTurn();
    int right_enemy = 0;
    void enemy_event();
    void checking_event();
    static const int posi[4];
    int start_flag = 0;
    void update_score_label();

protected:
    void keyPressEvent(QKeyEvent *event) ;

signals:
   // void keyPressEvent(QKeyEvent *keyevent) override;

private slots:
    void on_canvasButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_health;
    QGraphicsScene *scene_power;
    QGraphicsScene *scene_sky;
    HealthBar* health_ = new HealthBar(0, - 170,372); ;
    PowerBar* power_ = new PowerBar(0, 186 , 372);;
    Player * player_ = new Player (150,461);
    QTimer *enemy_showup = new QTimer(this);
    QTimer *timer = new QTimer(this);
    int score = 0;
};

#endif // MAINWINDOW_H
