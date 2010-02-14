//MultiPointObject.cpp
#include "stdafx.h"
#include "MultiPointObject.h"

#define DEFAULT_POINTS 20
#define PTS_PER_COORD 3

MultiPointObject::MultiPointObject()
{
	numPoints = DEFAULT_POINTS*PTS_PER_COORD;
	points = (LaserPoint*)malloc(numPoints*sizeof(LaserPoint));
	objectName = "MObj";
}

void MultiPointObject::step()
{
	//subclasses can animate
}

void MultiPointObject::rebuildPoints()
{
	int nControlPts = controlPoints.size();
	if(nControlPts > 0)
	{	
		ControlPoint * cur = controlPoints.at(0);
		ControlPoint * next = controlPoints.at(0);
		if(nControlPts > 1)
		{
			next = controlPoints.at(1);
		}

		int nPoints = numPoints/PTS_PER_COORD;
		int ptsLeft = nPoints;
		int ptsPerLine = nPoints;
		if(nControlPts > 2){
			ptsPerLine = floor((1.0*nPoints)/nControlPts);
		}
		int curSegment = 0;
		int curPtIndex = 0;
		for(int i = 0; i < nPoints; i++)
		{
			
			if(curSegment == nControlPts - 1)
			{
				
			}
			LaserPoint * currentPoint = points + i*PTS_PER_COORD;
			float currentStep = (1.0*curPtIndex)/(ptsPerLine - 1);
			SharedUtility::InterpolateBetween(cur->pt, next->pt, currentStep, currentPoint);
			for(int j = 1; j < PTS_PER_COORD; j++)
			{
				SharedUtility::CopyPointToPoint(currentPoint, currentPoint + j);
			}
			ptsLeft--;
			if(curPtIndex == ptsPerLine - 1)
			{
				if(nControlPts <= 2)
				{
					return;
				}
				curSegment++;
				cur = next;
				if(curSegment < nControlPts - 1)
				{
					next = controlPoints.at(curSegment + 1);
				}else
				{
					next = controlPoints.at(0);
					ptsPerLine = ptsLeft - 3;
				}
				curPtIndex = 0;
			}else{
				curPtIndex++;
			}
		}
	}
}

void MultiPointObject::addControlPoint(ControlPoint * newControlPoint)
{
	controlPoints.push_back(newControlPoint);
}

void MultiPointObject::setPointAtIndex(int index, float xVal, float yVal)
{
	ControlPoint * ctrlPoint = this->pointAtIndex(index);
	ctrlPoint->setCoords(xVal, yVal);
}

int MultiPointObject::numControlPoints()
{
	return controlPoints.size();
}

ControlPoint * MultiPointObject::pointAtIndex(int index)
{
	return controlPoints.at(index);
}