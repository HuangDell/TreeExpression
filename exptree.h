#ifndef EXPTREE_H
#define EXPTREE_H
#include <QChar>

struct Node{
    QChar val;
    Node* left;
    Node* right;
    Node(QChar val,Node* left=nullptr,Node *right=nullptr):val(val),left(left),right(right){}
};

class ExpTree
{
    Node* head;
public:
    ExpTree();

};

#endif // EXPTREE_H
