#pragma once
#include"base.h"//ÒÅ´«Ëã·¨


void GA();
void DNA2to10(int n);
double DNA10(int DNA[], int choice = 0);
int flag_limit_area(int limit_area[], int i);
void get_fitness(); 
void crossover_and_variation();
void select();
void copy();
int DNA2to10_vaild(int DNA[]);