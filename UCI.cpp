#include <fstream>//For writing the game to a text file
#include "Bitboard.h"
#include "MakeMove.h"
#include "UCI.h"
#include <string>
#include <iostream>
#include <ctime>
#include "windows.h"
#include <chrono> //For multithreading--must be using C++11 compiler
#include "Thread.h"//Threading header file
#include "C:\TinyThread++-1.1-src\TinyThread++-1.1\source\tinythread.h"//Thread library

using namespace std;
int CheckUci();
string UciCommand;
Bitboard Current_Rank = 72057594037927936; 
ofstream Log("Log.txt");//For writing to a text file
int wtime = 0;
int btime = 0;
int Time_Usage = 0;

LINE PVline;

int CheckUci()
{
	bool Is_Fen = false;
	int Parse_Fen(string Fen);
		
while (cin >> UciCommand)
{
	Log << ">> " << UciCommand << endl;
	if(UciCommand == "uci")
	{
cout << "id name Chess\n";
cout << "id author David Cimbalista\n";
cout << "option name TimePerMove type spin default 3 min 1 max 5\n";
cout << "uciok\n";
}
else if(UciCommand == "isready")
cout << "readyok\n";

else if(UciCommand == "quit")
exit(0);//Exit the program if called to quit

else if (UciCommand == "ucinewgame") 
{
Searching = false; 
Nodes = 0;
}

else if(UciCommand == "startpos")
{//Set up the board internally
White_Pieces = 65535;
Black_Pieces = 18446462598732840960ULL;
White_King = 16;
Black_King = 1152921504606846976;
White_Queens = 8;
White_Rooks = 129;
White_Bishops = 36;
White_Knights = 66;
White_Pawns = 65280;
Black_Queens = 576460752303423488;
Black_Rooks = 9295429630892703744ULL;
Black_Bishops = 2594073385365405696;
Black_Knights = 4755801206503243776;
Black_Pawns = 71776119061217280;
Current_Turn = true;
White_Turn = true; 
}

else if (Is_Fen)
{
Parse_Fen(UciCommand); 
Is_Fen = false;
}

else if (UciCommand == "fen")
Is_Fen = true;
 
else if (UciCommand == "setoption")
{
	string name = "";
	cin >> name;
	string optionname = "";
	cin >> optionname;
	if(optionname == "TimePerMove")
	{
		string value = "";
		cin >> value;
		int value2 = 0;
		cin >> value2;
		Time_Usage = value2;
	}
}

else if(UciCommand == "go") 
{
 
 string time_left_white = "";
 string time_left_black = "";
 cin >> time_left_white >> wtime >> time_left_black >> btime;
 Log << ">> " << time_left_white << " >> " << wtime << " >> " << time_left_black << " >> " << btime << endl;
 if((time_left_white == "btime") || (time_left_black == "wtime"))
 {
 int w;
 w = wtime;
 wtime = btime;
 btime = w;
}
 string first;	
 string second;
 
 
 
 Searching = true;
 using namespace tthread;
 thread t(Runthread, &PVline);//Spawn new thread to constantly output infos the the GUI while the search function is running
 
 using namespace std;
 /* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();
    int f, g, h = 0, j = 0;
    Move blank;
	blank = Think(wtime, btime, h, j);
    Searching = false;
    t.join();
    
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);
    
 float temporary = (Nodes / d.count());
 //float temp_and_one = temporary * 1000.0;
 /*cout << "Number of nodes searched: " << Nodes << endl;
 cout << "Time in milliseconds: " << d.count() << endl;
 cout << "KNps: " << temporary << endl;
 cout << "Best move score: " << blank.Score << endl;*/
 
 MakeMove(blank);
		for( int h = 0; h < 64; h++)
			{
        	if(GeneralBoard[h] & blank.From)
        	{
        	cout << "bestmove " << PlayerMoves[h];
        	first = PlayerMoves[h];
        	}
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & blank.To)
        	{
        	cout  << PlayerMoves[h] << endl;
        	second = PlayerMoves[h];
        	}
		}
		//cout << "info currmove " << first << second << "currmovenumber 1" << "depth 2" << "score cp " << (blank.Score / 100) << " nodes " << Nodes << "pv d2d4 d7d5 c2c4 " << endl;	
		//cout << "bestmove " << first << second << endl;
		Nodes = 0;
		Searching = false;
		}
else if (UciCommand == "moves")
{
//Log << UciCommand << endl;
Moves_Command();
}


}

return 0;
}


int Parse_Fen(string Fen)
{

char Current_Square;
for(int h = 0; h < (Fen.length()); h++)
{
	Current_Square = Fen[h];
	

Read_Fen(Current_Square);
}
char Curr_Turn;
cin >> Curr_Turn;
Log << Curr_Turn << endl;
if(Curr_Turn == 'w')
{
Current_Turn = true;
White_Turn = true;
}
else
{
Current_Turn = false;
White_Turn = false;
}
string Legal_Castling;
cin >> Legal_Castling;
Log << Legal_Castling << endl;
string En_Passant;
cin >> En_Passant;
Log << En_Passant << endl;
string Pawn_Moves;
cin >> Pawn_Moves;
Log << Pawn_Moves << endl;
string Move_Count;
cin >> Move_Count;
Log << Move_Count << endl;
	

	
	return 0;
}


