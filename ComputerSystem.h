#ifndef SRC_COMPUTERSYSTEM_H_
#define SRC_COMPUTERSYSTEM_H_

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dispatch.h>
#include <vector>
#include "Plane.h"
typedef struct plane_info {
	int ID, posX, posY, posZ, velX, velY, velZ;
} plane_info;

class ComputerSystem {
	pthread_mutex_t mutex;
	friend void * start_routine(void* arg); // thread start routine
	void *ptr;
	int rcvid;
public:
	std::vector<plane_info> planes;
	pthread_t thread_id;
	void * threadTask(void *);
	ComputerSystem();
	void fromRadar();
	void calcCollision();
	void toDisplay();
	virtual ~ComputerSystem();
};
