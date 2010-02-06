// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <winsock2.h>
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <cmath>

//for OSC

#include <stdlib.h>
#include <mmsystem.h>
#include <signal.h>
#include <assert.h>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <cassert>
#include <string>
#include <pthread.h>

#define LDDLL_PREFIX extern "C"
#include "Ld2000.h"
#include "Color.h"
#include "LaserController.h"
#include "OSCLaserController.h"

//SharedLibrary stuff
#include "SharedObject.h"
#include "SharedCollection.h"
#include "SharedUtility.h"
#include "LineObject.h"

//OSC stuff
#include "IpEndpointName.h"
#include "NetworkingUtils.h"
#include "TimerListener.h"
#include "PacketListener.h"
#include "UdpSocket.h"
#include "OscTypes.h"
#include "OscReceivedElements.h"
#include "OscHostEndianness.h"
#include "OscOutboundPacketStream.h"
#include "OscPrintReceivedElements.h"

