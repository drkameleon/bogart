/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| board_gen.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Move Generation
//=======================================================

void Board::possibleMoves(vector<Move> & moves)
{
	U64 ownPieces = this->piecesForColor(this->playing);
	U64 occupied = ~(this->pieces[empty]);
	
	moves.reserve(250);
	
	//-----------------------------------------
	// "Normal" Piece Moves
	//-----------------------------------------
	
	BOOL promPossible = false;
	
	const int from = (1+(this->playing))*3;
	const int to = (1+(this->playing))*3+6;
	
	for (int pieceType=from; pieceType<to; pieceType++)
	{
		U64 piece = this->pieces[pieceType];
		
		for (; piece != 0; piece &= (piece - 1))
	    {
	        UINT pos = log2(piece & ~(piece-1));
	    
			U64 move;
			switch (pieceType)
			{
				case bPawns: 	move = BPAWN_(pos,ownPieces,occupied); if (move&ROW_MASK[a1]) promPossible=true; break;
				case wPawns: 	move = WPAWN_(pos,ownPieces,occupied); if (move&ROW_MASK[a8]) promPossible=true; break;
				case bRooks:
				case wRooks: 	move = ROOK_(pos,ownPieces,occupied); break;
				case bKnights:
				case wKnights: 	move = KNIGHT_(pos,ownPieces,occupied); break;
				case bBishops:
				case wBishops: 	move = BISHOP_(pos,ownPieces,occupied); break;
				case bQueen:
				case wQueen: 	move = QUEEN_(pos,ownPieces,occupied); break;
				case bKing:
				case wKing: 	move = KING_(pos,ownPieces,occupied); break;
				default:break;
			}
	
			for (; move !=0; move &= (move-1))
			{
				moves.push_back(Move(pos, log2(move&~(move-1)),this));
			}
		}
	}
	
	//-----------------------------------------
	// Promotions
	//-----------------------------------------
	
	if (promPossible)
	{
		vector<Move> newMoves;
		newMoves.reserve(20);
	
		FOREACH (Move, move, moves)
		{
			if (((*move).pieceFrom==wPawns) && ((*move).to>=56)) { 
				(*move).pieceFromB = wPawns;
				(*move).pieceFrom = wQueen;
				(*move).type = Promotion;
			
				Move r = Move((*move).from,(*move).to,this); r.pieceFrom = wRooks; r.pieceFromB = wPawns; r.type=Promotion;
				Move n = Move((*move).from,(*move).to,this); n.pieceFrom = wKnights; n.pieceFromB = wPawns; n.type=Promotion;
				Move b = Move((*move).from,(*move).to,this); b.pieceFrom = wBishops; b.pieceFromB = wPawns; b.type=Promotion;
			
				newMoves.push_back(r);
				newMoves.push_back(n);
				newMoves.push_back(b);
			}
			else if (((*move).pieceFrom==bPawns) && ((*move).to<=7)) {
				(*move).pieceFromB = bPawns;
				(*move).pieceFrom = bQueen;
				(*move).type = Promotion;
			
				Move r = Move((*move).from,(*move).to,this); r.pieceFrom = bRooks; r.pieceFromB = bPawns; r.type=Promotion;
				Move n = Move((*move).from,(*move).to,this); n.pieceFrom = bKnights; n.pieceFromB = bPawns; n.type=Promotion;
				Move b = Move((*move).from,(*move).to,this); b.pieceFrom = bBishops; b.pieceFromB = bPawns; b.type=Promotion;
			
				newMoves.push_back(r);
				newMoves.push_back(n);
				newMoves.push_back(b);
			}
		}
	
		FOREACH (Move, newMove, newMoves)
		{
			moves.push_back((*newMove));
		}
	}
	
	//-----------------------------------------
	// Castle Moves
	//-----------------------------------------
	
	if (this->playing==Black)
	{
		if ((this->castling[bCastleOO]) && (this->atPosition[e8]==bKing) && (this->atPosition[h8]==bRooks) && (!this->isKingAttacked()) && (!this->isAttacked(f8)) && ((CASTLE_MASK[bCastleOO]&~occupied)==CASTLE_MASK[bCastleOO]) ) { moves.push_back(Move((Castling)bCastleOO));}
		if ((this->castling[bCastleOOO]) && (this->atPosition[e8]==bKing) && (this->atPosition[a8]==bRooks) && (!this->isKingAttacked()) && (!this->isAttacked(d8)) && ((CASTLE_MASK[bCastleOOO]&~occupied)==CASTLE_MASK[bCastleOOO]) ) { moves.push_back(Move((Castling)bCastleOOO));}
	}
	else
	{
		if ((this->castling[wCastleOO]) && (this->atPosition[e1]==wKing) && (this->atPosition[h1]==wRooks) && (!this->isKingAttacked()) && (!this->isAttacked(f1)) && ((CASTLE_MASK[wCastleOO]&~occupied)==CASTLE_MASK[wCastleOO]) ) { moves.push_back(Move((Castling)wCastleOO));}
		if ((this->castling[wCastleOOO]) && (this->atPosition[e1]==wKing) && (this->atPosition[a1]==wRooks) && (!this->isKingAttacked()) && (!this->isAttacked(d1)) && ((CASTLE_MASK[wCastleOOO]&~occupied)==CASTLE_MASK[wCastleOOO]) ) { moves.push_back(Move((Castling)wCastleOOO));}
	}
	
	//-----------------------------------------
	// En Passant
	//-----------------------------------------
	
	if (this->enPassant)
	{
		if (this->playing==Black) {
			U64 oSquares = occupied | (1ULL<<this->enPassant);
			U64 ownSquares = (~ownPieces &occupied) | (1ULL<<this->enPassant);
			
			U64 enpMoves = (WPAWN_(this->enPassant,ownSquares,oSquares)) & (this->pieces[bPawns]);

			if (enpMoves)
			{
				vector <UINT> attackingPawns = BITSSET(enpMoves);
				FOREACH(UINT,attackingPawn,attackingPawns)
				{
					moves.push_back(Move(this->enPassant+8,this->enPassant,(*attackingPawn),this->enPassant,this));
				}
			}
		}
		else
		{
			U64 oSquares = occupied | (1ULL<<this->enPassant);
			U64 ownSquares = (~ownPieces &occupied) | (1ULL<<this->enPassant);
			
			U64 enpMoves = (BPAWN_(this->enPassant,ownSquares,oSquares)) & (this->pieces[wPawns]);
			
			if (enpMoves)
			{
				vector <UINT> attackingPawns = BITSSET(enpMoves);
				FOREACH(UINT,attackingPawn,attackingPawns)
				{
					moves.push_back(Move(this->enPassant-8,this->enPassant,(*attackingPawn),this->enPassant,this));
				}
			}
		}
	}
}
