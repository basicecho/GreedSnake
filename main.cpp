#include "game.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game w;
    w.show();

    QScreen* screen = a.primaryScreen();
    int screenWidth = screen->size().width();
    int screenHeight = screen->size().height();
    w.move((screenWidth - w.width()) / 2, (screenHeight - w.height()) / 2);

    return a.exec();
}
