#include "calculate.h"

Calculate::Calculate(const QString& prex):expr(prex),prex(prex),midx(expr.getMidx()){}

void Calculate::calPrex(const QString& prex)
{
    isLegal=true;
}
