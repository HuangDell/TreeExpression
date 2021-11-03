#ifndef CALCULATE_H
#define CALCULATE_H
#include <QString>
#include "exptree.h"


class Calculate
{
private:
    ExpTree expr;
    QString prex;
    QString midx;
    bool isLegal;
    void calPrex(const QString& prex);


public:
    Calculate(const QString& prex);

    QString getPrex(){return prex;}
    QString getMidx(){return midx;}
    QSet<QChar> getVary(){return expr.getVary();}

};

#endif // CALCULATE_H
