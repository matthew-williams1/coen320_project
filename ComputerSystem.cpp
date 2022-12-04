/*
 * ComputerSystem.cpp
 *
 *  Created on: Dec. 2, 2022
 *      Author: coen320
 */

#include "ComputerSystem.h"
#include "math.h"
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

ComputerSystem::ComputerSystem() {
	// TODO Auto-generated constructor stub

}

int point_2_point_dist(int x1, int y1, int x2, int y2) {
int d;
d = sqrt( (x2 - x1)^2 + (y1 - y2)^2 );
return d;
}

void calcCollision() {
	int xyResult = 0;
	bool xyCollision = false;
	bool zCollision = false;
	ComputerSystem::planes;

	for (int i = 0; i < 180; i ++) {
		for(int j = 0; j < planes.size(); j++){
			for(int s = 0; s < planes.size(); s++){
				xyResult = point_2_point_dist(planes.at(j).posX, planes.at(j).posY,
								   ComputerSystem::planes.at(s).posX, ComputerSystem::planes.at(s).posY);
				if (xyResult <= 3000) {
					xyCollision = true;
				}
				if (abs(ComputerSystem::planes.at(j).posZ - ComputerSystem::planes.at(s).posZ)) {
					 zCollision = true;
				}
			}
		}
		for(int h = 0; h < ComputerSystem::planes.size(); h++){
			ComputerSystem::planes.at(h).posX += ComputerSystem::planes.at(h).velX;
			ComputerSystem::planes.at(h).posY += ComputerSystem::planes.at(h).velY;
			ComputerSystem::planes.at(h).posZ += ComputerSystem::planes.at(h).velZ;
		}
	}
}



ComputerSystem::~ComputerSystem() {
	// TODO Auto-generated destructor stub
}
