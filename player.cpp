#include "player.h"

const int healthBarWidth = 60;
const QSize playerFixedSize(72, 72);

Player::Player(const QPoint& pos, const char* imagePath, int maxHp)
                : Unit(imagePath, pos, playerFixedSize)
                , m_maxHp(maxHp)
                , m_currentHp(maxHp)
{
}

void Player::setPosition(const QPoint& pos)
{
    m_pos = pos;
}

void Player::draw(QPainter *painter) const{
    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-healthBarWidth / 2, -m_size.height() / 3 - 15);
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

void Player::getDamage(int damageVal)
{
    m_currentHp -= damageVal;
    if (m_currentHp <= 0){
        m_currentHp = 0;
    }
}
