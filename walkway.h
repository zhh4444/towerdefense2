#ifndef WALKWAY_H
#define WALKWAY_H

#include <QPoint>
#include <vector>

class WalkWay
{
public:
    WalkWay();
    void setPath(const std::vector<std::vector<int>>& path);
    QPoint next(const QPoint& currentPos);
    QPoint startPos();
    QPoint endPos();

private:
    std::vector<QPoint> m_path; // 记录起点，终点和路径的拐点
    QPoint m_startPos;
    QPoint m_endPos;
};

#endif // WALKWAY_H
