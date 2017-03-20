#include "GraphsWidget.h"
#include <QPainter>
GraphsWidget::GraphsWidget(QWidget *parent) :
    QWidget(parent)
{

}
void GraphsWidget::Clear()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
}
void GraphsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    Clear();
}
