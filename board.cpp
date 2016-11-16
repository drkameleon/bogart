/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| board.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Constructors
//=======================================================

Board::Board() // from starting position				 	
{
	new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::Board(std::string fen)
{
	vector<string> parts;
	boost::split(parts,fen,boost::is_any_of(" "),boost::token_compress_on);
	
	//-----------------------------------------
	// Position
	//-----------------------------------------
	string position = parts[0];
	
	for (int i=0; i<14; i++)
		this->pieces[i] = 0;
		
	for (int i=0; i<64; i++)
		this->atPosition[i] = empty;

	int shift=64;

	for (int i=0; i<position.length(); i++)
	{
		shift--;
		int oldshift = shift;
		char ch = position.at(i);

		int index = PIECE_STR.find(ch);
		if (index!=string::npos) { this->pieces[index] |= (1ull<<shift); this->atPosition[shift] = index; }
		else
		{
			if (ch=='/') shift++;
			else shift = shift - ((ch-'0')-1);

			for (int k=oldshift; k>=shift; k--)
			{
				this->pieces[12] |= (1ULL<<k);
				this->atPosition[k] = empty;
			}
		}
	}
	
	//-----------------------------------------
	// Playing
	//-----------------------------------------
	string turn = parts[1];
	if (turn=="w") this->playing = White;
	else this->playing = Black;
	
	//-----------------------------------------
	// Castling
	//-----------------------------------------
	string castle = parts[2];
	
	for (int k=0; k<4; k++)
		this->castling[k] = false;
		
	if (castle!="-")
	{
		for (int k=0; k<castle.length(); k++)
		{
			if (castle[k]=='k') this->castling[bCastleOO] = true;
			else if (castle[k]=='q') this->castling[bCastleOOO] = true;
			else if (castle[k]=='K') this->castling[wCastleOO] = true;
			else if (castle[k]=='Q') this->castling[wCastleOOO] = true;
 		}
	}
	
	//-----------------------------------------
	// En Passant
	//-----------------------------------------
	string ep = parts[3];
	
	this->enPassant = 0;
	
	if (ep!="-") this->enPassant = ((string)"12345678").find(ep[1])*8 + (7-((string)"abcdefgh").find(ep[0]));
	
	//-----------------------------------------
	// Half-Move Counter
	//-----------------------------------------
	string hmc = parts[4];
	
	this->fiftyMoveCounter = atoi(hmc.c_str());
	
	//-----------------------------------------
	// Move Counter
	//-----------------------------------------
	string mc = parts[5];
	
	this->moveCounter = atoi(mc.c_str());
	
	//-----------------------------------------
	// Score
	//-----------------------------------------
	this->score = 0;
	
	//-----------------------------------------
	// Calculate Zobrist Key
	//-----------------------------------------
	this->key = this->zobristKey(this->playing);
	
	//-----------------------------------------
	// Check if it also contains "moves"
	//-----------------------------------------
	int movesPos = fen.find("moves");
	
	if (movesPos!=-1)
	{
		string moves = fen.substr(movesPos+6);
		this->performMoves(moves);
	}
}

Board::~Board()
{
	
}

//=======================================================
// Misc Functions
//=======================================================

void Board::performMoves(std::string moves)
{
	vector<string> movesParts;
	boost::split(movesParts,moves,boost::is_any_of(" "),boost::token_compress_on);
	
	//-----------------------------------------
	// Perform every single move
	//-----------------------------------------
	for (int i=0; i<movesParts.size(); i++)
	{
		Log::msg(SSTR("Performing move : |" << movesParts[i] << "|\n"));
		if (movesParts[i]=="e1g1") { Move nMove=Move("h1f1",this); MAKE(nMove,this); this->castling[wCastleOO] = false; }
		else if (movesParts[i]=="e1c1") { Move nMove = Move("a1d1",this); MAKE(nMove,this); this->castling[wCastleOOO] = false; }
		else if (movesParts[i]=="e8g8") { Move nMove = Move("h8f8",this); MAKE(nMove,this); this->castling[bCastleOO] = false; }
		else if (movesParts[i]=="e8c8") { Move nMove = Move("a8d8",this); MAKE(nMove,this); this->castling[bCastleOOO] = false; }
		
		Move move = Move(movesParts[i], this);
		MAKE(move, this);
		this->playing *= -1;
	}
	
	//-----------------------------------------
	// Calculate Zobrist Key
	//-----------------------------------------
	this->key = this->zobristKey(this->playing);
}

U64 Board::zobristKey(int color)
{
	U64 key = 0;

	for (int i=12; i>=0; i--)
	{
		vector<UINT> positions = BITSSET(this->pieces[i]);
		int positionsSize = positions.size();

		for (int k=0; k<positionsSize; k++)
			key ^= ZOBR(color,i,positions[k]);
	}

	return key;
}

//=======================================================
// Output
//=======================================================

string Board::out(void)
{
	stringstream ss;

	for (int i=63; i>=0; i--)
	{
		int p = this->atPosition[i];
		char ch = '.';

		if (p!=empty) ch = PIECE_STR.at(p);

		ss << ch << " ";
		if (i%8==0) ss << "\n";
	}

	return ss.str();
}

void Board::debug(void)
{
	cout << this->out() << endl;
	
	string pl = (this->playing==White)? "White" : "Black";
	string cstl = "";
	
	if (this->castling[2]) cstl += "K";
	if (this->castling[3]) cstl += "Q";
	if (this->castling[0]) cstl += "k";
	if (this->castling[1]) cstl += "q";
	
	cout << "Castling : " << cstl << ", Turn : " << pl << endl;
	cout << "Move : " << this->moveCounter << ", Half-Moves : " << this->fiftyMoveCounter << ", E.p. : " << this->enPassant << endl;
}
