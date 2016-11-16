/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| board_eval.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Evaluation
//=======================================================

int Board::eval()
{
	int final = 
		this->score+
		this->attackDelta()+
		this->isolatedPawns()+
		this->doubledPawns()+
		this->bishopPair()+
		this->knightPair()+
		this->kingTropism();	
	/*
	cout << "Score ::\n====================\n";
	cout << "Position Score :: " << this->score << endl;
	cout << "Attack Delta :: " << this->attackDelta() << endl;
	cout << "Isolated Pawns :: " << this->isolatedPawns() << endl;
	cout << "Doubled Pawns :: " << this->doubledPawns() << endl;
	cout << "Bishop pair :: " << this->bishopPair() << endl;
	cout << "Knight pair :: " << this->knightPair() << endl;
	cout << "King tropism :: " << this->kingTropism() << endl;
	cout << "----------------------------" << endl;
	cout << "TOTAL :: " << final << endl << endl;
*/
//	this->playing *= -1;
	
	return final;
}


//=======================================================
// Attack Squares
//=======================================================

UINT Board::nofAttackers(int sq, int color)
{
	U64 ownPieces = this->piecesForColor(color) | (1ULL<<sq);
	U64 occupied = ~(this->pieces[empty]) | (1ULL<<sq);
	int p = 3*(-color)+3;
	
	U64 pawnAttackers = (color==White) ? ((WPAWN_(sq,ownPieces,occupied)) & (this->pieces[bPawns])) : ((BPAWN_(sq,ownPieces,occupied)) & (this->pieces[wPawns]));
	
	U64 attackers = (
					((QUEEN_(sq,ownPieces,occupied)) & (this->pieces[p+bQueen])) |
	 				((BISHOP_(sq,ownPieces,occupied)) & (this->pieces[p+bBishops])) |
					((KNIGHT_(sq,ownPieces,occupied)) & (this->pieces[p+bKnights])) |
					((ROOK_(sq,ownPieces,occupied)) & (this->pieces[p+bRooks])) |
					((KING_(sq,ownPieces,occupied)) & (this->pieces[p+bKing])) |
					pawnAttackers 
					);
					
	return BITCOUNT(attackers);
}

int Board::attackDelta(int sq, int color)
{
	int attackers = this->nofAttackers(sq, color);
	int defenders = this->nofAttackers(sq, -color);

	return (color==White) ? (defenders-attackers) : (attackers-defenders);
}

int Board::attackDelta()
{
	int d = 0;
	
	for (int i=0; i<64; i++)
		d += this->attackDelta(i,White);	// From White's perspective as usual
		
	return d*ATTACKDELTAFACTOR_VALUE;
}

//=======================================================
// Pawn Structure
//=======================================================

int Board::isolatedPawns()
{
	U64 Bpawns = this->pieces[bPawns];
	U64 Wpawns = this->pieces[wPawns];
	
	UINT b = 0, w = 0;
	
	if (!((COL_MASK[a1]|COL_MASK[c1]) & Wpawns) ||
	    !((COL_MASK[b1]|COL_MASK[d1]) & Wpawns) ||	
		!((COL_MASK[c1]|COL_MASK[e1]) & Wpawns) ||
		!((COL_MASK[d1]|COL_MASK[f1]) & Wpawns) ||
		!((COL_MASK[e1]|COL_MASK[g1]) & Wpawns) ||
		!((COL_MASK[f1]|COL_MASK[h1]) & Wpawns)) w = 1;
	
	if (!((COL_MASK[a1]|COL_MASK[c1]) & Wpawns) ||
	    !((COL_MASK[b1]|COL_MASK[d1]) & Wpawns) ||	
		!((COL_MASK[c1]|COL_MASK[e1]) & Wpawns) ||
		!((COL_MASK[d1]|COL_MASK[f1]) & Wpawns) ||
		!((COL_MASK[e1]|COL_MASK[g1]) & Wpawns) ||
		!((COL_MASK[f1]|COL_MASK[h1]) & Wpawns)) b = 1;
	
	return (w-b)*ISOLATEDPAWN_VALUE;
}

