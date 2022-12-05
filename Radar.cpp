#include "Radar.h"
#include "Plane.h"

#define COMPUTER_ATTACH_POINT "ComputerSystem"

using namespace std;

class Plane;

// send all plane info to CompSys
int Radar::toComputerSys(all_planes data){
	if ((server_coid = name_open(COMPUTER_ATTACH_POINT, 0)) == -1){
		return EXIT_FAILURE;
	}
	if (MsgSend(server_coid, &data, sizeof(data), 0, 0) == -1){
		return EXIT_FAILURE;
	}
	name_close(server_coid);
	return EXIT_SUCCESS;
}

// go through the list of planes in vector airspace and send message requesting their info
void Radar::pingAirspace(){
	while (1){
		msg msg;
		plane_info rmsg;
		all_planes data;
		char buffer[10];
		msg.hdr.type = 0x00;
		airspace = Plane::airspace; // get the populated airspace

		if (airspace.empty()){
			// do nothing
		}
		else {
			for (int i : airspace){
				// go through the airspace and ping each plane
				if ((server_coid = name_open(itoa(i,buffer,10), 0)) == -1){
					break;
				}
				if (MsgSend(server_coid, &msg, sizeof(msg), &rmsg, sizeof(rmsg)) == -1){
					break;
				}
				name_close(server_coid);

				// add plane data to data structure destined to CompSys
				allPlaneData.push_back(rmsg);
			}
			data.hdr.type = 0x01;
			data.allPlanes = allPlaneData;
			toComputerSys(data); // send data to CompSys
			allPlaneData.clear(); // clear the data structure to send a new message at the next iteration
		}
	}
}

// radar thread start routine call pingAirspace()
void* radar_start_routine(void *arg)
{
	Radar& radar = *(Radar*) arg;
	radar.pingAirspace();
	return NULL;
}

Radar::Radar()
{
	if(pthread_create(&thread_id,NULL,radar_start_routine,(void *) this)!=EOK)
	{
		thread_id=NULL;
	}
}

Radar::~Radar()
{
}

