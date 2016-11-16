/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| bogart.h
|**********************************************************************/

#ifndef __BOGART_H__
#define __BOGART_H__
	
//=======================================================
// Pragmas
//=======================================================
	
#ifdef __llvm__
	#pragma GCC diagnostic ignored "-Wdangling-else"
#endif

//=======================================================
// Includes
//=======================================================

#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
	#include <mach/clock.h>
	#include <mach/mach.h>
#endif

using namespace std;

#include <boost/program_options.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/unordered_map.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

namespace po = boost::program_options;

//=======================================================
// Types
//=======================================================

class Move;

typedef bool 			BOOL;
typedef std::string 	STR;
typedef uint64_t 		U64;
typedef unsigned int 	UINT;

typedef boost::unordered_map<U64, U64>  U64_HASH;
typedef boost::unordered_map<U64, Move*> MOVE_HASH;
typedef boost::unordered_map<U64, int> INT_HASH;

//=======================================================
// Global Constants
//=======================================================

// Infinity 
#define PLUS_INF		10000000
#define MINUS_INF		-10000000

// Environment Variables
extern BOOL DEBUG;
extern BOOL UCI;

// Tables
extern U64_HASH ROOK_SLIDES[64];
extern U64_HASH BISHOP_SLIDES[64];
extern U64_HASH WPAWN_SLIDES[64];
extern U64_HASH BPAWN_SLIDES[64];

extern INT_HASH ZOBRIST;
extern U64 ZOBRIST_HASHKEY[3][13][64];

// Square Distance
extern UINT SQUARE_DISTANCE[64][64];

//=======================================================
// Prototypes
//=======================================================

#include "version.h"
#include "utils.h"
#include "masks.h"
#include "cmdline.h"
#include "init.h"
#include "bitboard.h"
#include "timer.h"
#include "log.h"
#include "settings.h"
#include "board.h"
#include "move.h"
#include "engine.h"
#include "benchmark.h"

#endif
