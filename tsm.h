#pragma once

#include <iostream>
#include <cmath>
#include <string.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

#ifndef _TSP_
#define _TSP_

const int _INFI = 99999999;
const int MAX_VER = 23;

int Left_Shift(int Num_Ver);
void Run_DP(int graph[30][30], int Num_Ver, int Start_Idx);
void Find_MinCost(int graph[30][30], int Num_Ver, int Start_Idx, int& Min_Cost, int& Last_Ver);
string CPath(int graph[30][30], int Num_Ver, int Start_Idx, int Last_Ver);
string Traveling(int G[30][30], int n, char Start_Ver);
int pathlength(int G[30][30], int n, string Traveling);


#endif
