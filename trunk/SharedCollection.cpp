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
	objects.push_back(newObject);
}

void SharedCollection::removeSharedObject(SharedObject * deletedObject)
{
	vector<SharedObject*>::iterator position = positionOfObjectWithID(deletedObject->objectID);
	objects.erase(position);
}

void SharedCollection::processNewMessage(const osc::ReceivedMessage & m)
{

}

SharedObject * SharedCollection::newObjectForTypeName(string & objectName)
{
	return NULL;
}

SharedObject * SharedCollection::objectWithID(int objectID)
{
	vector<SharedObject*>::iterator position = positionOfObjectWithID(objectID);
	if(position != objects.end())
	{
		return position;
	}
	
	return NULL;
}

vector<SharedObject*>::iterator SharedCollection::positionOfObjectWithID(int objectID)
{
	vector<SharedObject*>::iterator theIterator;
	for(theIterator = objects.begin(); theIterator != objects.end(); theIterator++)
	{
		SharedObject * curObject = *theIterator;
		if(curObject->objectID == objectID)
		{
			return theIterator;
		}
	}

	return theIterator;
}
