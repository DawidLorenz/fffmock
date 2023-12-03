#include "main.h"
#include "hmi.h"
#include "math.h"

#ifdef UNIT_TEST
int mainProductionCode(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    return printAll();
}

int printAll()
{
    printf("2 + 3 = %f\n", MATH_Add(2, 3));
    printf("4 + 3 = %f\n", MATH_Add(4, 3));
    printf("5 * 5 = %f\n", MATH_Multiplication(5, 5));
    printf("2 / 4 = %f\n", MATH_Division(2, 4));
    printf("2 / 42 = %f\n", MATH_Division(2, 42));
    printf("1 / 2 = %f\n", MATH_Division(1, 2));
    printf("Newton Second Law Of Montion for m = 2 and a = 6 is: %f\n", HMI_NewtonSecondLawOfMontion(2, 6));
    printf("Kinetic Energy Equation for m = 4 and v = 10 is: %f\n", HMI_KineticEnergyEquation(4, 10));

    return 0;
}