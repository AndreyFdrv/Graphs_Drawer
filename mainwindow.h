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

private:
    Ui::MainWindow *ui;
signals:
    void ScaleChanged(int scale);
    void AxisesNamesChanged(QString name1, QString name2);
};

#endif // MAINWINDOW_H
