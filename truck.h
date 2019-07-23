#pragma once
#ifndef TRUCK_H
#define TRUCK_H
#include "vehicle.h"

class Truck : public Vehicle
{

private:
	double v = 0;
	double m = 10000;
	double a = 0;
public:
	Truck();
};

#endif
