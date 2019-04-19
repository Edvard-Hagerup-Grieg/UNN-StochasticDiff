#pragma once

#include <stdlib.h>
#include "nummeth.h"
#include "omp.h"
#include <time.h>

using namespace std;
void main(int argc, char* argv[])
{
	double time = 0.0;

	//Euler
	if (argv[1][0] == '0') 
		time = Euler(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), atof(argv[7]));
	//Heun
	else if (argv[1][0] == '1')
		time = Heun(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), atof(argv[7]));
	//Jump experiment
	else if (argv[1][0] == '2')
		time = Jump(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), atof(argv[7]));
	else
	{
		cout << "Invalid argument." << endl;
		cin.get();
	}
	cout << time;

	//time = Heun(1.5, 0.0, 1.0, 0.01, 1000, 1.0);
	//cin.get();
}