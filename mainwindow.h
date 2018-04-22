#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cellularautomation.h"

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
    void on_Start_clicked();

    void on_radioButton_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;
    CellularAutomation *CellUI;

    int Sexual, SizeW, SizeH, RadDisp, RadBreed,
        Fertility, Density, CountKind, Time;

};

#endif // MAINWINDOW_H
