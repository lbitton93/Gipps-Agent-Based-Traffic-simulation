#define _USE_MATH_DEFINES

#include "Road.h"
#include <cmath>
#include <stdio.h>

double Normal_dist(double mu, double sig);

Road::Road()
{
}


// write overtake check method
void Road::init_Road()
{
	printf("Road initialisation begun... \n\n\n\n");


/*
	// read in parameters
	printf("Enter number of lanes: ");
	scanf_s("%d", &n0_lanes);
	lane_array.resize(n0_lanes);

	printf("Enter speed limit: ");
	scanf_s("%d", &spd_lim);

	printf("Enter road road_length: ");
	scanf_s("%d", &road_len);
	printf("\n\n");

	printf("Enter initial vehicle distribution of unity sum (Car, Truck, Van) \n\n");

	while ((prop_car + prop_van + prop_truck) != 1)
	{
		printf("Proportion of type car: ");
		scanf_s("%f", &prop_car);
		printf("\n\n");

		printf("Proportion of type truck: ");
		scanf_s("%f", &prop_truck);
		printf("\n\n");

		printf("Proportion of type van: ");
		scanf_s("%f", &prop_van);
		printf("\n\n");

		if ((prop_car + prop_van + prop_truck) != 1)
		{
			printf("Vehicle proportions do not sum to 1, please re-enter\n\n");
		}

	}

	printf("Enter the baseline vehicle flux, i.e the amount of vehicles passing across a perpendicular line to the road per second: ");
	scanf_s("%d", &vehicle_flux);
	printf("\n\n");
*/
	prop_car = 0.7;
	prop_truck = 0.2;
	prop_van = 0.1;
	n0_lanes = 2;
	spd_lim = 30;
	road_len = 2000;
	lane_array.resize(n0_lanes);
	vehicle_flux = 1.2;
// section to add vehicles to lanes 
}
int Road::lane_count(int lane)
{
	return lane_array[lane].count();
}
void Road::extract_insert(int elane, int eindex, int ilane)
{	
	// This function extracts a vehicle from inner lanes and passes to the outer lanes i.e only overtaking allowed
	int i=1;
    while (i<lane_array[0].count())
	{
		lane_array[1].insert(lane_array[0].extract(i,'+'));
		i++;
	}

}

// This function adds a vehicle to a specific lane
void Road::add_vehicle(std::string &type, int lane_index)
{
	//printf("first vehicle pos %f\n",lane_array[lane_index].printVehiclePos());
	int spd;
	spd=lane_array[lane_index].avg_visible_speed(spd_lim);
	lane_array[lane_index].addToHead(type,spd);
} 

// ------------------------------------------------------------------------
// This function accounts for a baseline flow of vehicles through the road.
// It is useful for roads such as motorways, that do not begin at the entry
// point aka junction that we are dealing with. The rate of flow of these
// vehicles, along with the distribution of types... is determined in the 
// road_init() class.
// ------------------------------------------------------------------------

void Road::base_flow_inject(int steps)
{
	double P,inter_t;
	int PL;

    // approximate function to determine the inter arrival time distribution.
	inter_t = hstep/ Normal_dist(1.2, 0.5);

	int count = 0;

	while (count <int(round(flux)))
	{
		P = ((double)rand() / (RAND_MAX));   // create pseudo random doubles between 0-1

		if (P < prop_car)   // add car to a randomly chosen lane according to its probability
		{
			PL = rand() % n0_lanes;
		    printf("Car passed to lane %d\n", PL + 1);
			lane_array[PL].addToHead("car",spd_lim);
		}
		else
		{
			P = ((double)rand() / (RAND_MAX));

			if (P < (prop_truck - prop_van)/prop_truck)   // else add a truck to lane
			{
				PL = rand() % n0_lanes;
				printf("Truck passed to lane %d\n", PL + 1);
				lane_array[PL].addToHead("truck", spd_lim);
			}
			else
			{
				PL = rand() % n0_lanes;     // else add a van 
				printf("Van passed to lane %d\n", PL + 1);
				lane_array[PL].addToHead("van", spd_lim);
			}
		}
		count++;
	}
}


double Road::vehicle_Data(int lane,int index,std::string call)
{
	return lane_array[lane].vehicleData(index,call);
}

void Road::update_road()
{
	for (int i = 0; i < n0_lanes; i++)                 // loop over lanes
	{
		//lane_array[i].extract(3);		
		lane_array[i].updateVehiclePos();
	}

}
// Allows readout of road data 

int Road::return_data(char info)
{
	int a;
	if ( info == 's') 
	{
	a = spd_lim;
	}

	if (info == 'n')
	{
		a = n0_lanes;
	}

	if (info == 'l')
	{
		a = road_len;
	}
	return a;
}

