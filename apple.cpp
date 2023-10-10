#include "apple.h"

// 使用继承的关系进行构造
Apple::Apple(int width, int height):QRectF(0, 0, width, height)
{
    image.load(":/images/apple.png");

    image = image.scaled(QSize(this->width(), this->height()), Qt::KeepAspectRatio);
}

int Apple::getReward()
{
    return reward;
}

void Apple::setReward(int newReward)
{
    reward = newReward;
}

QImage Apple::getImage()
{
    return image;
}
