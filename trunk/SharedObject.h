//SharedObject.h
#pragma once
#include <string>

using namespace std;

class osc::ReceivedMessage;
struct LaserPoint;

class SharedObject {
	public:
		int objectID;
		int getNumPoints();
		LaserPoint * pointAt(int);
		string objectName;
		virtual void setFromMessage(const osc::ReceivedMessage&);
		virtual void step();
		void setColor(float r, float g, float b);
		SharedObject();
		~SharedObject();
	protected:
		LaserPoint * points;
		int numPoints;

};