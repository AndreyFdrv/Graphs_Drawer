#include "Graph.h"

Graph::Graph()
{
}
void Graph::AddPoint(double x, double y)
{
    int i;
    for(i=0; i<points.count(); i++)
    {
        if(points.at(i).x()>x)
            break;
    }
    points.insert(i, QPoint(x, y));
}
void Graph::RemovePoint(int index)
{
    points.removeAt(index);
}
