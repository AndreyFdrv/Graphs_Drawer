#include "GraphsArea.h"

GraphsArea::GraphsArea()
{
    legend_area_width=200;
    x_axis_offset=50;
    y_axis_offset=50;
    x_divisions_count=10;
    y_divisions_count=10;
    x_name="x";
    y_name="y";
    scale=100;
    isLeftButtonDown=false;
    frame_x_offset=0;
    chosen_graph_number=-1;
    chosen_point_number=-1;
}
GraphsArea::GraphsArea(QString x_name, QString y_name, double scale)
{
    legend_area_width=200;
    x_axis_offset=50;
    y_axis_offset=50;
    x_divisions_count=10;
    y_divisions_count=10;
    this->x_name=x_name;
    this->y_name=y_name;
    this->scale=scale;
    isLeftButtonDown=false;
    frame_x_offset=0;
    chosen_graph_number=-1;
    chosen_point_number=-1;
}
void GraphsArea::DrawPoint(int x, int y, QColor color, int point_radius)
{
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    painter->drawEllipse(QPoint(x, y), point_radius, point_radius);
}
void GraphsArea::DrawLine(int x0, int y0, int x1, int y1, QColor color)
{
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    painter->drawLine(QPoint(x0, y0), QPoint(x1, y1));
}
QColor GraphsArea::GenerateColor(int index)
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
    else
    {
        return QColor(255-((index-5)/6)*20, 0, 255-((index-5)/6)*20);
    }
}
void GraphsArea::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    isLeftButtonDown=false;
}
void GraphsArea::setScale(int scale)
{
    this->scale=scale;
}
void GraphsArea::setAxisesName(QString name1, QString name2)
{
    x_name=name1;
    y_name=name2;
}
QString GraphsArea::getXName()
{
    return x_name;
}
QString GraphsArea::getYName()
{
    return y_name;
}
double GraphsArea::getScale()
{
    return scale;
}
