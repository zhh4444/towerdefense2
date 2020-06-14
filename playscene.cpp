#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QTimer>
#include "chooselevelscene.h"
#include <QPainter>
PlayScene::PlayScene (int levelNum){
    QString str = QString("你选择第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;
    setFixedSize(1500,900);
    setWindowIcon(QIcon(":/image/fruits.png"));
    setWindowTitle("水果保卫战");

    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
}

void PlayScene::paintEvent(QPaintEvent *){
         QPainter painter(this);
         QPixmap pix;
         pix.load(":/image/map1.png");
         painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
