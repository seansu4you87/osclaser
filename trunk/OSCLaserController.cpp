#include "stdafx.h"
#include "OSCLaserController.h"
#include "LaserController.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include "pthread.h"

using namespace std;

#pragma comment(lib, "pthreadVCE2.lib")

OSCLaserController::OSCLaserController()
{
}

void OSCLaserController::step()
{
	collection.step();
}

void * asynchronousStartListeningOnPort(void * socketAddr)
{
	UdpListeningReceiveSocket * socketPtr = (UdpListeningReceiveSocket*)socketAddr;
	socketPtr->RunUntilSigInt();
	return socketAddr;
}

void OSCLaserController::startListeningOnPort(int thePort, OscPacketListener * theListener)
{
	UdpListeningReceiveSocket * s = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, thePort), theListener);
	pthread_t * listenThread = new pthread_t();
	pthread_create(listenThread, NULL, asynchronousStartListeningOnPort, s);
}

void OSCLaserController::ProcessMessage(const osc::ReceivedMessage& m, 
				const IpEndpointName& remoteEndpoint)
{
	cout << endl << "Received message with pattern: " << m.AddressPattern();
}

void OSCLaserController::setPointsFromCollection()
{
	pthread_mutex_lock(&(collection.accessLock));
	int currentPoint = 0;
	for(int i = 0; i < collection.objects.size(); i++)
	{
		SharedObject * curObject = collection.objects.at(i);
		for(int j = 0; j < curObject->getNumPoints(); j++)
		{
			LaserPoint * curObjectPoint = curObject->pointAt(j);

			LONG laserXCoord = (LONG)(xMin + (xMax - xMin)*curObjectPoint->x);
			LONG laserYCoord = (LONG)(yMin + (yMax - yMin)*curObjectPoint->y);
			LONG laserZCoord = (LONG)(curObjectPoint->z);
			LONG laserFCoord = (LONG)(curObjectPoint->f);

			if(j == 0)
			{
				LaserPoints[currentPoint].XCoord = laserXCoord;
				LaserPoints[currentPoint].YCoord = laserYCoord;
				LaserPoints[currentPoint].ZCoord = laserZCoord;
				LaserPoints[currentPoint].FCoord = laserFCoord;
				LaserPoints[currentPoint].RGBValue = RGB(0, 0, 0);
				LaserPoints[currentPoint].Status = 0;
				currentPoint++;
			}

			LaserPoints[currentPoint].XCoord = laserXCoord;
			LaserPoints[currentPoint].YCoord = laserYCoord;
			LaserPoints[currentPoint].ZCoord = laserZCoord;
			LaserPoints[currentPoint].FCoord = laserFCoord;

			//cout << endl << "wrote point: " << LaserPoints[currentPoint].XCoord << ", " << LaserPoints[currentPoint].YCoord;
			
			//LaserPoints[currentPoint].RGBValue = RGB(250, 0, 0);
			LaserPoints[currentPoint].RGBValue = RGB(curObjectPoint->r, curObjectPoint->g, curObjectPoint->b);
			// Special flag which tells the laser this is a corner point and also the last point
			if(j == curObject->getNumPoints() - 1)
			{
				LaserPoints[currentPoint].Status = 4096;//corner point
			}else if(j == 0){
				LaserPoints[currentPoint].Status = 0;//not a corner point
			}else{
				LaserPoints[currentPoint].Status = 0;//not a corner point
			}
			currentPoint++;
		}

	}
	pthread_mutex_unlock(&(collection.accessLock));
}