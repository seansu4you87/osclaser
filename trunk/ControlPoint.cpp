//ControlPoint.cpp

#include "stdafx.h"
#include "ControlPoint.h"

ControlPoint::ControlPoint(float x, float y)
{
	this->setCoords(x, y);
	pt.z = 0;
	pt.f = 0;
}

void ControlPoint::setColor(float r, float g, float b)
{
	pt.r = r;
	pt.g = g;
	pt.b = b;
}

void ControlPoint::setCoords(float x, float y)
{
	pt.x = x;
	pt.y = 1.0 - y;
}