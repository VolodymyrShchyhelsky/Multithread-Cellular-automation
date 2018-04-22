#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Start_clicked()
{
    SizeW = 50;// ui->SizeW->toPlainText().toInt();
    SizeH = 50;//ui->SizeH->toPlainText().toInt();
    RadDisp = 1;//ui->RadDisp->toPlainText().toInt();
    RadBreed = 4;//ui->RadBreed->toPlainText().toInt();
    Fertility = 9;//ui->Fertility->toPlainText().toInt();
    Density = 3;//ui->Density->toPlainText().toInt();
    Time = ui->Time->toPlainText().toInt();
    CountKind = 9;//ui->CountKind->toPlainText().toInt();
    CellUI = new CellularAutomation(this, Sexual, SizeW, SizeH, RadDisp, RadBreed, Fertility, Density, Time, CountKind);
    CellUI->show();
}

void MainWindow::on_radioButton_clicked()
{
    if(ui->radioButton->isChecked()) {
        ui->RadBreed->setEnabled(false);
        Sexual = 0;
    }
}

void MainWindow::on_radioButton_3_clicked()
{
    if(ui->radioButton_3->isChecked()) {
        ui->RadBreed->setEnabled(true);
        Sexual = 3;
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    if(ui->radioButton_2->isChecked()) {
        ui->RadBreed->setEnabled(true);
        Sexual = 2;
    }
}
