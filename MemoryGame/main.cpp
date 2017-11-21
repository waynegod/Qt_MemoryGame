#include "widget.h"
#include "topiclist.h"
#include "ui_widget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget game;
    game.show();

    game.uiset();

    return a.exec();
}

