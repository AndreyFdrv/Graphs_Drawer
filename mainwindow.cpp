#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include "Graph.h"
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(ScaleChanged(int)),
               ui->graphs_widget, SLOT(setScale(int)));
    QObject::connect(this, SIGNAL(AxisesNamesChanged(QString, QString)),
               ui->graphs_widget, SLOT(setAxisesName(QString, QString)));
    QObject::connect(this, SIGNAL(AddPoint(QString, double, double)),
               ui->graphs_widget, SLOT(AddPoint(QString, double, double)));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ScaleSlider_valueChanged(int value)
{
    ui->ScaleLabel->setText("Масштаб: "+QString::number(25*value)+"%");
    emit ScaleChanged(25*value);
}

void MainWindow::on_LoadGraphButton_clicked()
{
    ui->graphs_widget->no_repaint=true;//почему-то перерисовка подписей осей и легенды вызывает
    //зависание окна выбора файла, поэтому временно запретим любую перерисовку в области графика
    QString filename=QFileDialog::getOpenFileName();
    ui->graphs_widget->no_repaint=false;
    if(filename!="")
        ui->graphs_widget->AddGraph(filename);
}
void MainWindow::on_AxisesNamesButton_clicked()
{
    emit AxisesNamesChanged(ui->Axis1LineEdit->text(), ui->Axis2LineEdit->text());
}
void MainWindow::on_AddPointButton_clicked()
{
    emit AddPoint(ui->GraphLineEdit->text(), (ui->Coordinate1LineEdit->text()).toDouble(),
                  (ui->Coordinate2LineEdit->text()).toDouble());
}
