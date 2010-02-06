//SharedCollection.h
#pragma once

#include <string>
#include <vector>
#include "pthread.h"
using namespace std;

#define ADD_STRING "add"
#define DELETE_STRING "del"
#define MANIPULATE_STRING "manip"

class SharedObject;
class osc::ReceivedMessage;

class SharedCollection
{
	public:
		SharedCollection();
		void processNewMessage(const osc::ReceivedMessage&);
		void addSharedObject(SharedObject*);
		void removeSharedObject(SharedObject*);
		SharedObject * objectWithID(int);
		void step();
	private:
		vector<SharedObject*>::iterator positionOfObjectWithID(int);
		vector<SharedObject*> objects;
		SharedObject * newObjectForTypeName(string&);
		pthread_mutex_t accessLock;
};