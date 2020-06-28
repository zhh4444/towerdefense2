#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QPainter>

#include "unit.h"
#include "enemy.h"

class Bullet : public Unit
{
public:
    Bullet(Enemy* target, const char* imagePath, const QPoint& pos,
           int attackVal);
    void draw(QPainter *painter) const;
    void move();
    void attack();
    bool invalid();
private:
    Enemy* m_target;
    int m_attackVal;
    bool m_invalid;
};

#endif // BULLET_H
