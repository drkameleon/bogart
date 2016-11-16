/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| move.h
|**********************************************************************/

#ifndef __MOVE_H__
#define __MOVE_H__

//=======================================================
// Macros
//=======================================================
	
//-----------------------------------------
// Move/Unmove single piece From...To
//-----------------------------------------
#define MAKE_FROMTO(FR,TO,PF,PT,BOARD) 		BOARD->atPosition[FR] = empty;\
						   			  		BOARD->atPosition[TO] = PF;\
						   			  		BOARD->score -= PIECE_VALUE[PT] + PIECE_POSVALUE[PT][TO] - PIECE_POSVALUE[PF][TO] + PIECE_POSVALUE[PF][FR];\
						   			  		TOGGLEBITS(BOARD->pieces[PF],FR,TO);\
						   			  		UNSETBIT(BOARD->pieces[PT],TO);\
						   			  		SETBIT(BOARD->pieces[empty],FR);\
											if (PF==wKing) { BOARD->castling[wCastleOO] = false; BOARD->castling[wCastleOOO] = false; }\
											if (PF==bKing) { BOARD->castling[bCastleOO] = false; BOARD->castling[bCastleOOO] = false; }\
											if (PF==wRooks) if (FR==h1) BOARD->castling[wCastleOO] = false; else if (FR==a1) BOARD->castling[wCastleOOO] = false;\
											if (PF==bRooks) if (FR==h8) BOARD->castling[bCastleOO] = false; else if (FR==a8) BOARD->castling[bCastleOOO] = false;
						
#define UNMAKE_FROMTO(FR,TO,PF,PT,BOARD)	BOARD->atPosition[FR] = PF;\
											BOARD->atPosition[TO] = PT;\
											BOARD->score += PIECE_VALUE[PT] + PIECE_POSVALUE[PT][TO] - PIECE_POSVALUE[PF][TO] + PIECE_POSVALUE[PF][FR];\
									    	TOGGLEBITS(BOARD->pieces[PF],FR,TO);\
											SETBIT(BOARD->pieces[PT],TO);\
									    	UNSETBIT(BOARD->pieces[empty],FR);
									
//-----------------------------------------
// Make/Unmake a simple move
//-----------------------------------------
#define MAKE1(MOVE,BOARD)   MOVE.ep = BOARD->enPassant; MOVE.cs = BOARD->castling;\
							MAKE_FROMTO(MOVE.from,MOVE.to,MOVE.pieceFrom,MOVE.pieceTo,BOARD);\
							if (((MOVE.pieceFrom==wPawns)||(MOVE.pieceFrom==bPawns)) && (abs(MOVE.from-MOVE.to)==16)) BOARD->enPassant = (MOVE.from+MOVE.to)/2; else BOARD->enPassant = 0;
#define UNMAKE1(MOVE,BOARD)	UNMAKE_FROMTO(MOVE.from,MOVE.to,MOVE.pieceFrom,MOVE.pieceTo,BOARD);\
							BOARD->enPassant = MOVE.ep; BOARD->castling = MOVE.cs;

//-----------------------------------------
// Make/Unmake Castling/EnPassant move
//-----------------------------------------
#define MAKE2(MOVE,BOARD)	MOVE.ep = BOARD->enPassant; MOVE.cs = BOARD->castling;\
                            MAKE_FROMTO(MOVE.from,MOVE.to,MOVE.pieceFrom,MOVE.pieceTo,BOARD);\
							MAKE_FROMTO(MOVE.fromB,MOVE.toB,MOVE.pieceFromB,MOVE.pieceToB,BOARD);\
							BOARD->enPassant = 0;
							
#define UNMAKE2(MOVE,BOARD) UNMAKE_FROMTO(MOVE.fromB,MOVE.toB,MOVE.pieceFromB,MOVE.pieceToB,BOARD);\
							UNMAKE_FROMTO(MOVE.from,MOVE.to,MOVE.pieceFrom,MOVE.pieceTo,BOARD);\
							BOARD->enPassant = MOVE.ep; BOARD->castling = MOVE.cs;
							
//-----------------------------------------
// Make/Unmake Promotion move
//-----------------------------------------
#define MAKE3(MOVE,BOARD)	BOARD->atPosition[MOVE.from] = MOVE.pieceFrom; SETBIT(BOARD->pieces[MOVE.pieceFrom],MOVE.from); UNSETBIT(BOARD->pieces[MOVE.pieceFromB],MOVE.from);\
							MAKE1(MOVE,BOARD);
							
#define UNMAKE3(MOVE,BOARD)	UNMAKE1(MOVE,BOARD);\
							BOARD->atPosition[MOVE.from] = MOVE.pieceFromB; UNSETBIT(BOARD->pieces[MOVE.pieceFrom],MOVE.from); SETBIT(BOARD->pieces[MOVE.pieceFromB],MOVE.from);
							
//-----------------------------------------
// Make/Unmake General move
//-----------------------------------------
#define MAKE(MOVE,BOARD)			switch (MOVE.type)\
									{\
										case Normal 	: MAKE1(MOVE,BOARD); break;\
										case Castle 	:\
										case EnPassant	: MAKE2(MOVE,BOARD); break;\
										case Promotion	: MAKE3(MOVE,BOARD); break;\
										default			: break;\
									}
									
#define UNMAKE(MOVE,BOARD)			switch (MOVE.type)\
									{\
										case Normal 	: UNMAKE1(MOVE,BOARD); break;\
										case Castle 	:\
										case EnPassant	: UNMAKE2(MOVE,BOARD); break;\
										case Promotion	: UNMAKE3(MOVE,BOARD); break;\
										default			: break;\
									}
	
