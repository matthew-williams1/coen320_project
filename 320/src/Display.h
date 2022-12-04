/*
 * Display.h
 *
 *  Created on: Dec. 3, 2022
 *      Author: coen320
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <iostream>
#include <pthread.h>
#include <vector>
#include <tuple>
#include "ComputerSystem.h"
#include "cTimer.h"



class Display {
public:
	void clear();
	pthread_t thread_id_disp;
	Display();
	friend void * display_start_routine(void* arg);
	//void *ptr;
	void push();
	void runDisplay();
	void receiveData();
	//std::tuple <int, int, int> plane; // tuple (ID, positionX, positionY)
	//std::vector< tuple<int, int, int> > planes;


	static std::vector<int> ID;
	static std::vector<int> posX;
	static std::vector<int> posY;
};


//virtual ~Display();



#endif /* DISPLAY_H_ */
