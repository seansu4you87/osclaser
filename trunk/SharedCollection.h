//SharedCollection.h
#pragma once

#include <string>
#include <vector>
#include "pthread.h"
#include "Ld2000.h"
using namespace std;

#define ADD_STRING "add"
#define DELETE_STRING "del"
#define MANIPULATE_STRING "set"
#define SET_ALL_STRING "setAll"

class SharedObject;
class osc::ReceivedMessage;

class SharedCollection
{
	public:
		SharedCollection();
		void processNewMessage(const osc::ReceivedMessage &);
		void addSharedObject(SharedObject*);
		void removeSharedObject(SharedObject*);
		SharedObject * objectWithID(int);
		void step();
		vector<SharedObject*> objects;
	private:
		int numTotalPoints();
		vector<SharedObject*>::iterator positionOfObjectWithID(int);
		
		SharedObject * newObjectForTypeName(string&);
		pthread_mutex_t accessLock;
};