/**********************************************************************
|
| Bogart
| Chess Engine
|
| Copyright (C) 2009-2013 Dr.Kameleon
|
|**********************************************************************
| engine.h
|**********************************************************************/

#ifndef __ENGINE_H__
#define __ENGINE_H__

//=======================================================
// Definitions
//=======================================================

// UCI Incoming Messages
#define CMD_UCI             "uci"
#define CMD_DEBUG           "debug"         // [on|off]
#define CMD_ISREADY         "isready"
#define CMD_SETOPTION       "setoption"     // name [value]
#define CMD_UCINEWGAME      "ucinewgame"
#define CMD_POSITION        "position"      // [fen|startpos] moves
#define CMD_GO              "go"    
#define CMD_STOP            "stop"
#define CMD_PONDERHIT       "ponderhit"
#define CMD_QUIT            "quit"

// UCI Outgoing Messages
#define CMD_VERSION      "name " BOGART_VERSION
#define CMD_AUTHOR       "author " BOGART_AUTHOR

#define CMD_ID          "id"
#define CMD_UCIOK       "uciok"
#define CMD_READYOK     "readyok"
#define CMD_BESTMOVE    "bestmove"
#define CMD_INFO        "info"
#define CMD_OPTION      "option"
	
#define CMD_SETOPTION_OWNBOOK 	CMD_OPTION " name OwnBook type check default true"

// Misc Messages
#define USER_PROMPT     "Enter a move > "

//=======================================================
// Prototype
//=======================================================

class Engine
{
	public:
		//-----------------------------------------
		// Methods
		//-----------------------------------------
		Engine();
		virtual ~Engine ();

		void ignite();

		void handleGUIInput(string input);
		void handleUserInput(string input);
		void sendCommand(string cmd);
		void sendCommand(string cmd,string param);

		//-----------------------------------------
		// Variables
		//-----------------------------------------
		Board* board;
		bool active;
};

#endif
