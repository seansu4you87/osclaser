#include "stdafx.h"
#include "OSCLaserController.h"
#include "pthread.h"

#include <iostream>
#include <cmath>
#include <cstring>

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
	//cout << "STARTING TO LISTEN";
	UdpListeningReceiveSocket * socketPtr = (UdpListeningReceiveSocket*)socketAddr;
	socketPtr->RunUntilSigInt();
	//cout << "STOPPED LISTENING";
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