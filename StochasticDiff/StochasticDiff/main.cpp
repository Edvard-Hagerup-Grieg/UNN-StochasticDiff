#pragma once

#include <stdlib.h>
#include "nummeth.h"

using namespace std;
void main(int argc, char* argv[])
{
	//Euler
	if (argv[1][0] == '0') 
		Euler(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atoi(argv[6]));
	//
	else if (argv[1][0] == '1')
		cout << "No code." << endl;
	else
	{
		cout << "Invalid argument." << endl;
		cin.get();
	}
}