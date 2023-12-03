#include "hmi.h"
#include "math.h"

double HMI_NewtonSecondLawOfMontion(int m, int a)
{
    double f = MATH_Multiplication(m, a);
    return f;
}

double HMI_KineticEnergyEquation (int m, int v)
{
    double _v = MATH_Multiplication(v, v);
    double _m = MATH_Division(m, 2);
    double E = MATH_Multiplication(_m, _v);
    return E;
}
