#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include "Graph.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphs_widget->AddGraph("График 1.txt");
}
MainWindow::~MainWindow()
{
    delete ui;
}
