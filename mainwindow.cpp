#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameid(0)
    , background(":/image/background.png")
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/fruits.png"));
    setWindowTitle("defend fruit");
    QIcon icon(":/image/start.png");
    ui->pushButton->setIcon(icon);
    ui->pushButton->setIconSize(QSize(200, 200));
    connect(ui->pushButton,SIGNAL(clicked()),this, SLOT(startButtonEvent()));
    QIcon icon2(":/image/selection1.png");
    ui->pushButton_2->setIcon(icon2);
    ui->pushButton_2->setIconSize(QSize(200, 200));

    QIcon icon3(":/image/selection2.png");
    ui->pushButton_3->setIcon(icon3);
    ui->pushButton_3->setIconSize(QSize(200, 200));

    QIcon icon4(":/image/selection3.png");
    ui->pushButton_4->setIcon(icon4);
    ui->pushButton_4->setIconSize(QSize(200, 200));

    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    connect(ui->pushButton_2,SIGNAL(clicked()),this, SLOT(gameButton2Event()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this, SLOT(gameButton3Event()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this, SLOT(gameButton4Event()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(background.c_str());
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void MainWindow::startButtonEvent(){
    ui->pushButton->hide();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
    background = ":/image/background2.png";
    repaint();
}

void MainWindow::gameButton2Event(){
    gameid = 1;
    close();
}

void MainWindow::gameButton3Event(){
    gameid = 2;
    close();
}

void MainWindow::gameButton4Event(){
    gameid = 3;
    close();
}
