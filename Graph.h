#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QPoint>
#include <QString>
class Graph
{
private:
    QVector<QPointF> points;
    QString name;
public:
    Graph();
    void AddPoint(double x, double y);
    void DeletePoint(int index);
    void LoadGraphFromFile(QString filename);
    QString getName();
    double getX(int index);
    double getY(int index);
    void setX(int index, double value);
    void setY(int index, double value);
    int PointsCount();
};

#endif // GRAPH_H
