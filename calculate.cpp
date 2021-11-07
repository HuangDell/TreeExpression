#include "calculate.h"
using std::string;

Calculate::Calculate(const QString& prex):expr(prex),prex(prex),midx(expr.getMidx()){}//构造器初始化

double Calculate::calExpression(const QMap<QString, double> &vals)
{
    return expr.calTree(vals);//调用二叉树进行表达式计算
}

QString Calculate::compoundExpr(const Calculate &cal)//表达式复合：本质上就是两个表达式之间进行相加
{
    Py_Initialize();
    auto pModule = PyImport_ImportModule("cal");
    auto args=PyTuple_New(2);
    PyTuple_SetItem(args,0,Py_BuildValue("s",midx.toStdString().c_str()));
    PyTuple_SetItem(args,1,Py_BuildValue("s",cal.midx.toStdString().c_str()));
    auto pFunhello= PyObject_GetAttrString(pModule,"com");
    auto reans=PyObject_CallObject(pFunhello,args);
    char *an;
    PyArg_Parse(reans,"s",&an);//获得答案
    Py_Finalize();
    return QString(an);
}

QVector<char*> Calculate::diff()//求偏导
{
    QVector<char*> ans;
    const auto vary=expr.getVary();
    for(auto var:vary)
    {
        Py_Initialize();
        char ch=var.toLatin1();
        auto pModule = PyImport_ImportModule("cal");
        auto args=PyTuple_New(2);
        PyTuple_SetItem(args,0,Py_BuildValue("s",midx.toStdString().c_str()));
        PyTuple_SetItem(args,1,Py_BuildValue("c",ch));
        auto pFunhello= PyObject_GetAttrString(pModule,"diff");
        auto reans=PyObject_CallObject(pFunhello,args);
        char *an;
        PyArg_Parse(reans,"s",&an);
        ans.push_back(an);
        Py_Finalize();
    }
    return ans;
}

Calculate Calculate::mergeConst()//合并常数
{
    auto ans=*this;
    ans.expr.mergeTree();
    ans.midx=ans.expr.getMidx();
    return ans;
}
