#ifndef TWOCOORDINATESYSTEMGRAPHSAREA_H
#define TWOCOORDINATESYSTEMGRAPHSAREA_H
#include <QVector>
#include "Graph.h"
#include <QPainter>
#include <QLabel>
#include <QString>
#include "GraphsArea.h"
#include "GraphsWidget.h"
class GraphsWidget;
class TwoCoordinateSystemsGraphsArea:public GraphsArea
{
friend class GraphsWidget;
private:
    QVector<Graph *> lower_graphs, upper_graphs;
    double upper_y_min, upper_y_max, lower_y_min, lower_y_max;
    double upper_y_scale, lower_y_scale;
    QVector<QLabel *> upper_x_labels;
    QVector<QLabel *> upper_y_labels;
    QVector<QLabel *> lower_x_labels;
    QVector<QLabel *> lower_y_labels;
    QLabel *upper_x_name_label, *upper_y_name_label;
    QLabel *lower_x_name_label, *lower_y_name_label;
    double upper_frame_y_offset, lower_frame_y_offset;
    bool isUpperGraphChosen;
    GraphsWidget *widget;
    void Clear();
    void ComputeBorders();
    void ComputeScales();
    void DrawGraphs();
    void DrawGrid();
    void DrawAxises();
    void DrawLegend();
    void Paint(bool no_repaint);
    void AddPoint(QString graph_name, double x, double y);
    void mouseMoveEvent(QMouseEvent * e);
    bool mousePressEvent(QMouseEvent *e, double &x, double &y);
    void DeleteAllLabels();
public:
    TwoCoordinateSystemsGraphsArea(GraphsWidget* widget);
    TwoCoordinateSystemsGraphsArea(GraphsWidget* widget, QVector<Graph *> graphs, QString x_name,
                                   QString y_name, double scale);
    void AddGraph(QString filename);
    bool isGraphExsist(QString name);
    void DeleteChosenPoint();
    void setChoosenPointCoordinates(double x, double y);
    QVector<Graph *> getGraphs();
};

#endif // ONECOORDINATESYSTEMGRAPHSAREA_H
