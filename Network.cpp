#define _USE_MATH_DEFINES
#include "Network.h"

#include <cmath>

Engine *m_pEngine;

Network::Network() 
{
}

void Network::init()
{
	m_pEngine = engOpen("null");

	rd1 = new Road();

	count.resize(lanes);
	add.resize(lanes);
	inter.resize(lanes);
	carpos2d.resize(lanes, vector<double>(0, 0));

	//initialise the lane counter to zero for all lanes. this controls vechicular arrival in lanes
	for (l = 0; l < lanes; l++)
	{
		count[l] = 0;
		add[l] = 0;
	}

	rd1->init_Road();

	// iterate over time
}
void Network::update()
{
	{
		for (l = 0; l<lanes; l++)           // iterate over all lanes
		{
			if (count[l] == 0)
			{
				inter[l] = Normal_dist(0.2, 0.5) / hstep;
			}
			count[l]++;

			if (add[l] > 0)
			{
				//printf("first vechile in lane %d at ... %f\n", l, (*rd1).returnVehPos(l, 0));
				first[l] = (*rd1).vehicle_Data(l, 0,"pos");
			}

			int vehtype = 1;

			// if the selected inter arrival time has been reached...			
			if (count[l] > inter[l])
				// if the road is empty or if there is space at the road entrance ...
				if ((add[l] == 0) || ((add[l] > 0) && ((*rd1).vehicle_Data(l, 0, "pos") > (3/2)*(*rd1).vehicle_Data(l, 0, "len"))))
				{
					{
						rd1->add_vehicle(type[vehtype], l);
						count[l] = 0;
					}
				}
		}

		rd1->update_road();

		rd1->extract_insert(0, 2,0);
		printf("asfasafafs\n");
// ----------------------------------------------------------------------------------------------------
// This section deals with the arrays sent to the rendering function. add[l] holds the number of 
// vehicles on lane l. carpos 2d and carpos contain positional data for the vehicles.
// ----------------------------------------------------------------------------------------------------
		for (l = 0; l < lanes; l++)
		{
			add[l] = (*rd1).lane_count(l);

			for (int j = 0; j < add[l]; j++)
			{

				carpos2d[l].push_back(0);
				carpos.push_back(0);			
				carpos2d[l][j] = (*rd1).vehicle_Data(l, j, "pos");
				carpos[j] = (*rd1).vehicle_Data(l, j, "pos");	

			}
			printf("add %d = %d\n", l, add[l]);
		}

		// counts the total number of cars on the road
		int numberofcars = 0;
		for (l = 0; l < lanes; l++)
		{
			numberofcars += add[l];
		}

		// adds these cars from a 2d lane wise array to a 1d array for matlab to read
		int i2 = 0;
		l = 0;
		printf("number of vehicles %d\n", numberofcars);

	    draw_cars(carpos2d[0], carpos2d[1], m_pEngine, numberofcars, add);
	}

}

double Normal_dist(double mu, double sig)
{
	double P, u1, u2, ve;
	P = ((double)rand() / (RAND_MAX));   // create pseudo random doubles between 0-1
	u1 = ((double)rand() / (RAND_MAX));
	u2 = ((double)rand() / (RAND_MAX));

	if (u1 == 0 || u2 == 0)
	{
		ve = mu;
	}
	else
	{
		if (P > 0.5)
		{
			ve = mu + sig*(sqrt(-2 * log(u1)))*cos(2 * M_PI*u2);
		}
		else
		{
			ve = mu - sig*(sqrt(-2 * log(u1)))*sin(2 * M_PI*u2);
		}

	}
	return ve;
}


void draw_cars(vector<double> &veccy, vector<double> &veccy2, Engine *m_pEngine, int numonroad, vector<int> &add)
{
	int i;
	double a = 1;
	mxArray *lane_0 = mxCreateDoubleMatrix(add[0], 1, mxREAL);
	mxArray *lane_1 = mxCreateDoubleMatrix(add[1], 1, mxREAL);

	double *l0 = mxGetPr(lane_0);
	double *l1 = mxGetPr(lane_1);

	for (i = 0; i < add[0]; i++)
	{
		l0[i] = veccy[i];
	}
	for (i = 0; i < add[1]; i++)
	{
		l1[i] = veccy2[i];
	}

	engPutVariable(m_pEngine, "z0", lane_0);
	engPutVariable(m_pEngine, "z1", lane_1);
	engEvalString(m_pEngine, ",h=plot(z0,1,'.',z1,1.1,'.','markersize',4),axis([0 200 0 2]),drawnow ");
	//engClose(m_pEngine);
}