int MakeMove(Move& Best_Move)
{

if(Current_Turn)
	{
		MakeWhiteMove(Best_Move);//Plays White's moves out on the internal bitboards
	}
else 
	{
		MakeBlackMove(Best_Move);//Plays Black's moves out on the internal bitboards
	}
   
    return 0;
}

int Read_Fen(char Current_Square)
{
	switch(Current_Square)
{
	case '1':
		if(!((Current_Rank * 2) & (A_Pawn_Mask)))
		Current_Rank *= 2;
		else
		Current_Rank *= 1;
		break;
	case '2':
		if(!((Current_Rank * 4) & (A_Pawn_Mask)))
		Current_Rank *= 4;
		else
		Current_Rank *= 2;
		break;
	case '3':
	    if(!((Current_Rank * 8) & (A_Pawn_Mask)))
		Current_Rank *= 8;
		else
		Current_Rank *= 4;
	    break;
	case '4':
		if(!((Current_Rank * 16) & (A_Pawn_Mask)))
		Current_Rank *= 16;
		else
		Current_Rank *= 8;
		break;
	case '5':
		if(!((Current_Rank * 32) & (A_Pawn_Mask)))
		Current_Rank *= 32;
		else
		Current_Rank *= 16;
		break;
	case '6':
		if(!((Current_Rank * 64) & (A_Pawn_Mask)))
		Current_Rank *= 64;
		else
		Current_Rank *= 32;
		break;
	case '7':
		if(!((Current_Rank * 128) & (A_Pawn_Mask)))
		Current_Rank *= 128;
		else
		Current_Rank *= 64;
		break;
	case '8':
		Current_Rank *= 128;
		break;
    case 'K':
    	White_King = Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'k':
    	Black_King = Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'Q':
    	White_Queens |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'q':
    	Black_Queens |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'R':
    	White_Rooks |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'r':
    	Black_Rooks |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'B':
    	White_Bishops |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'b':
    	Black_Bishops |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'N':
    	White_Knights |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'n':
    	Black_Knights |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'P':
    	White_Pawns |= Current_Rank;
    	White_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case 'p':
    	Black_Pawns |= Current_Rank;
    	Black_Pieces |= Current_Rank;
    	if(!(Current_Rank & H_Pawn_Mask))
    	Current_Rank *= 2;
    	break;
    case '/':
    	Current_Rank /= 32768;
		break;
}
return 0;
}

int Moves_Command()
{ 
	char First_Part[5];
	char Second_Part[5];
	string Promotion_Type;
	while(First_Part != "go")
	{
		cin.get();
		cin.get(First_Part, 3);
		Log << ">> " << First_Part;
		string F = "go";
		//cin.get(); 
		if(First_Part == F)
		{
			break;
		}
		cin.get(Second_Part, 3);
		Log << Second_Part << endl;
		string a8 = "a8";
		string b8 = "b8";
		string c8 = "c8";
		string d8 = "d8";
		string e8 = "e8";
		string f8 = "f8";
		string g8 = "g8";
		string h8 = "h8";
		string a1 = "a1";
		string b1 = "b1";
		string c1 = "c1";
		string d1 = "d1";
		string e1 = "e1";
		string f1 = "f1";
		string g1 = "g1";
		string h1 = "h1";
		string a7 = "a7";
		string b7 = "b7";
		string c7 = "c7";
		string d7 = "d7";
		string e7 = "e7";
		string f7 = "f7";
		string g7 = "g7";
		string h7 = "h7";
		string a2 = "a2";
		string b2 = "b2";
		string c2 = "c2";
		string d2 = "d2";
		string e2 = "e2";
		string f2 = "f2";
		string g2 = "g2";
		string h2 = "h2";
		Bitboard Fr;
		Bitboard T_o;
		for(int i = 0; i < 64; i++)
		{
			if(First_Part == PlayerMoves[i])
			Fr = GeneralBoard[i];
			
		}
		for(int i = 0; i < 64; i++)
		{
			if(Second_Part == PlayerMoves[i])
		    T_o = GeneralBoard[i];
			
		}
		if(((T_o & Eigth_Rank_White) && (Fr & Seventh_Rank_White) && (Fr & White_Pawns)) || ((T_o & Eigth_Rank_Black) && (Fr & Seventh_Rank_Black) && (Fr & Black_Pawns)))
		{
			cin >> Promotion_Type;
			Log << Promotion_Type << endl;
			Parse_Moves(First_Part, Second_Part, Promotion_Type);
		}
		
		else
		{
			
			Parse_Moves(First_Part, Second_Part);
			
			
		}
		White_Turn ^= 1;
		Current_Turn ^= 1;
		
		
	}
	
		cin.putback('o');
		cin.putback('g');
		
	return 0;		
}

