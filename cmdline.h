/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| cmdline.h
|**********************************************************************/

#ifndef __CMDLINE_H__
#define __CMDLINE_H__

//=======================================================
// Types
//=======================================================

struct ParseResult
{
	STR cmd;
	STR fen;
	UINT depth;
	BOOL verbose;
	BOOL loop;
};

//=======================================================
// Prototype
//=======================================================

class Cmdline
{
	public:
		//-----------------------------------------
		// Methods
		//-----------------------------------------
		static void optionsConflict(const po::variables_map& vm, const char* optA, const char* optB);
		static void optionsDepend(const po::variables_map& vm, const char* opt, const char* dependsOn);
		static ParseResult parseArgs(int argc, char *argv[]);
};

#endif
