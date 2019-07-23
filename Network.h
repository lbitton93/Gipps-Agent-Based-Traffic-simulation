#pragma once
#ifndef NETWORK_H
#define NETWORK_H

#include <Engine.h>                                     // Matlab engine
#include <iostream>
#include <string>
#include <cmath>

#include "Road.h"
#include <vector>

#pragma comment (lib, "libmat.lib")                     // Matlab libraries
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libeng.lib")

using namespace std;

double Normal_dist(double mu, double sig);              // Normal distribution function

void draw_cars(vector<double> &veccy, vector<double> &veccy2, Engine *m_pEngine, int numonroad, vector<int> &add);

class Network {

private:

	vector<double> inter;
	int lanes = 2;
	int l;
	vector<int> add;
	vector<int> count;
	vector<double> first = { 0,0 };
	vector<double> carpos;
	vector<vector<double>> carpos2d;
	Road* rd1;
	vector<std::string> type = { "car","truck","van" };
public:

	Network();
	void update();
	void init();

};
#endif