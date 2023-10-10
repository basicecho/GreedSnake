#ifndef APPLE_H
#define APPLE_H

#include <QObject>
#include <QRectF>
#include <QImage>

class Apple: public QRectF
{
public:
    Apple(int width = 30, int height = 30);
    int getReward();
    void setReward(int newReward);
    QImage getImage();


    int reward = 10;

private:
    QImage image;


};

#endif // APPLE_H
