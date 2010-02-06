//LineObject

#pragma once
#include "SharedObject.h"
#include "SharedUtility.h"

class LineObject : public SharedObject{
	public:
		LineObject();
		void setFromMessage(const osc::ReceivedMessage&);
		void setStartPoint(float, float);
		void setEndPoint(float, float);
		virtual void step();
	private:
		LaserPoint startPoint;
		LaserPoint endPoint;
		virtual void rebuildPoints();
};