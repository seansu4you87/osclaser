//MultiPointObject.h
#pragma once

#include <vector>
#include "ControlPoint.h"
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
private:
	vector<ControlPoint*> controlPoints;
};