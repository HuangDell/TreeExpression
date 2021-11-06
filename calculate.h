#ifndef CALCULATE_H
#define CALCULATE_H
#include <QString>
#include "Python.h"
#include <QVector>
#include <string>
#include <QMap>
#include "exptree.h"
#include <cstring>


class Calculate
{
private:
    ExpTree expr;
    QString prex;
    QString midx;
    bool isLegal;

public:
    Calculate(const QString &prex);

    Calculate mergeConst();
    QVector<char*> diff();
    int calExpression(const QMap<QString,int> &vals);

    QString getPrex(){return prex;}
    QString getMidx(){return midx;}
    bool getLegal(){return isLegal;}
    QSet<QChar> getVary(){return expr.getVary();}

};

#endif // CALCULATE_H
