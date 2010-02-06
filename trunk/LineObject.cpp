#include "stdafx.h"
#include "LineObject.h"
#include "SharedUtility.h"

LineObject::LineObject()
{
	numPoints = 2;
	points = (LaserPoint*)malloc(numPoints*sizeof(LaserPoint));
	objectName = "LObj";
}

void LineObject::setStartPoint(float percentX, float percentY)
{
	startPoint.x = percentX;
	startPoint.y = percentY;
	startPoint.z = 0;
	startPoint.f = 0;
}

void LineObject::step()
{
	//do any animation here
}

void LineObject::setEndPoint(float percentX, float percentY)
{
	endPoint.x = percentX;
	endPoint.y = percentY;
	endPoint.z = 0;
	endPoint.f = 0;
}

void LineObject::rebuildPoints()
{
	for(int i = 0; i < numPoints; i++)
	{
		LaserPoint * currentPoint = points + i;
		float currentStep = (1.0*i)/(numPoints - 1);
		SharedUtility::InterpolateBetween(startPoint, endPoint, currentStep, currentPoint);
	}
}

void LineObject::setFromMessage(const osc::ReceivedMessage& m)
{
	//assume it's a set all message
	osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
	osc::int32 objID;
	float startX, startY, endX, endY;
	args >> objID >> startX >> startY >> endX >> endY >>osc::EndMessage;
	setStartPoint(startX, startY);
	setEndPoint(startX, startY);
	rebuildPoints();
}