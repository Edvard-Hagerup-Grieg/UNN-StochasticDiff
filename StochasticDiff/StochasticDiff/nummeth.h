#pragma once

#include "omp.h"
#include <time.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


double function(double x, double t, double a)
{
	return a - sin(x);
}

double Euler(double a, double t0, double x0, double dt, int n)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;

	double t = t0;
	double *x = new double[n];
	double *xt = new double[n];

	x[0] = x0;

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\";
	path = path + "Euler_n" + to_string(n) + "_dt" + to_string(dt) + "_a" + to_string(a) + ".txt";

	ofstream outfile;
	outfile.open(path);

	start = omp_get_wtime();
	for (int i = 0; i < n; i++)
	{
		xt[i] = function(x[i], t, a);
		x[i + 1] = dt * xt[i] + x[i];

		t += dt;
	}
	finish = omp_get_wtime();

	for (int i = 0; i < n; i++)
		outfile << x[i] << " " << xt[i] << endl;


	outfile.close();
	return (finish - start);
}

double Heun(double a, double t0, double x0, double dt, int n)
{
	srand(static_cast<unsigned int>(time(0)));
	double start = 0, finish = 0;

	double t = t0, xeuler;
	double *x = new double[n];
	double *xt = new double[n];

	x[0] = x0;

	start = omp_get_wtime();
	for (int i = 0; i < n; i++)
	{
		xt[i] = function(x[i], t, a);
		xeuler = dt * xt[i] + x[i];
		x[i + 1] = dt * (xt[i] + function(xeuler, t + dt, a)) / 2. + x[i];

		t += dt;
	}
	finish = omp_get_wtime();

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\";
	path = path + "Heun_n" + to_string(n) + "_dt" + to_string(dt) + "_a" + to_string(a) + ".txt";

	ofstream outfile;
	outfile.open(path);

	for (int i = 0; i < n; i++)
		outfile << x[i] << " " << xt[i] << endl;

	outfile.close();
	return (finish - start);
}