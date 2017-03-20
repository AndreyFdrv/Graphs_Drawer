#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QWidget>

class GraphsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphsWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
private:
    void Clear();
signals:

public slots:

};

#endif // GRAPHSWIDGET_H
