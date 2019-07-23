#pragma once
//#pragma once
#ifndef VEHICLE_POOL_H
#define VEHICLE_POOL_H

#include "vehicle.h"

class Vehicle_pool {

private:

public:
	Vehicle_pool();
	Vehicle inject();
	void populate(float, float, float);
};

#endif