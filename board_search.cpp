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
	
class MoveCompare
{
	public:
		bool operator() (Move a,Move b) { return (a.value>b.value); }
};

class MoveCompareReverse
{
	public:
		bool operator() (Move a,Move b) { return (a.value<b.value); }
};

//=======================================================
// Count Nodes (Perft)
//=======================================================

UINT Board::countNodes(int ply, int depth)
{
	if (ply==depth) return 1;

	int result = 0;

	vector<Move> moves;
	moves.reserve(250);
	this->possibleMoves(moves);
	
	FOREACH(Move, move, moves)
	{
		MAKE((*move),this);
		
		if (!this->isKingAttacked())
		{
			this->playing *= -1;

			result += this->countNodes(ply+1,depth);
			
			this->playing *= -1;
		}
		
		UNMAKE((*move),this);
	}

	return result;
}

//=======================================================
// Search Functions
//=======================================================

Move Board::search(SearchType tp, int depth)
{
	int bestScore;
	
	//this->searchDepth = depth;
	
	//ZOBRIST.clear();
	
	Move pvs = Move("e2e4",this);
	Move* bMove;
	
	this->maxPv = -1;
	
	this->nofNodes = 0;
	
	int startA = MINUS_INF;
	int startB = PLUS_INF;
	int lastScore = 0;
	
	for (int d=depth; d<=depth; d++)
	{
		//ZOBRIST.clear();
		
		this->searchDepth = d;
		this->pvMoves.clear();
	
		pvs = Move("e2e4",this);
	
		if (tp==MiniMax) bestScore = this->miniMax_(0);
		else if (tp==AlphaBeta) bestScore = this->alphaBeta_(0, MINUS_INF, PLUS_INF);
		else if (tp==NegaScout) bestScore = this->negaScout_(0, MINUS_INF, PLUS_INF);
		else if (tp==AlphaBetaPvs) bestScore = this->alphaBetaPvs_(0, MINUS_INF, PLUS_INF, pvs);
		
		cout << "info depth " << d << " score cp " << bestScore << " nodes " << this->nofNodes << " pv ";
		
		//cout << "PV [" << d << "] :: " << setw(6) << bestScore << " :: ";
		
		bMove = (pvs.subMove)? pvs.subMove : this->bestMove;
		
		while (pvs.subMove)
		{
			this->pvMoves.push_back(*pvs.subMove);
			cout << (pvs.subMove)->notation() << " ";
			pvs = *pvs.subMove;
		}
		
		cout << endl;
		this->maxPv++;
	}

	bMove->value = bestScore;
	
	return (*bMove);
}
/*
Move Board::superSearch(int depth)
{
	Move best = this->search(AlphaBetaPvs,6);
	
	MAKE(best,this);
	this->playing *= -1;
	
	while (best.subMove)
	{
		best = *best.subMove;
		MAKE(best,this);
		this->playing *= -1;
	}
	
	int bestScore = this->search(AlphaBeta,6);
	this->bestMove->value = bestScore;
	
	return (*this->bestMove);
}
*/
int Board::miniMax_(int ply)
{
	if (ply == this->searchDepth) return this->playing*this->eval();
	
	int best = MINUS_INF;

	vector<Move> moves;
	moves.reserve(250);
	this->possibleMoves(moves);

	FOREACH(Move, move, moves)
	{
		MAKE((*move),this);
		
		this->playing *= -1;
		
		int val = -this->miniMax_(ply+1);

		this->playing *= -1;

		if (val>best) { 
			if (!this->isKingAttacked())
			{
				if (ply==0) this->bestMove = &(*move); 
				best = val; 
			}
		}
		
		UNMAKE((*move),this);
		
	}
	return best;
}

int Board::negaScout_(int ply, int alpha, int beta)
{
	if (ply == this->searchDepth) return this->playing*this->eval();
	
	int b = beta;
	
	vector<Move> moves;
	this->possibleMoves(moves);
	
	FOREACH(Move,move,moves)
	{
		MAKE((*move),this);
		this->playing *= -1;
		int val = -this->negaScout_(ply+1, -b, -alpha);
		this->playing *= -1;
		UNMAKE((*move),this);
		
		cout << "Ply : " << ply << " Move : " << (*move).notation() << " Score = " << val << " Alpha = " << alpha << " Beta = " << beta << endl;
		
		if ((alpha<val) && (move!=moves.begin()))
			val = -this->negaScout_(ply+1, -beta, -alpha);
		
		cout << "Ply : " << ply << " Move : " << (*move).notation() << " Score = " << val << " Alpha = " << alpha << " Beta = " << beta << endl;
		
		alpha = max(alpha,val);
		
		cout << "Alpha = " << alpha << endl;
		
		if (alpha>=beta)
		{
			cout << "Alpha >= beta" << endl;
			if (ply==0) { this->bestMove = &(*move); cout << "Setting bestMove" << endl; }
			cout << "Returning Alpha" << endl;
			return alpha;
		}
		
		b = alpha+1;
		
		cout << "b = alpha+1 = " << b << endl;
	}
	
	//if (ply==0) this->bestMove = &(*move);
	cout << "FIN :: Returning Alpha" << endl;
	return alpha;
}

