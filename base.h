#pragma once

#include<stdio.h>
#include <iostream>
#include<random>
#include<math.h>
#include<algorithm>
#include <vector>

using namespace std;

struct POS
{
	double x;
	double y;
	//POS(double x, double y) : x(x), y(y) {}
};



inline double fun(double x, double y)
{
	return 4 * pow(x, 6) - 2.1 * pow(x, 4) + pow(x, 6) / 3.0
		+ x * y - 4 * pow(y, 2) + 4 * pow(y, 4);
	//return 5 * cos(x * y) + x * y + y * y * y;
}