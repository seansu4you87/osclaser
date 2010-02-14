#include "stdafx.h"
#include <string>
#include "SharedCollection.h"
#include "SharedObject.h"
#include "SharedUtility.h"
#include "MultiPointObject.h"

#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

#define ADD_POINT_STRING "addPt"
#define MULTI_STRING "MObj"


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

int SharedCollection::numTotalPoints()
{
	int result = 0;
	pthread_mutex_lock(&accessLock);
	for(int i = 0; i < objects.size(); i++)
	{
		MultiPointObject * curMultiObj = (MultiPointObject*)(objects.at(i));
		result += curMultiObj->numControlPoints();
	}
	pthread_mutex_unlock(&accessLock);
	return result;
}

void SharedCollection::processNewMessage(const osc::ReceivedMessage & m)
{
	
	vector<string> parts;
	SharedUtility::StringExplode(m.AddressPattern(), "/", &parts);
	if(parts.size() >= 2)
	{
		//cout << endl << "processing message: " << m.AddressPattern();
		string function = parts.at(1);
		if(strcmp(function.c_str(), SET_ALL_STRING) == 0){
			if(objects.size() == 0)
			{
				return;
			}
			string objName = parts.at(0);
			if(strcmp(objName.c_str(), MULTI_STRING) == 0)
			{
				osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				int count = 0;
				int curObjectIndex = 0;
				MultiPointObject * curObject = (MultiPointObject*)(objects.at(curObjectIndex));
				int curNumPoints = curObject->numControlPoints();
				int curPoint = 0;
				float xVal, yVal;
				while(arg != m.ArgumentsEnd())
				{
					if(count%2 == 0)
					{
						xVal = arg->AsFloat();
					}else{
						yVal = arg->AsFloat();
						curObject->setPointAtIndex(curPoint, xVal, yVal);
						curPoint++;
						if(curPoint == curNumPoints)
						{
							curObjectIndex++;
							curObject->rebuildPoints();
							if(curObjectIndex < objects.size())
							{
								curObject = (MultiPointObject*)(objects.at(curObjectIndex));
								curNumPoints = curObject->numControlPoints();
								curPoint = 0;
							}
						}
					}
					arg++;
					count++;
				}
			}
		}else if(strcmp(function.c_str(), ADD_STRING) == 0)
		{
			string objName = parts.at(0);
			if(strcmp(objName.c_str(), MULTI_STRING) == 0)
			{
				MultiPointObject * newObj = new MultiPointObject();
				osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				int count = 0;
				float xVal, yVal;
				while(arg != m.ArgumentsEnd())
				{
					if(count == 0)
					{
						newObj->objectID = arg->AsInt32();
					}else if(count%2 == 1)
					{
						xVal = arg->AsFloat();
					}else{
						yVal = arg->AsFloat();
						newObj->addControlPoint(new ControlPoint(xVal, yVal));
					}
					arg++;
					count++;
				}
				newObj->rebuildPoints();
				addSharedObject(newObj);
			}
		}else if(strcmp(function.c_str(), DELETE_STRING) == 0)
		{
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 objID;
			args >> objID >> osc::EndMessage;

			SharedObject * theObject = objectWithID((int)objID);
			if(theObject != NULL)
			{
				removeSharedObject(theObject);
			}
		}else if(strcmp(function.c_str(), MANIPULATE_STRING) == 0)
		{
			string objName = parts.at(0);
			if(strcmp(objName.c_str(), MULTI_STRING) == 0)
			{
				string fncName = parts.at(2);
				if(strcmp(fncName.c_str(), ADD_POINT_STRING) == 0)
				{
					osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
					int count = 0;
					MultiPointObject * theObj;
					float xVal, yVal;
					while(arg != m.ArgumentsEnd())
					{
						if(count == 0)
						{
							theObj = (MultiPointObject*)(this->objectWithID(arg->AsInt32()));
						}else if(count == 1)
						{
							xVal = arg->AsFloat();
						}else if(count == 2)
						{
							yVal = arg->AsFloat();
							theObj->addControlPoint(new ControlPoint(xVal, yVal));
						}
						arg++;
						count++;
					}
					theObj->rebuildPoints();
				}else{
				}
			}
		}
	}
}

SharedObject * SharedCollection::newObjectForTypeName(string & objectName)
{
	if(strcmp(objectName.c_str(), "LObj") == 0)
	{
		return new LineObject();
	}else if(strcmp(objectName.c_str(), "MObj") == 0){
		return new MultiPointObject();
	}else{
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
