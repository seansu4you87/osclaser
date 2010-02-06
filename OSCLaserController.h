#pragma once

//OSCLaserController
#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

#include "SharedCollection.h"

class OSCLaserController : public LaserController, public osc::OscPacketListener
{
	public:
		OSCLaserController();
		void startListeningOnPort(int, OscPacketListener*);
		SharedCollection collection;
		virtual void step();
	protected:
		virtual void ProcessMessage(const osc::ReceivedMessage&, const IpEndpointName&);
};