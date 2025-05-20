#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_PluspushButton_clicked();

    void on_MinuspushButton_clicked();

    void on_MultiplypushButton_clicked();

    void on_DividepushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
