#include "towerdefence.h"
#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QContextMenuEvent>
#include "enemy.h"
#include <cstdlib>

const int timeinterval = 50;

TowerDefence::TowerDefence(int gameid, QWidget *parent) : QWidget(parent)
                , m_enemyInterval(100)//怪物出现事件间隔
                , m_goldTotal(1000)//初始金币
                , m_goldLeft(1000)//剩余金币
                , m_timesteps(0)//事件步
                , m_player(m_walkway.endPos(), ":/image/fruits.png")
                , m_gameid(gameid)
                , m_isOver(false)


{
    setWindowIcon(QIcon(":/image/fruits.png"));
    setWindowTitle("defend fruit");
    setFixedSize(1040, 640);
    m_timerid = startTimer(timeinterval);
    initGame();
}

void TowerDefence::initGame(){
    if (m_gameid == 2){
        m_bgImage = ":/image/game_map2.jpg";
        std::vector<std::vector<int>> path = {
            {1024, 220},
            {866, 220},
            {866, 145},
            {765, 145},
            {765, 310},
            {555, 310},
            {555, 490},
            {150, 490},
            {150, 255}
        };
        m_walkway.setPath(path);
        m_player.setPosition(m_walkway.endPos());
        m_enemyInterval = 90; //出怪的间隔
        m_enemyTotalNum = 120; //怪的总数，打完就算过关
        m_enemyEnhanceFactor = 1; //怪的增强系数，随着游戏进行，怪的各项数值会增加
        m_enemyWeights = {5, 4, 1};
    }
    else if (m_gameid == 3){
        m_bgImage = ":/image/game_map2.jpg";
        std::vector<std::vector<int>> path = {
            {1024, 220},
            {866, 220},
            {866, 145},
            {765, 145},
            {765, 310},
            {555, 310},
            {555, 490},
            {150, 490},
            {150, 255}
        };
        m_walkway.setPath(path);
        m_player.setPosition(m_walkway.endPos());
        m_enemyInterval = 80; //出怪的间隔
        m_enemyTotalNum = 80; //怪的总数，打完就算过关
        m_enemyEnhanceFactor = 1; //怪的增强系数，随着游戏进行，怪的各项数值会增加
        m_enemyWeights = {4, 4, 2};
    }
    else {
        m_bgImage = ":/image/game_map1.jpg";
        std::vector<std::vector<int>> path = {
            {1024, 470},
            {770, 470},
            {770, 375},
            {450, 375},
            {450, 470},
            {140, 470},
            {140, 180}
        };
        m_walkway.setPath(path);
        m_player.setPosition(m_walkway.endPos());
        m_enemyInterval = 100; //出怪的间隔
        m_enemyTotalNum = 50; //怪的总数，打完就算过关
        m_enemyEnhanceFactor = 1; //怪的增强系数，随着游戏进行，怪的各项数值会增加
        m_enemyWeights = {6,3,1};
    }
    m_enemyCreateNum = 0; //制造的怪的个数
    m_enemyDestroyNum = 0; //消灭的怪的个数
}

