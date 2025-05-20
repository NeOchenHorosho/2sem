#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PluspushButton_clicked()
{
    QString firstArgText = ui->FirstArglineEdit->text();
    double firstArgNum = firstArgText.toDouble();
    QString secondArgText = ui->SecondArglineEdit->text();
    double secondArgNum = secondArgText.toDouble();
    double res = firstArgNum + secondArgNum;
    QString ResStr = QString::number(res);
    ui->ResultlineEdit->setText(ResStr);
}


void MainWindow::on_MinuspushButton_clicked()
{
    QString firstArgText = ui->FirstArglineEdit->text();
    double firstArgNum = firstArgText.toDouble();
    QString secondArgText = ui->SecondArglineEdit->text();
    double secondArgNum = secondArgText.toDouble();
    double res = firstArgNum - secondArgNum;
    QString ResStr = QString::number(res);
    ui->ResultlineEdit->setText(ResStr);
}


void MainWindow::on_MultiplypushButton_clicked()
{
    QString firstArgText = ui->FirstArglineEdit->text();
    double firstArgNum = firstArgText.toDouble();
    QString secondArgText = ui->SecondArglineEdit->text();
    double secondArgNum = secondArgText.toDouble();
    double res = firstArgNum * secondArgNum;
    QString ResStr = QString::number(res);
    ui->ResultlineEdit->setText(ResStr);
}


void MainWindow::on_DividepushButton_clicked()
{
    QString firstArgText = ui->FirstArglineEdit->text();
    double firstArgNum = firstArgText.toDouble();
    QString secondArgText = ui->SecondArglineEdit->text();
    double secondArgNum = secondArgText.toDouble();
    if(secondArgNum == 0)
    {
        ui->ResultlineEdit->setText("ДЕЛИТЬ НА НОЛЬ НЕЛЬЗЯ!!!");
        return;
    }
    double res = firstArgNum + secondArgNum;
    QString ResStr = QString::number(res);
    ui->ResultlineEdit->setText(ResStr);
}

