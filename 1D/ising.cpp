/* Written By : Eric Tan
 *
 * Monte Carlo simulation for the 1D Ising model
 * Outputs data points with error bars
 *
 * Compiles with g++
 * Flags : -g -Wall -ansi -std=gnu++11
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>

#define SWEEP 10000 // Number of sweeps through lattice
#define SQUARE(X) (X * X)

using namespace std;

/* Set RNG with time seed */
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 engine(seed);
uniform_real_distribution<double> distribution(0.0, 1.0);

/* Forward Declarations */
void set_spin(int *S, const int N);
void sweep(int *S, const int N, const double B, ofstream &ouf);
int get_pos(const int N);
double measure_E(int *S, const int N);
void write_data(double *E, const int N_points, const double T, ofstream &ouf);

/* Function to randomly set spins in lattice
 */
void set_spin(int *S, const int N)
{
  double r;

  for (int i = 0; i < N; i++)
  {
    r = distribution(engine);

    if (r < 0.5)
      S[i] = 1;
    else
      S[i] = -1;
  } // Set the Spin array

  return;
}

/* Function to perform the Metropolis algorithm
 * Perform N sweeps through the lattice
 * Measure at every N-th iteration
 */
void sweep(int *S, const int N, const double B, ofstream &ouf)
{
  int x, x_neg, x_pos;
  int count = 0;
  double dE, r;
  double E[SWEEP];

  for (int i = 0; i < N * SWEEP; i++)
  {
    r     = distribution(engine);
    x     = get_pos(N);
    x_neg = (x + 1 + N) % N;
    x_pos = (x + 1) % N;

    // Calculate dE with perodic boundries
    dE = 2 * S[x] * (S[x_neg] + S[x_pos]);

    if (r < exp(-B * dE))
      S[x] = -S[x];

    if ((i % N) == 0)
    {
      E[count] = measure_E(S, N);
      count++;
    } // Measure the energy after N sweeps
  } // Perform the Metropolis algorithm

  write_data(E, count, 1.0 / B, ouf);

  return;
}

/* Helper function to generate position for flipping
 */
int get_pos(const int N)
{
  double r = distribution(engine);

  return (int) (r * N);
}

/* Helper function to measure <E> / N
 */
double measure_E(int *S, const int N)
{
  double E = 0;

  for (int i = 0; i < N; i++)
  {
    if (i == (N - 1))
      E += S[N - 1] * S[0];
    else
      E += S[N] * S[N + 1];
  } // Looper to measure the energy

  return -E; // Energy is negative overall
}


/* Outputs data generate
 */
void write_data(double *E, const int N_points, const double T, ofstream &ouf)
{
  double avg  = 0;     // <E>
  double avg2 = 0;     // <E^2>
  double sd   = 0;     // Standard Deviation
  double upper, lower; // Error bars

  for (int i = 0; i < N_points; i++)
  {
    avg  += E[i];
    avg2 += SQUARE(E[i]);
  } // Calcualte <E> and <E^2>

  avg   = avg  / (double) N_points;
  avg2  = avg2 / (double) N_points;
  sd    = sqrt((avg2 - SQUARE(avg)) / (N_points - 1));
  upper = avg + sd;
  lower = avg - sd;

  ouf << setw(10) << left << T << " " << setw(10) << avg << " "
      << setw(10) << lower << " " << upper << endl;

  return;
}


int main(void)
{
  ofstream ouf("data.dat");
  int N      = 16;
  int N_data = 8;
  int *S;
  double B;
  double T[8] = {0.1, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 6.0};

  ouf << "#Temp     Data Point  Lower Bar   Upper Bar" << endl;

  for (int i = 0; i < N_data; i++)
  {
    B = 1.0 / T[i];
    S = new int[N];

    set_spin(S, N);
    sweep(S, N, B, ouf);

    delete[] S;
  } // Perform simulation over the points

  return 0;
}
