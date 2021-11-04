#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItem>
#include <QVector>
#include "calculate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int choose;
    void initTableView();
    void initAnsList();
    void initInput();
    void initButton();
    void getInput();
    Ui::MainWindow *ui;
    QVector<Calculate> anses;
};
#endif // MAINWINDOW_H
