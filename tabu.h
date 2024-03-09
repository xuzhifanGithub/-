#pragma once
#include"base.h"//½û¼ÉËÑË÷

void TABU();
double getNeighborValue(POS point, int index);
POS getBestNeighbor(POS current, vector<POS> tabuList);

POS getBestNeighborValue(double& candidate);