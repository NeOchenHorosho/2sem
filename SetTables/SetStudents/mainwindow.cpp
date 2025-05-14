#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    first = new mset<student>;
    second = new mset<student>;
    result = new mset<student>;

    ui->table1->setRowCount(10);
    ui->table1->setColumnCount(2);
    ui->table1->setHorizontalHeaderLabels(QStringList() << "имя" << "группа");

    ui->table2->setRowCount(10);
    ui->table2->setColumnCount(2);
    ui->table2->setHorizontalHeaderLabels(QStringList() << "имя" << "группа");

    ui->resultTable->setRowCount(20);
    ui->resultTable->setColumnCount(2);
    ui->resultTable->setHorizontalHeaderLabels(QStringList() << "имя" << "группа");
}

MainWindow::~MainWindow()
{
    delete ui;

    delete first;
    delete second;
    delete result;
}

void MainWindow::fillTableFromMset(QTableWidget* table, const mset<student>& students)
{
    //очистка таблицы и изменение числа строк
    table->clear();
    table->setRowCount(students.size());
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << "имя" << "группа");

    for (int i = 0; i < students.size(); ++i)
    {
        //создаем элементы таблицы
        QTableWidgetItem* nameItem = new QTableWidgetItem(students[i].name);
        QTableWidgetItem* groupItem = new QTableWidgetItem(QString::number(students[i].group));

        //элементы в таблицу
        table->setItem(i, 0, nameItem);
        table->setItem(i, 1, groupItem);
    }

    //выравниваем колонки
    //table->resizeColumnsToContents();
}

void MainWindow::on_Input_clicked()
{
    QFile filename("input.txt");
    filename.open(QIODevice::ReadOnly);
    QTextStream file(&filename);
    file >> *first >> *second;
    filename.close();

    fillTableFromMset(ui->table1, *first);
    fillTableFromMset(ui->table2, *second);

}


void MainWindow::on_Union_clicked()
{
    *result = *first + *second;

    fillTableFromMset(ui->resultTable, *result);
}


void MainWindow::on_Intersection_clicked()
{
    *result = *first ^ *second;

    fillTableFromMset(ui->resultTable, *result);
}


void MainWindow::on_Difference_clicked()
{
    *result = *first - *second;

    fillTableFromMset(ui->resultTable, *result);
}


void MainWindow::on_SymDifference_clicked()
{
    *result = *first | *second;

    fillTableFromMset(ui->resultTable, *result);
}


void MainWindow::on_SaveButton_clicked()
{
    QFile fout("output.txt");
    fout.open(QIODevice::WriteOnly);
    QTextStream out(&fout);
    out << *result << Qt::endl;
    fout.close();
}

