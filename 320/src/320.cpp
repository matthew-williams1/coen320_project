#include <pthread.h>
#include <stdio.h>
#include "Plane.h"

int main (int argc, char* argv[]) {
	// implement a read from input file and create vector of Plane objects

	Plane plane1(1,1,1,1,1,1,1,1);
	Plane plane2(1,2,1,1,1,1,1,1);
	Plane plane3(1,3,1,1,2,1,1,1);

	pthread_join(plane1.thread_id,NULL);
	pthread_join(plane2.thread_id,NULL);
	pthread_join(plane3.thread_id,NULL);

	return EXIT_SUCCESS;
}
