/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| cmdline.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Command Line Argument processing
//=======================================================

void Cmdline::optionsConflict(const po::variables_map& vm, const char* optA, const char* optB)
{
    if (vm.count(optA) && !vm[optA].defaulted() && vm.count(optB) && !vm[optB].defaulted())
        throw logic_error(string("Conflicting options '") + optA + "' and '" + optB + "'.");
}

void Cmdline::optionsDepend(const po::variables_map& vm, const char* opt, const char* dependsOn)
{
    if (vm.count(opt) && !vm[opt].defaulted())
        if (vm.count(dependsOn) == 0 || vm[dependsOn].defaulted())
            throw logic_error(string("Option '") + opt + "' requires option '" + dependsOn + "'.");
}

ParseResult Cmdline::parseArgs(int argc, char *argv[])
{
	ParseResult res;
	
    try
	{		
		STR fen;
		UINT depth;
		BOOL verbose;
		BOOL loop;

        po::options_description desc;

		po::options_description config("Configuration");
        config.add_options()
			("fen,f", po::value<STR>(&fen), "Load a FEN string")
			("depth,d", po::value<UINT>(&depth), "Specify search depth")
			("verbose,v", po::bool_switch(&verbose), "Debug output")
			("loop,l",po::bool_switch(&loop), "Loop up to depth (for 'eval' and 'perft')")
        ;

		po::options_description commands("Commands");
		commands.add_options()
			("eval,e", "Perform Evaluation Benchmark")
			("perft,p", "Perform Move Generation Benchmark")
			("console,c", "Ignite the Engine's console version")
			("generate,g", "Generate all moves given the position")
			("help,h", "Show help")
		;
		desc.add(config).add(commands);

        po::variables_map vm;        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

		Cmdline::optionsConflict(vm, "eval", "perft");
		Cmdline::optionsConflict(vm, "eval", "console");
		Cmdline::optionsConflict(vm, "perft", "console");
		Cmdline::optionsConflict(vm, "generate", "console");
		Cmdline::optionsConflict(vm, "generate", "perft");
		Cmdline::optionsConflict(vm, "generate", "eval");

		Cmdline::optionsDepend(vm, "eval", "fen");
		Cmdline::optionsDepend(vm, "eval", "depth");
		Cmdline::optionsDepend(vm, "perft", "fen");
		Cmdline::optionsDepend(vm, "perft", "depth");
		Cmdline::optionsDepend(vm, "generate", "fen");
		
		res.fen = fen;
		res.depth = depth;
		res.verbose = verbose;
		res.loop = loop;

		if (vm.count("help")) { cout << desc << endl; res.cmd = "help"; }
		else if (vm.count("console")) res.cmd = "console";
		else if (vm.count("eval")) res.cmd = "eval";
		else if (vm.count("perft")) res.cmd = "perft";
		else if (vm.count("generate")) res.cmd = "generate";
		else res.cmd = "engine";
		
    }
	catch(exception& e) { cerr << endl << "** ERROR : " << e.what() << endl << endl; }
    catch(...) { cerr << endl << "** ERROR : Unknown exception" << endl << endl; }

	return res;
}
