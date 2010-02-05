//SharedObject.h
#pragma once
#include <string>

using namespace std;

class osc::ReceivedMessage;

class SharedObject {
	public:
		int objectID;
		string objectName;
		virtual void setFromMessage(const osc::ReceivedMessage&);
		SharedObject();
	private:
		LONG * points;
		int numPoints;

};