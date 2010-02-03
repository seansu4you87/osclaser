#include "stdafx.h"
#include "SharedCollection.h"
#include "SharedObject.h"

#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

SharedCollection::SharedCollection()
{

}

void SharedCollection::addSharedObject(SharedObject * newObject)
{

}

void SharedCollection::removeSharedObject(SharedObject * deletedObject)
{

}

void SharedCollection::processNewMessage(const osc::ReceivedMessage & m)
{

}

SharedObject * SharedCollection::objectWithID(int objectID)
{
	return NULL;
}
