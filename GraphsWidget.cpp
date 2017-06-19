#include "GraphsWidget.h"
#include <QPainter>
#include <QMessageBox>
#include <float.h>
#include <QMouseEvent>
#include "math.h"
#include "GraphsWidget.h"
GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{
    one_system_area=new OneCoordinateSystemGraphsArea(this);
    two_systems_area=new TwoCoordinateSystemsGraphsArea(this);
    isOneCoordinateSystem=true;
    no_repaint=false;
    isFluentlyPaint=false;
    fluently_paint_iterations_count=100;
}
void GraphsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(isFluentlyPaint)
    {
        if(isOneCoordinateSystem)
            one_system_area->FluentlyPaint(
                        fluently_paint_iteration_number,
                        fluently_paint_iterations_count);
        else
            two_systems_area->FluentlyPaint(
                        fluently_paint_iteration_number,
                        fluently_paint_iterations_count);
    }
    else
    {
        if(isOneCoordinateSystem)
            one_system_area->Paint(no_repaint);
        else
            two_systems_area->Paint(no_repaint);
    }
}
void GraphsWidget::AddPoint(QString graph_name, double x, double y)
{
    if((graph_name==NULL)||(graph_name==""))
        return;
    isFluentlyPaint=true;
    if(isOneCoordinateSystem)
        one_system_area->AddPoint(graph_name, x, y);
    else
        two_systems_area->AddPoint(graph_name, x, y);
    for(int i=0; i<fluently_paint_iterations_count; i++)
    {
        fluently_paint_iteration_number=i;
        repaint();
    }
    isFluentlyPaint=false;
}
void GraphsWidget::AddGraph(QString filename)
{
    if(isOneCoordinateSystem)
        one_system_area->AddGraph(filename);
    else
        two_systems_area->AddGraph(filename);
    repaint();
}
bool GraphsWidget::isGraphExsist(QString name)
{
    bool result;
    if(isOneCoordinateSystem)
        result=one_system_area->isGraphExsist(name);
    else
        result=two_systems_area->isGraphExsist(name);
    return result;
}
void GraphsWidget::setScale(int scale)
{
    if(isOneCoordinateSystem)
        one_system_area->setScale(scale);
    else
        two_systems_area->setScale(scale);
    repaint();
}
void GraphsWidget::mousePressEvent(QMouseEvent *e)
{
    double x, y;
    if(isOneCoordinateSystem)
    {
        if(one_system_area->mousePressEvent(e, x, y))
            emit ChosenPointChanged(x, y);
    }
    else
    {
        if(two_systems_area->mousePressEvent(e, x, y))
            emit ChosenPointChanged(x, y);
    }
    repaint();
}
void GraphsWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(isOneCoordinateSystem)
        one_system_area->mouseReleaseEvent(e);
    else
        two_systems_area->mouseReleaseEvent(e);
}
void GraphsWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(isOneCoordinateSystem)
        one_system_area->mouseMoveEvent(e);
    else
        two_systems_area->mouseMoveEvent(e);
    repaint();
}
void GraphsWidget::setAxisesName(QString name1, QString name2)
{
    if(isOneCoordinateSystem)
        one_system_area->setAxisesName(name1, name2);
    else
        two_systems_area->setAxisesName(name1, name2);
    repaint();
}
void GraphsWidget::DeleteChosenPoint()
{
    if(isOneCoordinateSystem)
        one_system_area->DeleteChosenPoint();
    else
        two_systems_area->DeleteChosenPoint();
    repaint();
}
void GraphsWidget::setChoosenPointCoordinates(double x, double y)
{
    if(isOneCoordinateSystem)
        one_system_area->setChoosenPointCoordinates(x, y);
    else
        two_systems_area->setChoosenPointCoordinates(x, y);
    repaint();
}
void GraphsWidget::ChangeMode()
{
    one_system_area->DeleteAllLabels();
    two_systems_area->DeleteAllLabels();
    if(isOneCoordinateSystem)
    {
        isOneCoordinateSystem=false;
        delete two_systems_area;
        two_systems_area=new TwoCoordinateSystemsGraphsArea(this, one_system_area->getGraphs(),
                                                            one_system_area->getXName(),
                                                            one_system_area->getYName(),
                                                            one_system_area->getScale());
    }
    else
    {
        isOneCoordinateSystem=true;
        delete one_system_area;
        one_system_area=new OneCoordinateSystemGraphsArea(this, two_systems_area->getGraphs(),
                                                          two_systems_area->getXName(),
                                                          two_systems_area->getYName(),
                                                          two_systems_area->getScale());
    }
    repaint();
}
