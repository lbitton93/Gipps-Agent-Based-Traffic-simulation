#pragma once
#ifndef LANE_H
#define LANE_H
#include "vehicle.h"
#include "Car.h"
#include "Van.h"
#include "Truck.h"

class Lane 
{

private:
	Vehicle* head;
	Vehicle* newOne;
	Vehicle* iterator = head;
	int itcounter = 0;
	int size;
public:

    Lane();
	void addToHead(const std::string&,int);
    double vehicleData(int, std::string);
	int count();
	void setVehSpeed(int);
	Vehicle* extract(int,char);
	void insert(Vehicle*);
	double avg_visible_speed(int);
    void updateVehiclePos();
};

#endif