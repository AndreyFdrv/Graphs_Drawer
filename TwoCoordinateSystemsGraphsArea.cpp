#include "TwoCoordinateSystemsGraphsArea.h"
#include "math.h"
#include <float.h>
#include <QMessageBox>
#include <QMouseEvent>
void TwoCoordinateSystemsGraphsArea::FluentlyPaint(int i, int count)
{
    painter=new QPainter(widget);
    if(upper_graphs.length()+lower_graphs.length()==0)
        return;
    ComputeBorders();
    double x_max_1=x_max;
    double upper_y_max_1=upper_y_max;
    double lower_y_max_1=lower_y_max;
    double x_min_1=x_min;
    double upper_y_min_1=upper_y_min;
    double lower_y_min_1=lower_y_min;
    x_max=x_max_0+i*(x_max_1-x_max_0)/(count-1);
    upper_y_max=upper_y_max_0+i*(upper_y_max_1-upper_y_max_0)/(count-1);
    lower_y_max=lower_y_max_0+i*(lower_y_max_1-lower_y_max_0)/(count-1);
    x_min=x_min_0+i*(x_min_1-x_min_0)/(count-1);
    upper_y_min=upper_y_min_0+i*(upper_y_min_1-upper_y_min_0)/(count-1);
    lower_y_min=lower_y_min_0+i*(lower_y_min_1-lower_y_min_0)/(count-1);
    Clear();
    ComputeScales();
    DrawGrid();
    DrawGraphs();
    DrawAxises();
    DrawLegend();
}
TwoCoordinateSystemsGraphsArea::TwoCoordinateSystemsGraphsArea(GraphsWidget* widget):GraphsArea()
{
    upper_frame_y_offset=0;
    lower_frame_y_offset=0;
    upper_x_name_label=NULL;
    upper_y_name_label=NULL;
    lower_x_name_label=NULL;
    lower_y_name_label=NULL;
    this->widget=widget;
}
TwoCoordinateSystemsGraphsArea::TwoCoordinateSystemsGraphsArea(GraphsWidget* widget,
                                                               QVector<Graph *> graphs,
                                                               QString x_name, QString y_name,
                                                               double scale):GraphsArea(x_name, y_name,
                                                                                         scale)
{
    upper_frame_y_offset=0;
    lower_frame_y_offset=0;
    upper_x_name_label=NULL;
    upper_y_name_label=NULL;
    lower_x_name_label=NULL;
    lower_y_name_label=NULL;
    this->widget=widget;
    for(int i=0; i<graphs.length()/2; i++)
        upper_graphs.insert(upper_graphs.length(), graphs.at(i));
    for(int i=graphs.length()/2; i<graphs.length(); i++)
        lower_graphs.insert(lower_graphs.length(), graphs.at(i));
}
void TwoCoordinateSystemsGraphsArea::Paint(bool no_repaint)
{
    painter=new QPainter(widget);
    if(no_repaint)
        return;
    Clear();
    if(upper_graphs.length()+lower_graphs.length()!=0)
    {
        ComputeBorders();
        ComputeScales();
        DrawGrid();
        DrawGraphs();
        DrawAxises();
        DrawLegend();
    }
}
void TwoCoordinateSystemsGraphsArea::DrawAxises()
{
    DrawLine(x_axis_offset, widget->height()/2-y_axis_offset, widget->width()-legend_area_width,
            widget->height()/2-y_axis_offset, QColor(Qt::black));
    DrawLine(x_axis_offset, widget->height()/2-1, widget->width()-legend_area_width,
            widget->height()/2-1, QColor(Qt::black));
    int x=widget->width()-legend_area_width;
    int y=widget->height()/2-y_axis_offset;
    DrawLine(x-10, y-10, x, y, QColor(Qt::black));
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    y=widget->height()-y_axis_offset;
    DrawLine(x-10, y-10, x, y, QColor(Qt::black));
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    x=x_axis_offset;
    y=0;
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    DrawLine(x+10, y+10, x, y, QColor(Qt::black));
    y=widget->height()/2;
    DrawLine(x-10, y+10, x, y, QColor(Qt::black));
    DrawLine(x+10, y+10, x, y, QColor(Qt::black));
    double x_steep=(x_max-x_min)/(x_divisions_count-1);
    double eps=0.0001;
    for (double i = x_min; fabs(x_max-i)>eps; i+=x_steep)
    {
        x=x_scale * (i - x_min)+x_axis_offset;
        y=widget->height()/2-y_axis_offset;
        DrawLine(x, y-5, x, y+5, QColor(Qt::black));
        QLabel *label=new QLabel(widget);
        upper_x_labels.insert(upper_x_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-15, y+3);
        label->show();
        y=widget->height()-y_axis_offset;
        DrawLine(x, y-5, x, y+5, QColor(Qt::black));
        label=new QLabel(widget);
        lower_x_labels.insert(lower_x_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-15, y+3);
        label->show();
    }
    double upper_y_steep=(upper_y_max-upper_y_min)/(y_divisions_count-1);
    for(double i=upper_y_min; fabs(upper_y_max-i)>eps; i+=upper_y_steep)
    {
        x=x_axis_offset;
        y=widget->height()/2-y_axis_offset-upper_y_scale*(i-upper_y_min);
        DrawLine(x-5, y, x+5, y, QColor(Qt::black));
        QLabel *label=new QLabel(widget);
        upper_y_labels.insert(upper_y_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-45, y-7);
        label->show();
    }
    double lower_y_steep=(lower_y_max-lower_y_min)/(y_divisions_count-1);
    for(double i=lower_y_min; fabs(lower_y_max-i)>eps; i+=lower_y_steep)
    {
        x=x_axis_offset;
        y=widget->height()-y_axis_offset-lower_y_scale*(i-lower_y_min);
        DrawLine(x-5, y, x+5, y, QColor(Qt::black));
        QLabel *label=new QLabel(widget);
        lower_y_labels.insert(lower_y_labels.size(), label);
        label->setText(QString::number(i, 'f', 2));
        label->move(x-45, y-7);
        label->show();
    }
    upper_x_name_label=new QLabel(widget);
    upper_x_name_label->setText(x_name);
    x=widget->width()-legend_area_width;
    y=widget->height()/2-y_axis_offset;
    upper_x_name_label->move(x, y);
    upper_x_name_label->show();
    lower_x_name_label=new QLabel(widget);
    lower_x_name_label->setText(x_name);
    x=widget->width()-legend_area_width;
    y=widget->height()-y_axis_offset;
    lower_x_name_label->move(x, y);
    lower_x_name_label->show();
    upper_y_name_label=new QLabel(widget);
    upper_y_name_label->setText(y_name);
    x=x_axis_offset;
    y=0;
    upper_y_name_label->move(x+3, y);
    upper_y_name_label->show();
    lower_y_name_label=new QLabel(widget);
    lower_y_name_label->setText(y_name);
    x=x_axis_offset;
    y=widget->height()/2;
    lower_y_name_label->move(x+3, y);
    lower_y_name_label->show();
}
void TwoCoordinateSystemsGraphsArea::DeleteAllLabels()
{
    for(int i=0; i<upper_x_labels.size(); i++)
        delete upper_x_labels.at(i);
    upper_x_labels.clear();
    for(int i=0; i<upper_y_labels.size(); i++)
        delete upper_y_labels.at(i);
    upper_y_labels.clear();
    for(int i=0; i<legend_labels.size(); i++)
        delete legend_labels.at(i);
    legend_labels.clear();
    if(upper_x_name_label!=NULL)
        delete upper_x_name_label;
    upper_x_name_label=NULL;
    if(upper_y_name_label!=NULL)
        delete upper_y_name_label;
    upper_y_name_label=NULL;
    for(int i=0; i<lower_x_labels.size(); i++)
        delete lower_x_labels.at(i);
    lower_x_labels.clear();
    for(int i=0; i<lower_y_labels.size(); i++)
        delete lower_y_labels.at(i);
    lower_y_labels.clear();
    if(lower_x_name_label!=NULL)
        delete lower_x_name_label;
    lower_x_name_label=NULL;
    if(lower_y_name_label!=NULL)
        delete lower_y_name_label;
    lower_y_name_label=NULL;
}
void TwoCoordinateSystemsGraphsArea::Clear()
{
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(0, 0, widget->width()-1, widget->height()-1);
    painter->drawRect(x_axis_offset, 0, widget->width()-legend_area_width-x_axis_offset, widget->height()-y_axis_offset);
    DeleteAllLabels();
}
void TwoCoordinateSystemsGraphsArea::ComputeBorders()
{
    x_min=DBL_MAX;
    upper_y_min=DBL_MAX;
    lower_y_min=DBL_MAX;
    for(int i=0; i<upper_graphs.length(); i++)
    {
        for(int j=0; j<upper_graphs.at(i)->PointsCount(); j++)
        {
            if(upper_graphs.at(i)->getX(j)<x_min)
                x_min=upper_graphs.at(i)->getX(j);
            if(upper_graphs.at(i)->getY(j)<upper_y_min)
                upper_y_min=upper_graphs.at(i)->getY(j);
        }
    }
    for(int i=0; i<lower_graphs.length(); i++)
    {
        for(int j=0; j<lower_graphs.at(i)->PointsCount(); j++)
        {
            if(lower_graphs.at(i)->getX(j)<x_min)
                x_min=lower_graphs.at(i)->getX(j);
            if(lower_graphs.at(i)->getY(j)<lower_y_min)
                lower_y_min=lower_graphs.at(i)->getY(j);
        }
    }
    x_max=-DBL_MAX;
    upper_y_max=-DBL_MAX;
    lower_y_max=-DBL_MAX;
    for(int i=0; i<upper_graphs.length(); i++)
    {
        for(int j=0; j<upper_graphs.at(i)->PointsCount(); j++)
        {
            if(upper_graphs.at(i)->getX(j)>x_max)
                x_max=upper_graphs.at(i)->getX(j);
            if(upper_graphs.at(i)->getY(j)>upper_y_max)
                upper_y_max=upper_graphs.at(i)->getY(j);
        }
    }
    for(int i=0; i<lower_graphs.length(); i++)
    {
        for(int j=0; j<lower_graphs.at(i)->PointsCount(); j++)
        {
            if(lower_graphs.at(i)->getX(j)>x_max)
                x_max=lower_graphs.at(i)->getX(j);
            if(lower_graphs.at(i)->getY(j)>lower_y_max)
                lower_y_max=lower_graphs.at(i)->getY(j);
        }
    }
    double k=(double)(100-scale)/200;
    double a=x_max-x_min;
    double upper_b=upper_y_max-upper_y_min;
    double lower_b=lower_y_max-lower_y_min;
    x_min+=k*a;
    x_max-=k*a;
    upper_y_min+=k*upper_b;
    upper_y_max-=k*upper_b;
    lower_y_min+=k*lower_b;
    lower_y_max-=k*lower_b;
    x_min+=frame_x_offset;
    x_max+=frame_x_offset;
    upper_y_min+=upper_frame_y_offset;
    upper_y_max+=upper_frame_y_offset;
    lower_y_min+=lower_frame_y_offset;
    lower_y_max+=lower_frame_y_offset;
}
void TwoCoordinateSystemsGraphsArea::ComputeScales()
{
    if(x_max==x_min)
        x_scale=1;
    else
        x_scale=(widget->width()-legend_area_width-x_axis_offset)/(x_max-x_min);
    if(upper_y_max==upper_y_min)
        upper_y_scale=1;
    else
        upper_y_scale=(widget->height()/2-y_axis_offset)/(upper_y_max-upper_y_min);
    if(lower_y_max==lower_y_min)
        lower_y_scale=1;
    else
        lower_y_scale=(widget->height()/2-y_axis_offset)/(lower_y_max-lower_y_min);
}
void TwoCoordinateSystemsGraphsArea::DrawLegend()
{
    int x=widget->width()-legend_area_width+5;
    int y=5;
    const int size=10;
    const int row_distance=15;
    for(int i=0; i<upper_graphs.length(); i++)
    {
        QColor color=GenerateColor(i);
        painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));
        painter->setBrush(QBrush(color, Qt::SolidPattern));
        painter->drawRect(x, y+row_distance*i, size, size);
        QLabel *label=new QLabel(widget);
        legend_labels.insert(legend_labels.size(), label);
        label->setText(upper_graphs.at(i)->getName());
        label->move(x+15, y+row_distance*i-4);
        label->show();
    }
    for(int i=0; i<lower_graphs.length(); i++)
    {
        QColor color=GenerateColor(upper_graphs.length()+i);
        painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));
        painter->setBrush(QBrush(color, Qt::SolidPattern));
        painter->drawRect(x, y+row_distance*(i+upper_graphs.length()), size, size);
        QLabel *label=new QLabel(widget);
        legend_labels.insert(legend_labels.size(), label);
        label->setText(lower_graphs.at(i)->getName());
        label->move(x+15, y+row_distance*(i+upper_graphs.length())-4);
        label->show();
    }
}
void TwoCoordinateSystemsGraphsArea::DrawGraphs()
{
    painter->setClipRect(x_axis_offset+1, 0, widget->width()-x_axis_offset-legend_area_width-1,
                         widget->height()/2-y_axis_offset);
    for(int i=0; i<upper_graphs.length(); i++)
    {
        QColor color=GenerateColor(i);
        if(upper_graphs.at(i)->PointsCount()==0)
            break;
        double x0=upper_graphs.at(i)->getX(0);
        x0=x_scale*(x0-x_min)+x_axis_offset;
        double y0=upper_graphs.at(i)->getY(0);
        y0=widget->height()/2-y_axis_offset-upper_y_scale*(y0-upper_y_min);
        int point_radius=3;
        if((isUpperGraphChosen)&&(chosen_graph_number==i)&&(chosen_point_number==0))
            point_radius=5;
        DrawPoint((int)x0, (int)y0, color, point_radius);
        for(int j=1; j<upper_graphs.at(i)->PointsCount(); j++)
        {
            double x1=upper_graphs.at(i)->getX(j);
            x1=x_scale*(x1-x_min)+x_axis_offset;
            double y1=upper_graphs.at(i)->getY(j);
            y1=widget->height()/2-y_axis_offset-upper_y_scale*(y1-upper_y_min);
            DrawLine((int)x0, (int)y0, (int)x1, (int)y1, color);
            point_radius=3;
            if((isUpperGraphChosen)&&(chosen_graph_number==i)&&(chosen_point_number==j))
                point_radius=5;
            DrawPoint((int)x1, (int)y1, color, point_radius);
            x0=x1;
            y0=y1;
        }
    }
    painter->setClipRect(x_axis_offset+1, widget->height()/2,
                         widget->width()-x_axis_offset-legend_area_width-1,
                         widget->height()/2-y_axis_offset);
    for(int i=0; i<lower_graphs.length(); i++)
    {
        QColor color=GenerateColor(upper_graphs.length()+i);
        if(lower_graphs.at(i)->PointsCount()==0)
            break;
        double x0=lower_graphs.at(i)->getX(0);
        x0=x_scale*(x0-x_min)+x_axis_offset;
        double y0=lower_graphs.at(i)->getY(0);
        y0=widget->height()-y_axis_offset-lower_y_scale*(y0-lower_y_min);
        int point_radius=3;
        if((!isUpperGraphChosen)&&(chosen_graph_number==i)&&(chosen_point_number==0))
            point_radius=5;
        DrawPoint((int)x0, (int)y0, color, point_radius);
        for(int j=1; j<lower_graphs.at(i)->PointsCount(); j++)
        {
            double x1=lower_graphs.at(i)->getX(j);
            x1=x_scale*(x1-x_min)+x_axis_offset;
            double y1=lower_graphs.at(i)->getY(j);
            y1=widget->height()-y_axis_offset-lower_y_scale*(y1-lower_y_min);
            DrawLine((int)x0, (int)y0, (int)x1, (int)y1, color);
            point_radius=3;
            if((!isUpperGraphChosen)&&(chosen_graph_number==i)&&(chosen_point_number==j))
                point_radius=5;
            DrawPoint((int)x1, (int)y1, color, point_radius);
            x0=x1;
            y0=y1;
        }
    }
    painter->setClipRect(0, 0, widget->width(), widget->height());
    painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter->drawRect(x_axis_offset, widget->height()/2-y_axis_offset+1,
                      widget->width()-x_axis_offset-legend_area_width, y_axis_offset-3);
}
void TwoCoordinateSystemsGraphsArea::DrawGrid()
{
    double x_steep=(x_max-x_min)/(x_divisions_count-1);
    for (double i = x_min+x_steep; i < x_max; i+=x_steep)
    {
        int x = x_scale * (i - x_min)+x_axis_offset;
        DrawLine(x, widget->height()/2-y_axis_offset, x, 0, QColor(Qt::gray));
        DrawLine(x, widget->height()-y_axis_offset, x, widget->height()/2, QColor(Qt::gray));
    }
    double upper_y_steep=(upper_y_max-upper_y_min)/(y_divisions_count-1);
    for(double i=upper_y_min+upper_y_steep; i<upper_y_max; i+=upper_y_steep)
    {
        int y=widget->height()/2-y_axis_offset-upper_y_scale*(i-upper_y_min);
        DrawLine(x_axis_offset, y, widget->width()-legend_area_width, y, QColor(Qt::gray));
    }
    double lower_y_steep=(lower_y_max-lower_y_min)/(y_divisions_count-1);
    for(double i=lower_y_min+lower_y_steep; i<lower_y_max; i+=lower_y_steep)
    {
        int y=widget->height()-y_axis_offset-lower_y_scale*(i-lower_y_min);
        DrawLine(x_axis_offset, y, widget->width()-legend_area_width, y, QColor(Qt::gray));
    }
}
void TwoCoordinateSystemsGraphsArea::AddPoint(QString graph_name, double x, double y)
{
    frame_x_offset=0;
    upper_frame_y_offset=0;
    lower_frame_y_offset=0;
    if(isUpperGraphChosen)
    {
        if((chosen_point_number!=-1)&&(x<upper_graphs.at(chosen_graph_number)->getX(chosen_point_number)))
            chosen_point_number++;
    }
    else
    {
        if((chosen_point_number!=-1)&&(x<lower_graphs.at(chosen_graph_number)->getX(chosen_point_number)))
            chosen_point_number++;
    }
    Graph *graph=NULL;
    for(int i=0; i<upper_graphs.length(); i++)
    {
        if(upper_graphs.at(i)->getName()==graph_name)
        {
            graph=upper_graphs.at(i);
            break;
        }
    }
    if(graph==NULL)
    {
        for(int i=0; i<lower_graphs.length(); i++)
        {
            if(lower_graphs.at(i)->getName()==graph_name)
            {
                graph=lower_graphs.at(i);
                break;
            }
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
    upper_y_min_0=upper_y_min;
    lower_y_min_0=lower_y_min;
    x_max_0=x_max;
    upper_y_max_0=upper_y_max;
    lower_y_max_0=lower_y_max;
    graph->AddPoint(x, y);
}
void TwoCoordinateSystemsGraphsArea::AddGraph(QString filename)
{
    frame_x_offset=0;
    upper_frame_y_offset=0;
    lower_frame_y_offset=0;
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
    if(upper_graphs.length()<lower_graphs.length())
        upper_graphs.insert(upper_graphs.size(), graph);
    else
        lower_graphs.insert(lower_graphs.size(), graph);
}
bool TwoCoordinateSystemsGraphsArea::isGraphExsist(QString name)
{
    for(int i=0; i<upper_graphs.length(); i++)
    {
        if(upper_graphs.at(i)->getName()==name)
            return true;
    }
    for(int i=0; i<lower_graphs.length(); i++)
    {
        if(lower_graphs.at(i)->getName()==name)
            return true;
    }
    return false;
}
bool TwoCoordinateSystemsGraphsArea::mousePressEvent(QMouseEvent *e, double &point_x, double &point_y)
{
    mouse_x_0=e->x();
    mouse_y_0=e->y();
    isLeftButtonDown=true;
    for(int i=0; i<upper_graphs.size(); i++)
    {
        for(int j=0; j<upper_graphs.at(i)->PointsCount(); j++)
        {
            double x=upper_graphs.at(i)->getX(j);
            x=x_scale*(x-x_min)+x_axis_offset;
            double y=upper_graphs.at(i)->getY(j);
            y=widget->height()/2-y_axis_offset-upper_y_scale*(y-upper_y_min);
            double eps=5;
            if(sqrt(pow(e->x()-x, 2)+pow(e->y()-y, 2))<eps)
            {
                isUpperGraphChosen=true;
                chosen_graph_number=i;
                chosen_point_number=j;
                point_x=upper_graphs.at(i)->getX(j);
                point_y=upper_graphs.at(i)->getY(j);
                return true;
            }
        }
    }
    for(int i=0; i<lower_graphs.size(); i++)
    {
        for(int j=0; j<lower_graphs.at(i)->PointsCount(); j++)
        {
            double x=lower_graphs.at(i)->getX(j);
            x=x_scale*(x-x_min)+x_axis_offset;
            double y=lower_graphs.at(i)->getY(j);
            y=widget->height()-y_axis_offset-lower_y_scale*(y-lower_y_min);
            double eps=5;
            if(sqrt(pow(e->x()-x, 2)+pow(e->y()-y, 2))<eps)
            {
                isUpperGraphChosen=false;
                chosen_graph_number=i;
                chosen_point_number=j;
                point_x=lower_graphs.at(i)->getX(j);
                point_y=lower_graphs.at(i)->getY(j);
                return true;
            }
        }
    }
    return false;
}
void TwoCoordinateSystemsGraphsArea::mouseMoveEvent(QMouseEvent *e)
{
    if(!isLeftButtonDown)
        return;
    int mouse_x_1=e->x();
    int mouse_y_1=e->y();
    int dx=mouse_x_0-mouse_x_1;
    int dy=mouse_y_1-mouse_y_0;
    frame_x_offset+=(double)dx/x_scale;
    upper_frame_y_offset+=(double)dy/upper_y_scale;
    lower_frame_y_offset+=(double)dy/lower_y_scale;
    mouse_x_0=mouse_x_1;
    mouse_y_0=mouse_y_1;
}
void TwoCoordinateSystemsGraphsArea::DeleteChosenPoint()
{
    if(chosen_point_number==-1)
        return;
    frame_x_offset=0;
    upper_frame_y_offset=0;
    lower_frame_y_offset=0;
    if(isUpperGraphChosen)
        upper_graphs.at(chosen_graph_number)->DeletePoint(chosen_point_number);
    else
        lower_graphs.at(chosen_graph_number)->DeletePoint(chosen_point_number);
    chosen_graph_number=-1;
    chosen_point_number=-1;
}
void TwoCoordinateSystemsGraphsArea::setChoosenPointCoordinates(double x, double y)
{
    if(chosen_graph_number==-1)
        return;
    frame_x_offset=0;
    upper_frame_y_offset=0;
    lower_frame_y_offset=0;
    if(isUpperGraphChosen)
    {
        upper_graphs.at(chosen_graph_number)->setX(chosen_point_number, x);
        upper_graphs.at(chosen_graph_number)->setY(chosen_point_number, y);
    }
    else
    {
        lower_graphs.at(chosen_graph_number)->setX(chosen_point_number, x);
        lower_graphs.at(chosen_graph_number)->setY(chosen_point_number, y);
    }
}
QVector<Graph *> TwoCoordinateSystemsGraphsArea::getGraphs()
{
    QVector <Graph *>graphs;
    for(int i=0; i<upper_graphs.length(); i++)
        graphs.insert(graphs.length(), upper_graphs.at(i));
    for(int i=0; i<lower_graphs.length(); i++)
        graphs.insert(graphs.length(), lower_graphs.at(i));
    return graphs;
}
