#define _USE_MATH_DEFINES

#include <cstdio>
#include <Network.h>                                  // Network contains subclasses for roads lanes and vehicles
using namespace std;

int main()
{
	Network N1;                                       // Create network object N1

	N1.init();                                        // Initialise

	for (int t = 0; t < 5000; t++)                    // Iterate
	{
		N1.update();                                  // Update network
	}

	system("pause");

}

