#include "ComputerSystem.h"
#define COMPUTER_ATTACH_POINT "ComputerSystem"
#define DISPLAY_ATTACH_POINT "Display"

const uint64_t timeout = 5000000; //timeout value

//computer system thread start function
void* compsys_start_routine(void *arg){
	ComputerSystem& compsys = *(ComputerSystem*)arg;
	compsys.fromRadar();
	return NULL;
}

//messaging function to Display object
int ComputerSystem::toDisplay(all_planes planes){
	if ((server_coid = name_open(DISPLAY_ATTACH_POINT, 0)) == -1){
		return EXIT_FAILURE;
	}
	if (MsgSend(server_coid, &planes, sizeof(planes), 0, 0) == -1){
		return EXIT_FAILURE;
	}
	name_close(server_coid);
	return EXIT_SUCCESS;
}

// calculates the distance between two points on the x-y plane
int point_2_point_dist(int x1, int y1, int x2, int y2) {
	int d;
	d = sqrt( ((x2 - x1)^2) + (y1 - y2)^2 );
	return d;
}

// calculates the distance between two points in 3 dimensions
int point_3_point_dist(int x1, int y1, int x2, int y2, int z1, int z2) {
	int d;
	d = sqrt( ((x1 - x2)^2) + (y1 - y2)^2 + (z1-z2)^2);
	return d;
}

//calculates if there will be a collision in the next 3 minutes
void ComputerSystem::calcCollision() {
	std::vector<int>crashedPlane; //stores the IDs of planes that will crash
	bool jcrash = false; //plane crash flag
	bool scrash = false; //plane crash flag
	int xyResult = 0;
	bool xyCollision = false; //plane crash flag
	bool zCollision = false; //plane crash flag
	//n represents the interval at which the computer system dynamically
	//changes how often it updates based on the conjestion
	int n = (1/planes.size()*180);

	for (int i = 0; i < 180; i++) { //if n worked correctly, i would increment by i+=n instead of i++
		for(int j = 0; j < planes.size()-1; j++){//these loops check the current position of each plane against every other plane
			for(int s = 0; s < planes.size(); s++){
				bool xyCollision = false;
				bool zCollision = false;
				if (s == j){
					s++;
				}
				else{
					xyResult = point_2_point_dist(planes.at(j).posX, planes.at(j).posY, //determines XY distance
							   planes.at(s).posX, planes.at(s).posY);
				}

				if (xyResult <= 3000) {
					xyCollision = true;
				}
				if (point_3_point_dist(planes.at(j).posX, planes.at(j).posY, planes.at(j).posZ, planes.at(s).posX, planes.at(s).posY, planes.at(s).posZ) <= 1000) { //determines xyz distance
					zCollision = true;
				}
				if (xyCollision){ //collects plane ID that will crash
					for(int u : crashedPlane){
						if (u == planes.at(j).ID){
							jcrash = true;
						}
						if (u == planes.at(s).ID){
							scrash = true;
						}
					}
					if (!jcrash){
						crashedPlane.push_back(planes.at(j).ID);
					}
					if (!scrash){
						crashedPlane.push_back(planes.at(s).ID);
					}

				}
				if (zCollision){ //collects plane ID that will crash
					for(int u : crashedPlane){
						if (u == planes.at(j).ID){
							jcrash = true;
						}
						if (u == planes.at(s).ID){
							scrash = true;
						}
					}
					if (!jcrash){
						crashedPlane.push_back(planes.at(j).ID);
					}
					if (!scrash){
						crashedPlane.push_back(planes.at(s).ID);
					}
				}

			}
		}
		for(int h = 0; h < planes.size(); h++){ //updates the plane's position for the next second based on their current velocity
			planes.at(h).posX += planes.at(h).velX;
			planes.at(h).posY += planes.at(h).velY;
			planes.at(h).posZ += planes.at(h).velZ;
		}
	}
	if (crashedPlane.size() > 0){ //prints out to console the ALARM that says which planes will crash
		for(int k : crashedPlane){
			cout << "WARNING: Plane ID: " << k << " is going to crash in the next 3 minutes!" << "\n";
		}
	}

}
//messaging from radar
int ComputerSystem::fromRadar(){
	name_attach_t *attach;
	all_planes data;

	if((attach = name_attach(NULL, COMPUTER_ATTACH_POINT, 0)) == NULL){
		printf("ComputerSys failed to create channel\n\n");
		return EXIT_FAILURE;
	}

	while (1){
		rcvid = MsgReceive(attach->chid, &data, sizeof(data), NULL); // receive messages from radar
		if (rcvid == -1) {/* Error condition, exit */
			break;
		}

		if (rcvid == 0) {/* Pulse received */
		    switch (data.hdr.code) {
		    	case _PULSE_CODE_DISCONNECT:
		    		/*
		    		 * A client disconnected all its connections (called
		    		 * name_close() for each name_open() of our name) or
		    		 * terminated
		    		 */
		    		ConnectDetach(data.hdr.scoid);
		    		break;
		    	case _PULSE_CODE_UNBLOCK:
		             /*
		              * REPLY blocked client wants to unblock (was hit by
		              * a signal or timed out).  It's up to you if you
		              * reply now or later.
		              */
		    		break;
		    	default:
		             /*
		              * A pulse sent by one of your processes or a
		              * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
		              * from the kernel?
		              */
		    		break;
		    }
		    continue;
		}

		/* name_open() sends a connect message, must EOK this */
		if (data.hdr.type == _IO_CONNECT ) {
			MsgReply( rcvid, EOK, NULL, 0 );
		    continue;
		}

		/* Some other QNX IO message was received; reject it */
		if (data.hdr.type > _IO_BASE && data.hdr.type <= _IO_MAX ) {
			MsgError( rcvid, ENOSYS );
		    continue;
		}
		// check for appropriate header and copy the data to planes
		if (data.hdr.type == 0x01){
			planes = data.allPlanes;
		}
		MsgReply(rcvid, EOK, 0, 0);
		toDisplay(data);
		calcCollision();

	}
	name_detach(attach, 0);
	return EXIT_SUCCESS;
}

ComputerSystem::ComputerSystem() {
	if(pthread_create(&thread_id,NULL,compsys_start_routine,(void *) this)!=EOK){
		thread_id=NULL;
	}
}

ComputerSystem::~ComputerSystem() {

}
