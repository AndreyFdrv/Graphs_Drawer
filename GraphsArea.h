#ifndef GRAPHSAREA_H
#define GRAPHSAREA_H
#include <QVector>
#include <QPainter>
#include <QLabel>
#include <QString>
#include "Graph.h"
class GraphsArea
{
protected:
    int legend_area_width;
    int x_axis_offset, y_axis_offset;
    QPainter *painter;
    double x_min, x_max;
    double x_scale;
    int x_divisions_count, y_divisions_count;
    QVector<QLabel *> legend_labels;
    QString x_name, y_name;
    int scale;
    bool isLeftButtonDown;
    int mouse_x_0, mouse_y_0;
    double frame_x_offset;
    int chosen_graph_number;
    int chosen_point_number;
    double x_min_0, x_max_0;
    void DrawPoint(int x, int y, QColor color, int point_radius);
    QColor GenerateColor(int index);
    void DrawLine(int x0, int y0, int x1, int y1, QColor color);
    void mouseReleaseEvent(QMouseEvent *e);
    virtual void Clear()=0;
    virtual void ComputeBorders()=0;
    virtual void ComputeScales()=0;
    virtual void DrawGraphs()=0;
    virtual void DrawGrid()=0;
    virtual void DrawAxises()=0;
    virtual void DrawLegend()=0;
    virtual void Paint(bool no_repaint)=0;
    virtual void AddPoint(QString graph_name, double x, double y)=0;
    virtual void mouseMoveEvent(QMouseEvent * e)=0;
    virtual bool mousePressEvent(QMouseEvent *e, double &x, double &y)=0;
    virtual void DeleteAllLabels()=0;
    virtual void FluentlyPaint(int i, int count)=0;
public:
    GraphsArea();
    GraphsArea(QString x_name, QString y_name, double scale);
    void setScale(int scale);
    void setAxisesName(QString name1, QString name2);
    QString getXName();
    QString getYName();
    double getScale();
    virtual void AddGraph(QString filename)=0;
    virtual bool isGraphExsist(QString name)=0;
    virtual void DeleteChosenPoint()=0;
    virtual void setChoosenPointCoordinates(double x, double y)=0;
    virtual QVector<Graph *> getGraphs()=0;
};

#endif // GRAPHSAREA_H
