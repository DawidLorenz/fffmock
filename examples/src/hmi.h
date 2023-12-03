#ifndef __HMI_H__
#define __HMI_H_
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif


double HMI_NewtonSecondLawOfMontion(int m, int a);
double HMI_KineticEnergyEquation (int m, int v);

#ifdef __cplusplus
}
#endif

#endif /* __HMI_H_ */