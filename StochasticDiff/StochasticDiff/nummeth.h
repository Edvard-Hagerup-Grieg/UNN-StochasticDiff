#pragma once

#include "omp.h"
#include <time.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>

#include "mkl_vsl.h"

#define ITER 1000
#define PI 3.1415
#define SEED 0
#define METHOD  0
#define BRNG VSL_BRNG_MT2203

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

using namespace std;


float gasdev(long *idum)
{
	float ran2(long *idum);
	static int iset = 0;
	static float gset;
	float fac, rsq, v1, v2;

	if (iset == 0) {
		do {
			v1 = 2.0*ran2(idum) - 1.0;
			v2 = 2.0*ran2(idum) - 1.0;
			rsq = v1 * v1 + v2 * v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac = sqrt(-2.0*log(rsq) / rsq);
		gset = v1 * fac;
		iset = 1;
		return v2 * fac;
	}
	else {
		iset = 0;
		return gset;
	}
}

float ran2(long *idum)
{
	int j;
	long k;
	static long idum2 = 123456789;
	static long iy = 0;
	static long iv[NTAB];
	float temp;

	if (*idum <= 0) {
		if (-(*idum) < 1) *idum = 1;
		else *idum = -(*idum);
		idum2 = (*idum);
		for (j = NTAB + 7; j >= 0; j--) {
			k = (*idum) / IQ1;
			*idum = IA1 * (*idum - k * IQ1) - k * IR1;
			if (*idum < 0) *idum += IM1;
			if (j < NTAB) iv[j] = *idum;
		}
		iy = iv[0];
	}
	k = (*idum) / IQ1;
	*idum = IA1 * (*idum - k * IQ1) - k * IR1;
	if (*idum < 0) *idum += IM1;
	k = idum2 / IQ2;
	idum2 = IA2 * (idum2 - k * IQ2) - k * IR2;
	if (idum2 < 0) idum2 += IM2;
	j = iy / NDIV;
	iy = iv[j] - idum2;
	iv[j] = *idum;
	if (iy < 1) iy += IMM1;
	if ((temp = AM * iy) > RNMX) return RNMX;
	else return temp;
}


double Euler(double a, double t0, double x0, double dt, int n, double D)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;

	long seed = (long)time(NULL);
	double noise;

	double t = t0, sqD = sqrt(D), sqdt = sqrt(dt);
	double *x = new double[n];
	double *xt = new double[n];

	x[0] = x0;

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\";
	path = path + "Euler_n" + to_string(n) + "_dt" + to_string(dt) + "_a" + to_string(a) + "_D" + to_string(D) + ".txt";

	ofstream outfile;
	outfile.open(path);

	start = omp_get_wtime();
	for (int i = 0; i < n; i++)
	{
		noise = gasdev(&seed);

		xt[i] = a - sin(x[i]) + sqD * noise;
		x[i + 1] = dt * xt[i] + x[i] + sqD * sqdt * noise;

		t += dt;
	}
	finish = omp_get_wtime();

	for (int i = 0; i < n; i++)
		outfile << x[i] << " " << xt[i] << endl;


	outfile.close();
	return (finish - start);
}

double Heun(double a, double t0, double x0, double dt, int n, double D)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;

	long seed = (long)time(NULL);
	double noise;

	double t = t0, sqD = sqrt(D), sqdt = sqrt(dt), xeuler;
	double *x = new double[n];
	double *xt = new double[n];

	x[0] = x0;

	start = omp_get_wtime();
	for (int i = 0; i < n; i++)
	{
		noise = gasdev(&seed);

		xt[i] = a - sin(x[i]) + sqD * noise;
		xeuler = dt * xt[i] + x[i] + sqD * sqdt * noise;
		x[i + 1] = dt * (xt[i] + a - sin(xeuler)) / 2. + x[i] + sqD * sqdt * noise;

		t += dt;
	}
	finish = omp_get_wtime();

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\";
	path = path + "Heun_n" + to_string(n) + "_dt" + to_string(dt) + "_a" + to_string(a) + "_D" + to_string(D) + ".txt";

	ofstream outfile;
	outfile.open(path);

	for (int i = 0; i < n; i++)
		outfile << x[i] << " " << xt[i] << endl;

	outfile.close();
	return (finish - start);
}

double Jump(double a, double t0, double x0, double dt, int n, double D)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;

	double t = t0, sqD = sqrt(D), sqdt = sqrt(dt);
	double x, dx, xeuler;

	long seed = (long)time(NULL);
	double noise;

	double *jump = new double[n];

	for (int i = 0; i < n; i++)
		jump[i] = 0;

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\";
	path = path + "Jump_n" + to_string(n) + "_dt" + to_string(dt) + "_a" + to_string(a) + "_D" + to_string(D) + ".txt";

	ofstream outfile;
	outfile.open(path);

	start = omp_get_wtime();
	for (int iter = 0; iter < ITER; iter++)
	{
		x = x0;
		for (int i = 0; i < n; i++)
		{
			noise = gasdev(&seed);
			dx = a - sin(x) + sqD * noise;

			xeuler = x + dt*dx + sqD * sqdt * noise;
			x = x + dt * (dx + a - sin(xeuler)) / 2. + sqD * sqdt * noise;

			if ((x < PI) && (x > -PI))
				jump[i]++;

			t += dt;
		}
	}
	finish = omp_get_wtime();

	for (int i = 0; i < n; i++)
		outfile << jump[i] / ITER << endl;
	outfile.close();

	return (finish - start);
}

double Jump_vec(double a, double t0, double x0, double dt, int n, double D)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;

	double t = t0, sqD = sqrt(D), sqdt = sqrt(dt);
	double x, dx, xeuler;

	float *noise = new float[n];
	float xmean = 0.0;
	float sigma = 1.0;
	int errcode;

	double *jump = new double[n];
	for (int i = 0; i < n; i++)
		jump[i] = 0;

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\";
	path = path + "Jump_n" + to_string(n) + "_dt" + to_string(dt) + "_a" + to_string(a) + "_D" + to_string(D) + ".txt";

	ofstream outfile;
	outfile.open(path);

	unsigned int  NT = 4;
	omp_set_dynamic(0);
	omp_set_num_threads(NT); 
	VSLStreamStatePtr stream[8];

	start = omp_get_wtime();
#pragma omp parallel 
	{
		for (int m = 0; m <= (2 * NT - 1); m++)
			vslNewStream(&stream[m], VSL_BRNG_MT2203 + m, SEED);

		unsigned int CT;
		CT = omp_get_thread_num();

#pragma omp for
		for (int iter = 0; iter < ITER; iter++)
		{
#pragma omp critical
			{
				errcode = vsRngGaussian(METHOD, stream[CT], n, noise, xmean, sigma);
			}

			x = x0;
			for (int i = 0; i < n; i++)
			{
				dx = a - sin(x) + sqD * noise[i];

				xeuler = x + dt * dx + sqD * sqdt * noise[i];
				x = x + dt * (dx + a - sin(xeuler)) / 2. + sqD * sqdt * noise[i];

				if ((x < PI) && (x > -PI))
					jump[i]++;

				t += dt;
			}
		}
	}
	finish = omp_get_wtime();

	for (int i = 0; i < n; i++)
		outfile << jump[i] / ITER << endl;
	outfile.close();

	return (finish - start);
}


#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX