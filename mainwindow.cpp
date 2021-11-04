#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow),choose(0)
{
    ui->setupUi(this);
    initTableView();
    initInput();
    initButton();
    initAnsList();
}

void MainWindow::initTableView()
{
    ui->table->setHorizontalHeaderItem(0,new QTableWidgetItem("变量"));
    ui->table->setHorizontalHeaderItem(1,new QTableWidgetItem("值"));
}

void MainWindow::initButton()
{
    connect(ui->solve,&QAbstractButton::clicked,this,[this](){
        QMap<QString,int> vals;
        int row=anses[choose].getVary().size();
        for(int i=0;i<row;i++)
        {
            auto item0=ui->table->item(i,0)->text()[0];
            auto item1=ui->table->item(i,1)->text().toInt();
            vals[item0]=item1;
        }
        int ans=anses[choose].calExpression(vals);
        ui->ansView->append("Ans="+QString::number(ans));
    });

    connect(ui->clear,&QAbstractButton::clicked,this,[this](){
        ui->ansView->clear();
        ui->table->clear();
    });

    connect(ui->simply,&QAbstractButton::clicked,this,[this](){
        auto ans=anses[choose].mergeConst();
        ui->ansView->append("Ans:"+ans.getMidx());
        anses.push_back(ans);
        ui->ansList->addItem(ans.getMidx());
    });

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
        choose=ui->ansList->currentRow();
        auto size=anses[choose].getVary().size();
        int i=0;
        ui->ansView->setText(cur->text());
        for(auto v:anses[choose].getVary())
        {
            auto item0=new QTableWidgetItem(v);
            auto item1=new QTableWidgetItem("0");
            ui->table->setItem(size-i-1,0,item0);
            ui->table->setItem(size-i-1,1,item1);
            i++;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

