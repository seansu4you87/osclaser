#include "stdafx.h"
#include "LineObject.h"

LineObject::LineObject()
{
	numPoints = 2;
	points = (LONG*)malloc(numPoints*sizeof(LONG));
}

void LineObject::setFromMessage(const osc::ReceivedMessage& m)
{
	cout << endl << "RECEIVED A MESSAGE with type " << m.AddressPattern();
	/*
			if( strcmp( m.AddressPattern(), "/1/fader5" ) == 0 )
			{
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
				float faderValue;
			}
			*/
}