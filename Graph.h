#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QPoint>
#include <QString>
class Graph
{
private:
    QVector<QPointF> points;//точки отсортированы по координате x
    QString name;
public:
    Graph();
    void AddPoint(double x, double y);
    void RemovePoint(int index);
    void LoadGraphFromFile(char* filename);
};

#endif // GRAPH_H
