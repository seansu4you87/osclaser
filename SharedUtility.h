//SharedUtility
#pragma once

#include <string>
#include <vector>

using namespace std;

struct LaserPoint {
	float x;
	float y;
	float z;
	float f;
};

class SharedUtility {
	public:
		static void StringExplode(string, string, vector<string>*);
		static void InterpolateBetween(LaserPoint & start, LaserPoint & end, float t, LaserPoint * changed);
};

