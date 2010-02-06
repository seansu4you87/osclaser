#include "stdafx.h"
#include "SharedUtility.h"

void SharedUtility::StringExplode(string str, string separator, vector<string>* results){
    int found;
    found = str.find_first_of(separator);
    while(found != string::npos){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
}

void SharedUtility::InterpolateBetween(LaserPoint & start, LaserPoint & end, float t, LaserPoint * changed)
{
	changed->x = start.x + t*(end.x - start.x);
	changed->y = start.y + t*(end.y - start.y);
	changed->z = start.z + t*(end.z - start.z);
	changed->f = start.f + t*(end.f - start.f);
}