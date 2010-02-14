#include "stdafx.h"
#include "SharedObject.h"

#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

SharedObject::SharedObject()
{
	numPoints = 0;
	points = NULL;
	objectID = 0;
	objectName = "";
}

SharedObject::~SharedObject()
{
	if(points != NULL)
	{
		free(points);
	}
}

int SharedObject::getNumPoints()
{
	return numPoints;
}

LaserPoint * SharedObject::pointAt(int index)
{
	return points + index;
}

void SharedObject::step()
{
}

void SharedObject::setFromMessage(const osc::ReceivedMessage& m)
{
}