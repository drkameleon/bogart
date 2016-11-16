/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| init.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Global Variables
//=======================================================

U64_HASH ROOK_SLIDES[64];
U64_HASH BISHOP_SLIDES[64];
U64_HASH WPAWN_SLIDES[64];
U64_HASH BPAWN_SLIDES[64];

U64 ZOBRIST_HASHKEY[3][13][64];
INT_HASH ZOBRIST;

UINT SQUARE_DISTANCE[64][64];

//=======================================================
// Main Initialization Method
//=======================================================

void Init::all()
{	
	// Square Distance
	Init::squareDistance();
	
	// Zobrist Keys
	Init::zobristKeys();
	
	// Slider Tables
	Init::rookSlides();
	Init::bishopSlides();
	Init::pawnSlides();
}

//=======================================================
// Square Distance
//=======================================================

void Init::squareDistance()
{
	for (int sq1=0; sq1<64; sq1++)
	{
		for (int sq2=0; sq2<64; sq2++)
		{
	 	   int rowDist = abs (NROW(sq2) - NROW(sq1));
	 	   int colDist = abs (NCOL(sq2) - NCOL(sq1));
		   
		   SQUARE_DISTANCE[sq1][sq2] = max(rowDist,colDist);
		}
	}
}

//=======================================================
// Zobrist Keys Initialization
//=======================================================

void Init::zobristKeys()
{
	for (int playing=0; playing<3; playing++)
		for (int piece=0; piece<13; piece++)
			for (int pos=0; pos<64; pos++)
				ZOBRIST_HASHKEY[playing][piece][pos] = Bitboard::getRandom();
}

//=======================================================
// Slider Tables Initialization
//=======================================================

void Init::rookSlides()
{
	for (int pos=0; pos<64; pos++)
	{
		U64 n = ROOK_MASK[pos] ^ (1ULL<<pos);			// Get all possible moves for a Rook at pos, except pos
		vector<UINT> bits = BITSSET(n);					// Get all possible positions 

		LOOP14
		{	
			U64 num = n;
			for (int i=0; i<14; i++) if (loop[i]==0) num &= ~(1ULL<<bits[i]);			// Get combination using pattern

			U64 res = 0ULL, bit; int sh; bool go;

			/* UP */ 	RESET_POS; while ((sh+8<64)&&(go)) { sh+=8; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }
			/* DOWN */ 	RESET_POS; while ((sh-8>=0)&&(go)) { sh-=8; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }
			/* LEFT */ 	RESET_POS; while ((sh+1<64)&&(ROW_MASK[sh+1]&ROW_MASK[pos])&&(go)) { sh+=1; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }
			/* RIGHT */ RESET_POS; while ((sh-1>=0)&&(ROW_MASK[sh-1]&ROW_MASK[pos])&&(go)) { sh-=1; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }

			ROOK_SLIDES[pos][num|(1ULL<<pos)] = res;
		}
	}
}

void Init::bishopSlides()
{
	for (int pos=0; pos<64; pos++)
	{
		U64 n = BISHOP_MASK[pos] ^ (1ULL<<pos);			// Get all possible moves for a Bishop at pos, except pos
		vector<UINT> bits = BITSSET(n);					// Get all possible positions 

		LOOP14
		{			
			U64 num = n;
			for (int i=0; i<14; i++) if (loop[i]==0) num &= ~(1ULL<<bits[i]);			// Get combination using pattern

			U64 res = 0ULL, bit; int sh; bool go;

			/* LEFT-UP */		RESET_POS; while ((sh+9<64)&&((sh+9)%8>sh%8)&&(go)) { sh+=9; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }
			/* LEFT-DOWN */ 	RESET_POS; while ((sh-7>=0)&&((sh-7)%8>sh%8)&&(go)) { sh-=7; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }
			/* RIGHT-UP */		RESET_POS; while ((sh+7<64)&&((sh+7)%8<sh%8)&&(go)) { sh+=7; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }
			/* RIGHT-DOWN */	RESET_POS; while ((sh-9>=0)&&((sh-9)%8<sh%8)&&(go)) { sh-=9; bit = 1ULL<<sh; res |= bit; (num&bit)?go=false:go; }

			BISHOP_SLIDES[pos][num|(1ULL<<pos)] = res;
		}		
	}
}

void Init::pawnSlides()
{
	for (int pos=0; pos<64; pos++)
	{
		U64 n = WPAWN_MASK[pos];				
		vector<UINT> bits = BITSSET(n);

		if (bits.size()==1)
		{
			WPAWN_SLIDES[pos][n] = 0ULL;
			WPAWN_SLIDES[pos][0] = n;
		}
		else // bits = 2 (first move)
		{
			WPAWN_SLIDES[pos][n] = 0ULL;
			WPAWN_SLIDES[pos][n^(1ULL<<(pos+8))] = 1ULL<<(pos+8);
			WPAWN_SLIDES[pos][n^(1ULL<<(pos+16))] = 0ULL;
			WPAWN_SLIDES[pos][0] = n;
		}
	}

	for (int pos=0; pos<64; pos++)
	{
		U64 n = BPAWN_MASK[pos];				
		vector<UINT> bits = BITSSET(n);

		if (bits.size()==1)
		{
			BPAWN_SLIDES[pos][n] = 0ULL;
			BPAWN_SLIDES[pos][0] = n;
		}
		else // bits = 2 (first move)
		{
			BPAWN_SLIDES[pos][n] = 0ULL;
			BPAWN_SLIDES[pos][n^(1ULL<<(pos-8))] = 1ULL<<(pos-8);
			BPAWN_SLIDES[pos][n^(1ULL<<(pos-16))] = 0ULL;
			BPAWN_SLIDES[pos][0] = n;
		}
	}
}
