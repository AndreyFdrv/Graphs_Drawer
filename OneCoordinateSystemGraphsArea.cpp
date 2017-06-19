#include "OneCoordinateSystemGraphsArea.h"
#include "math.h"
#include <float.h>
#include <QMessageBox>
#include <QMouseEvent>
OneCoordinateSystemGraphsArea::OneCoordinateSystemGraphsArea(GraphsWidget* widget):GraphsArea()
{
    frame_y_offset=0;
    x_name_label=NULL;
    y_name_label=NULL;
    this->widget=widget;
}
OneCoordinateSystemGraphsArea::OneCoordinateSystemGraphsArea(GraphsWidget* widget,
                                                             QVector<Graph *> graphs,
                                                             QString x_name, QString y_name,
                                                             double scale):GraphsArea(x_name, y_name,
                                                                                      scale)
{
    frame_y_offset=0;
    x_name_label=NULL;
    y_name_label=NULL;
    this->widget=widget;
    this->graphs=graphs;
}
void OneCoordinateSystemGraphsArea::Paint(bool no_repaint)
{
    painter=new QPainter(widget);
    if(no_repaint)
        return;
    Clear();
    if(graphs.length()!=0)
    {
        ComputeBorders();
        ComputeScales();
        DrawGrid();
        DrawGraphs();
        DrawAxises();
        DrawLegend();
    }
}
void OneCoordinateSystemGraphsArea::FluentlyPaint(int i, int count)
{
    painter=new QPainter(widget);
    if(graphs.length()==0)
        return;
    ComputeBorders();
    double x_max_1=x_max;
    double y_max_1=y_max;
    double x_min_1=x_min;
    double y_min_1=y_min;
    x_max=x_max_0+i*(x_max_1-x_max_0)/(count-1);
    y_max=y_max_0+i*(y_max_1-y_max_0)/(count-1);
    x_min=x_min_0+i*(x_min_1-x_min_0)/(count-1);
    y_min=y_min_0+i*(y_min_1-y_min_0)/(count-1);
    Clear();
    ComputeScales();
    DrawGrid();
    DrawGraphs();
    DrawAxises();
    DrawLegend();
}
void OneCoordinateSystemGraphsArea::DrawAxises()
{
    int x=widget->width()-legend_area_width;
    int y=widget->height()-y_axis_offset;
    DrawLine(x-10, y-10, x, y, QColor(Qt::black));
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    x=x_axis_offset;
    y=0;
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    DrawLine(x+10, y+10, x, y, QColor(Qt::black));
    double x_steep=(x_max-x_min)/(x_divisions_count-1);
    double eps=0.0001;
    for (double i = x_min; fabs(x_max-i)>eps; i+=x_steep)
    {
        x=x_scale * (i - x_min)+x_axis_offset;
        y=widget->height()-y_axis_offset;
        DrawLine(x, y-5, x, y+5, QColor(Qt::black));
        QLabel *label=new QLabel(widget);
        x_labels.insert(x_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-15, y+3);
        label->show();
    }
    double y_steep=(y_max-y_min)/(y_divisions_count-1);
    for(double i=y_min; fabs(y_max-i)>eps; i+=y_steep)
    {
        x=x_axis_offset;
        y=widget->height()-y_axis_offset-y_scale*(i-y_min);
        DrawLine(x-5, y, x+5, y, QColor(Qt::black));
        QLabel *label=new QLabel(widget);
        y_labels.insert(y_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-45, y-7);
        label->show();
    }
    x_name_label=new QLabel(widget);
    x_name_label->setText(x_name);
    x=widget->width()-legend_area_width;
    y=widget->height()-y_axis_offset;
    x_name_label->move(x, y);
    x_name_label->show();
    y_name_label=new QLabel(widget);
    y_name_label->setText(y_name);
    x=x_axis_offset;
    y=0;
    y_name_label->move(x+3, y);
    y_name_label->show();
}
void OneCoordinateSystemGraphsArea::DeleteAllLabels()
{
    for(int i=0; i<x_labels.size(); i++)
        delete x_labels.at(i);
    x_labels.clear();
    for(int i=0; i<y_labels.size(); i++)
        delete y_labels.at(i);
    y_labels.clear();
    for(int i=0; i<legend_labels.size(); i++)
        delete legend_labels.at(i);
    legend_labels.clear();
    if(x_name_label!=NULL)
        delete x_name_label;
    x_name_label=NULL;
    if(y_name_label!=NULL)
        delete y_name_label;
    y_name_label=NULL;
}
void OneCoordinateSystemGraphsArea::Clear()
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(0, 0, widget->width()-1, widget->height()-1);
    painter->drawRect(x_axis_offset, 0, widget->width()-legend_area_width-x_axis_offset, widget->height()-y_axis_offset);
    DeleteAllLabels();
}
void OneCoordinateSystemGraphsArea::ComputeBorders()
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
    x_min+=frame_x_offset;
    x_max+=frame_x_offset;
    y_min+=frame_y_offset;
    y_max+=frame_y_offset;
}
void OneCoordinateSystemGraphsArea::ComputeScales()
{
    if(x_max==x_min)
        x_scale=1;
    else
        x_scale=(widget->width()-legend_area_width-x_axis_offset)/(x_max-x_min);
    if(y_max==y_min)
        y_scale=1;
    else
        y_scale=(widget->height()-y_axis_offset)/(y_max-y_min);
}
void OneCoordinateSystemGraphsArea::DrawLegend()
{
    int x=widget->width()-legend_area_width+5;
    int y=5;
    const int size=10;
    const int row_distance=15;
    for(int i=0; i<graphs.length(); i++)
    {
        QColor color=GenerateColor(i);
        painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));
        painter->setBrush(QBrush(color, Qt::SolidPattern));
        painter->drawRect(x, y+row_distance*i, size, size);
        QLabel *label=new QLabel(widget);
        legend_labels.insert(legend_labels.size(), label);
        label->setText(graphs.at(i)->getName());
        label->move(x+15, y+row_distance*i-4);
        label->show();
    }
}
void OneCoordinateSystemGraphsArea::DrawGraphs()
{
    for(int i=0; i<graphs.length(); i++)
    {
        QColor color=GenerateColor(i);
        if(graphs.at(i)->PointsCount()==0)
            break;
        double x0=graphs.at(i)->getX(0);
        x0=x_scale*(x0-x_min)+x_axis_offset;
        double y0=graphs.at(i)->getY(0);
        y0=widget->height()-y_axis_offset-y_scale*(y0-y_min);
        int point_radius=3;
        if((chosen_graph_number==i)&&(chosen_point_number==0))
            point_radius=5;
        DrawPoint((int)x0, (int)y0, color, point_radius);
        for(int j=1; j<graphs.at(i)->PointsCount(); j++)
        {
            double x1=graphs.at(i)->getX(j);
            x1=x_scale*(x1-x_min)+x_axis_offset;
            double y1=graphs.at(i)->getY(j);
            y1=widget->height()-y_axis_offset-y_scale*(y1-y_min);
            DrawLine((int)x0, (int)y0, (int)x1, (int)y1, color);
            point_radius=3;
            if((chosen_graph_number==i)&&(chosen_point_number==j))
                point_radius=5;
            DrawPoint((int)x1, (int)y1, color, point_radius);
            x0=x1;
            y0=y1;
        }
    }
    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(1, 1, x_axis_offset-2, widget->height()-y_axis_offset);
    painter->drawRect(1, widget->height()-y_axis_offset+1, widget->width()-3, y_axis_offset-3);
    painter->drawRect(widget->width()-legend_area_width+1, 1, legend_area_width-3, widget->height()-3);
}
void OneCoordinateSystemGraphsArea::DrawGrid()
{
    double x_steep=(x_max-x_min)/(x_divisions_count-1);
    for (double i = x_min+x_steep; i < x_max; i+=x_steep)
    {
        int x = x_scale * (i - x_min)+x_axis_offset;
        DrawLine(x, widget->height()-y_axis_offset, x, 0, QColor(Qt::gray));
    }
    double y_steep=(y_max-y_min)/(y_divisions_count-1);
    for(double i=y_min+y_steep; i<y_max; i+=y_steep)
    {
        int y=widget->height()-y_axis_offset-y_scale*(i-y_min);
        DrawLine(x_axis_offset, y, widget->width()-legend_area_width, y, QColor(Qt::gray));
    }
}
void OneCoordinateSystemGraphsArea::AddPoint(QString graph_name, double x, double y)
{
    if((chosen_point_number!=-1)&&(x<graphs.at(chosen_graph_number)->getX(chosen_point_number)))
        chosen_point_number++;
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
    x_min_0=x_min;
    y_min_0=y_min;
    x_max_0=x_max;
    y_max_0=y_max;
    frame_x_offset=0;
    frame_y_offset=0;
    graph->AddPoint(x, y);
}
void OneCoordinateSystemGraphsArea::AddGraph(QString filename)
{
    frame_x_offset=0;
    frame_y_offset=0;
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
    graphs.insert(graphs.size(), graph);
}
bool OneCoordinateSystemGraphsArea::isGraphExsist(QString name)
{
    for(int i=0; i<graphs.length(); i++)
    {
        if(graphs.at(i)->getName()==name)
            return true;
    }
    return false;
}
bool OneCoordinateSystemGraphsArea::mousePressEvent(QMouseEvent *e, double &point_x, double &point_y)
{
    mouse_x_0=e->x();
    mouse_y_0=e->y();
    isLeftButtonDown=true;
    for(int i=0; i<graphs.size(); i++)
    {
        for(int j=0; j<graphs.at(i)->PointsCount(); j++)
        {
            double x=graphs.at(i)->getX(j);
            x=x_scale*(x-x_min)+x_axis_offset;
            double y=graphs.at(i)->getY(j);
            y=widget->height()-y_axis_offset-y_scale*(y-y_min);
            double eps=5;
            if(sqrt(pow(e->x()-x, 2)+pow(e->y()-y, 2))<eps)
            {
                chosen_graph_number=i;
                chosen_point_number=j;
                point_x=graphs.at(i)->getX(j);
                point_y=graphs.at(i)->getY(j);
                return true;
            }
        }
    }
    return false;
}
void OneCoordinateSystemGraphsArea::mouseMoveEvent(QMouseEvent *e)
{
    if(!isLeftButtonDown)
        return;
    int mouse_x_1=e->x();
    int mouse_y_1=e->y();
    int dx=mouse_x_0-mouse_x_1;
    int dy=mouse_y_1-mouse_y_0;
    frame_x_offset+=(double)dx/x_scale;
    frame_y_offset+=(double)dy/y_scale;
    mouse_x_0=mouse_x_1;
    mouse_y_0=mouse_y_1;
}
void OneCoordinateSystemGraphsArea::DeleteChosenPoint()
{
    if(chosen_point_number==-1)
        return;
    frame_x_offset=0;
    frame_y_offset=0;
    graphs.at(chosen_graph_number)->DeletePoint(chosen_point_number);
    chosen_graph_number=-1;
    chosen_point_number=-1;
}
void OneCoordinateSystemGraphsArea::setChoosenPointCoordinates(double x, double y)
{
    if(chosen_graph_number==-1)
        return;
    frame_x_offset=0;
    frame_y_offset=0;
    graphs.at(chosen_graph_number)->setX(chosen_point_number, x);
    graphs.at(chosen_graph_number)->setY(chosen_point_number, y);
}
QVector<Graph *> OneCoordinateSystemGraphsArea::getGraphs()
{
    return graphs;
}
