//SharedObject.h
#pragma once
#include <string>

using namespace std;

class osc::ReceivedMessage;

class SharedObject {
	public:
		int objectID;
		string objectName;
		void setFromMessage(const osc::ReceivedMessage&);

};