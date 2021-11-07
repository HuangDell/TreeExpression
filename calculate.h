#ifndef CALCULATE_H
#define CALCULATE_H
#include <QString>
#include "Python.h"
#include <QVector>
#include <string>
#include <QMap>
#include "exptree.h"
#include <cstring>


class Calculate//定义表达式类
{
private:
    ExpTree expr;//表达式本质上是一颗二叉表达式树
    QString prex;//前缀形式
    QString midx;//后缀形式
    bool isLegal;

public:
    Calculate(const QString &prex);
    Calculate mergeConst();//合并常数
    QVector<char*> diff();//求导数
    double calExpression(const QMap<QString,double> &vals);//计算表达式
    QString compoundExpr(const Calculate&cal);//合并表达式:将表达式相加

    QString getPrex(){return prex;}//进行封装操作
    QString getMidx(){return midx;}
    bool getLegal(){return isLegal;}
    QSet<QChar> getVary(){return expr.getVary();}

};

#endif // CALCULATE_H
