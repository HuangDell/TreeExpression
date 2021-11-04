#ifndef CALCULATE_H
#define CALCULATE_H
#include <QString>
#include <QMap>
#include "exptree.h"


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
    int calExpression(const QMap<QString,int> &vals);

    QString getPrex(){return prex;}
    QString getMidx(){return midx;}
    bool getLegal(){return isLegal;}
    QSet<QChar> getVary(){return expr.getVary();}

};

#endif // CALCULATE_H
