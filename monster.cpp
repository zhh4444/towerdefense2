#include "monster.h"
#include "waypoint.h"
#include "mainwindow.h"
#include "utility.h"
#include "tower.h"


#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QVector2D>

const QSize Monster::m_fixedSize(22,23);

Monster::Monster(EnemyWay * startpoint,MainWindow * game,const QPixmap & sprite):
    QObject(0),
    m_game(game),
    m_pos(startpoint->getpoint()),
    m_sprite(sprite)
{
    m_maxHp=40;
    m_currentHp=m_maxHp;
    m_walkingSpeed=1;
    m_active=false;
    m_destinationWayPoint=startpoint->getnextpoint();
}

Monster::~Monster()
{
    m_attackTowerList.clear();
    m_destinationWayPoint=NULL;
    m_game=NULL;
}

void Monster::draw(QPainter *painter) const
{
    if(!m_active)
    {
        return ;
    }
    painter->save();
    static const int healthBarWidth=m_fixedSize.width();
    QPoint healthBarPoint=m_pos+QPoint(-m_fixedSize.width()/2,-m_fixedSize.height());
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)m_currentHp/m_maxHp*healthBarWidth,2));
    painter->drawRect(healthBarRect);

    QPoint tmp(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2);
    painter->drawPixmap(tmp.x(),tmp.y(),m_sprite);
    painter->restore();
}

void Monster::move()
{
    if(!m_active)
    {
        return ;
    }
    if(collisionWithCircle(m_pos,1,m_destinationWayPoint->getpoint(),1))//到达了航点
    {
        if(m_destinationWayPoint->getnextpoint())//如果还有下一个航点
        {
            m_pos=m_destinationWayPoint->getpoint();
            m_destinationWayPoint=m_destinationWayPoint->getnextpoint();
        }
        else//没有下一个航点，代表进入基地
        {
            m_game->getHpDamage();
            m_game->removeEnemy(this);
            return ;
        }
    }
    else//还在路上
    {
        QPoint targetPoint=m_destinationWayPoint->getpoint();
        double movementSpeed=m_walkingSpeed;
        QVector2D normalized(targetPoint-m_pos);
        normalized.normalize();
        m_pos=m_pos+normalized.toPoint()*movementSpeed;
    }
}

void Monster::doActive()
{
    m_active=true;
}

QPoint Monster::get_pos()
{
    return m_pos;
}

void Monster::getAttack(Tower *tower)
{
    m_attackTowerList.push_back(tower);
}

void Monster::getDamage(int damage)
{
    m_currentHp-=damage;
    if(m_currentHp<=0)
    {
        m_game->awardGlod();
        getRemoved();
    }
}

void Monster::getRemoved()
{
    if(m_attackTowerList.empty())
    {
        return ;
    }
    else
    {
        foreach(Tower * tower,m_attackTowerList)
            tower->targetKilled();
        m_game->removeEnemy(this);
    }
}

void Monster::getLostSight(Tower *tower)
{
    m_attackTowerList.removeOne(tower);
}

void Monster::reSetHp(int maxHp)
{
    m_maxHp=maxHp;
    m_currentHp=maxHp;
}
