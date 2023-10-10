#include "snake.h"

Snake::Snake(int width, int height)
{
    snakeHead = new QRectF(30, 30, width, height);

    headImage.load(":/images/Down.png");
    headImage = headImage.scaled(QSize(snakeHead->width(), snakeHead->height()), Qt::KeepAspectRatio);

    // 进行旋转，并保存四张图片
    for(int i = 0; i < 4; i++) {
        QTransform rotation;
        rotation.rotate(90 * i);
        images[i] = headImage.transformed(rotation);
    }

    for(int i = 0; i < 3; i++) {
        addRectF();
    }
}

void Snake::addRectF()
{
    // 又被指针坑了
    snakeBody.prepend(*snakeHead);

    headImage = images[direction];
    switch(direction) {
    case Down:
        *snakeHead = snakeHead->translated(0, snakeHead->height());
        break;
    case Left:
        *snakeHead = snakeHead->translated(-snakeHead->width(), 0);
        break;
    case Up:
        *snakeHead = snakeHead->translated(0, -snakeHead->height());
        break;
    case Right:
        *snakeHead = snakeHead->translated(snakeHead->width(), 0);
        break;
    }
}

QRectF* Snake::getSnakeHead()
{
    return snakeHead;
}

QList<QRectF> Snake::getSnakeBody()
{
    return snakeBody;
}

void Snake::deleteSnakeTail()
{
    snakeBody.removeLast();
}

const Snake::Move Snake::getDirection()
{
    return direction;
}

void Snake::setDirection(Move newDirection)
{
    direction = newDirection;
}

bool Snake::isEating(QRectF apple)
{
    if(apple == *snakeHead)return true;
    for(int i = 0; i < snakeBody.size(); i++) {
        if(apple == snakeBody.at(i)) {
            return true;
        }
    }
    return false;
}

bool Snake::isOutGame()
{
    for(int i = 0; i < snakeBody.size(); i++) {
        if(*snakeHead == snakeBody.at(i)) {
            return true;
        }
    }
    return false;
}

QImage Snake::getHeadImage()
{
    return headImage;
}
