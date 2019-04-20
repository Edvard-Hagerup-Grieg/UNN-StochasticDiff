#pragma once

#include <stdlib.h>
#include "nummeth.h"
#include "omp.h"
#include <time.h>

using namespace std;
int main(int argc, char* argv[])
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
		time = Jump_vec(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), atof(argv[7]));
	else
	{
		cout << "Invalid argument." << endl;
		cin.get();
	}
	cout << time;

	//for (double d = 0.0; d < 8.1; d += 0.1)
	//{
	//	time = Jump_vec(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]), d);
	//	cout << d << "\t" << time << endl;
	//}
	//cin.get();

	return 0;
}