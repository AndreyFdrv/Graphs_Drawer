#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H
#include <QWidget>
#include <QVector>
#include "Graph.h"
#include <QPainter>
#include <QLabel>
#include <QString>
#include "OneCoordinateSystemGraphsArea.h"
#include "TwoCoordinateSystemsGraphsArea.h"
class OneCoordinateSystemGraphsArea;
class TwoCoordinateSystemsGraphsArea;
class GraphsWidget : public QWidget
{
    Q_OBJECT
private:
    OneCoordinateSystemGraphsArea *one_system_area;
    TwoCoordinateSystemsGraphsArea *two_systems_area;
    bool isFluentlyPaint;
    int fluently_paint_iteration_number;
    int fluently_paint_iterations_count;
public:
    bool isOneCoordinateSystem;
    GraphsWidget(QWidget *parent = 0);
    bool no_repaint;
    void AddGraph(QString filename);
    bool isGraphExsist(QString name);
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void ChosenPointChanged(double x, double y);
public slots:
    void setScale(int scale);
    void mouseMoveEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent *e);
    void setAxisesName(QString name1, QString name2);
    void AddPoint(QString graph_name, double point_x, double point_y);
    void DeleteChosenPoint();
    void setChoosenPointCoordinates(double x, double y);
    void ChangeMode();
};

#endif // GRAPHSWIDGET_H
