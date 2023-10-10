#include "game.h"
#include "./ui_game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    resize(1200, 1200);
    setWindowTitle("贪吃蛇小游戏");
    setStyleSheet("background-color: lightgreen");

    mySnake = new Snake();

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSnake()));
    timer->start();

    appleTimer = new QTimer(this);
    appleTimer->setInterval(5000);
    connect(appleTimer, SIGNAL(timeout()), this, SLOT(updateApple()));
    appleTimer->start();

}

Game::~Game()
{
    delete ui;
}

bool Game::checkOutRange()
{
    const QPointF topLeft = mySnake->getSnakeHead()->topLeft();
    const QPointF bottomRight = mySnake->getSnakeHead()->bottomRight();
    if(topLeft.x() < 0 || topLeft.y() < 0) return true;
    if(bottomRight.x() > width() || bottomRight.y() > height()) return true;
    return false;
}

void Game::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    pen.setColor(Qt::black);                // 边框颜色
    brush.setColor(Qt::green);              // 填充颜色
    brush.setStyle(Qt::SolidPattern);       // 实心填充
    painter.setPen(pen);
    painter.setBrush(brush);

    for(int i = 0; i < apples.size(); i++)
        if(mySnake->isEating(apples.at(i))) {
            socres += apples.at(i).reward;
            mySnake->addRectF();
            apples.resize(i);
    }


    if(mySnake->isOutGame()) gameOver = true;

    if(gameOver) {
        timer->stop();
        appleTimer->stop();
        QFont font("Arial", 40);
        painter.setFont(font);
        QPoint socrePosition(this->width() / 2 - 80, 300);
        painter.drawText(socrePosition, QString("游戏结束，你的得分是：") + QString("%1").arg(socres));
    }

    painter.drawImage(*mySnake->getSnakeHead(), mySnake->getHeadImage());

    brush.setColor(Qt::darkGreen);
    painter.setBrush(brush);

    const QList<QRectF> snakeBody = mySnake->getSnakeBody();
    for(int i = 0; i < snakeBody.size(); i++) {
        painter.drawRect(snakeBody.at(i));
    }

    for(int i = 0; i < apples.size(); i++) {
        painter.drawImage((QRectF)apples.at(i), apples[i].getImage());
    }

    QFont font("Arial", 20);
    painter.setFont(font);
    painter.setPen(QColor(Qt::black));
    QPoint socrePosition(this->width() / 2 - 80, 30);
    painter.drawText(socrePosition, QString("当前得分：") + QString("%1").arg(socres));
}

void Game::keyPressEvent(QKeyEvent* event)
{
    switch(event->key()) {
    case Qt::Key_Up:
        if(mySnake->getDirection() != Snake::Down) {
            mySnake->setDirection(Snake::Up);
        }
        break;
    case Qt::Key_Down:
        if(mySnake->getDirection() != Snake::Up) {
            mySnake->setDirection(Snake::Down);
        }
        break;
    case Qt::Key_Left:
        if(mySnake->getDirection() != Snake::Right) {
            mySnake->setDirection(Snake::Left);
        }
        break;
    case Qt::Key_Right:
        if(mySnake->getDirection() != Snake::Left) {
            mySnake->setDirection(Snake::Right);
        }
        break;
    }

    update();
}

void Game::updateSnake()
{
    mySnake->addRectF();
    mySnake->deleteSnakeTail();
    if(checkOutRange()) gameOver = true;
    update();
}

void Game::updateApple()
{
    QRandomGenerator random;
    random.seed(time(0));
    if(apples.size() == rewardMax)
        apples.remove(random.bounded(rewardMax));
    Apple apple;
    int rangeX = width() / apple.width();
    int rangeY = height() / apple.height();

    int x = random.bounded(rangeX) * apple.width();
    int y = random.bounded(rangeY) * apple.height();
    apple.translate(x, y);
    apples.append(apple);


    update();
}
