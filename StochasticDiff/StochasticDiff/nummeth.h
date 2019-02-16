#pragma once

#include <math.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


double function(double x, double t, double a)
{
	return a - sin(x);
}

void Euler(double a, double t0, double x0, double dt, int n)
{
	double t = t0, xt;
	double x = x0, xnext;

	string path = "C:\\Users\\Franz\\Desktop\\GitHub\\UNN-StochasticDiff\\results\\";
	path = path + "Euler_n" + to_string(n) + "_dt" + to_string(dt) + "_a" + to_string(a) + ".txt";

	ofstream outfile;
	outfile.open(path);

	for (int i = 0; i < n; i++)
	{
		xt = function(x, t, a);
		xnext = dt * function(x, t, a) + x;

		x = xnext;
		t += dt;

		outfile << x << " " << xt << endl;
	}

	outfile.close();
}