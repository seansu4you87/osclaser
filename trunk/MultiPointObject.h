//MultiPointObject.h
#pragma once

#include <vector>
#include "ControlPoint.h"

#define DEFAULT_POINTS 20
#define PTS_PER_COORD 3

using namespace std;

class MultiPointObject : public SharedObject {
public:
	MultiPointObject();
	void addControlPoint(ControlPoint * newControlPoint);
	int numControlPoints();
	ControlPoint * pointAtIndex(int index);
	void setPointAtIndex(int index, float xVal, float yVal);
	virtual void step();
	virtual void rebuildPoints();
	void setObjectColor(float r, float g, float b);
private:
	vector<ControlPoint*> controlPoints;
	float r;
	float g;
	float b;
};