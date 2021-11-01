#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTableView();
    initInput();
    initAnsList();
}

void MainWindow::initTableView()
{
    ui->table->setHorizontalHeaderItem(0,new QTableWidgetItem("变量"));
    ui->table->setHorizontalHeaderItem(1,new QTableWidgetItem("值"));
}

void MainWindow::initInput()
{
    connect(ui->input,&QLineEdit::returnPressed,this,[this](){
        Calculate cas(ui->input->text());
        ui->ansList->addItem(cas.getMidx());
        anses.push_back(cas);
    });
}

void MainWindow::initAnsList()
{
    connect(ui->ansList,&QListWidget::itemDoubleClicked,this,[this](){
        auto cur=ui->ansList->currentItem();
        ui->ansView->setText(cur->text());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

