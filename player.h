#ifndef PLAYER_H
#define PLAYER_H

#include "unit.h"

class Player : public Unit
{
public:
    Player(const QPoint& pos, const char* imagePath, int maxHp = 100);
    void draw(QPainter *painter) const;
    void getDamage(int damageVal);
    void setPosition(const QPoint& pos);
    bool gameOver() { return m_currentHp <= 0; }
    int currentHp() { return m_currentHp; };

private:
    int m_maxHp;
    int	m_currentHp;
};

#endif // PLAYER_H
