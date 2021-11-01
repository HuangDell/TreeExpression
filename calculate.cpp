#include "calculate.h"

Calculate::Calculate(const QString& prex)
{
    calPrex(prex);
}

void Calculate::calPrex(const QString& prex)
{
    isLegal=true;
    this->prex=prex;
    midx="TO BE WORK";
}
