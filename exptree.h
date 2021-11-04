#ifndef EXPTREE_H
#define EXPTREE_H
#include <QChar>
#include <QString>
#include <QStack>
#include <QDebug>
#include <QSet>
#include <QMap>

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
    int getPriority(const QString &st);
    bool mergeTree(Node* ptr);
    void medTraversal(Node* ptr,QString& midx,QStack<QString> &st);
    int postTraversal(Node* ptr,const QMap<QString,int> &vals);
    void buildTree(Node* &ptr,const QString& prex,int& index);
public:
    ExpTree(const QString& prex);
    ExpTree(const ExpTree& tree);
    ~ExpTree(){clear();}
    QString getMidx();
    void clear();
    void mergeTree();
    int calTree(const QMap<QString,int> &vals);
    QSet<QChar> getVary(){return vary;}
};

#endif // EXPTREE_H
