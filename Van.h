#pragma once
#ifndef VAN_H
#define VAN_H
#include "vehicle.h"

class Van : public Vehicle
{

private:
	double v = 0;
	double m = 3000;
	double a = 0;
public:
	Van();
};

#endif