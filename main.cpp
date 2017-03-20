#include "mainwindow.h"
#include <QApplication>
#include "Graph.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Graph *graph=new Graph();
    graph->LoadGraphFromFile("График 1.txt");
    delete graph;
    return a.exec();
}
