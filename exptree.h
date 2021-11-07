#ifndef EXPTREE_H
#define EXPTREE_H
#include <QChar>
#include <QString>
#include <QStack>
#include <QDebug>
#include <QSet>
#include <QMap>
#include <cmath>
#define CHECKERROR(i)\
    if (i>=prex.size()) throw "请重新输入";

#define ADDVARY(ch)\
    if(ch.isLetter()) vary.insert(ch);


struct Node{
    QString val;
    Node* left;
    Node* right;
    Node(QString val,Node* left=nullptr,Node *right=nullptr):val(val),left(left),right(right){}
};

class ExpTree
{
private:
    Node* head;
    QSet<QChar> vary;
    QString prex;

    void clear(Node* ptr);
    bool isOperator(const QChar &ch);
    bool isFunction(int index);
    bool isFunction(const QString &st);
    int getPriority(const QString &st);

    bool mergeTree(Node* ptr);
    void buildTree(Node* &ptr,const QString& prex,int& index);
    bool checkTree(Node* ptr);
    bool checkTree();

    void medTraversal(Node* ptr,QString& midx,QStack<QString> &st);
    double postTraversal(Node* ptr,const QMap<QString,double> &vals);

public:
    ExpTree(const QString& prex);
    ExpTree(const ExpTree& tree);
    ~ExpTree(){clear();}
    QString getMidx();
    void clear();
    void mergeTree();
    double calTree(const QMap<QString,double> &vals);
    QSet<QChar> getVary(){return vary;}
};

#endif // EXPTREE_H
