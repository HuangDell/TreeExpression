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

void MainWindow::initInput()//初始化输入框
{
    connect(ui->input,&QLineEdit::returnPressed,this,[this](){
        Calculate cas(ui->input->text());
        ui->ansList->addItem(cas.getMidx());
        anses.push_back(cas);
        ui->input->clear();
    });
}

void MainWindow::initAnsList()
{
    connect(ui->ansList,&QListWidget::itemDoubleClicked,this,[this](){
        auto cur=ui->ansList->currentItem();
        auto index=ui->ansList->currentIndex();
        int i=0;
        ui->ansView->setText(cur->text());
        for(auto v:anses[index.row()].getVary())
        {
            auto item0=new QTableWidgetItem(v);
            auto item1=new QTableWidgetItem("0");
            ui->table->setItem(i,0,item0);
            ui->table->setItem(i++,1,item1);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

