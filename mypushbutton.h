#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg,QString pressImg = "");


    QString normalImgPath;
    QString pressImgPath;

    //点击弹起
    void zoomup();
    void zoomdown();
signals:

};

#endif // MYPUSHBUTTON_H
