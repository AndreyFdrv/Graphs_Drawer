#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include "Graph.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(ScaleChanged(int)),
               ui->graphs_widget, SLOT(setScale(int)));
    ui->graphs_widget->AddGraph("График 1.txt");
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
