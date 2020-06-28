#include "bullet.h"
#include <cmath>
const QSize bulletFixedSize(12, 12);
const int bulletSpeed = 5;

Bullet::Bullet(Enemy* target, const char* imagePath, const QPoint& pos,
               int attackVal) : Unit(imagePath, pos, bulletFixedSize)
                , m_target(target)
                , m_attackVal(attackVal)
                , m_invalid(false)
{
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_pos, m_sprite);
}

bool Bullet::invalid()
{
    return m_invalid || m_target->invalid();//
}

void Bullet::move()
{
    QPoint direction = m_target->pos() - m_pos;
    float distance = std::sqrt(direction.dotProduct(direction, direction));//
    if (distance <= bulletSpeed){
       attack();
       return;
    }
    m_pos += direction * bulletSpeed / distance;//
}

void Bullet::attack()
{
     m_invalid = true;
     m_target->getDamage(m_attackVal);
}
