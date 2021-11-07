#include "exptree.h"
ExpTree::ExpTree(const QString& prex):head(nullptr),prex(prex)
{
    int i=0;
    buildTree(head,prex,i);
    if(!checkTree(head))//如果不是标准二叉表达树就报错
        throw "请重新输入";
}

ExpTree::ExpTree(const ExpTree &tree):head(nullptr),prex(tree.prex),vary(tree.vary)//复制构造函数
{
    int i=0;
    buildTree(head,tree.prex,i);
    if(!checkTree(head))
        throw "请重新输入";
}

bool ExpTree::isFunction(int index)//输入的是函数
{
    if(index+3<=prex.size())
        return isFunction(prex.mid(index,3));
    return false;
}
bool ExpTree::isFunction(const QString &func)//判断输入的是否为函数
{
    if(func=="log")
        return true;
    else if(func=="sin")
        return true;
    else if(func=="cos")
        return true;
    else if(func=="tan")
        return true;
    else if(func=="exp")
        return true;
    return false;
}

void ExpTree::buildTree(Node* &ptr,const QString &prex,int& index)//关键函数：生成表达树
{
    if(prex.size()==1 && prex[0].isLetterOrNumber())//如果只输入了一个字母或者数字
    {
        ADDVARY(prex[index]);
        ptr=new Node(prex[index++]);
        return;
    }
    if(isFunction(index) && !ptr)//如果是输入函数
    {
        ptr=new Node(prex.mid(index,3));
        index+=3;
        ptr->right=new Node("");
    }
    else if(!ptr)//如果是运算符
    {
        CHECKERROR(index)
        ADDVARY(prex[index]);
        ptr=new Node(prex[index++]);
    }
    if(!ptr->left)//如果左节点为空
    {
        CHECKERROR(index)
        if(isOperator(prex[index]) || isFunction(index))//如果是运算符或者函数继续向下构造
            buildTree(ptr->left,prex,index);
        else//是数字就写入树节点钟
        {
            ADDVARY(prex[index]);
            ptr->left=new Node(prex[index++]);
        }
    }
    if(!ptr->right)//同左节点操作
    {
        CHECKERROR(index)
        if(isOperator(prex[index]) || isFunction(index))
            buildTree(ptr->right,prex,index);
//        else if(isFunction(index)) {
//            ptr->right=new Node(prex.mid(index,3));
//            index+=3;
//            ptr->right->right=new Node("");
//            buildTree(ptr->right->left,prex,index);
//        }
        else
        {
            ADDVARY(prex[index]);
            ptr->right=new Node(prex[index++]);
        }
    }
}


bool ExpTree::checkTree()//判断表达树：可被外界调用
{
    if(!head->left && !head->right && (!head->val[0].isLetterOrNumber() || isFunction(head->val)))
        return false;
    return checkTree(head);
}

bool ExpTree::checkTree(Node *ptr)//判断表达树：内部实现
{
    if(ptr->val.size()==0)
        return true;
    if(!ptr->left && !ptr->right && (!ptr->val[0].isLetterOrNumber() || ptr->val.size()!=1 ))
        return false;
    else if(!ptr->left && !ptr->right)
        return true;
    if(isOperator(ptr->val[0]) || isFunction(ptr->val))
        return checkTree(ptr->left) && checkTree(ptr->right);
    else
        return false;
    return true;
}

int ExpTree::getPriority(const QString &st)//获得运算符优先级
{
    if(st.isEmpty())
        return 0;
    else if(st=="+" || st=="-")
        return 1;
    else if(st=="*" || st=="/")
        return 2;
    else if(st=="^")
        return 3;
    return 4;
}

void ExpTree::medTraversal(Node* ptr,QString &midx, QStack<QString> &st)//中序遍历输出中序表达式
{
    if(!ptr)
        return;
    if(isOperator(ptr->val[0]))//是运算符则要根据运算符优先级进行添加括号
    {
        if(!st.empty() && getPriority(ptr->val)<getPriority(st.top()))//如果输入运算符优先级小于栈顶的优先级
            midx.push_back('(');//则添加括号
        st.push(ptr->val);
    }
    else if(isFunction(ptr->val))//如果输入函数,将函数视为开始，重新调用一边中序遍历输出表达式
    {
        QStack<QString> temp;
        midx.push_back(ptr->val);
        midx.push_back("(");
        medTraversal(ptr->left,midx,temp);
        midx.push_back(")");
        return;
    }
    medTraversal(ptr->left,midx,st);
    midx.push_back(ptr->val);
    medTraversal(ptr->right,midx,st);
   if(isOperator(ptr->val[0]))//加上）
   {
       st.pop();
       if(!st.empty() &&getPriority(ptr->val)<getPriority(st.top()))
            midx.push_back(')');
   }
}


double ExpTree::postTraversal(Node *ptr,const QMap<QString,double > &vals)//后序遍历,计算表达式结果
{
    if(ptr->val.isEmpty())
        return 0;
    if(!ptr->left && !ptr->right && ptr->val.size()==1)
    {
        if( ptr->val[0].isLetter())
            return vals[ptr->val];
        return ptr->val[0].toLatin1()-'0';
    }
    double left=postTraversal(ptr->left,vals);
    double right=postTraversal(ptr->right,vals);
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
    if(ptr->val=="cos")
        return cos(left);
    if(ptr->val=="sin")
        return sin(left);
    if(ptr->val=="tan")
        return tan(left);
    if(ptr->val=="exp")
        return exp(left);
    if(ptr->val=="log")
        return log(left);
    return 0;
}


bool ExpTree::mergeTree(Node *ptr)//合并常数
{
    qDebug()<<ptr->val;
    if(ptr->val.size()==0)//首先判断是否可以合并
        return false;
    if(ptr->val[0].isLetter() && !isFunction(ptr->val))
        return false;
    if(!ptr->left && !ptr->right)
        return true;
    auto bool1=mergeTree(ptr->left);
    auto bool2=mergeTree(ptr->right);
    if(bool1 && bool2)//如果左右子树都可以合并
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
        delete ptr->left;//删除合并了的节点
        delete ptr->right;
        ptr->left=nullptr;
        ptr->right=nullptr;
        return true;
    }
    else if(!bool1 && bool2 && getPriority(ptr->left->val)==getPriority(ptr->val))//如果与其他树的节点还可以合并
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
    else if(!bool2 &&bool1 && getPriority(ptr->right->val)==getPriority(ptr->val))//同上一个else if分支
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

bool ExpTree::isOperator(const QChar &ch)//判断是否为运算符
{
    if(ch=='+' || ch=='-' || ch=='*' || ch=='^' || ch=='/')
            return true;
    return false;
}


QString ExpTree::getMidx()//返回正常表达式
{
    QString midx;
    QStack<QString> st;
    medTraversal(head,midx,st);
    return midx;
}

double ExpTree::calTree(const QMap<QString,double> &vals)
{
    return postTraversal(head,vals);
}

void ExpTree::clear()
{
    clear(head);
    head=nullptr;
}

void ExpTree::clear(Node* ptr)//树的析构
{
    if(!ptr)
        return;
    clear(ptr->left);
    clear(ptr->right);
    delete ptr;
    ptr=nullptr;
}
