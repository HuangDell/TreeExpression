#ifndef EXPTREE_H
#define EXPTREE_H
#include <QChar>
#include <QString>
#include <QSet>

#define ADDVARY(ch)\
    if(ch.isLetter()) vary.insert(ch);

struct Node{
    QChar val;
    Node* left;
    Node* right;
    Node(QChar val,Node* left=nullptr,Node *right=nullptr):val(val),left(left),right(right){}
};

class ExpTree
{
private:
    Node* head;
    QSet<QChar> vary;
    void clear(Node* ptr);
    void medTraversal(Node* ptr,QString& midx,int floor);
    void buildTree(Node* &ptr,const QString& prex,int& index);
    bool isOperator(const QChar &ch);
public:
    ExpTree(const QString& prex);
    QSet<QChar> getVary(){return vary;}
    QString getMidx();
    void clear();
    void mergeTree();
};

#endif // EXPTREE_H
