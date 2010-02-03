//SharedCollection.h
#pragma once

#include <vector>
using namespace std;

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
	private:
		vector<SharedObject*> objects;
};