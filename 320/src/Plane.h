#ifndef PLANE_H_
#define PLANE_H_

#include "cTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

class Plane {
	pthread_mutex_t mutex;
	friend void * start_routine(void* arg);
	int ID, time, posX, posY, posZ, velX, velY, velZ;
	void *ptr;

public:
	pthread_t thread_id;
	void * threadTask(void * );
	Plane(int time, int ID, int posX, int posY, int posZ, int velX, int velY, int velZ);

	void setPlane(int time, int ID, int posX, int posY, int posZ, int velX, int velY, int velZ);
	void setCoordinates(int posX, int posY, int posZ);
	void setVelocity(int velX, int velY, int velZ);
	int getID() { return ID; }
	int getTime() { return time; }
	int getPosX() { return posX; }
	int getPosY() { return posY; }
	int getPosZ() { return posZ; }
	int getVelX() { return velX; }
	int getVelY() { return velY; }
	int getVelZ() { return velZ; }

	void updateLocation();
	void sendInfo();

	virtual ~Plane();
};

#endif /* PLANE_H_ */