// 绘制右上角文字信息
void TowerDefence::drawText(QPainter* painter)
{
    painter->save();
    char buffer[256] = {'\0'};

    QFont font("Courier", 10, QFont::DemiBold);//设置字体
    QFontMetrics fm(font);


    painter->setFont(font);
    int w = width();
    snprintf(buffer, 255, "Current HP: %d", m_player.currentHp());//绘画基地血量
    QString message = buffer;
    painter->translate(QPoint(w - 100, 30));
    int textWidth = fm.width(message);
    painter->drawText(-textWidth/2, 0, message);

    snprintf(buffer, 255, "Enemy Left: %d", m_enemyTotalNum - m_enemyDestroyNum);//绘画剩余地人数量
    message = buffer;
    painter->translate(QPoint(0, 20));
    textWidth = fm.width(message);
    painter->drawText(-textWidth/2, 0, message);

    snprintf(buffer, 255, "Tower number: %d", m_towerList.size());//建造塔数量
    message = buffer;
    painter->translate(QPoint(0, 20));
    textWidth = fm.width(message);
    painter->drawText(-textWidth/2, 0, message);

    snprintf(buffer, 255, "Gold Left: %d", m_goldLeft);//金币
    message = buffer;
    painter->translate(QPoint(0, 20));
    textWidth = fm.width(message);
    painter->drawText(-textWidth/2, 0, message);

    painter->restore();
}
//触发右键事件
void TowerDefence::contextMenuEvent(QContextMenuEvent *event)//触发
{
      if (m_isOver){
          return;
      }
      //显示窗口，三种塔供选择
      QMenu* pop_menu = new QMenu();
      QAction* actionAddTower1 = new QAction("bottle", this);
      QAction* actionAddTower2 = new QAction("sun", this);
      QAction* actionAddTower3 = new QAction("octopus", this);
      connect(actionAddTower1, SIGNAL(triggered()), this, SLOT(addTower1()));
      connect(actionAddTower2, SIGNAL(triggered()), this, SLOT(addTower2()));
      connect(actionAddTower3, SIGNAL(triggered()), this, SLOT(addTower3()));

      pop_menu->addAction(actionAddTower1);
      pop_menu->addAction(actionAddTower2);
      pop_menu->addAction(actionAddTower3);
      m_towerPos = QCursor::pos() - mapToGlobal(QPoint(0, 0));
      pop_menu->exec(QCursor::pos());
      event->accept();
      delete pop_menu;
}
//用来定坐标的函数
void TowerDefence::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_mousePos = QCursor::pos() - mapToGlobal(QPoint(0, 0));
    qDebug("--->%d %d", QCursor::pos().x(), QCursor::pos().y());
    qDebug("---->%d %d", m_mousePos.x(), m_mousePos.y());
}

TowerDefence::~TowerDefence(){

}
//添加三种塔，设置塔属性
void TowerDefence::addTower1(){
    qDebug("add tower1");
    addTower1(m_towerPos);
}

void TowerDefence::addTower2(){
    qDebug("add tower2");
    addTower2(m_towerPos);
}

void TowerDefence::addTower3(){
    qDebug("add tower3");
    addTower3(m_towerPos);
}

void TowerDefence::addTower1(const QPoint& pos){
    const int val = 100;
    if (m_goldLeft < val){
        QMessageBox::warning(NULL, "warning", "Gold not enough", QMessageBox::Yes, QMessageBox::Yes);//警告金币不够
        return;
    }
    m_goldLeft -= val;
    m_towerList.push_back(Tower(pos, ":/image/tower-1.png",
                          30, 0.5, 400, 1));
}

