#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QPainter>

class Unit
{
public:
    Unit(const char* imagePath, const QPoint& pos);
    Unit(const char* imagePath, const QPoint& pos, const QSize size);
    virtual ~Unit() {}
    virtual void draw(QPainter *painter) const;
protected:
    QPixmap m_sprite;
    QPoint m_pos;
    QSize m_size;
};

#endif // UNIT_H
