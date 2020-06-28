#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <list>

#include "unit.h"
#include "enemy.h"
#include "bullet.h"

class Tower : public Unit
{
public:
    Tower(const QPoint& pos, const char* imagePath,
          int attackVal = 10,
          float attackSpeed = 1.0,
          int attackRange = 500,
          int attackNum = 3);
    bool canAttack(Enemy& enemy);
    void draw(QPainter *painter) const;
    bool canAttack(float currTime);
    void attack(std::list<Enemy>& enemyList, std::list<Bullet>& bulletList, float currTime);

private:
    int m_attackVal; // 攻击力
    float m_attackSpeed; // 攻速，每秒多少下
    int m_attackRange;  // 攻击距离
    int m_attackNum;  // 同时攻击的目标个数
    float m_lastAttackTime;
};

#endif // TOWER_H
