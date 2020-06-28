#include "enemy.h"

const int healthBarWidth = 40;

const QSize enemyFixedSize(52, 52);

Enemy::Enemy(WalkWay* walkway, const char* imagePath, int maxHp, int attackVal, float speed)
                    : Unit(imagePath, walkway->startPos(), enemyFixedSize)
                    , m_walkway(walkway)
                    , m_maxHp(maxHp)
                    , m_currentHp(maxHp)
                    , m_attackVal(attackVal)//
                    , m_runSpeed(speed)
                    , m_invalid(false)
{
}

void Enemy::draw(QPainter *painter) const
{
    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-healthBarWidth / 2, -m_size.height() / 3 - 10);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(healthBarWidth, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * healthBarWidth, 2));
    painter->drawRect(healthBarRect);
    QPoint offsetPoint(-m_size.width() / 2, -m_size.height() / 2);
    painter->translate(m_pos);

    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Enemy::getDamage(int damageVal)
{
    m_currentHp -= damageVal;
    if (m_currentHp <= 0){
        m_invalid = true;
    }
}

void Enemy::move()
{
    m_pos = m_walkway->next(m_pos);
    if (m_pos == m_walkway->endPos()){
        m_invalid = true;
    }
}

bool Enemy::invalid(){
    return m_invalid;
}

void Enemy::attack(Player& player){
    player.getDamage(m_attackVal);
}
