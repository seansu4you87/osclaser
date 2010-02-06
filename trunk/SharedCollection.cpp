#include "stdafx.h"
#include <string>
#include "SharedCollection.h"
#include "SharedObject.h"
#include "SharedUtility.h"

#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"


SharedCollection::SharedCollection()
{
	accessLock = PTHREAD_MUTEX_INITIALIZER;
}

void SharedCollection::addSharedObject(SharedObject * newObject)
{
	pthread_mutex_lock(&accessLock);
	objects.push_back(newObject);
	pthread_mutex_unlock(&accessLock);
}

void SharedCollection::removeSharedObject(SharedObject * deletedObject)
{
	pthread_mutex_lock(&accessLock);
	vector<SharedObject*>::iterator position = positionOfObjectWithID(deletedObject->objectID);
	objects.erase(position);
	pthread_mutex_unlock(&accessLock);
}

void SharedCollection::processNewMessage(const osc::ReceivedMessage & m)
{
	//cout << endl << "processing message: " << m.AddressPattern();
	vector<string> parts;
	SharedUtility::StringExplode(m.AddressPattern(), "/", &parts);
	if(parts.size() >= 2)
	{
		
		string function = parts.at(1);
		if(strcmp(function.c_str(), ADD_STRING) == 0)
		{
			string objName = parts.at(0);

			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 objID;
			args >> objID >> osc::EndMessage;

			cout << endl << "processing add with id: " << objID;
			SharedObject * newObj = newObjectForTypeName(objName);
			newObj->objectID = (int)objID;
			addSharedObject(newObj);
		}else if(strcmp(function.c_str(), DELETE_STRING) == 0)
		{
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 objID;
			args >> objID >> osc::EndMessage;

			cout << endl << "processing delete with id: " << objID;
			SharedObject * theObject = objectWithID((int)objID);
			if(theObject != NULL)
			{
				removeSharedObject(theObject);
			}
		}else if(strcmp(function.c_str(), MANIPULATE_STRING) == 0)
		{
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 objID;
			float startX, startY, endX, endY;
			args >> objID >> startX >> startY >> endX >> endY >>osc::EndMessage;

			cout << endl << "processing manipulate with id: " << objID;
			SharedObject * theObject = objectWithID((int)objID);
			
			if(theObject != NULL)
			{
				theObject->setFromMessage(m);
			}
			
		}
	}
}

SharedObject * SharedCollection::newObjectForTypeName(string & objectName)
{
	if(strcmp(objectName.c_str(), "LObj") == 0)
	{
		return new LineObject();
	}else {
		return new SharedObject();
	}
}

void SharedCollection::step()
{
	pthread_mutex_lock(&accessLock);
	for(int i = 0; i < objects.size(); i++)
	{
		SharedObject * curObject = objects.at(i);
		curObject->step();
	}
	pthread_mutex_unlock(&accessLock);
}

SharedObject * SharedCollection::objectWithID(int objectID)
{
	vector<SharedObject*>::iterator position = positionOfObjectWithID(objectID);
	if(position != objects.end())
	{
		return (SharedObject*)(*position);
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
