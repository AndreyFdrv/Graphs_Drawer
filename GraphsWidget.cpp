#include "GraphsWidget.h"
#include <QPainter>
#include <QMessageBox>
#include <float.h>
GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{
    legend_area_width=200;
    x_offset=50;
    y_offset=50;
    x_divisions_count=10;
    y_divisions_count=10;
    x_name="x";
    y_name="y";
    scale=100;
}
GraphsWidget::~GraphsWidget()
{
    delete painter;
}
void GraphsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter=new QPainter(this);
    Clear();
    if(graphs.length()!=0)
    {
        ComputeBorders();
        ComputeScales();
        DrawGrid();
        DrawGraphs();
        DrawAxises();
    }
}
void GraphsWidget::AddPoint(QString graph_name, double x, double y)
{
    Graph *graph=NULL;
    for(int i=0; i<graphs.length(); i++)
    {
        if(graphs.at(i)->getName()==graph_name)
        {
            graph=graphs.at(i);
            break;
        }
    }
    if(graph==NULL)
    {
        QMessageBox msgBox;
        QString message="Графика с именем \""+graph_name+
                "\" не существует\n";
        msgBox.setText(message);
        msgBox.exec();
        return;
    }
    graph->AddPoint(x, y);
    repaint();
}
void GraphsWidget::DrawAxises()
{
    int x=width()-legend_area_width;
    int y=height()-y_offset;
    DrawLine(x-10, y-10, x, y, QColor(Qt::black));
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    x=x_offset;
    y=0;
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    DrawLine(x+10, y+10, x, y, QColor(Qt::black));
    double x_steep=(x_max-x_min)/(x_divisions_count-1);
    double eps=0.001;
    for (double i = x_min; abs(x_max-i)>eps; i+=x_steep)
    {
        x=x_scale * (i - x_min)+x_offset;
        y=height()-y_offset;
        DrawLine(x, y-5, x, y+5, QColor(Qt::black));
        QLabel *label=new QLabel(this);
        x_labels.insert(x_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-15, y+3);
        label->show();
    }
    double y_steep=(y_max-y_min)/(y_divisions_count-1);
    for(double i=y_min; abs(y_max-i)>eps; i+=y_steep)
    {
        x=x_offset;
        y=height()-y_offset-y_scale*(i-y_min);
        DrawLine(x-5, y, x+5, y, QColor(Qt::black));
        QLabel *label=new QLabel(this);
        y_labels.insert(y_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-45, y-7);
        label->show();
    }
    x_name_label=new QLabel(this);
    x_name_label->setText(x_name);
    x=width()-legend_area_width;
    y=height()-y_offset;
    x_name_label->move(x, y);
    x_name_label->show();
    y_name_label=new QLabel(this);
    y_name_label->setText(y_name);
    x=x_offset;
    y=0;
    y_name_label->move(x+3, y);
    y_name_label->show();
}
void GraphsWidget::Clear()
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(0, 0, this->width()-1, this->height()-1);
    painter->drawRect(x_offset, 0, this->width()-legend_area_width-x_offset, this->height()-y_offset);
    for(int i=0; i<x_labels.size(); i++)
        delete x_labels.at(i);
    for(int i=0; i<y_labels.size(); i++)
        delete y_labels.at(i);
    x_labels.clear();
    y_labels.clear();
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
    double k=(double)(100-scale)/200;
    double a=x_max-x_min;
    double b=y_max-y_min;
    x_min+=k*a;
    x_max-=k*a;
    y_min+=k*b;
    y_max-=k*b;
}
void GraphsWidget::ComputeScales()
{
    if(x_max==x_min)
        x_scale=1;
    else
        x_scale=(width()-legend_area_width-x_offset)/(x_max-x_min);
    if(y_max==y_min)
        y_scale=1;
    else
        y_scale=(height()-y_offset)/(y_max-y_min);
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
        x0=x_scale*(x0-x_min)+x_offset;
        double y0=graphs.at(i)->getY(0);
        y0=height()-y_offset-y_scale*(y0-y_min);
        DrawPoint((int)x0, (int)y0, color);
        for(int j=1; j<graphs.at(i)->PointsCount(); j++)
        {
            double x1=graphs.at(i)->getX(j);
            x1=x_scale*(x1-x_min)+x_offset;
            double y1=graphs.at(i)->getY(j);
            y1=height()-y_offset-y_scale*(y1-y_min);
            DrawLine((int)x0, (int)y0, (int)x1, (int)y1, color);
            DrawPoint((int)x1, (int)y1, color);
            x0=x1;
            y0=y1;
        }
    }
    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(1, 1, x_offset-2, this->height()-y_offset);
    painter->drawRect(1, this->height()-y_offset+1, this->width()-3, y_offset-3);
    painter->drawRect(this->width()-legend_area_width+1, 1, legend_area_width-3, this->height()-3);
}
void GraphsWidget::DrawGrid()
{
    double x_steep=(x_max-x_min)/(x_divisions_count-1);
    for (double i = x_min+x_steep; i < x_max; i+=x_steep)
    {
        int x = x_scale * (i - x_min)+x_offset;
        DrawLine(x, height()-y_offset, x, 0, QColor(Qt::gray));
    }
    double y_steep=(y_max-y_min)/(y_divisions_count-1);
    for(double i=y_min+y_steep; i<y_max; i+=y_steep)
    {
        int y=height()-y_offset-y_scale*(i-y_min);
        DrawLine(x_offset, y, width()-legend_area_width, y, QColor(Qt::gray));
    }
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
void GraphsWidget::setScale(int scale)
{
    this->scale=scale;
    repaint();
}
