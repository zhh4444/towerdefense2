#ifndef TOWERDEFENCE_H
#define TOWERDEFENCE_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>

#include <list>
#include "enemy.h"
#include "walkway.h"
#include "tower.h"
#include "bullet.h"
#include "player.h"


class TowerDefence : public QWidget
{
    Q_OBJECT
public:
    TowerDefence(int gameid = 1, QWidget *parent = 0);
    ~TowerDefence();
    void addEnemy();
    void addEnemy1();
    void addEnemy2();
    void addEnemy3();
    void addTower1(const QPoint& pos);
    void addTower2(const QPoint& pos);
    void addTower3(const QPoint& pos);
protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void contextMenuEvent(QContextMenuEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void gameOver(QPainter &qp, bool win=false);
private:
    void doDraw();

    void drawText(QPainter* painter);
    void initGame();
    int m_timerid;
    std::list<Enemy> m_enemyList;
    std::list<Tower> m_towerList;
    std::list<Bullet> m_bulletList;
    WalkWay m_walkway;
    // 游戏难度控制参数
    int m_enemyInterval; //出怪的间隔
    int m_enemyTotalNum; //怪的总数，打完就算过关
    float m_enemyEnhanceFactor; //怪的增强系数，随着游戏进行，怪的各项数值会增加
    int m_enemyCreateNum; // 制造的怪的个数
    int m_enemyDestroyNum; // 消灭的怪的个数
    std::vector<int> m_enemyWeights; //三种怪的权重
    int m_goldTotal;
    int m_goldLeft;
    // end

    uint64_t m_timesteps;
    Player m_player;
    QPoint m_towerPos;
    QPoint m_mousePos;
    int m_gameid;
    std::string m_bgImage;
    bool m_isOver;
private slots:
   void addTower1();
   void addTower2();
   void addTower3();
};

#endif // TOWERDEFENCE_H
