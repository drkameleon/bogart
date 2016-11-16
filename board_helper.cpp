/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| board_search.cpp
|**********************************************************************/

#include "bogart.h"
	
//=======================================================
// Attack Squares
//=======================================================

BOOL Board::isAttacked(int sq)
{
	U64 ownPieces = this->piecesForColor(this->playing) | (1ULL<<sq);
	U64 occupied = ~(this->pieces[empty]) | (1ULL<<sq);
	int p = 3*(-this->playing)+3;
	
	if ((QUEEN_(sq,ownPieces,occupied)) & (this->pieces[p+bQueen])) return true;
	if ((BISHOP_(sq,ownPieces,occupied)) & (this->pieces[p+bBishops])) return true;
	if ((KNIGHT_(sq,ownPieces,occupied)) & (this->pieces[p+bKnights])) return true;
	if ((ROOK_(sq,ownPieces,occupied)) & (this->pieces[p+bRooks])) return true;
	if ((this->playing==White) && ((WPAWN_(sq,ownPieces,occupied)) & (this->pieces[bPawns]))) return true;
	if ((this->playing==Black) && ((BPAWN_(sq,ownPieces,occupied)) & (this->pieces[wPawns]))) return true;
	if ((KING_(sq,ownPieces,occupied)) & (this->pieces[p+bKing])) return true;
	
	return false;
}

BOOL Board::isKingAttacked()
{
	U64 king = this->pieces[3*this->playing+3+bKing];
	
	if (king!=0)
	{
		UINT pos = FIRSTBIT(king);
	
		return this->isAttacked(pos);
	}
	else return true;
}