int Board::doubledPawns()
{
	U64 Bpawns = this->pieces[bPawns];
	U64 Wpawns = this->pieces[wPawns];
	
	UINT sc = 0;
	
	int A, B, C, D, E, F, G, H;
	
	A = COL_MASK[a1] & Bpawns; if (A&(A-1)) sc++;
	B = COL_MASK[b1] & Bpawns; if (B&(B-1)) sc++;
	C = COL_MASK[c1] & Bpawns; if (C&(C-1)) sc++;
	D = COL_MASK[d1] & Bpawns; if (D&(D-1)) sc++;
	E = COL_MASK[e1] & Bpawns; if (E&(E-1)) sc++;
	F = COL_MASK[f1] & Bpawns; if (F&(F-1)) sc++;
	G = COL_MASK[g1] & Bpawns; if (G&(G-1)) sc++;
	H = COL_MASK[h1] & Bpawns; if (H&(H-1)) sc++;
	
	A = COL_MASK[a1] & Wpawns; if (A&(A-1)) sc--;
	B = COL_MASK[b1] & Wpawns; if (B&(B-1)) sc--;
	C = COL_MASK[c1] & Wpawns; if (C&(C-1)) sc--;
	D = COL_MASK[d1] & Wpawns; if (D&(D-1)) sc--;
	E = COL_MASK[e1] & Wpawns; if (E&(E-1)) sc--;
	F = COL_MASK[f1] & Wpawns; if (F&(F-1)) sc--;
	G = COL_MASK[g1] & Wpawns; if (G&(G-1)) sc--;
	H = COL_MASK[h1] & Wpawns; if (H&(H-1)) sc--;
	
	return sc*DOUBLEDPAWNS_VALUE;
}

//=======================================================
// Bishops
//=======================================================

int Board::bishopPair()
{
	U64 Bbishops = this->pieces[bBishops];
	U64 Wbishops = this->pieces[wBishops];
	
	UINT b = (BITCOUNT(Bbishops)==2);
	UINT w = (BITCOUNT(Wbishops)==2);
	
	return (w-b)*BISHOPPAIRBONUS_VALUE;
}

//=======================================================
// Knights
//=======================================================

int Board::knightPair()
{
	U64 Bknights = this->pieces[bKnights];
	U64 Wknights = this->pieces[wKnights];
	
	U64 pawns = this->pieces[bPawns] | this->pieces[wPawns];
	
	UINT b = ((BITCOUNT(Bknights)==2)&&(BITCOUNT(pawns)>10));
	UINT w = ((BITCOUNT(Wknights)==2)&&(BITCOUNT(pawns)>10));
	
	return (w-b)*KNIGHTPAIRWITHPAWNSBONUS_VALUE;
}

//=======================================================
// King Safety
//=======================================================

int Board::kingTropism()
{
	if (this->pieces[bKing]==0) return CHECKMATE_VALUE;
	if (this->pieces[wKing]==0) return -CHECKMATE_VALUE;
	
	vector<UINT> Bqueens = BITSSET(this->pieces[bQueen]);
	vector<UINT> Brooks = BITSSET(this->pieces[bRooks]);
	vector<UINT> Bknights = BITSSET(this->pieces[bKnights]);
	UINT Bking = FIRSTBIT(this->pieces[bKing]);
	
	vector<UINT> Wqueens = BITSSET(this->pieces[wQueen]);
	vector<UINT> Wrooks = BITSSET(this->pieces[wRooks]);
	vector<UINT> Wknights = BITSSET(this->pieces[wKnights]);
	UINT Wking = FIRSTBIT(this->pieces[wKing]);

	int sc = 0;
	
	FOREACH(UINT,Bqueen,Bqueens) { sc += SQUARE_DISTANCE[(*Bqueen)][Wking]*3; }
	FOREACH(UINT,Brook,Brooks) { sc += SQUARE_DISTANCE[(*Brook)][Wking]*2; }
	FOREACH(UINT,Bknight,Bknights) { sc += SQUARE_DISTANCE[(*Bknight)][Wking]*2; }
	
	FOREACH(UINT,Wqueen,Wqueens) { sc -= SQUARE_DISTANCE[(*Wqueen)][Bking]*3; }
	FOREACH(UINT,Wrook,Wrooks) { sc -= SQUARE_DISTANCE[(*Wrook)][Bking]*2; }
	FOREACH(UINT,Wknight,Wknights) { sc -= SQUARE_DISTANCE[(*Wknight)][Bking]*2; }
	
	return sc*KINGATTACKERSDISTANCEBONUS_VALUE;
}

