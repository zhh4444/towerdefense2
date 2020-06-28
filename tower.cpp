#include "tower.h"
#include <cmath>

const QSize towerFixedSize(72, 72);

Tower::Tower(const QPoint& pos, const char* imagePath,
             int attackVal, float attackSpeed,
             int attackRange, int attackNum)
                : Unit(imagePath, pos, towerFixedSize)
                , m_attackVal(attackVal)
                , m_attackSpeed(attackSpeed)
                , m_attackRange(attackRange)
                , m_attackNum(attackNum)
                , m_lastAttackTime(0)
{
}

bool Tower::canAttack(Enemy& enemy)
{
    if (enemy.invalid()){
        return false;
    }
    QPoint disp = enemy.pos() - m_pos;
    if (disp.dotProduct(disp, disp) <= m_attackRange * m_attackRange){//
        return true;
    }
    return false;
}

bool Tower::canAttack(float currTime)
{
    if (currTime - m_lastAttackTime >= 1 / m_attackSpeed){//
        return true;
    }
    return false;
}

void Tower::attack(std::list<Enemy>& enemyList, std::list<Bullet>& bulletList,
                   float currTime)
{
    bool attacked = false;
    int attack_num = m_attackNum;//
    if (!canAttack(currTime)){
        return;
    }
    for(Enemy& enemy : enemyList){
        if (attack_num > 0 && canAttack(enemy)){
            attacked = true;
            --attack_num;
            bulletList.push_back(Bullet(&enemy, ":/image/bullet-1.png",
                                        m_pos, m_attackVal));
        }
    }
    if (attacked){
        m_lastAttackTime = currTime;
    }
}

void Tower::draw(QPainter *painter) const
{
    painter->drawPixmap(m_pos, m_sprite);
}
