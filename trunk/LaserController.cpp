#include "stdafx.h"
#include "LaserController.h"
#include "MultiPointObject.h"

#define NUM_OBJECTS 4

#define X_MIN -8000
#define X_MAX 8000
#define Y_MIN -8000
#define Y_MAX 8000

LaserController::LaserController()
{
	maxframes = 6000;
    maxpoints = 6000;
    maxbuffer = 7000;
    numberofundos = 5;

	xMin = -8000;
	xMax = 8000;
	yMin = -8000;
	yMax = 8000;

	numPoints = NUM_OBJECTS*(DEFAULT_POINTS*PTS_PER_COORD + 1);
}


bool LaserController::initLD()
{
	//OpenLDCommWindow();	//<---- Un-rem this if you want to see all of the LD2000.DLL function calls made from this program

	std::cout << "About to call BeginSession. Please wait..." << std::endl;
    BeginSessionEx(&version, &maxframes, &maxpoints, &maxbuffer, &numberofundos, &Status);
    if(Status != LDERR_OK)
    {
        //Put up some sort of error message box here...
        //Exit your program or whatever...
        std::cerr << "Failed to open LD2000.DLL." << std::endl;
        return false;
    }

    memset(&LaserFrame, 0, sizeof(LaserFrame));
    memset(LaserPoints, 0, sizeof(LaserPoints));

	SetWorkingScanners(1);
    SetWorkingTracks(1);
    SetWorkingFrame(1);
    DisplayFrame(1);
    //DisplayScale(100, 100, 100);
    //DisplayWindowX(-100, 100);
    //DisplayWindowY(-100, 100);
    //DisplayWindowZ(-100, 100);
    SetLaserWindow((LONG)xMin, (LONG)xMax, (LONG)yMin, (LONG)yMax, 0);
	
	//these are the custom values for bounding
	//we always initialize the window using -8000, 8000, and then use these
	//to restrict the drawing
	xMin = X_MIN;
	xMax = X_MAX;
	yMin = Y_MIN;
	yMax = Y_MAX;

	return true;
}

void LaserController::killLD()
{
	SetWorkingScanners(-1);		//Once the loop expires, display "nothing" on all tracks and all scanners.
    SetWorkingTracks(-1);
    DisplayFrame(0);
    DisplayUpdate();

	std::cout << "LD finished." << std::endl;
    Sleep(2000);
}

void LaserController::writeFrame()
{
	LaserFrame.NumPoints = numPoints;
	LaserFrame.VOFlag = 1;

    // Write this into frame 1 (as specified ty SetWorkingFrame above)
    WriteFrame(&LaserFrame, &LaserPoints[0]);
}

void LaserController::displayFrame()
{
	SetWorkingTracks(-1);	//Make sure all other tracks are displaying nothing
    DisplayFrame(0);

    SetWorkingTracks(1);	//Indicate that the working tracks (in this case, track 1 set one line above) will display frame 1
    DisplayFrame(1);
    DisplayUpdate();
}

void LaserController::setNumPoints(int nPoints)
{
	numPoints = nPoints;
}