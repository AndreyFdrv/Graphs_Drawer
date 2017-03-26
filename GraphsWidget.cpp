#include "GraphsWidget.h"
#include <QPainter>
#include <QMessageBox>
#include <float.h>
GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{
    legend_area_width=200;
}
GraphsWidget::~GraphsWidget()
{
    delete painter;
}
void GraphsWidget::Clear()
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(0, 0, this->width()-1, this->height()-1);
    painter->drawRect(0, 0, this->width()-legend_area_width, this->height()-1);
}
void GraphsWidget::ComputeBorders()
{
    x_min=DBL_MAX;
    y_min=DBL_MAX;
    for(int i=0; i<graphs.length(); i++)
    {
        for(int j=0; j<graphs.at(i)->PointsCount(); j++)
        {
            if(graphs.at(i)->getX(j)<x_min)
                x_min=graphs.at(i)->getX(j);
            if(graphs.at(i)->getY(j)<y_min)
                y_min=graphs.at(i)->getY(j);
        }
    }
    x_max=-DBL_MAX;
    y_max=-DBL_MAX;
    for(int i=0; i<graphs.length(); i++)
    {
        for(int j=0; j<graphs.at(i)->PointsCount(); j++)
        {
            if(graphs.at(i)->getX(j)>x_max)
                x_max=graphs.at(i)->getX(j);
            if(graphs.at(i)->getY(j)>y_max)
                y_max=graphs.at(i)->getY(j);
        }
    }
}
void GraphsWidget::ComputeScales()
{
    if(x_max==x_min)
        x_scale=1;
    else
        x_scale=(width()-legend_area_width)/(x_max-x_min);
    if(y_max==y_min)
        y_scale=1;
    else
        y_scale=height()/(y_max-y_min);
}
void GraphsWidget::DrawPoint(int x, int y, QColor color)
{
    const int point_radius=3;
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    painter->drawEllipse(QPoint(x, y), point_radius, point_radius);
}
QColor GraphsWidget::GenerateColor(int index)
{
    if(index%6==0)
    {
        return QColor(255-(index/6)*20, 0, 0);
    }
    else if(index%6==1)
    {
        return QColor(0, 255-((index-1)/6)*20, 0);
    }
    else if(index%6==2)
    {
        return QColor(0, 0, 255-((index-2)/6)*20);
    }
    else if(index%6==3)
    {
        return QColor(255-((index-3)/6)*20, 255-((index-3)/6)*20, 0);
    }
    else if(index%6==4)
    {
        return QColor(0, 255-((index-4)/6)*20, 255-((index-4)/6)*20);
    }
    else if(index%6==5)
    {
        return QColor(255-((index-5)/6)*20, 0, 255-((index-5)/6)*20);
    }
}
void GraphsWidget::DrawLine(int x0, int y0, int x1, int y1, QColor color)
{
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    painter->drawLine(QPoint(x0, y0), QPoint(x1, y1));
}
void GraphsWidget::DrawGraphs()
{
    for(int i=0; i<graphs.length(); i++)
    {
        QColor color=GenerateColor(i);
        if(graphs.at(i)->PointsCount()==0)
            break;
        double x0=graphs.at(i)->getX(0);
        x0=x_scale*(x0-x_min);
        double y0=graphs.at(i)->getY(0);
        y0=height()-y_scale*(y0-y_min);
        DrawPoint((int)x0, (int)y0, color);
        for(int j=1; j<graphs.at(i)->PointsCount(); j++)
        {
            double x1=graphs.at(i)->getX(j);
            x1=x_scale*(x1-x_min);
            double y1=graphs.at(i)->getY(j);
            y1=height()-y_scale*(y1-y_min);
            DrawLine((int)x0, (int)y0, (int)x1, (int)y1, color);
            DrawPoint((int)x1, (int)y1, color);
            x0=x1;
            y0=y1;
        }
    }
}
void GraphsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter=new QPainter(this);
    Clear();
    ComputeBorders();
    ComputeScales();
    DrawGraphs();
}
void GraphsWidget::AddGraph(char *filename)
{
    Graph *graph=new Graph();
    graph->LoadGraphFromFile(filename);
    if(isGraphExsist(graph->getName()))
    {
        QMessageBox msgBox;
        QString message="График с именем \""+graph->getName()+
                "\" уже существует, поэтому не может быть добавлен\n";
        msgBox.setText(message);
        msgBox.exec();
        return;
    }
    graphs.insert(0, graph);
    repaint();
}
bool GraphsWidget::isGraphExsist(QString name)
{
    for(int i=0; i<graphs.length(); i++)
    {
        if(graphs.at(i)->getName()==name)
            return true;
    }
    return false;
}