void TowerDefence::addTower2(const QPoint& pos){
    const int val = 200;
    if (m_goldLeft < val){
        QMessageBox::warning(NULL, "warning", "Gold not enough", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    m_goldLeft -= val;
    m_towerList.push_back(Tower(pos, ":/image/tower-2.png",
                          20, 1, 400, 3));
}

void TowerDefence::addTower3(const QPoint& pos){
    const int val = 300;
    if (m_goldLeft < val){
        QMessageBox::warning(NULL, "warning", "Gold not enough", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    m_goldLeft -= val;
    m_towerList.push_back(Tower(pos, ":/image/tower-3.png",
                          50, 0.5, 250, 2));
}
//重画enemy,tower与bullet
void TowerDefence::doDraw(){
    QPainter qp(this);
    QPixmap pix;
    pix.load(m_bgImage.c_str());
    qp.drawPixmap(0,0,this->width(),this->height(),pix);

    for(Enemy& enemy : m_enemyList){
        enemy.draw(&qp);
    }
    for(Tower& tower : m_towerList){
        tower.draw(&qp);
    }
    for(Bullet& bullet : m_bulletList){
        bullet.draw(&qp);
    }
    m_player.draw(&qp);
    if (m_player.gameOver()){
        gameOver(qp);
    }
    if (m_enemyDestroyNum >= m_enemyTotalNum){
        gameOver(qp, true);
    }

    drawText(&qp);

}
//封装一下dodraw
void TowerDefence::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    doDraw();
}

void TowerDefence::timerEvent(QTimerEvent *e){//定时器，每隔50ms调用该函数一次
    if (m_timesteps % m_enemyInterval == 0){//记录下时间步，用此定时添加敌人
        addEnemy();
    }
    m_timesteps += 1;
    float currTime = timeinterval / 1000.0 * m_timesteps;//计算游戏时间，为计算塔对攻击间隔服务
    e->timerId();
    //遍历寻找符合攻击间隔可发子弹和敌人在射程内可发射子弹的塔攻击敌人，有的塔可以同时攻击多个敌人
    for(Tower& tower : m_towerList){
        tower.attack(m_enemyList, m_bulletList, currTime);
    }
    //遍历敌人，控制敌人移动
    for(Enemy& enemy : m_enemyList){
        enemy.move();
        if (enemy.invalid()){//敌人无效，即敌人到达了基地
            enemy.attack(m_player);//攻击基地
        }
    }
    //子弹移动，追击敌人
    for(Bullet& bullet : m_bulletList){
        bullet.move();
    }
    //移除无效，移除子弹，移除死亡和到达基地的敌人，
    int enemyNum = m_enemyList.size();
    m_bulletList.remove_if([](Bullet& b){ return b.invalid(); });
    m_enemyList.remove_if([](Enemy& enemy){ return enemy.invalid(); });
    //统计清除多少敌人
    int enemyDestroy = enemyNum - m_enemyList.size() ;
    m_enemyDestroyNum += enemyDestroy;
    m_goldLeft += enemyDestroy * 20;
    m_enemyEnhanceFactor = 1 + m_enemyDestroyNum * 1.0 / m_enemyTotalNum;
    //重新绘画敌人，子弹，塔
    repaint();
    //增强敌人
    qDebug("factor-->%.2f", m_enemyEnhanceFactor);
}
//添加敌人
void TowerDefence::addEnemy()
{
    if (m_enemyCreateNum >= m_enemyTotalNum){
        return;
    }
    ++m_enemyCreateNum;
    int num = std::rand() % 10;
    //设置三种怪物的比重，实现概率产生怪物
    if (num < m_enemyWeights[0]){
        addEnemy1();
        return;
    }
    num -= m_enemyWeights[0];
    if (num < m_enemyWeights[1]){
        addEnemy2();
        return;
    }
    addEnemy3();
}
//画出敌人，强化敌人
void TowerDefence::addEnemy1()
{
    m_enemyList.push_back(Enemy(&m_walkway, ":/image/monster-1.png", (int)(500 * m_enemyEnhanceFactor)));
}

void TowerDefence::addEnemy2()
{
    m_enemyList.push_back(Enemy(&m_walkway, ":/image/monster-2.png", (int)(1000 * m_enemyEnhanceFactor)));
}

void TowerDefence::addEnemy3()
{
    m_enemyList.push_back(Enemy(&m_walkway, ":/image/monster-3.png", (int)(1500 * m_enemyEnhanceFactor)));
}

//判断并画出获胜失败的字样
void TowerDefence::gameOver(QPainter &qp, bool win) {
    m_isOver = true;
    std::string message_str;
    if (win){
        message_str = "YOU WIN!";
        qp.setBrush(Qt::red);
    } else{
        message_str = "YOU LOSE!";
    }
    QString message = message_str.c_str();
    QFont font("Courier", 45, QFont::DemiBold);//设置字体
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));//移动画笔
    qp.drawText(-textWidth/2, 0, message);
    killTimer(m_timerid);//关闭计时器，让界面停止
}
