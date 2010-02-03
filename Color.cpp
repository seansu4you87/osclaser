#include "stdafx.h"
#include "Color.h"
#include <cmath>

void advanceHueToRGB(float hue, float * nextRed, float * nextGreen, float * nextBlue)
{
	HSVtoRGB(hue, 1.0, 1.0, nextRed, nextGreen, nextBlue);
}

void HSVtoRGB(float h, float s, float v, float * r, float * g, float *b)
{
	int numSixties = (int)floor(h/60.0);
	int h_i = numSixties % 6;
	float f = (float)(h/60.0 - numSixties);
	float p = v*(1-s);
	float q = v*(1-f*s);
	float t = v*(1-(1-f)*s);

	float newR = *r;
	float newG = *g;
	float newB = *b;

	switch(h_i)
	{
		case 0:
			newR = v;
			newG = t;
			newB = p;
			break;
		case 1:
			newR = q;
			newG = v;
			newB = p;
			break;
		case 2:
			newR = p;
			newG = v;
			newB = t;
			break;
		case 3:
			newR = p;
			newG = q;
			newB = v;
			break;
		case 4:
			newR = t;
			newG = p;
			newB = v;
			break;
		case 5:
			newR = v;
			newG = p;
			newB = q;
			break;
	}

	*r = newR;
	*g = newG;
	*b = newB;
}