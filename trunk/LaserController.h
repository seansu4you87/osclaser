#pragma once
//LaserController
#include "stdafx.h"
#include "Ld2000.h"

class LaserController{
	
public:
	//variables
	FRAMESTRUCT     LaserFrame;         // Frame to associate points into
	PTSTRUCT        LaserPoints[6000];  // Array to draw points with into the current frame
	
	LONG maxframes, maxpoints, maxbuffer, numberofundos, version, Status;

	int numPoints;
	double yMin, yMax, xMin, xMax;

	//functions
	LaserController();
	void virtual step(){}
	bool initLD();
	void killLD();
	void writeFrame();
	void displayFrame();
	void setNumPoints(int);
};