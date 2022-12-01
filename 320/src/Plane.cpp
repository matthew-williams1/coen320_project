#include "Plane.h"
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include "Timer.h"

using namespace std;

void* plane_start_routine(void *arg)
{
	Plane& plane = *(Plane*) arg;
	plane.updateLocation();
	return NULL;
}

void Plane::updateLocation()
{
	cTimer timer(1,0);
//	Timer timer(1,1);
	while (posX <= 10 && posY <= 10 && posZ <= 10)
	{
//		timer.wait_next_execution();
		timer.waitTimer();
		printf("Plane ID: #%d, Updated Coordinates: %d, %d, %d\n\n", getID(), getPosX(), getPosY(), getPosZ());
		this->posX += velX;
		this->posY += velY;
		this->posZ += velZ;
		// send message to radar with all information

	}
	pthread_exit(NULL);
}

Plane::Plane(int time, int ID, int posX, int posY, int posZ, int velX, int velY, int velZ) {
	// TODO Auto-generated constructor stub
	setPlane(time, ID, posX, posY, posZ, velX, velY, velZ);
	if(pthread_create(&thread_id,NULL,plane_start_routine,(void *) this)!=EOK){
			thread_id=NULL;
		}
}

void Plane::setPlane(int time, int ID, int posX, int posY, int posZ, int velX, int velY, int velZ)
{
	this->time = time;
	this->ID = ID;
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->velX = velX;
	this->velY = velY;
	this->velZ = velZ;
}

void Plane::setCoordinates(int posX, int posY, int posZ)
{
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
}

void Plane::setVelocity(int velX, int velY, int velZ)
{
	this->velX = velX;
	this->velY = velY;
	this->velZ = velZ;
}

void Plane::sendInfo()
{
	// send data to radar
}

Plane::~Plane() {
	pthread_mutex_destroy( &mutex );
	thread_id = NULL;
}

