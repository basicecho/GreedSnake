#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "apple.h"

#include <QDebug>
#include <QList>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QPoint>
#include <QImage>
#include <QMessageBox>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    bool checkOutRange();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateSnake();
    void updateApple();

private:    
    Ui::Game *ui;
    Snake* mySnake;
    QList<Apple> apples;

    int rewardMax = 3;
    int socres = 0;
    bool gameOver = false;

    QTimer* timer;
    QTimer* appleTimer;

};
#endif // GAME_H
