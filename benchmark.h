/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| benchmark.h
|**********************************************************************/

#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

//=======================================================
// Macros
//=======================================================

#define BENCH_HEADER(X)		"========================================" << endl\
                        	<< X << endl << "========================================" << endl;
#define BENCH_SUBHEADER(X)	endl << "-------------------------" << endl\
							<< X << endl << "-------------------------" << endl;

//=======================================================
// Prototype
//=======================================================

class Benchmark
{
	public:
		//-----------------------------------------
		// Methods
		//-----------------------------------------
		Benchmark(Board* b);
		
		void perft(UINT depth, BOOL loop);
		void eval(UINT depth, BOOL loop);
		void generate();
		
		//-----------------------------------------
		// Variables
		//-----------------------------------------
		Board* board;
		int depth;
};

#endif
