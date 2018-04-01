// Copyright Hansol Park (anav96@naver.com, mooming.go@gmail.com). All rights reserved.

#include "System/Time.h"

#include <chrono>
#include <thread>

using namespace std;
using namespace HardBop;

Time::MilliSec Time::GetTimeSec()
{
	using namespace std::chrono;
	const seconds ms = duration_cast<seconds>(steady_clock::now().time_since_epoch());
	return ms.count();
}

Time::MilliSec Time::GetTimeMilli()
{
	using namespace std::chrono;
	const milliseconds ms = duration_cast<milliseconds>(steady_clock::now().time_since_epoch());
	return ms.count();
}

void Time::Sleep(Time::MilliSec milli)
{
	using namespace std::chrono;
	this_thread::sleep_for(milliseconds(milli));
}
