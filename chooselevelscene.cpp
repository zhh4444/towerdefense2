#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include "playscene.h"
#include <QLabel>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1500,900);
    setWindowIcon(QIcon(":/image/fruits.png"));
    setWindowTitle("选择关卡");
    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/image/back.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击返回";
        //返回主场景
        QTimer::singleShot(500,this,[=]{
            emit this->chooseSceneBack();
        });
    });

    for(int i=0;i<3;i++){
        MyPushButton * menuBtn = new MyPushButton(":/image/selectionbutton.png");
        menuBtn->setParent(this);
        menuBtn->move(700,200+200*i);

        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str = QString("你选择第%1关").arg(i+1);
            qDebug()<<str;
            menuBtn->zoomup();
            menuBtn->zoomdown();

            //进入游戏场景
            play = new PlayScene(i+1);
            QTimer::singleShot(500,this,[=](){
                this->hide();
                play->show();
            });
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(780,200+200*i);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background2.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
