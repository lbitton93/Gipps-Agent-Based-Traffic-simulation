
#define _USE_MATH_DEFINES
#include "Lane.h"
#include <cmath>
using namespace std;

double Normal_dist(double mu, double sig);

Lane::Lane():head(0),size(0)
{
	
}

// Creates a vehicle pointer to the head, iterates across the list to 'index' and returns its position

/* The lane extract function passes a Vehcile pointer to the insert function.
   Upon passing tests, which are embedded in the fucntions, 1)
   does the vehcile wish to overtake?, 2) is there room
   to safely do so in the adjacent lane? the extract insert succeeds and
    linkage pointers between vehicles in the lanes are readdressed.
*/

Vehicle* Lane::extract(int index,char c)
{
    // create a pointer that stores in lane private to the extractee's following car,
	// if the car isnt extracted save pointer to its follower, so we dont have to iterate from head,
	// so we can search across all vehicles faster without repeating previous calcs

    // only run extract process if car wants to, and can overtake, include the minimum threshold for
	// the space so that if unfeasible no car overtakes
	Vehicle* cur;
	Vehicle* follow;
	Vehicle* ahead;


	cur = head;
	follow = cur;
	ahead = cur->next;

		for (int i = 0; i < index; i++)
		{
			if ( (follow != 0) && (ahead != 0) && (cur != 0) )
			{

				follow = cur;
				cur = cur->next;
				ahead = cur->next;
			}
			else
			{
				if ((follow != 0) && (cur != 0))
				{
					follow = cur;
					cur = cur->next;
				}
				else
				{
					if (cur != 0)
					{
						cur = cur->next;
					}
				}
			}
		}

			// if the extractee is in the middle of two vehicles
			if ((follow != 0) && (ahead != 0) && (cur != 0))
			{
				if (((cur->v_desired - ahead->v) > 0) && (ahead->pos - cur->pos))
				{
					follow->next = ahead;
					//iterator = follow;

				}
			}
			//if the extractee is in the lead


			
			return cur;
			delete cur;
		

}

void Lane::insert(Vehicle* vin)
{
// if a vehicle decides to move lane
	if (vin != 0)
	{
		Vehicle* cur = head;
		int count1 = 0;
		int count2 = 0;
		Vehicle* trail = 0;

		while (cur != 0)
		{
			count1++;
			cur = cur->next;
		}
		cur = head;
		while ((cur != 0) && (cur->pos < vin->pos))
		{
			printf("passed pos %f, check pos %f\n", vin->pos, cur->pos);
			trail = cur;
			cur = cur->next;
			count2++;
			// count 2 is the insert position for the extracted overtaking vehicle
		}

		printf("count2 %d, count1 %d\n", count2, count1);

		// insert in case where in middle not at head or tail 
		if ((count2 > 0) && (count1 != count2))
		{
			trail->next = vin;
			vin->next = cur;
		}
		else
		{
			// case 2 being the leader of the traffic line
			if ((count2 > 0) && (count1 == count2))
			{
				trail->next = vin;
				vin->next = 0;
			}

		}
	}
		
}

int Lane::count()
{
	Vehicle* tp = head;
	int count = 0;
	while(tp != 0)
	{
		tp = tp->next;
		count++;
	}
	printf("Cars on Lane %d\n",count);
	return (count);
}
double Lane::vehicleData(int index,std::string call)
{
	Vehicle* tp = head;
	double ret;

	for(int i=0;i<index;i++)
	{
		tp = tp->next;
	}

	if (call == "pos")
	{
	  ret =	(*tp).pos;
	}
	else
	{
		if (call == "len")
		{
			ret = double((*tp).vehicle_length);
		}
		else
		{
			if (call == "vel")
			{
				ret = (*tp).v;
			}
			else
			{
				printf("\n\n ERROR: invalid function call, Lane.vehicleData(int, string) accepts, 'len', 'vel' or 'pos' as function calls \n\n");
			}
		}
	}

	return ret;
}

double Lane::avg_visible_speed(int spd_limit)
{
	Vehicle* tp = head;
	double v_sum=0;
	double vret;
	int vis_range = 100;
	int count = 0;

	if (tp == 0)
	{
		vret = Normal_dist(spd_limit, 1);
	}
	while(tp != 0 && (((*tp).pos)<vis_range))
	{
			v_sum += tp->post_Speed('a');
			count++;
			tp = tp->next;
			vret = (v_sum / double(count));
	}


	printf("vset %f \n", vret);
	return 	vret;
}
void Lane::setVehSpeed(int speed)
{
	Vehicle* tp = head;

	while (tp != 0)
	{
//		cout << *tp << endl;
		(*tp).v = speed;
		tp = tp->next;

	}
}

void Lane::updateVehiclePos()
{
	Vehicle* tp = head;
	Vehicle* ahead;
	int count = 0;
	double dspeed=0;
	double want_index;

	while (tp != 0)

	{
		ahead = tp->next;
		if (tp == head)
		{
		//	printf("this is the head \n");
		}

		if(tp->next !=NULL)
		{
		(*tp).move("normal");              // move mode normal is the scheme for following cars
		(*tp).va = (*ahead).v;             // sets va to the speed of the vehicle in front
		(*tp).la = (*ahead).vehicle_length;             // sets la to the length of the vehcile in front
		(*tp).xfa = (*ahead).pos + 0.5*((*tp).vehicle_length);     // sets xfa to the pos the front of the vehicle in front
		(*tp).ba = (*ahead).bmax;


		// function to determine wether the car wishes to overtake or not
		// make function of distance, speed difference, space and aggression
		dspeed = (*tp).va - (*tp).v;
		want_index = dspeed+(*tp).aggro;
		printf("want index %f\n", want_index);
				
		if (Normal_dist(1,1)<want_index)
		{
			(*tp).overtake_want = 1;
			printf("wants to overtake %f\n");
		}
		else
		{
			(*tp).overtake_want = 0;
			printf("doesnt want to overtake %f\n");
		}

		}
		else
		{
			(*tp).v2 = 1000;               // sets the leading vehicles parameters so it reaches v desired
			(*tp).move("leading");         // sets the regime for the leading car
		}
		tp = tp->next;
		count++;

	}

}

void Lane::addToHead(const string& type, int slip_road_speed)
{

	Vehicle* tp = head;
	Vehicle* ahead;
	double pos;

	if (tp != head)
	{
		ahead = tp->next;
			
			(*tp).va = (*ahead).v;                                     // sets va to the speed of the vehicle in front
			(*tp).la = (*ahead).vehicle_length;                        // sets la to the length of the vehcile in front
			(*tp).xfa = (*ahead).pos + 0.5*((*tp).vehicle_length);     // sets xfa to the pos the front of the vehicle in front
			(*tp).ba = (*ahead).bmax;
			(*tp).move("normal");
	}
	pos = 0;

	if (type == "car")
	{   
			newOne = new Car();
			newOne->init(slip_road_speed, pos);
     		//printf("Car added to lane succesfully\n\n");
	}
	if (type == "truck")
	{
		newOne = new Truck();
		newOne->init(slip_road_speed,pos);
		//printf("Truck added to lane succesfully\n\n");
	}
	if (type == "van")
	{
		newOne = new Van();
		newOne->init(slip_road_speed,pos);
		//printf("Van added to lane succesfully\n\n");
	}


		if (head == 0)
		{
			head = newOne;
		}
		else
		{
			newOne->next = head;
			head = newOne;
		}

		size++;
		//printf("Vehicle added\n");

}
