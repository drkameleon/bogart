/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| engine.cpp
|**********************************************************************/

#include "bogart.h"

//=======================================================
// Constructor & Destructor
//=======================================================

Engine::Engine()
{
	this->board = new Board();
	this->active = true;
}

Engine::~Engine(void)
{

}

//=======================================================
// GUI Functions
//=======================================================

void Engine::sendCommand(string cmd, string param)
{
	cout << cmd;
	if (param!="") cout << " " << param;
	cout << endl;

	Log::out(cmd + " " + param);
}

void Engine::sendCommand(string cmd)
{
	this->sendCommand(cmd,"");
}

void Engine::handleGUIInput(string input)
{
	Log::in(input);

	vector<string> parts;
	boost::split(parts,input,boost::is_any_of(", "),boost::token_compress_on);
	string cmd = parts[0];

	if (cmd==CMD_UCI) 
	{
        this->sendCommand(CMD_ID,CMD_VERSION);
        this->sendCommand(CMD_ID,CMD_AUTHOR);
		this->sendCommand(CMD_SETOPTION_OWNBOOK);
        this->sendCommand(CMD_UCIOK);
    }
    else if (cmd==CMD_ISREADY) 
	{
        this->sendCommand(CMD_READYOK);
    }
    else if (cmd==CMD_POSITION) 
	{	
		string fen = boost::trim_copy(input.substr(input.find("fen")+4));

		this->board = new Board(fen);
		
		Log::out(SSTR("Got fen : |" << fen <<"|\n"));
		Log::out(SSTR("Board :\n" << this->board->out()<<"\n"));
		Log::out(SSTR("Playing :\n" << this->board->playing <<"\n"));
    }
    else if (cmd==CMD_GO) 
	{
		Move bestMove = this->board->search(AlphaBetaPvs,7);

		this->sendCommand(CMD_BESTMOVE,bestMove.notation());
		
		Log::out(SSTR("BestMove :: "<<bestMove.out()));
    }
    else if (cmd==CMD_QUIT) 
	{
		this->active=false;
    }
    else if (cmd==CMD_STOP) { /* Stop Calculating */ }
    else if (cmd==CMD_PONDERHIT) { /* Expected move was played */ }
    else if (cmd==CMD_UCINEWGAME) { /* Let's begin a new game */ }
}

//=======================================================
// Console Functions
//=======================================================

void Engine::handleUserInput(string input)
{
	cout << "Handling user input : " << input << endl;
}

//=======================================================
// Main Method
//=======================================================

void Engine::ignite(void)
{
	Log::start();

	string input;
	do 
	{
	    if (UCI)
		{
	        getline(cin,input);
			this->handleGUIInput(input);
		}
	    else
		{
			printf("%s",USER_PROMPT);
	        getline(cin,input);
			this->handleUserInput(input);
		}

	} while (this->active);
}
