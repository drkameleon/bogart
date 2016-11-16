/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| benchmark.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Constructors
//=======================================================
	
Benchmark::Benchmark(Board* b)
{
	this->board = b;
	/*
	this->board->debug();
	cout << "KEY : " << this->board->key << endl;
	
	Move m = Move("e2e4",this->board);
	
	MAKE(m,this->board);
	HASHUNHASH(m,this->board);
	
	this->board->debug();
	cout << "KEY : " << this->board->key << endl;
	
	UNMAKE(m,this->board);
	HASHUNHASH(m,this->board);
	
	this->board->debug();
	cout << "KEY : " << this->board->key << endl;
	cout << "--------------" << endl;*/
	
	cout << BENCH_HEADER("Benchmark");
	cout << BENCH_SUBHEADER("Board");
	this->board->debug();
	cout << BENCH_SUBHEADER("Result");
}

//=======================================================
// Functions
//=======================================================

void Benchmark::perft(UINT depth, BOOL loop)
{	
	int start = (loop)? 1 : depth;
	
	for (int i=start; i<=depth; i++)
	{
		Timer *timer = new Timer();
		UINT result = this->board->countNodes(0,i);
		cout << "Perft(" << i << ") = " << left << setw(20) << result << "(" << (timer->timeElapsed()/1000) << "s)" << endl;
	}
	cout << endl;
}

void Benchmark::eval(UINT depth, BOOL loop)
{
	this->board->kingTropism();
	int start = (loop)? 1 : depth;
	
	for (int i=start; i<=depth; i++)
	{
		Timer *timer = new Timer();
		Move result = this->board->search(AlphaBetaPvs,i);
		cout << "Eval(" << i << ") = " << left << setw(20) << result.out() << "(" << (timer->timeElapsed()/1000) << "s)" << endl;
	}
	cout << endl;
}

void Benchmark::generate()
{
	vector<Move> moves;
	this->board->possibleMoves(moves);
	
	int cnt=0;
	
	FOREACH(Move,move,moves)
	{
		MAKE((*move),this->board);
		
		if (!this->board->isKingAttacked())
		{
			cout << ++cnt << "\t: " << (*move).notation() << endl;
		}
		
		UNMAKE((*move),this->board);
	}
	cout << endl;
}