//-----------------------------------------
// Hash/Unhash move
//-----------------------------------------	
								
#define HASHUNHASH_FROMTO(F,T,PF,PT,BOARD)	 BOARD->key ^= ZOBR(BOARD->playing,PF,F) ^ ZOBR(BOARD->playing,PF,T) ^ ZOBR(BOARD->playing,PT,T) ^ ZOBR(BOARD->playing,empty,F);

#define HASHUNHASH(MOVE,BOARD)		switch (MOVE.type)\
									{\
										case Normal 	: HASHUNHASH_FROMTO(MOVE.from,MOVE.to,MOVE.pieceFrom,MOVE.pieceTo,BOARD); break;\
										case Castle 	:\
										case EnPassant	:\
												HASHUNHASH_FROMTO(MOVE.from,MOVE.to,MOVE.pieceFrom,MOVE.pieceTo,BOARD);\
												HASHUNHASH_FROMTO(MOVE.fromB,MOVE.toB,MOVE.pieceFromB,MOVE.pieceToB,BOARD);\
												break;\
										case Promotion	: break;\
										default			: break;\
									}
								
//-----------------------------------------
// Misc. Macros
//-----------------------------------------
#define NROW(X)			X/8
#define NCOL(X)			7-(X%8)
#define SROW(X)			NROW(X)+1
#define SCOL(X)			((string)"abcdefgh").at(NCOL(X))
#define SPOS(X)			SCOL(X) << SROW(X)

#define ALG2FROM(X)		((string)"12345678").find(X[1])*8 + (7-((string)"abcdefgh").find(X[0]))
#define ALG2TO(X)		((string)"12345678").find(X[3])*8 + (7-((string)"abcdefgh").find(X[2]))

//=======================================================
// Types
//=======================================================

enum MoveType
{
	Normal,
	Castle,
	EnPassant,
	Promotion
};

//=======================================================
// Prototype
//=======================================================

class Move
{
	public:
		//-----------------------------------------
		// Methods
		//-----------------------------------------
		Move (string m, Board* b) : from(ALG2FROM(m)), to(ALG2TO(m)), pieceFrom(b->atPosition[from]), pieceTo(b->atPosition[to]), type(Normal), ep(0), subMove(NULL) {}
		Move (int f, int t, Board* b) : from(f), to(t), pieceFrom(b->atPosition[from]), pieceTo(b->atPosition[to]), type(Normal), ep(b->enPassant), subMove(NULL) {}
		Move (int f, int t, int fb, int tb, Board* b) : from(f), to(t), fromB(fb), toB(tb), pieceFrom(b->atPosition[from]), pieceTo(empty), pieceFromB(b->atPosition[fromB]), pieceToB(b->atPosition[from]), type(EnPassant), ep(0), subMove(NULL) {}
		Move (const Move& m) : from(m.from), to(m.to), pieceFrom(m.pieceFrom), pieceTo(m.pieceTo), fromB(m.fromB), toB(m.toB), pieceFromB(m.pieceFromB), pieceToB(m.pieceToB), value(m.value), type(m.type), ep(m.ep), cs(m.cs), subMove(m.subMove) {}
		Move (int f, int t, int pf, int pt, int v) : from(f), to(t), pieceFrom(pf), pieceTo(pt), value(v), type(Normal), ep(0), subMove(NULL) {}
		Move (Castling cstl) {
			if (cstl==bCastleOO) { this->from=e8; this->to=g8; this->fromB=h8; this->toB=f8; this->pieceFrom = bKing; this->pieceTo=empty; this->pieceFromB = bRooks; this->pieceToB=empty; }
			else if (cstl==bCastleOOO) { this->from=e8; this->to=c8; this->fromB=a8; this->toB=d8; this->pieceFrom = bKing; this->pieceTo=empty; this->pieceFromB = bRooks; this->pieceToB=empty;}
			else if (cstl==wCastleOO) { this->from=e1; this->to=g1; this->fromB=h1; this->toB=f1; this->pieceFrom = wKing; this->pieceTo=empty; this->pieceFromB = wRooks; this->pieceToB=empty;}
			else if (cstl==wCastleOOO) { this->from=e1; this->to=c1; this->fromB=a1; this->toB=d1; this->pieceFrom = wKing; this->pieceTo=empty; this->pieceFromB = wRooks; this->pieceToB=empty;}
			this->ep = 0;
			this->type = Castle;
			this->subMove = NULL;
		}
		
		inline string notation();
		inline string out();
		
		//-----------------------------------------
		// Variables
		//-----------------------------------------
		int from, to;
		int fromB, toB;
		int pieceFrom, pieceTo;
		int pieceFromB, pieceToB;
		MoveType type;
		int value;
		
		int ep;
		boost::array<bool,4> cs;
		
		Move* subMove;
};

//=======================================================
// Inline Functions
//=======================================================

inline string Move::notation()
{
	if (this->type==Promotion)
	{
		string pc = "";
		if ((this->pieceFrom==bQueen)||(this->pieceFrom==wQueen)) pc = "q";
		else if ((this->pieceFrom==bRooks)||(this->pieceFrom==wRooks)) pc = "r";
		else if ((this->pieceFrom==bKnights)||(this->pieceFrom==wKnights)) pc = "n";
		else if ((this->pieceFrom==bBishops)||(this->pieceFrom==wBishops)) pc = "b";
		
		return SSTR(SPOS(this->from) << SPOS(this->to) << pc);
	}
	else if (this->type==EnPassant)
	{
		return SSTR(SPOS(this->fromB) << SPOS(this->toB));
	}
	else return SSTR(SPOS(this->from) << SPOS(this->to));
}

inline string Move::out()
{
	return SSTR(this->notation() << " :: " << this->value);
}

#endif
