#pragma once
#ifndef ROAD_H
#define ROAD_H

#include "vehicle.h"
#include "Lane.h"
#include <vector>

class Road{

private:

	int n0_lanes;
	int road_len;
	float prop_car = 0;
	float prop_truck = 0;
	float prop_van = 0;
	float vehicle_flux = 0;
	float flux;
	int spd_lim= 30;
	float sig = 1;
	std::vector<Lane> lane_array;  //creates vector of lanes
public:
	Road();
	void init_Road();
	int lane_count(int);
	void extract_insert(int, int,int);
	double vehicle_Data(int, int,std::string);
	//double print_road_data(int);
	void base_flow_inject(int);
	void update_road();
	void add_vehicle(std::string &type, int);
	int return_data(char);
};

#endif