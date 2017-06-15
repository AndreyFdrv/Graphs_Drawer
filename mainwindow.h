#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ScaleSlider_valueChanged(int value);

    void on_LoadGraphButton_clicked();

    void on_AxisesNamesButton_clicked();

    void on_AddPointButton_clicked();

    void on_DeletePointButton_clicked();

    void on_ChnagePointButton_clicked();

public slots:
    void setChangeCoordinatesLineEdits(double x, double y);
private:
    Ui::MainWindow *ui;
signals:
    void ScaleChanged(int scale);
    void AxisesNamesChanged(QString name1, QString name2);
    void AddPoint(QString name, double x, double y);
    void DeletePoint();
    void CoordinatesChanged(double x, double y);
};

#endif // MAINWINDOW_H