int Board::alphaBetaPvs_(int ply, int alpha, int beta, Move & pv)
{
	if (ply == this->searchDepth) { this->nofNodes++; return this->playing*this->eval(); }
	
	vector<Move> moves;
	this->possibleMoves(moves);
	
	FOREACH(Move,move,moves)
	{
		MAKE((*move),this);
		(*move).value = this->score;
		UNMAKE((*move),this);
	}
	
	
	(this->playing==White) ? sort(moves.begin(),moves.end(),MoveCompare())
						   : sort(moves.begin(),moves.end(),MoveCompareReverse()); 
	
	//if (ply<=this->maxPv) moves[0] = this->pvMoves[ply];

	int kk = 0;
	bool searchPv = true;
	//int rng = moves.size()/1.3;// - (moves.size()*((ply+1)/20));
	
	//FOREACH(Move, move, moves)
	for (vector<Move>::iterator move = moves.begin(); move!=moves.end(); ++move)
	{
		kk++;
		if (ply==0) cout << "info currmove " << (*move).notation() << " currmovenumber " << kk << endl;
			MAKE((*move),this);
			//cout << "AFTER MOVE :: " << (*move).notation() << endl;
			//HASHUNHASH((*move),this);
			
			this->playing *= -1;
			
			int val;
			
			//if (ZOBRIST.find(this->key)!=ZOBRIST.end()) val = ZOBRIST[this->key];
			//else
			//{
			if (searchPv)
			{
				val = -this->alphaBetaPvs_(ply+1,-beta,-alpha, (*move));
			}
			else
			{
				val = -this->alphaBetaPvs_(ply+1,-alpha-1,-alpha,(*move));
				if (val>alpha)
				{
					val = -this->alphaBetaPvs_(ply+1,-beta, -alpha,(*move));
				}
			}
			//	if (this->searchDepth-ply>=8)
			//		ZOBRIST[this->key] = val;
			//}
				
			this->playing *= -1;
			
			if (val >= beta) 
			{ 
				UNMAKE((*move),this);  
				//HASHUNHASH((*move),this);
				return beta; 
			}
			else if (val > alpha) 
			{ 
				if (!this->isKingAttacked())
				{
					pv.subMove = new Move((*move));
					
					//ZOBRIST[this->key] = val;
					
					alpha = val; 
					searchPv = false;
				}
			}
		
		UNMAKE((*move),this);
		//HASHUNHASH((*move),this);
	}
	
	return alpha;
}


int Board::alphaBeta_(int ply, int alpha, int beta)
{
	if (ply == this->searchDepth) return this->playing*this->eval();
	
	vector<Move> moves;
	this->possibleMoves(moves);

	FOREACH(Move, move, moves)
	{
			MAKE((*move),this);
			//HASHUNHASH((*move),this);
		
			this->playing *= -1;
			
			int val;
			
			//if (ZOBRIST.find(this->key)!=ZOBRIST.end())
			//	val = ZOBRIST[this->key];
			//else
			//{
				val = -this->alphaBeta_(ply+1,-beta,-alpha);
				
				//if (this->searchDepth-ply>=2) 
			//		ZOBRIST[this->key] = val;
				//}
			
			this->playing *= -1;
			
			if (val >= beta) { UNMAKE((*move),this); /*HASHUNHASH((*move),this);*/ return beta; }
			else if (val > alpha) { 
				if (!this->isKingAttacked())
				{
					if (ply==0) this->bestMove = &(*move);
					//cout << "Ply :: " << ply << ", BestMove :: " << (*move).notation() << endl;
					alpha = val; 
				}
			}
		
		UNMAKE((*move),this);	
		//HASHUNHASH((*move),this);	
	}
	
	return alpha;
}
