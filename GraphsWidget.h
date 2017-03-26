#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>
#include <QVector>
#include "Graph.h"
#include <QPainter>
class GraphsWidget : public QWidget
{
    Q_OBJECT
private:
    int legend_area_width;
    QVector<Graph *> graphs;//точки отсортированы по координате x
    QPainter *painter;
    double x_min, x_max, y_min, y_max, x_scale, y_scale;
    void Clear();
    void DrawGraph(Graph *graph);
    void ComputeBorders();
    void ComputeScales();
    void DrawGraphs();
    void DrawPoint(int x, int y, QColor color);
    QColor GenerateColor(int index);
    void DrawLine(int x0, int y0, int x1, int y1, QColor color);
public:
    explicit GraphsWidget(QWidget *parent = 0);
    ~GraphsWidget();
    void AddGraph(char *filename);
    bool isGraphExsist(QString name);
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:

};

#endif // GRAPHSWIDGET_H
