#ifndef CELLULARAUTOMATION_H
#define CELLULARAUTOMATION_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QSize>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QColor>
#include <QVector>
#include <QRandomGenerator>
#include <QPair>
#include <QThread>
#include <QMutex>

namespace Ui {
class CellularAutomation;
}

class CellularAutomation : public QDialog
{
    Q_OBJECT

public:
    explicit CellularAutomation(QWidget *parent = 0, int _Sexual = 0, int _SizeW = 20, int _SizeH = 20, int _RadDisp = 4,
                                int _RadBreed = 4, int _Fertility = 4, int _Density = 4, int _Time = 0, int _CountKind = 4);
    ~CellularAutomation();

    QPixmap *pm;
    QPainter *paint;
    QTimer *timer;
    QVector< QVector< QPair<int, int> > > Coordinates;
    QVector< QVector<int> > Array;
    QVector< QVector< QVector<int> > > NewArray;
    QVector< QColor > color;
    void FillArray();
    int Sexual, SizeW, SizeH, RadDisp, RadBreed,
        Fertility, Density, CountKind, Time;

private:
    Ui::CellularAutomation *ui;

private slots:
    void next_step();
    void draw();
    void step();
    void SwitchArray();

};

class MyThread : public QThread {
    Q_OBJECT
public:
    CellularAutomation* CelAut;
    int num;
    MyThread(CellularAutomation* _CelAut, int _num) : CelAut(_CelAut), num(_num) {}
private:
    void run() override;
};

#endif // CELLULARAUTOMATION_H
