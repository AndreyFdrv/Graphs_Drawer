#include "Graph.h"
#include "QFile"
#include <QTextStream>
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
    points.insert(i, QPointF(x, y));
}
void Graph::RemovePoint(int index)
{
    points.removeAt(index);
}
void Graph::LoadGraphFromFile(char* filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        printf("%s can not be found\n", filename);
        return;
    }
    QTextStream in(&file);
    name = in.readLine();
    while(true)
    {
        QString line=in.readLine();
        if(line==NULL)
            break;
        line.replace(',', '.');
        int i;
        for(i=0; (line.at(i)!='\t')&&(line.at(i)!=' '); i++);
        QString number_str=line.mid(0, i);
        double x=number_str.toDouble();
        while((line.at(i)=='\t')||(line.at(i)==' '))
            i++;
        number_str=line.mid(i, line.length()-i);
        double y=number_str.toDouble();
        AddPoint(x, y);
    }
}
