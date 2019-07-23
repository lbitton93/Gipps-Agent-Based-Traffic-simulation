
#define _USE_MATH_DEFINES

#include "Vehicle.h"
#include <cmath>
#include <stdio.h>
#include "Car.h"
#include "Road.h"
#include "Network.h"


using namespace std;
double Normal_dist(double mu, double sig);

Vehicle::Vehicle(string n):type(n),next(NULL)
{

	double spd_limit = double(Road().return_data('s'));

	if (type == "car")
	{
		Car v1;
	}
	else
	{
		if (type == "truck")
		{
			Truck v1;
		}
		else
			if (type == "van")
			{
				Van v1;

			}
	}
	v_desired = Normal_dist(spd_limit, 6.0);

}
void Vehicle::init(double muint,double posit)
{   

	v = Normal_dist(muint, (muint/10));
	printf("Initial speed = %f\n", v);
	pos = posit;
	xf = pos + 0.5*vehicle_length;

	aggro=Normal_dist(0.5,0.3);
	v1 = v + 2.5*amax*reaction*(1 - (v / v_desired))*(sqrt(0.025 + (v / v_desired)));
	v2 = bmax*reaction + sqrt(bmax*bmax*reaction*reaction - bmax*( 2 * (xfa - 1.3*la - xf) - v*reaction - va*va / ba) );

	if (v1 > v2)
	{
		v = v2;
	}
	else
	{
		v = v1;
	}
	pos = pos + v*hstep;
	printf("Desired speed = %f\n", v_desired);
}

double Vehicle::fuel_con(double v,double a,double m)
{
	fr = 0.0136 + 0.0000004*v*v;
	power= (  (m*g*v*fr/3.6)  +  0.5*pA*cD*aF*(v*v*v/3.6)*(v*v*v / 3.6)*(v*v*v / 3.6) + m*yM*a )/nT ;
	printf("%f\n",power);
	return 0;
}

double Vehicle::post_Speed(char info) 
{
	int ret;
	if (info == 'a')
	{
		ret = v;
	}

	if (info == 'd')
	{
		ret = v_desired;
	}
	printf(" THHHHHHHHHHHHHHAAAA  ssssp = %f\n", v);
	return ret;
}

void Vehicle::move(std::string mode)
{
	if (mode == "normal")
	{
		pos = pos + v*hstep;
		xf = pos + 0.5*vehicle_length;
		//printf("amax = %f\n", amax);
		//printf("Vehicle ahead speed = %f\n", va);
		//printf("length = %d\n", vehicle_length);
		//printf("pos = %f\n", pos);
		v1 = v + 2.5*amax*reaction*(1 - (v / v_desired))*(sqrt(0.025 + (v / v_desired)));
		//printf("v1 = %f\n", v1);
		//printf("v = %f\n", v);
		v2 = bmax*reaction + sqrt(bmax*bmax*reaction*reaction - bmax*(2 * (xfa - 1.3*la - xf) - v*reaction - va*va / ba));

		if (v1 > v2)
		{
			v = v2;
		}
		else
		{
			v = v1;
		}
		//printf("v2 = %f\n\n\n", v2);
	}
	else 
	{
		if (mode == "leading")
		{
			pos = pos + v*hstep;
		//	printf("amax = %f\n", amax);
		//	printf("Vehicle ahead speed = %f\n", va);
		//	printf("length = %d\n", vehicle_length);
		//	printf("pos = %f\n", pos);
			v = v + 2.5*amax*reaction*(1 - (v / v_desired))*(sqrt(0.025 + (v / v_desired)));
		//	printf("v1 = %f\n", v1);
		//	printf("v = %f\n\n\n", v);
		}
		else
		{
			printf(" ERROR : Incorrect driving mode string passed to move command within the vehicle class:");
		}
	}
//	printf("new position = %f\n",pos);
}

