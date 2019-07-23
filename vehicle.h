//#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H
#define hstep 0.01
#include <string>
#include <iostream>


class Vehicle {
	
	// friend allows other class to access private data members
//	friend std::ostream& operator<<(std::ostream& os, const Vehicle& c); 
	friend class Lane;
	friend class Car;
	friend class Truck;
	friend class Van;

private:
	//double mass;
	int overtake_want;
	int road_length;
	double reaction  = 0.25;
	double aggro;

	std::string type;
	double fr,power,pA,cD,aF,yM,nT,v,v_desired,xf,amax,bmax,v1,v2;
	double va,la,xfa,ba;
	double pos = 0;
	const double g = 9.81;
	int vehicle_length;
	Vehicle* next;
public:

	Vehicle(std::string type = "none");
	double fuel_con(double ,double, double);
	double post_Speed(char);
	void move(std::string );
	void init(double,double);
};

#endif
