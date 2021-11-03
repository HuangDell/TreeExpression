#include "exptree.h"

ExpTree::ExpTree(const QString& prex):head(nullptr)
{
    int i=0;
    buildTree(head,prex,i);
}

void ExpTree::buildTree(Node* &ptr,const QString &prex,int& index)
{
    if(!ptr)
    {
        ADDVARY(prex[index]);
        ptr=new Node(prex[index++]);
    }
    if(!ptr->left)
    {
        if(isOperator(prex[index]))
            buildTree(ptr->left,prex,index);
        else
        {
            ADDVARY(prex[index]);
            ptr->left=new Node(prex[index++]);
        }
    }
    if(!ptr->right)
    {
        if(isOperator(prex[index]))
            buildTree(ptr->right,prex,index);
        else
        {
            ADDVARY(prex[index]);
            ptr->right=new Node(prex[index++]);
        }
    }
}

void ExpTree::medTraversal(Node* ptr,QString &midx, int floor)
{
    if(!ptr)
        return;
    if(floor>1 && ptr->left && ptr->right)
        midx.push_back('(');
    medTraversal(ptr->left,midx,floor+1);
    midx.push_back(ptr->val);
    medTraversal(ptr->right,midx,floor+1);
    if(floor>1 && ptr->left && ptr->right)
        midx.push_back(')');
}

void ExpTree::mergeTree()
{
}

bool ExpTree::isOperator(const QChar &ch)
{
    if(ch=='+' || ch=='-' || ch=='*' || ch=='^' || ch=='\\')
            return true;
    return false;
}


QString ExpTree::getMidx()
{
    QString midx;
    medTraversal(head,midx,0);
    return midx;
}


void ExpTree::clear()
{
    clear(head);
}

void ExpTree::clear(Node* ptr)
{
    if(!ptr)
        return;
    clear(ptr->left);
    clear(ptr->right);
    delete ptr;
    ptr=nullptr;
}
