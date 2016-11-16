/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| bitboard.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Output
//=======================================================

const char* Bitboard::str(U64 bitboard)
{
    static char b[65];
    b[0] = '\0';

    for (U64 z = (1ULL<<63); z > 0; z >>= 1)
    {
        strcat(b, ((bitboard & z) == z) ? "1" : "0");
    }
    return b;
}

string Bitboard::out(U64 bitboard)
{
	string res = "";

	for (int i=63; i>=0; i--)
	{
		U64 position = 1ULL<<i;
		(bitboard&position)==position ? res += "X " : res += ". ";
		if (i%8==0) res += "\n";
	}

	return res;
}

string Bitboard::outAndMark(U64 bitboard, int pos)
{
	string res = "";

	for (int i=63; i>=0; i--)
	{
		U64 position = 1ULL<<i;
		if (i==pos) res+= "O ";
		else
		{
			(bitboard&position)==position ? res += "X " : res += ". ";
		}
		if (i%8==0) res += "\n";
	}

	return res;
}

void Bitboard::print(U64 bitboard)
{
	cout << Bitboard::out(bitboard);
}