int Parse_Moves(string First, string Second)
{
	Bitboard From;
	Bitboard To;
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == First)
		From = GeneralBoard[i];
	}
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == Second)
		To = GeneralBoard[i];
	}
	if(White_Turn)
	{
		White_Pieces ^= From;
		White_Pieces |= To;
		if(White_Rooks & From)
		{
		White_Rooks ^= From;
		White_Rooks |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Knights & From)
		{
		White_Knights ^= From;
		White_Knights |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Bishops & From)
		{
		White_Bishops ^= From;
		White_Bishops |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Pawns & From)
		{
		White_Pawns ^= From;
		White_Pawns |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_King & From)
		{
		White_King ^= From;
		White_King |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Queens & From)
		{
		White_Queens ^= From;
		White_Queens |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
		if((To == 64) && (From == 16) && (White_King & From) && (White_King & To))
		{
			White_Pieces |= To;
            White_Pieces ^= From;
            White_Pieces |= 32;
            White_Pieces ^= 128;
            White_Rooks |= 32;
            White_Rooks ^= 128;
            White_King |= To;
            White_King ^= From;
		}
	    }
	}
	else
	{
		Black_Pieces ^= From;
		Black_Pieces |= To;
		if(Black_Rooks & From)
		{
		Black_Rooks ^= From;
		Black_Rooks |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Knights & From)
		{
		Black_Knights ^= From;
		Black_Knights |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Bishops & From)
		{
		Black_Bishops ^= From;
		Black_Bishops |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Pawns & From)
		{
		Black_Pawns ^= From;
		Black_Pawns |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_King & From)
		{
		Black_King ^= From;
		Black_King |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Queens & From)
		{
		Black_Queens ^= From;
		Black_Queens |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
		if((To == 4611686018427387904) && (From == 1152921504606846976) && (Black_King & From) && (Black_King & To))
		{
			Black_Pieces |= To;
            Black_Pieces ^= From;
            Black_Pieces |= 4611686018427387904;
            Black_Pieces ^= 1152921504606846976;
            Black_Rooks |= 2305843009213693952;
            Black_Rooks ^= 9223372036854775808ULL;
            Black_King |= To;
            Black_King ^= From;
		}
		}
		
	}
return 0;	
}




int Parse_Moves(string First, string Second, string Promotion_Type)
{
	Bitboard From;
	Bitboard To;
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == First)
		From = GeneralBoard[i];
	}
	for(int i = 0; i < 64; i++)
	{
		if(PlayerMoves[i] == Second)
		To = GeneralBoard[i];
	}
	if(White_Turn)
	{
		White_Pieces ^= From;
		White_Pieces |= To;
		if(White_Rooks & From)
		{
		White_Rooks ^= From;
		White_Rooks |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Knights & From)
		{
		White_Knights ^= From;
		White_Knights |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Bishops & From)
		{
		White_Bishops ^= From;
		White_Bishops |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Pawns & From)
		{
		White_Pawns ^= From;
		White_Pawns |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_King & From)
		{
		White_King ^= From;
		White_King |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	    if(White_Queens & From)
		{
		White_Queens ^= From;
		White_Queens |= To;
		if(Black_Pieces & To)
		{
			Black_Pieces ^= To;
			Black_Queens |= To;
			Black_Queens ^= To;
			Black_Rooks |= To;
			Black_Rooks ^= To;
			Black_Bishops |= To;
			Black_Bishops ^= To;
			Black_Knights |= To;
			Black_Knights ^= To;
			Black_Pawns |= To;
			Black_Pawns ^= To;			
		}
	    }
	}
	else
	{
		Black_Pieces ^= From;
		Black_Pieces |= To;
		if(Black_Rooks & From)
		{
		Black_Rooks ^= From;
		Black_Rooks |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Knights & From)
		{
		Black_Knights ^= From;
		Black_Knights |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Bishops & From)
		{
		Black_Bishops ^= From;
		Black_Bishops |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Pawns & From)
		{
		Black_Pawns ^= From;
		Black_Pawns |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_King & From)
		{
		Black_King ^= From;
		Black_King |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
	    if(Black_Queens & From)
		{
		Black_Queens ^= From;
		Black_Queens |= To;
		if(White_Pieces & To)
		{
			White_Pieces ^= To;
			White_Queens |= To;
			White_Queens ^= To;
			White_Rooks |= To;
			White_Rooks ^= To;
			White_Bishops |= To;
			White_Bishops ^= To;
			White_Knights |= To;
			White_Knights ^= To;
			White_Pawns |= To;
			White_Pawns ^= To;			
		}
	    }
		
	}
	string Queen = "q";
	string Rook = "r";
	string Bishop = "b";
	string Knight = "n";
	if(Promotion_Type == Queen)
	{
		if(White_Turn)
		White_Queens |= To;
		else
		Black_Queens |= To;
	}
	if(Promotion_Type == Rook)
	{
		if(White_Turn)
		White_Rooks |= To;
		else
		Black_Rooks |= To;
	}
	if(Promotion_Type == Bishop)
	{
		if(White_Turn)
		White_Bishops |= To;
		else
		Black_Bishops |= To;
	}
	if(Promotion_Type == Knight)
	{
		if(White_Turn)
		White_Knights |= To;
		else
		Black_Knights |= To;
	}
	
return 0;	
}
