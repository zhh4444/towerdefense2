#include "mypushbutton.h"
#include <QDebug>
#include <qpropertyanimation>
//MyPushButton::MyPushButton(QWidget *parent) : MyPushButton(parent)
//{

//}
MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool image = pix.load(normalImg);
    if (!image){
        qDebug()<<"图片加载失败";
        return ;
    }

    this->setFixedSize(pix.width(),pix.height());//设置图片固定大小
    this->setStyleSheet("QPushButton{border:Opx;}");//设置不规则图片样式
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));//设置图标大小

}

void MyPushButton::zoomup(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoomdown(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
