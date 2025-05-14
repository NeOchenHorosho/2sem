#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include "mset.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Input_clicked();

    void on_Union_clicked();

    void on_Intersection_clicked();

    void on_Difference_clicked();

    void on_SymDifference_clicked();

    void on_SaveButton_clicked();

private:
    Ui::MainWindow *ui;

    mset<student> *first;
    mset<student> *second;
    mset<student> *result;

    void fillTableFromMset(QTableWidget* table, const mset<student>& students);
};
#endif // MAINWINDOW_H
