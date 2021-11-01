#ifndef CALCULATE_H
#define CALCULATE_H
#include <QString>


class Calculate
{
private:
    QString prex;
    QString midx;
    bool isLegal;
    void calPrex(const QString& prex);


public:
    Calculate(const QString& prex);

    QString getPrex(){return prex;}
    QString getMidx(){return midx;}

};

#endif // CALCULATE_H
