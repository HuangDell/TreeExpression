#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), choose(0),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTableView();//初始化各种构件
    initInput();
    initButton();
    initAnsList();
}

void MainWindow::initTableView()//初始化表格
{
    ui->table->setHorizontalHeaderItem(0,new QTableWidgetItem("变量"));
    ui->table->setHorizontalHeaderItem(1,new QTableWidgetItem("值"));
}

void MainWindow::initButton()//初始化按钮
{
    connect(ui->solve,&QAbstractButton::clicked,this,[this](){
        QMap<QString,double> vals;
        int row=anses[choose].getVary().size();
        for(int i=0;i<row;i++)
        {
            auto item0=ui->table->item(i,0)->text()[0];
            auto item1=ui->table->item(i,1)->text().toDouble();
            vals[item0]=item1;
        }
        double ans=anses[choose].calExpression(vals);
        ui->ansShow->append("Ans="+QString::number(ans));
    });

    connect(ui->clear,&QAbstractButton::clicked,this,[this](){
        ui->ansView->clear();
        ui->ansShow->clear();
        ui->table->clear();
    });

    connect(ui->simply,&QAbstractButton::clicked,this,[this](){
        auto ans=anses[choose].mergeConst();
        ui->ansShow->append("Ans:"+ans.getMidx());
    });

    connect(ui->del,&QAbstractButton::clicked,this,[this](){
        qDebug()<<choose;
        anses.erase(anses.cbegin()+choose);
        delete ui->ansList->takeItem(choose);
        ui->ansView->clear();
        ui->ansShow->clear();
        ui->table->clear();
    });

    connect(ui->diff,&QAbstractButton::clicked,this,[this](){//初始化求导按钮
        auto ans=anses[choose].diff();
        int i=0;
        for(const auto var:anses[choose].getVary())
        {
            ui->ansShow->append(var);
            QTextCursor text_cursor(ui->ansShow->textCursor());
            text_cursor.movePosition(QTextCursor::End);
            ui->ansShow->setTextCursor(text_cursor);
            ui->ansShow->insertPlainText("'=");
            ui->ansShow->insertPlainText(ans[i]);
            i++;
        }
    });

    connect(ui->com,&QAbstractButton::clicked,this,[this]{
        auto ans=anses[choose].compoundExpr(anses[post]);
        ui->ansShow->clear();
        ui->ansShow->append(ans);
    });


}

void MainWindow::initInput()//初始化输入框
{
    connect(ui->input,&QLineEdit::returnPressed,this,[this](){
        try{
            Calculate cas(ui->input->text());
            ui->ansList->addItem(cas.getMidx());
            anses.push_back(cas);
            ui->ansShow->clear();
        }catch(const char *error){
            ui->ansShow->setText(error);
        }
            ui->input->clear();
    });
}

void MainWindow::initAnsList()//初始化列表
{
    connect(ui->ansList,&QListWidget::itemDoubleClicked,this,[this](){
        auto cur=ui->ansList->currentItem();
        post=choose;
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
    connect(ui->ansList,&QListWidget::itemClicked,this,[this]{
        post=choose;
        choose=ui->ansList->currentRow();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

