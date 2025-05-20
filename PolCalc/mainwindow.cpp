#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QString"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString inp_data;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_CalculateButton_clicked()
{

}

