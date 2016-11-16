/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| timer.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Constructor
//=======================================================

Timer::Timer()
{
	this->start = Timer::getTime();
}

//=======================================================
// Functions
//=======================================================

float Timer::timeElapsed()
{
	timespec end = Timer::getTime();
	
	return ((end.tv_sec - this->start.tv_sec)*1000) + ((end.tv_nsec-this->start.tv_nsec)/1000000);
}

timespec Timer::getTime()
{
	timespec ts;

	#ifdef __MACH__
		clock_serv_t cclock;
		mach_timespec_t mts;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
		clock_get_time(cclock, &mts);
		mach_port_deallocate(mach_task_self(), cclock);
		ts.tv_sec = mts.tv_sec;
		ts.tv_nsec = mts.tv_nsec;
	#else
		clock_gettime(CLOCK_REALTIME, &ts);
	#endif
	
	return ts;
}
