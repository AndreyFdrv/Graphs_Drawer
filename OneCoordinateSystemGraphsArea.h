#ifndef ONECOORDINATESYSTEMGRAPHSAREA_H
#define ONECOORDINATESYSTEMGRAPHSAREA_H
#include <QVector>
#include <QPainter>
#include <QLabel>
#include <QString>
#include "GraphsArea.h"
#include "GraphsWidget.h"
class GraphsWidget;
class OneCoordinateSystemGraphsArea:public GraphsArea
{
friend class GraphsWidget;
private:
    QVector<Graph *> graphs;
    double y_min, y_max, y_scale;
    QVector<QLabel *> x_labels;
    QVector<QLabel *> y_labels;
    QLabel *x_name_label, *y_name_label;
    double frame_y_offset;
    GraphsWidget *widget;
    double y_min_0, y_max_0;
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
    void FluentlyPaint(int i, int count);
public:
    OneCoordinateSystemGraphsArea(GraphsWidget* widget);
    OneCoordinateSystemGraphsArea(GraphsWidget* widget, QVector<Graph *> graphs, QString x_name,
                                  QString y_name, double scale);
    void AddGraph(QString filename);
    bool isGraphExsist(QString name);
    void DeleteChosenPoint();
    void setChoosenPointCoordinates(double x, double y);
    QVector<Graph *> getGraphs();
};

#endif // ONECOORDINATESYSTEMGRAPHSAREA_H
