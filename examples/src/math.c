#include "math.h"

double MATH_Add(int a, int b)
{
    return a + b;
}

double MATH_Multiplication(int a, int b)
{
    return a * b;
}

double MATH_Division(int a, int b)
{
    if (b == 0)
        return 0;

    return a / b;
}
