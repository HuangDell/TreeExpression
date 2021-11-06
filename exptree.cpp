#include "exptree.h"

ExpTree::ExpTree(const QString& prex):head(nullptr),prex(prex)
{
    int i=0;
    buildTree(head,prex,i);
}

ExpTree::ExpTree(const ExpTree &tree):head(nullptr),prex(tree.prex),vary(tree.vary)
{
    int i=0;
    buildTree(head,tree.prex,i);
}

void ExpTree::buildTree(Node* &ptr,const QString &prex,int& index)
{
    if(prex.size()==1)
    {
        ADDVARY(prex[index]);
        ptr=new Node(prex[index++]);
        return;
    }
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

int ExpTree::getPriority(const QString &st)
{
    if(st=="+" || st=="-")
        return 1;
    else if(st=="*" || st=="/")
        return 2;
    else if(st=="^")
        return 3;
    return 4;
}

void ExpTree::medTraversal(Node* ptr,QString &midx, QStack<QString> &st)
{
    if(!ptr)
        return;
    if(isOperator(ptr->val[0]))
    {
        if(!st.empty() && getPriority(ptr->val)<getPriority(st.top()))
            midx.push_back('(');
        st.push(ptr->val);
    }
    medTraversal(ptr->left,midx,st);
    midx.push_back(ptr->val);
    medTraversal(ptr->right,midx,st);
   if(isOperator(ptr->val[0]))
   {
       st.pop();
       if(!st.empty() &&getPriority(ptr->val)<getPriority(st.top()))
            midx.push_back(')');
   }
}


int ExpTree::postTraversal(Node *ptr,const QMap<QString, int> &vals)
{
    if(!ptr->left && !ptr->right && ptr->val.size()==1)
    {
        if( ptr->val[0].isLetter())
            return vals[ptr->val];
        return ptr->val[0].toLatin1()-'0';
    }
    int left=postTraversal(ptr->left,vals);
    int right=postTraversal(ptr->right,vals);
    if(ptr->val=='+')
        return left+right;
    if(ptr->val=='-')
        return left-right;
    if(ptr->val=='*')
        return left*right;
    if(ptr->val=='/')
        return left/right;
    if(ptr->val=='^')
        return pow(left,right);
    return 0;
}


bool ExpTree::mergeTree(Node *ptr)
{
    if(ptr->val[0].isLetter())
        return false;
    if(!ptr->left && !ptr->right)
        return true;
    auto bool1=mergeTree(ptr->left);
    auto bool2=mergeTree(ptr->right);
    if(bool1 && bool2)
    {
        auto left=ptr->left->val[0].toLatin1()-'0';
        auto right=ptr->right->val[0].toLatin1()-'0';
        int newval=0;
        if(ptr->val=='+')
            newval=left+right;
        else if(ptr->val=='-')
            newval=left-right;
        else if(ptr->val=='*')
            newval=left*right;
        else if(ptr->val=='/')
            newval=left/right;
        else if(ptr->val=='^')
            newval=pow(left,right);
        ptr->val=QString::number(newval);
        delete ptr->left;
        delete ptr->right;
        ptr->left=nullptr;
        ptr->right=nullptr;
        return true;
    }
    else if(!bool1 && bool2 && getPriority(ptr->left->val)==getPriority(ptr->val))
    {
        int left;
        Node* temp,*del;
        if(ptr->left->right->val[0].isDigit())
        {
            left=ptr->left->right->val[0].toLatin1()-'0';
            temp=ptr->left->left;
            del=ptr->left->right;
        }
        else if(ptr->left->left->val[0].isDigit())
        {
            left=ptr->left->left->val[0].toLatin1()-'0';
            temp=ptr->left->right;
            del=ptr->left->left;
        }
        else
            return false;
        auto right=ptr->right->val[0].toLatin1()-'0';
        int newval=0;
        if(ptr->val=='+')
            newval=left+right;
        else if(ptr->val=='-')
            newval=left-right;
        else if(ptr->val=='*')
            newval=left*right;
        else if(ptr->val=='/')
            newval=left/right;
        else if(ptr->val=='^')
            newval=left*right;
        ptr->right->val=QString::number(newval);
        delete ptr->left;
        delete del;
        ptr->left=temp;
    }
    else if(!bool2 &&bool1 && getPriority(ptr->right->val)==getPriority(ptr->val))
    {
        int right;
        Node* temp,*del;
        if(ptr->right->right->val[0].isDigit())
        {
            right=ptr->right->right->val[0].toLatin1()-'0';
            temp=ptr->right->left;
            del=ptr->right->right;
        }
        else if(ptr->right->left->val[0].isDigit())
        {
            right=ptr->right->left->val[0].toLatin1()-'0';
            temp=ptr->right->right;
            del=ptr->right->left;
        }
        else
            return false;
        auto left=ptr->left->val[0].toLatin1()-'0';
        int newval=0;
        if(ptr->val=='+')
            newval=left+right;
        else if(ptr->val=='-')
            newval=left-right;
        else if(ptr->val=='*')
            newval=left*right;
        else if(ptr->val=='/')
            newval=left/right;
        else if(ptr->val=='^')
            newval=left*right;
        ptr->left->val=QString::number(newval);
        delete ptr->right;
        delete del;
        ptr->right=temp;
    }
    return false;
}

void ExpTree::mergeTree()
{
    mergeTree(head);
}

bool ExpTree::isOperator(const QChar &ch)
{
    if(ch=='+' || ch=='-' || ch=='*' || ch=='^' || ch=='/')
            return true;
    return false;
}


QString ExpTree::getMidx()
{
    QString midx;
    QStack<QString> st;
    medTraversal(head,midx,st);
    return midx;
}

int ExpTree::calTree(const QMap<QString,int> &vals)
{
    return postTraversal(head,vals);
}

void ExpTree::clear()
{
    clear(head);
    head=nullptr;
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
