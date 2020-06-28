#include "mainwindow.h"
#include "towerdefence.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow startWin;
    startWin.show();
    a.exec();
    int gameid = startWin.getGameID();
    if (gameid == 0){
        return 0;
    }
    TowerDefence w(gameid);
    w.show();
    return a.exec();
}
