#ifndef SRC_COMPUTERSYSTEM_H_
#define SRC_COMPUTERSYSTEM_H_

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <vector>
#include <math.h>
#include "Plane.h"
#include "Structures.h"

class ComputerSystem {
	pthread_mutex_t mutex;
	friend void * start_routine(void* arg); // thread start routine
	void *ptr;
	int rcvid;
	int server_coid;
public:
	pthread_t thread_id;
	// remove this vector
	std::vector<plane_info> planes;
	void * threadTask(void * );
	ComputerSystem();
	int fromRadar();
	void calcCollision();
	int toDisplay(all_planes);
	virtual ~ComputerSystem();
};

#endif /* SRC_COMPUTERSYSTEM_H_ */
