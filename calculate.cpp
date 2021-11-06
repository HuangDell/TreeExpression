#include "calculate.h"
using std::string;

Calculate::Calculate(const QString& prex):expr(prex),prex(prex),midx(expr.getMidx()){}

int Calculate::calExpression(const QMap<QString, int> &vals)
{
    return expr.calTree(vals);
}

QVector<char*> Calculate::diff()
{
    QVector<char*> ans;
    const auto vary=expr.getVary();
    for(auto var:vary)
    {
        Py_Initialize();
        char ch=var.toLatin1();
        auto pModule = PyImport_ImportModule("test_py");  // 这里的test_py就是创建的python文件
        auto args=PyTuple_New(2);
        PyTuple_SetItem(args,0,Py_BuildValue("s",midx.toStdString().c_str()));
        PyTuple_SetItem(args,1,Py_BuildValue("c",ch));
        auto pFunhello= PyObject_GetAttrString(pModule,"diff");  // 这里的hellow就是python文件定义的函数
        auto reans=PyObject_CallObject(pFunhello,args);
        char *an;
        PyArg_Parse(reans,"s",&an);
        ans.push_back(an);
        Py_Finalize();
    }
    return ans;
}

Calculate Calculate::mergeConst()
{
    auto ans=*this;
    ans.expr.mergeTree();
    ans.midx=ans.expr.getMidx();
    return ans;
}
