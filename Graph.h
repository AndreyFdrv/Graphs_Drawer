#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QPoint>
class Graph
{
private:
    QVector<QPoint> points;//точки отсортированы по координате x
public:
    Graph();
    void AddPoint(double x, double y);
    void RemovePoint(int index);
};

#endif // GRAPH_H
