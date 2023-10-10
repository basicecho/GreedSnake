#ifndef SNAKE_H
#define SNAKE_H

#include <QDebug>
#include <QImage>
#include <QList>
#include <QRectF>
#include <QSize>
#include <QTransform>

class Snake
{
public:
    enum Move {
        Down, Left, Up, Right
    };

    Snake(int width = 30, int height = 30);

    // 身体边长是通过将头部进行移动形成的
    void addRectF();

    QRectF* getSnakeHead();
    QList<QRectF> getSnakeBody();
    void deleteSnakeTail();

    const Move getDirection();
    void setDirection(Move newDirection);
    bool isEating(QRectF apple);
    bool isOutGame();
    QImage getHeadImage();


private:
    QRectF* snakeHead;
    QList<QRectF> snakeBody;
    QImage headImage;
    QImage images[4];

    Move direction = Down;

};

#endif // SNAKE_H
