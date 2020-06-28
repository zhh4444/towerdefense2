#include "unit.h"

Unit::Unit(const char* imagePath, const QPoint& pos) : m_sprite(imagePath)
                    , m_pos(pos)
{

}

Unit::Unit(const char* imagePath, const QPoint& pos, const QSize size) : m_sprite(imagePath)
                     , m_pos(pos)
                     , m_size(size)
{
    m_sprite = m_sprite.scaled(m_size);
}

void Unit::draw(QPainter *painter) const
{
    painter->drawPixmap(m_pos, m_sprite);
}
