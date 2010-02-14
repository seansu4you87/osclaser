//ControlPoint.h

#pragma once

#include "SharedUtility.h"

class ControlPoint{
	public:
		ControlPoint(float x, float y);
		LaserPoint pt;
		void setCoords(float x, float y);
		void setColor(float r, float g, float b);
};