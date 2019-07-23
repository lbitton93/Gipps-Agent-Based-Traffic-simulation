#include "Vehicle_pool.h"
#include <cmath>
#include <stdio.h>

using namespace std;

Vehicle_pool::Vehicle_pool()
{

}
void Vehicle_pool::populate(float c, float v, float t)
{
    /*
	Create distribution of cars, vans, trucks
	*/
}
Vehicle Vehicle_pool::inject()
{
	/*
	some code to create lanes according to 'n0_lanes' which are linked lists of of vehicles whos type
	is determined by a user defined distribution as an argument. This could be done by potentially
	populating a vehicle pool, and injecting them into the lanes according to an algorithm? The
	justification for this being that each vehicle needs to autonomy to choose a road based on
	it's traffic flow.
	*/
	Vehicle current_vehicle; // line to pick a vehicle out pool and pass it to road

	return current_vehicle;

}