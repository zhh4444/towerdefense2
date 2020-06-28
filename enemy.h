#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QPainter>

#include "unit.h"
#include "walkway.h"
#include "player.h"

class Enemy : public Unit
{
public:
    Enemy(WalkWay* walkway, const char* imagePath, int maxHp = 100, int attackVal = 10, float speed = 1);
    void draw(QPainter *painter) const;
    void move();
    bool invalid();
    void attack(Player& player);
    void getDamage(int damageVal);
    QPoint pos() { return m_pos; }
    QSize size() { return m_size; };

private:
    WalkWay* m_walkway;
    int m_maxHp;
    int	m_currentHp;
    int m_attackVal;
    float m_runSpeed;
    bool m_invalid;

};

#endif // ENEMY_H
