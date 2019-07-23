//#pragma once
#ifndef CAR_H
#define CAR_H
#include "vehicle.h"

class Car: public Vehicle
{

private:
	double v = 0;
	double m = 1500;
	double a = 0;
public:
    Car();
};

#endif