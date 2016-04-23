/* Written By : Eric Tan
 *
 * Plot of the analytic solution for the 1D Ising model.
 * Compiles with : gcc
 * Flags : -g -Wall -lm
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 16

double f(double T)
{
  double E = - sinh(1.0 / T) * cosh(1.0 / T) * (pow(cosh(1.0 / T), N - 2)
             + pow(sinh(1.0 / T), N - 2)) / (pow(cosh(1.0 / T), N)
             + pow(sinh(1.0 / T), N));

  return E;
}

int main(void)
{
  FILE *ouf = fopen("plot.dat", "w");

  int i;
  double dT = 0.0001;

  for (i = 1; i < 80000; i++)
    fprintf(ouf, "%lf %lf\n", i * dT, f(i * dT));

  fclose(ouf);

  return 0;
}

