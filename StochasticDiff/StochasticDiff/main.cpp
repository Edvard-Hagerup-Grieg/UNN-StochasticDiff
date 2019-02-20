#pragma once

#include <stdlib.h>
#include "nummeth.h"

using namespace std;
void main(int argc, char* argv[])
{
	double time = 0.0;

	//Euler
	if (argv[1][0] == '0') 
		time = Euler(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]));
	//Heun
	else if (argv[1][0] == '1')
		time = Heun(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]));
	else
	{
		cout << "Invalid argument." << endl;
		cin.get();
	}

	cout << time;
}