//LineObject

#pragma once
#include "SharedObject.h"

class LineObject : public SharedObject{
	public:
		LineObject();
		void setFromMessage(const osc::ReceivedMessage&);
};