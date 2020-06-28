#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int getGameID() { return gameid; }
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    int gameid;
    std::string background;
private slots:
    void startButtonEvent();
    void gameButton2Event();
    void gameButton3Event();
    void gameButton4Event();

};
#endif // MAINWINDOW_H
