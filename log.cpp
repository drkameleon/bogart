/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| log.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Message Logging
//=======================================================

void Log::msg(string msg)
{
	if (msg.length()>3)
    {
        if (UCI)
		{
                ofstream logfile;
                logfile.open(LOGFILE,ios::app);
                logfile << msg << endl;
                logfile.close();
        }
		else
		{
				printf("%s\n",msg.c_str());
		}
    }
}

void Log::out(string msg)
{
	Log::msg(">> " + msg);
}

void Log::in(string msg)
{
	Log::msg("<< " + msg);
}

void Log::start()
{
	ofstream logfile;
    logfile.open(LOGFILE);
    logfile << endl;
    logfile.close();
}
