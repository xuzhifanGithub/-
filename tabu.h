#pragma once
#include"base.h"//��������

void TABU();
double getNeighborValue(POS point, int index);
POS getBestNeighbor(POS current, vector<POS> tabuList);

POS getBestNeighborValue(double& candidate);