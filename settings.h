/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| settings.h
|**********************************************************************/

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

//=======================================================
// Engine Values
//=======================================================

#define MAX_DEPTH			6

//=======================================================
// Position & Tactics Values
//=======================================================

#define ATTACKDELTAFACTOR_VALUE				0.5
#define DOUBLEDPAWNS_VALUE					-20
#define AVAILABLEMOVES_VALUE				1
#define ISOLATEDPAWN_VALUE					-20
#define BISHOPPAIRBONUS_VALUE				20
#define KNIGHTPAIRWITHPAWNSBONUS_VALUE		10
#define KINGATTACKERSDISTANCEBONUS_VALUE	1.5

//=======================================================
// Piece Values
//=======================================================

#define EMPTY_VALUE		0
#define PAWN_VALUE 		100
#define KNIGHT_VALUE 	300
#define BISHOP_VALUE 	302
#define ROOK_VALUE 		500
#define QUEEN_VALUE 	900
#define KING_VALUE 		10000

//=======================================================
// Piece Values (by position on the board)
//=======================================================

#define EMPTY_POSVALUE {\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0\
}

#define BROOK_POSVALUE {\
   0,   0,   0,   0,   0,   0,   0,   0,\
 -15, -15, -15, -15, -15, -15, -15, -15,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
  10,   0,   0, -10, -10,   0,   0,  10\
}

#define BKNIGHT_POSVALUE {\
  10,  10,  10,  10,  10,  10,  10,  10,\
  10,   0,   0,   0,   0,   0,   0,  10,\
  10,   0,  -5,  -5,  -5,  -5,   0,  10,\
  10,   0,  -5, -10, -10,  -5,   0,  10,\
  10,   0,  -5, -10, -10,  -5,   0,  10,\
  10,   0,  -5,  -5,  -5,  -5,   0,  10,\
  10,   0,   0,   0,   0,   0,   0,  10,\
  10,  30,  10,  10,  10,  10,  30,  10\
}

#define BBISHOP_POSVALUE {\
  10,  10,  10,  10,  10,  10,  10,  10,\
  10,   0,   0,   0,   0,   0,   0,  10,\
  10,   0,  -5,  -5,  -5,  -5,   0,  10,\
  10,   0,  -5, -10, -10,  -5,   0,  10,\
  10,   0,  -5, -10, -10,  -5,   0,  10,\
  10,   0,  -5,  -5,  -5,  -5,   0,  10,\
  10,   0,   0,   0,   0,   0,   0,  10,\
  10,  10,  20,  10,  10,  20,  10,  10\
}

#define BQUEEN_POSVALUE {\
  10,  10,  10,  10,  10,  10,  10,  10,\
  10,   0,   0,   0,   0,   0,   0,  10,\
  10,   0,  -5,  -5,  -5,  -5,   0,  10,\
  10,   0,  -5, -10, -10,  -5,   0,  10,\
  10,   0,  -5, -10, -10,  -5,   0,  10,\
  10,   0,  -5,  -5,  -5,  -5,   0,  10,\
  10,   0,   0,   0,   0,   0,   0,  10,\
  10,  10,  20,  10,  10,  20,  10,  10\
}

#define BKING_POSVALUE {\
  40,  40,  40,  40,  40,  40,  40,  40,\
  40,  40,  40,  40,  40,  40,  40,  40,\
  40,  40,  40,  40,  40,  40,  40,  40,\
  40,  40,  40,  40,  40,  40,  40,  40,\
  40,  40,  40,  40,  40,  40,  40,  40,\
  40,  40,  40,  40,  40,  40,  40,  40,\
  20,  20,  20,  20,  20,  20,  20,  20,\
 -20, -40,  20,   0,  20, -40, -20,   0\
}

#define BPAWN_POSVALUE {\
   0,   0,   0,   0,   0,   0,   0,   0,\
  -5, -10, -15, -20, -20, -15, -10,  -5,\
  -4,  -8, -12, -16, -16, -12,  -8,  -4,\
  -3,  -6,  -9, -12, -12,  -9,  -6,  -3,\
  -2,  -4,  -6,  -8,  -8,  -6,  -4,  -2,\
  -1,  -2,  -3,  10,  10,  -3,  -2,  -1,\
   0,   0,   0,  40,  40,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0\
}

#define WROOK_POSVALUE {\
 -10,   0,   0,  10,  10,   0,   0, -10,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0,   0,   0,   0,   0,   0,\
  15,  15,  15,  15,  15,  15,  15,  15,\
   0,   0,   0,   0,   0,   0,   0,   0\
}

#define WKNIGHT_POSVALUE {\
 -10, -30, -10, -10, -10, -10, -30, -10,\
 -10,   0,   0,   0,   0,   0,   0, -10,\
 -10,   0,   5,   5,   5,   5,   0, -10,\
 -10,   0,   5,  10,  10,   5,   0, -10,\
 -10,   0,   5,  10,  10,   5,   0, -10,\
 -10,   0,   5,   5,   5,   5,   0, -10,\
 -10,   0,   0,   0,   0,   0,   0, -10,\
 -10, -10, -10, -10, -10, -10, -10, -10\
}

#define WBISHOP_POSVALUE {\
 -10, -10, -20, -10, -10, -20, -10, -10,\
 -10,   0,   0,   0,   0,   0,   0, -10,\
 -10,   0,   5,   5,   5,   5,   0, -10,\
 -10,   0,   5,  10,  10,   5,   0, -10,\
 -10,   0,   5,  10,  10,   5,   0, -10,\
 -10,   0,   5,   5,   5,   5,   0, -10,\
 -10,   0,   0,   0,   0,   0,   0, -10,\
 -10, -10, -10, -10, -10, -10, -10, -10\
}

#define WQUEEN_POSVALUE {\
 -10, -10, -20, -10, -10, -20, -10, -10,\
 -10,   0,   0,   0,   0,   0,   0, -10,\
 -10,   0,   5,   5,   5,   5,   0, -10,\
 -10,   0,   5,  10,  10,   5,   0, -10,\
 -10,   0,   5,  10,  10,   5,   0, -10,\
 -10,   0,   5,   5,   5,   5,   0, -10,\
 -10,   0,   0,   0,   0,   0,   0, -10,\
 -10, -10, -10, -10, -10, -10, -10, -10\
}

#define WKING_POSVALUE {\
  20,  40, -20,   0, -20,  40,  20,   0,\
 -20, -20, -20, -20, -20, -20, -20, -20,\
 -40, -40, -40, -40, -40, -40, -40, -40,\
 -40, -40, -40, -40, -40, -40, -40, -40,\
 -40, -40, -40, -40, -40, -40, -40, -40,\
 -40, -40, -40, -40, -40, -40, -40, -40,\
 -40, -40, -40, -40, -40, -40, -40, -40,\
 -40, -40, -40, -40, -40, -40, -40, -40\
}

#define WPAWN_POSVALUE {\
   0,   0,   0,   0,   0,   0,   0,   0,\
   0,   0,   0, -40, -40,   0,   0,   0,\
   1,   2,   3, -10, -10,   3,   2,   1,\
   2,   4,   6,   8,   8,   6,   4,   2,\
   3,   6,   9,  12,  12,   9,   6,   3,\
   4,   8,  12,  16,  16,  12,   8,   4,\
   5,  10,  15,  20,  20,  15,  10,   5,\
   0,   0,   0,   0,   0,   0,   0,   0\
}

#endif