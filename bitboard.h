/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| bitboard.h
|**********************************************************************/

#ifndef __BITBOARD_H__
#define __BITBOARD_H__

//=======================================================
// Macros
//=======================================================

#define BITAT(X,Y) 			(((X)&(1ULL<<(Y)))>>(Y))
#define BITCOUNT(X)			__builtin_popcountll((X))
#define ISBITSET(X,Y)		((X)&(1ULL<<(Y)))
#define SETBIT(X,Y) 		X|=(1ULL<<(Y))
#define UNSETBIT(X,Y)		X&=(~(1ULL<<(Y)))
#define TOGGLEBIT(X,Y)  	X^=(1ULL<<(Y))
#define TOGGLEBITS(X,Y,Z)	X^=((1ULL<<(Y))|(1ULL<<(Z)))
#define VFLIPBITS(X) 		__builtin_bswap64(X)
#define FIRSTBIT(X)			Bitboard::firstBit((X))
#define BITSSET(X)			Bitboard::bitsSet((X))

//=======================================================
// Prototype
//=======================================================

class Bitboard
{
	public:
		//-----------------------------------------
		// Methods
		//-----------------------------------------
		static inline UINT firstBit(U64 bitboard);
		static inline vector<UINT> bitsSet(U64 bitboard);
		static inline U64 getRandom();

		static const char* str(U64 bitboard);
		static string out(U64 bitboard);
		static string outAndMark(U64 bitboard, int pos);
		static void print(U64 bitboard);

};

//=======================================================
// Inline Functions
//=======================================================

inline UINT Bitboard::firstBit(U64 bitboard)
{
	const int index64[64] = {
	    0, 47,  1, 56, 48, 27,  2, 60,
	   57, 49, 41, 37, 28, 16,  3, 61,
	   54, 58, 35, 52, 50, 42, 21, 44,
	   38, 32, 29, 23, 17, 11,  4, 62,
	   46, 55, 26, 59, 40, 36, 15, 53,
	   34, 51, 20, 43, 31, 22, 10, 45,
	   25, 39, 14, 33, 19, 30,  9, 24,
	   13, 18,  8, 12,  7,  6,  5, 63
	};

	const U64 debruijn64 = 0x03F79D71B4CB0A89ULL;
	assert (bitboard != 0);
	return index64[((bitboard ^ (bitboard-1)) * debruijn64) >> 58];
}

inline vector<UINT> Bitboard::bitsSet(U64 bitboard)
{
	UINT n;
    vector<UINT> res;

	res.reserve(64);
    for (n = 0; bitboard != 0; n++, bitboard &= (bitboard - 1))
    {
        res.push_back(log2(bitboard & ~(bitboard-1)));
    }
    return res;
}

		
inline U64 Bitboard::getRandom()
{	
	U64 r30 = RAND_MAX*rand()+rand();
	U64 s30 = RAND_MAX*rand()+rand();
	U64 t4  = rand() & 0xf;

	return (r30 << 34) + (s30 << 4) + t4;
}

#endif
