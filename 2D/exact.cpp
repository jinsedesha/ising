/* Written by : Eric Tan
 *
 * Code to exactly solve the 2D Ising model
 * Ran with a N x N lattice where N = 4.
 * runs in O(2^N^2).
 * Requires N x N loops
 */

#include <iostream>
#include <cmath>

#define J 1.0

int main(void)
{
  int S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, S16;
  double E, T;
  double Z     = 0;
  double E_avg = 0;

  cout << "Enter value for T : " << endl;
  cin  >> T;

  for (S1 = -1; S1 < 3; S1 += 2)
  {
    for (S2 = -1; S2 < 3; S2 += 2)
    {
      for (S3 = -1; S3 < 3; S3 += 2)
      {
        for (S4 = -1; S4 < 3; S4 += 2)
        {
          for (S5 = -1; S5 < 3; S5 += 2)
          {
            for (S6 = -1; S6 < 3; S6 += 2)
            {
              for (S6 = -1; S6 < 3; S6 += 2)
              {
                for (S7 = -1; S7 < 3; S7 += 2)
                {
                  for (S8 = -1; S8 < 3; S8 += 2)
                  { // At this point wanted to throw computer through window.
                    for (S9 = -1; S9 < 3; S9 += 2)
                    {
                      for (S10 = -1; S10 < 3; S10 += 2)
                      {
                        for (S11 = -1; S11 < 3; S11 += 2)
                        {
                          for (S12 = -1; S12 < 3; S12 += 2)
                          {
                            for (S13 = -1; S13 < 3; S13 += 2)
                            {
                              for (S14 = -1; S14 < 3; S14 += 2)
                              {
                                for (S15 = -1; S15 < 3; S15 += 2)
                                {
                                  for (S16 = -1; S16 < 3; S16 += 2)
                                  {
                                    E = J * (S1*S2   + S1*S5   + S2*S3   +
                                             S2*S6   + S3*S4   + S3*S7   +
                                             S4*S8   + S5*S6   + S5*S9   +
                                             S6*S7   + S6*S10  + S7*S8   +
                                             S7*S11  + S8*S12  + S9*S10  +
                                             S9*S13  + S10*S11 + S10*S14 +
                                             S11*S12 + S11*S15 + S12*S16 +
                                             S13*S14 + S14*S15 + S15*S16);
                                    Z += exp(-E / T);
                                    E_avg += E * exp(-E / T);
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  cout << "E_avg = " << E_avg << endl;

  return 0;
}
