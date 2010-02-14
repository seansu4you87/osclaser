// Life.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Color.h"
#include "Ld2000.h"
#include "OSCLaserController.h"

#include <iostream>
#include <cmath>
#include <cstring>
#include <pthread.h>

//OSC stuff
#include "OscReceivedElements.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

#define PORT 7000

#define NUM_X_POINTS 20
#define NUM_Y_POINTS 10

using namespace std;

class LifeController : public OSCLaserController
{
	bool newData;
	float currentSizeValue;
	float currentHueValue;
	float currentBrightnessValue;
	private:
		void setPoints()
		{
			double percentMin = 0.2;
			double percentMax = 0.95;
			double currentPercent = percentMin + currentSizeValue*(percentMax - percentMin);
			
			double totalLength = (xMax - xMin)*currentPercent;
			double startX = 0.0 - totalLength/2.0;
			double step = totalLength / numPoints;
			for(int i = 0; i < numPoints; i++)
			{
				LaserPoints[i].XCoord = (LONG)(startX + i*step);
				LaserPoints[i].YCoord = 0;
				LaserPoints[i].ZCoord = 0;
				LaserPoints[i].FCoord = 0;
				
				float brightMin = 25;
				float brightMax = 255;
				int Brightness = (int)(brightMin + currentBrightnessValue*(brightMax-brightMin));
				
				float redPercent = 1.0;
				float greenPercent = 1.0;
				float bluePercent = 1.0;
				float hue = (float)(currentHueValue*360.0);
				advanceHueToRGB(hue, &redPercent, &greenPercent, &bluePercent);
				// Indicate brightness of the laser
				LaserPoints[i].RGBValue = RGB((int)(Brightness*redPercent), (int)(Brightness*greenPercent), (int)(Brightness*bluePercent));
				// Special flag which tells the laser this is a corner point and also the last point
				if(i == numPoints - 1)
				{
					LaserPoints[i].Status = 4096;//corner point
				}else{
					LaserPoints[i].Status = 0;//not a corner point
				}
			}
		}
	public:
		void initLife()
		{
			newData = true;
			currentSizeValue = 0;
			currentHueValue = 0;
			currentBrightnessValue = 0;
		}

	protected:
		virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint)
		{
			collection.processNewMessage(m);	
		}
};

int main(int argc, char* argv[])
{
	LifeController control;
	control.initLife();
	
	if(!control.initLD())
	{
		return 1;
	}
	
	control.startListeningOnPort(PORT, &control);

	while(true)
    {
		control.step();
		control.setPointsFromCollection();
		control.writeFrame();
		control.displayFrame();
        
        //Sleep(10);
    }
    
	control.killLD();

    return 0;
}

