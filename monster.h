#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class EnemyWay;
class QPainter;
class MainWindow;
class Tower;

class Monster : public QObject
{
public:
    Monster(EnemyWay * start,MainWindow * game,const QPixmap & sprite=QPixmap(":/images/monster1.png"));
    ~Monster();
    void draw(QPainter * painter) const;
    void move();

    QPoint get_pos();

    void getAttack(Tower * tower);
    void getDamage(int damage);
    void getRemoved();
    void getLostSight(Tower * tower);
    void reSetHp(int maxHp);

private slots:
    void doActive();
private:
    int m_maxHp;
    int m_currentHp;
    int m_walkingSpeed;
    bool m_active;

    EnemyWay * m_destinationWayPoint;
    MainWindow * m_game;
    QPoint m_pos;
    QPixmap m_sprite;
    QList<Tower *> m_attackTowerList;

    static const QSize m_fixedSize;
};

#endif // MONSTER_H
