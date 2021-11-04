#include "calculate.h"

Calculate::Calculate(const QString& prex):expr(prex),prex(prex),midx(expr.getMidx()){}

int Calculate::calExpression(const QMap<QString, int> &vals)
{
    return expr.calTree(vals);
}

Calculate Calculate::mergeConst()
{
    auto ans=*this;
    ans.expr.mergeTree();
    ans.midx=ans.expr.getMidx();
    return ans;
}
