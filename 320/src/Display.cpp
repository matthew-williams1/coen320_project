/*
 * Display.cpp
 *
 *  Created on: Dec. 3, 2022
 *      Author: coen320
 */
#include "Display.h"
#include <pthread.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

void * display_start_routine(void* arg) {
	Display& display = *(Display*) arg;
	display.runDisplay();
	return NULL;
}

std::vector<int> Display::posX;
std::vector<int> Display::posY;
std::vector<int> Display::ID;

Display::Display(){
	if(pthread_create(&thread_id_disp,NULL,display_start_routine,(void *) this)!=EOK)
	{
		thread_id_disp=NULL;
	}
}

void Display::clear() {
	system("CLS");
}

void Display::push() {
	Display::ID.push_back(000);
	Display::posY.push_back(25000);
	Display::posX.push_back(25000);

	Display::ID.push_back(100);
	Display::posY.push_back(5000);
	Display::posX.push_back(5000);

	Display::ID.push_back(200);
	Display::posY.push_back(90000);
	Display::posX.push_back(90000);

}

void Display::runDisplay() {
	//cTimer timer(0,5);

	//while(1){
	//	timer.waitTimer();
		//system("CLS"); //clear the display

		for(int i = 0; i <51; i++){
			for (int j = 0; j < 102; j++){

				if (i == 0) {
					std::cout << "-";
				}
				else if (j == 0) {
					std::cout << "|";
				}
				else if (i == 50) {
					std::cout << "-";
				}
				else if (j == 101) {
					std::cout << "|";
				}

				else if (Display::ID.size() != 0){
					bool isprinted = false;
					for(unsigned int n = 0; n < Display::ID.size(); n++){
						if(i == ((Display::posX.at(n)/2000)+1) && (j == ((Display::posY.at(n)/1000)+1))) {

							std::cout << "P" << n;
							isprinted = true;
						}
					}

					if (!isprinted) {
						std::cout << " ";
					}

				}

				}

			std::cout << "\n";
				}


		for(unsigned int s = 0; s < Display::ID.size(); s++) {
			std::cout << "P" << s << ": " << "\n";
			std::cout << "ID: " << Display::ID.at(s) << "\n";
			std::cout << "Position X: " << Display::posX.at(s) << "\n";
			std::cout << "Position Y: " << Display::posY.at(s) << "\n" << "\n";
		}
}

//WIP client code
void receiveData()
{
	cTimer timer(time+1,5);
	while (1)
	{
		timer.waitTimer();

		// wait for radar ping
		msg msg;
		rmsg rmsg;
		rmsg = {};
		char buffer[10];

		name_attach_t *attach;
		if((attach = name_attach(NULL, itoa(ID,buffer,10), 0)) == NULL){
			printf("Failed to create channel\n\n");
		}
		rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
		if (msg.hdr.type == 0x00){
			MsgReply(rcvid, EOK, &rmsg, sizeof(rmsg));
		}
		name_detach(attach, 0);
	}

	pthread_exit(NULL);
}
