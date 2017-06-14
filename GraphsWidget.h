#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include <QVector>
#include "Graph.h"
#include <QPainter>
#include <QLabel>
#include <QString>
class GraphsWidget : public QWidget
{
    Q_OBJECT
private:
    int legend_area_width;
    int x_axis_offset, y_axis_offset;
    QVector<Graph *> graphs;//точки отсортированы по координате x
    QPainter *painter;
    double x_min, x_max, y_min, y_max, x_scale, y_scale;
    int x_divisions_count, y_divisions_count;
    void Clear();
    void DrawGraph(Graph *graph);
    void ComputeBorders();
    void ComputeScales();
    void DrawGraphs();
    void DrawPoint(int x, int y, QColor color);
    QColor GenerateColor(int index);
    void DrawLine(int x0, int y0, int x1, int y1, QColor color);
    void DrawGrid();
    void DrawAxises();
    void DrawLegend();
    QVector<QLabel *> x_labels;
    QVector<QLabel *> y_labels;
    QVector<QLabel *> legend_labels;
    QString x_name, y_name;
    QLabel *x_name_label, *y_name_label;
    int scale;
    bool isLeftButtonDown;
    int mouse_x_0, mouse_y_0;
    double frame_x_offset, frame_y_offset;
public:
    explicit GraphsWidget(QWidget *parent = 0);
    ~GraphsWidget();
    void AddGraph(char *filename);
    bool isGraphExsist(QString name);
    void AddPoint(QString graph_name, double x, double y);
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void setScale(int scale);
    void mouseMoveEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // GRAPHSWIDGET_H
