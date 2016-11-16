/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| board.h
|**********************************************************************/

#ifndef __BOARD_H__
#define __BOARD_H__

//=======================================================
// Definitions
//=======================================================
	
#define CHECKMATE_VALUE	KING_VALUE

const int PIECE_VALUE[13] = {
	-ROOK_VALUE, -KNIGHT_VALUE, -BISHOP_VALUE, -QUEEN_VALUE, -KING_VALUE, -PAWN_VALUE,
	ROOK_VALUE, KNIGHT_VALUE, BISHOP_VALUE, QUEEN_VALUE, KING_VALUE, PAWN_VALUE, EMPTY_VALUE
};

const int PIECE_POSVALUE[13][64] = {
	BROOK_POSVALUE, BKNIGHT_POSVALUE, BBISHOP_POSVALUE, BQUEEN_POSVALUE, BKING_POSVALUE, BPAWN_POSVALUE,
	WROOK_POSVALUE, WKNIGHT_POSVALUE, WBISHOP_POSVALUE, WQUEEN_POSVALUE, WKING_POSVALUE, WPAWN_POSVALUE, EMPTY_POSVALUE
};

//=======================================================
// Types
//=======================================================

enum SearchType
{
	MiniMax,
	AlphaBeta,
	AlphaBetaPvs,
	NegaScout
};

//=======================================================
// Enumerations
//=======================================================

enum PieceName {
	bRooks, bKnights, bBishops, bQueen, bKing, bPawns,
	wRooks, wKnights, wBishops, wQueen, wKing, wPawns, empty
};

enum PieceColor {
	Black = -1,
	White = 1
};

enum SquareName {
	h1, g1, f1, e1, d1, c1, b1, a1,
	h2, g2, f2, e2, d2, c2, b2, a2,
	h3, g3, f3, e3, d3, c3, b3, a3,
	h4, g4, f4, e4, d4, c4, b4, a4,
	h5, g5, f5, e5, d5, c5, b5, a5,
	h6, g6, f6, e6, d6, c6, b6, a6,
	h7, g7, f7, e7, d7, c7, b7, a7,
	h8, g8, f8, e8, d8, c8, b8, a8
};

enum Castling {
	bCastleOO,
	bCastleOOO,
	wCastleOO,
	wCastleOOO
};

//=======================================================
// Macros
//=======================================================

#define PIECE_STR		    	((string)"rnbqkpRNBQKP")

#define ZOBR(COL,I,POS)	   		(ZOBRIST_HASHKEY[(COL)+1][(I)][(POS)])

#define KING_(POS,OWN,OCC) 		((KING_MASK[POS])&(~OWN))
#define KNIGHT_(POS,OWN,OCC) 	((KNIGHT_MASK[POS])&(~OWN))
#define ROOK_(POS,OWN,OCC) 		((ROOK_SLIDES[POS][OCC&ROOK_MASK[POS]])&(~OWN))
#define BISHOP_(POS,OWN,OCC)	((BISHOP_SLIDES[POS][OCC&BISHOP_MASK[POS]])&(~OWN))
#define QUEEN_(POS,OWN,OCC)		(~OWN)&(ROOK_SLIDES[POS][OCC&ROOK_MASK[POS]]|BISHOP_SLIDES[POS][OCC&BISHOP_MASK[POS]])
#define WPAWN_(POS,OWN,OCC)		(~OWN)&(WPAWN_SLIDES[POS][OCC&WPAWN_MASK[POS]] | (WPAWN_ATTACKMASK[POS]&OCC))
#define BPAWN_(POS,OWN,OCC)		(~OWN)&(BPAWN_SLIDES[POS][OCC&BPAWN_MASK[POS]] | (BPAWN_ATTACKMASK[POS]&OCC))

//=======================================================
// Prototype
//=======================================================

//class Move;

struct pvNode
{
	Move* mv;
	UINT pl;
};

class Board
{
	public:
		//-----------------------------------------
		// Methods
		//-----------------------------------------
		Board ();
		Board (std::string fen);
		Board(std::string fen, std::string moves);
		virtual ~Board ();
		
		void performMoves(std::string moves);
		U64 zobristKey(int color);
				
		inline U64 piecesForColor(int color);
		inline U64 occupied();

		string out();
		void debug();
		
		// board_helper.cpp
		BOOL isAttacked(int sq);
		BOOL isKingAttacked();
		
		// board_gen.cpp
		void possibleMoves(vector<Move> & moves);
		
		// board_eval.cpp
		int eval();

		UINT nofAttackers(int sq, int color);
		int attackDelta(int sq, int color);		
		int attackDelta();
		int isolatedPawns();
		int doubledPawns();
		int bishopPair();
		int knightPair();
		int kingTropism();
		
		// board_search.cpp
		UINT countNodes(int ply, int depth);
		Move search(SearchType tp, int depth);
		int miniMax_(int ply);
		int alphaBeta_(int ply, int alpha, int beta);
		int alphaBetaPvs_(int ply, int alpha, int beta, Move & pv);
		int negaScout_(int ply, int alpha, int beta);
		
		//Move superSearch(int depth);
	
		//-----------------------------------------
		// Variables
		//-----------------------------------------
		boost::array<int,64> atPosition;
		boost::array<U64,14> pieces;
		U64 key;
		
		boost::array<bool,4> castling;		
		int playing;
		int fiftyMoveCounter;
		int moveCounter;
		int enPassant;	
		int score;
		
		Move* bestMove;
		bool pvFound;
		int searchDepth;
		
		vector<Move> pvMoves;
		
		int maxPv;
		int nofNodes;

};

//=======================================================
// Inline Functions
//=======================================================

inline U64 Board::piecesForColor(int color) 
{
	if (color==Black) return this->pieces[0]|this->pieces[1]|this->pieces[2]|this->pieces[3]|this->pieces[4]|this->pieces[5];
	else return this->pieces[6]|this->pieces[7]|this->pieces[8]|this->pieces[9]|this->pieces[10]|this->pieces[11];
}

inline U64 Board::occupied() 
{ 
	return ~(this->pieces[empty]); 
};

#endif
