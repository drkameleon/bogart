/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| main.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Global Variables
//=======================================================

BOOL DEBUG;
BOOL UCI;

//=======================================================
// Where all the magic begins...
//=======================================================

int main(int argc, char *argv[])
{
	cout << BOGART_VERSION << " - By " << BOGART_AUTHOR << endl;
	
	ParseResult pr = Cmdline::parseArgs(argc,argv);
	
	DEBUG = pr.verbose;
	UCI = (pr.cmd=="engine");
	
	if (pr.cmd=="help") return 1;
	else
	{
		Init::all();
		
		if ((pr.cmd=="console")||(pr.cmd=="engine"))
		{
			Engine* eng = new Engine();
			eng->ignite();
		}
		else
		{
			Benchmark* bench = new Benchmark(new Board(pr.fen));
			
			if (pr.cmd=="perft") bench->perft(pr.depth,pr.loop);
			else if (pr.cmd=="eval") bench->eval(pr.depth,pr.loop);
			else if (pr.cmd=="generate") bench->generate();
		}
	}
	
	return 0;
}

//=======================================================
// This is the end,...
// ...my only friend the end...
//=======================================================
