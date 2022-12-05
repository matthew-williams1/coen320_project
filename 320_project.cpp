#include <pthread.h>
#include <stdio.h>
#include "Plane.h"
#include "Radar.h"
#include "ComputerSystem.h"
#include "Display.h"

int main (int argc, char* argv[]) {
	// implement read from input file and create vector of Plane objects

	Display display; //display object
	ComputerSystem compsys; //computer system object
	Radar radar; //radar object
	//plane objects
	Plane plane1(5,1,1,1,2000,800,800,0);
	Plane plane2(3,2,50000,1,1,1,800,1);
//	Plane plane3(1,3,1,1,2,1,1,1);

//threads for planes to enter simulation
	pthread_join(plane1.thread_id,NULL);
	pthread_join(plane2.thread_id,NULL);
//	pthread_join(plane3.thread_id,NULL);
//	pthread_join(radar.thread_id,NULL);

	return EXIT_SUCCESS;
}
///data/var/tmp
