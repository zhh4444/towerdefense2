#include "walkway.h"
#include <QDebug>

WalkWay::WalkWay() : m_startPos(1, 300)
                   , m_endPos(1000, 300)
{
// 实现思路：可以只记录拐点，把下一个节点看做是移动目标
    m_path.push_back(m_startPos);
    m_path.push_back(QPoint(300, 300));
    m_path.push_back(QPoint(300, 400));
    m_path.push_back(QPoint(400, 400));
    m_path.push_back(QPoint(400, 300));
    m_path.push_back(m_endPos);
}

void WalkWay::setPath(const std::vector<std::vector<int>>& path)
{
    m_path.clear();
    for (size_t i = 0; i < path.size(); ++i){
        m_path.push_back(QPoint(path[i][0],path[i][1]));
    }
    m_startPos = m_path[0];
    m_endPos = m_path.back();
}
//根据当前点来确定下一个点
QPoint WalkWay::next(const QPoint& currentPos)
{
    for(size_t i = 1; i < m_path.size(); ++i){
        if (m_path[i].x() == m_path[i-1].x()){//判断垂直还是水平
            if (m_path[i].x() == currentPos.x() && std::min(m_path[i].y(), m_path[i-1].y()) <= currentPos.y()
                    && std::max(m_path[i].y(), m_path[i-1].y()) >= currentPos.y()
                    && m_path[i] != currentPos){//判断是否应该拐弯
                int sign = m_path[i].y() - m_path[i-1].y() > 0 ? 1 : -1;
                return QPoint(currentPos.x(), currentPos.y() + 1 * sign);
            }
        }
        if (m_path[i].y() == m_path[i-1].y()){//判断垂直还是水平
            if (m_path[i].y() == currentPos.y() && std::min(m_path[i].x(), m_path[i-1].x()) <= currentPos.x()
                    && std::max(m_path[i].x(), m_path[i-1].x()) >= currentPos.x()
                    && m_path[i] != currentPos){//判断是否应该拐弯
                int sign = m_path[i].x() - m_path[i-1].x() > 0 ? 1 : -1;
                return QPoint(currentPos.x() + 1 * sign, currentPos.y());
            }
        }
    }
    return QPoint(currentPos.x() + 1, currentPos.y());
}

QPoint WalkWay::startPos()
{
    return m_startPos;
}

QPoint WalkWay::endPos()
{
    return m_endPos;
}
