#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1500,900);
    setWindowIcon(QIcon(":/image/fruits.png"));
    setWindowTitle("水果保卫战");
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/image/start.png");
    startBtn->setParent(this);
    startBtn->move (this->width()*0.5 - startBtn->width()*0.5,this->height()*0.4);//设置按钮位置

    chooseScene = new ChooseLevelScene;

    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
            chooseScene->hide();
            this->show();
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击开始";
        //点击弹起
        startBtn->zoomup();
        startBtn->zoomdown();

        //选择关卡
        //延时进入
        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseScene->show();
        });
    });
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}

MainWindow::~MainWindow()
{
    delete ui;
}

