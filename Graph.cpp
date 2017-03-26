#include "Graph.h"
#include "QFile"
#include <QTextStream>
#include <QMessageBox>
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
        QMessageBox msgBox;
        QString message="Файл \""+QString(filename)+
                "\" не был найден\n";
        msgBox.setText(message);
        msgBox.exec();
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
QString Graph::getName()
{
    return name;
}
double Graph::getX(int index)
{
    return points.at(index).x();
}
double Graph::getY(int index)
{
    return points.at(index).y();
}
int Graph::PointsCount()
{
    return points.length();
}
