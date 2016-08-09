#include "Bitboard.h"
#include "UCI.h"
#include "windows.h"
#include <thread> //For multithreading--must be using C++11 compiler
#include "Thread.h"//Threading header file
#include "Search.h"
#include "Perft.h"
#include "Zobrist.h"
#include "Nalimov\TBINDEX.h"
#include "MoveGen.h"
#include "Util.h"
#include "TransTable.h"
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
            cout << "id name ";
            cout << setfill('0') << Engine_Info() << "\n";
            cout << "id author David Cimbalista\n";
            cout << "option name TimePerMove type spin default 3 min 1 max 5\n";
            cout << "option name NalimovPath type string default NULL\n";
            cout << "uciok\n";
        }
        else if(UciCommand == "isready")
            cout << "readyok" << endl;

        else if(UciCommand == "quit")
            exit(0);//Exit the program if called to quit

        else if(UciCommand == "stop")
            Search::STOP_SEARCHING_NOW = true;

        else if (UciCommand == "ucinewgame")
        {
            Search::Searching = false;
            Search::STOP_SEARCHING_NOW = false;
            Search::Nodes = 0;
        }

        else if(UciCommand == "startpos")
        {
            //Set up the board internally
            pos.Reset();
            Search::Searching = false;
            wtime = 0;
            btime = 0;
            Search::STOP_SEARCHING_NOW = false;
            Search::Nodes = 0;
            Search::Clear();
            TT.clear();
            //cout << Get_Current_Hash_Key() << endl;

        }
		else if(UciCommand == "bench")
        {
            Timer time;
            time.Start_Clock();
            for(int i = 0; i < 1000000; i++)
            {
            	Generate_White_Moves(false, &pos);
            	Search::Clear();
            	Generate_Black_Moves(false, &pos);
            	Search::Clear();
			}
			cout << time.Get_Time() << endl;
			Search::Clear();
			time.Start_Clock();
            for(int i = 0; i < 1000000; i++)
            {
            	Generate_White_Moves(false, &pos);
            	Generate_Black_Moves(false, &pos);
            }
			cout << time.Get_Time() << endl;
			Search::Clear();
		}
        else if(UciCommand == "perft")
        {
            Timer timer;
            timer.Start_Clock();
            int depth = 0;
            cin >> depth;
            int nodes = Root_Perft(depth);
            cout << "\n===========================\n";
            cout << "Total time (ms) : " << timer.Get_Time() << "\n";
            cout << "Nodes searched  : " << nodes << "\n";
            cout << "Nodes/second    : " << (nodes / (timer.Get_Time() + 1) * 1000)  << "\n";
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
            if(optionname == "NalimovPath")
            {
            	/*string option;
            	cin >> option;
            	cout << IInitializeTb(option.c_str()) << " man tablebases found" << endl;
            	int pieces[10];
            	int wpieces[16];
            	int bpieces[16];
            	int wc = 0, bc = 0;
            	pieces[0] = __builtin_popcountll(pos.White_Pawns);
            	pieces[1] = __builtin_popcountll(pos.White_Knights);
            	pieces[2] = __builtin_popcountll(pos.White_Bishops);
            	pieces[3] = __builtin_popcountll(pos.White_Rooks);
            	pieces[4] = __builtin_popcountll(pos.White_Queens);
            	pieces[5] = __builtin_popcountll(pos.Black_Pawns);
            	pieces[6] = __builtin_popcountll(pos.Black_Knights);
            	pieces[7] = __builtin_popcountll(pos.Black_Bishops);
            	pieces[8] = __builtin_popcountll(pos.Black_Rooks);
            	pieces[9] = __builtin_popcountll(pos.Black_Queens);
            	int tbid = IDescFindFromCounters(pieces);
            	cout << "Tablebase " << tbid << endl; 
            	Move m;
            	while(m.White_Pawns2)
            	{
            		int b = m.Convert_Bitboard(pos.White_Pawns);
            		wpieces[wc++] = b;
            		m.White_Pawns2 ^= GeneralBoard[b];
				}
				while(m.White_Knights2)
            	{
            		int b = m.Convert_Bitboard(pos.White_Knights);
            		wpieces[wc++] = b;
            		m.White_Knights2 ^= GeneralBoard[b];
				}
				while(m.White_Bishops2)
            	{
            		int b = m.Convert_Bitboard(pos.White_Bishops);
            		wpieces[wc++] = b;
            		m.White_Bishops2 ^= GeneralBoard[b];
				}
				while(m.White_Rooks2)
            	{
            		int b = m.Convert_Bitboard(pos.White_Rooks);
            		wpieces[wc++] = b;
            		m.White_Rooks2 ^= GeneralBoard[b];
				}
				while(m.White_Queens2)
            	{
            		int b = m.Convert_Bitboard(pos.White_Queens);
            		wpieces[wc++] = b;
            		m.White_Queens2 ^= GeneralBoard[b];
				}
				
				while(m.Black_Pawns2)
            	{
            		int b = m.Convert_Bitboard(pos.Black_Pawns);
            		bpieces[bc++] = b;
            		m.Black_Pawns2 ^= GeneralBoard[b];
				}
				while(m.Black_Knights2)
            	{
            		int b = m.Convert_Bitboard(pos.Black_Knights);
            		bpieces[bc++] = b;
            		m.Black_Knights2 ^= GeneralBoard[b];
				}
				while(m.White_Bishops2)
            	{
            		int b = m.Convert_Bitboard(pos.Black_Bishops);
            		bpieces[bc++] = b;
            		m.Black_Bishops2 ^= GeneralBoard[b];
				}
				while(m.Black_Rooks2)
            	{
            		int b = m.Convert_Bitboard(pos.Black_Rooks);
            		bpieces[bc++] = b;
            		m.Black_Rooks2 ^= GeneralBoard[b];
				}
				while(m.Black_Queens2)
            	{
            		int b = m.Convert_Bitboard(pos.Black_Queens);
            		bpieces[bc++] = b;
            		m.Black_Queens2 ^= GeneralBoard[b];
				}
				wpieces[15] = m.Convert_Bitboard(pos.White_King);
				bpieces[15] = m.Convert_Bitboard(pos.Black_King);
				unsigned long tbindex = PfnIndCalcFun(tbid, pos.Current_Turn);
            	cout << "Index " << tbindex << endl;
            	cout << "Score is " << TbtProbeTable(tbid, 1, tbindex) << endl;*/
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
            Timer timer;
            Search::Searching = true;
            Search::Time_Allocation = 10000;
            timer.Start_Clock();
            int h = 0, j = 0;
            Move blank;
            blank = Search::Think(wtime, btime, h, j);
            Search::Searching = false;
            for( int h = 0; h < 64; h++)
            {
                if(GeneralBoard[h] & blank.From)
                {
                    cout << "bestmove " << PlayerMoves[h];
                    Log << "<< bestmove " << PlayerMoves[h];
                }
            }
            for( int h = 0; h < 64; h++)
            {
                if(GeneralBoard[h] & blank.To)
                {
                    cout << PlayerMoves[h];
                    Log << PlayerMoves[h];
                    if((blank.To & Eigth_Rank_White) && (blank.From & Seventh_Rank_White) && ((blank.P == WP)))
                    {
                        cout << "q" << endl;
                        Log << "q" << endl;
                    }
                    else if((blank.To & Eigth_Rank_Black) && (blank.From & Seventh_Rank_Black) && ((blank.P == BP)))
                    {
                        cout << "q" << endl;
                        Log << "q" << endl;
                    }
                    else
                        cout << endl;
                }
            }
            Search::Nodes = 0;

        }
        else if (UciCommand == "moves")
        {
        	Moves_Command();
        }
    }

    return 0;
}


int Parse_Fen(string Fen)
{
    pos.Reset();
    Search::Searching = false;
    wtime = 0;
    btime = 0;
    Search::STOP_SEARCHING_NOW = false;
    Search::Nodes = 0;

    pos.White_Pieces = 0;
    pos.Black_Pieces = 0;
    pos.White_King = 0;
    pos.Black_King = 0;
    pos.White_Queens = 0;
    pos.White_Rooks = 0;
    pos.White_Bishops = 0;
    pos.White_Knights = 0;
    pos.White_Pawns = 0;
    pos.Black_Queens = 0;
    pos.Black_Rooks = 0;
    pos.Black_Bishops = 0;
    pos.Black_Knights = 0;
    pos.Black_Pawns = 0;
    char Current_Square;
    for(unsigned int h = 0; h < (Fen.length()); h++)
    {
        Current_Square = Fen[h];
        Read_Fen(Current_Square);
    }
    Current_Rank = 72057594037927936;
    char Curr_Turn;
    cin >> Curr_Turn;
    Log << Curr_Turn << endl;
    if(Curr_Turn == 'w')
    {
        pos.Current_Turn = true;
    }
    else
    {
        pos.Current_Turn = false;
    }
    string Legal_Castling = "";
    cin >> Legal_Castling;
    Log << Legal_Castling << endl;
    for(int i = 0; i < Legal_Castling.length(); i++)
    {
    	if(Legal_Castling[i] == "K")
    		pos.WhiteCanCastleK = true;
    	if(Legal_Castling[i] == "k")
    		pos.BlackCanCastleK = true;
    	if(Legal_Castling[i] == "Q")
    		pos.WhiteCanCastleQ = true;
    	if(Legal_Castling[i] == "q")
    		pos.BlackCanCastleQ = true;
    }
    string En_Passant;
    cin >> En_Passant;
    Log << En_Passant << endl;
    int Pawn_Moves;
    cin >> Pawn_Moves;
    Log << Pawn_Moves << endl;
    int Move_Count;
    cin >> Move_Count;
    Log << Move_Count << endl;

    return 0;
}

int Read_Fen(char Current_Square)
{
    switch(Current_Square)
    {
    case '1':
        if(!(Current_Rank & H_Pawn_Mask))
            Current_Rank *= 2;
        else
            Current_Rank *= 1;
        break;
    case '2':
        if(!(Current_Rank & G_Pawn_Mask))
            Current_Rank *= 4;
        else
            Current_Rank *= 2;
        break;
    case '3':
        if(!(Current_Rank & F_Pawn_Mask))
            Current_Rank *= 8;
        else
            Current_Rank *= 4;
        break;
    case '4':
        if(!(Current_Rank & E_Pawn_Mask))
            Current_Rank *= 16;
        else
            Current_Rank *= 8;
        break;
    case '5':
        if(!(Current_Rank & D_Pawn_Mask))
            Current_Rank *= 32;
        else
            Current_Rank *= 16;
        break;
    case '6':
        if(!(Current_Rank & C_Pawn_Mask))
            Current_Rank *= 64;
        else
            Current_Rank *= 32;
        break;
    case '7':
        if(!(Current_Rank & B_Pawn_Mask))
            Current_Rank *= 128;
        else
            Current_Rank *= 64;
        break;
    case '8':
        Current_Rank *= 128;
        break;
    case 'K':
        pos.White_King = Current_Rank;
        pos.White_Pieces |= Current_Rank;
        if(!(Current_Rank & H_Pawn_Mask))
            Current_Rank *= 2;
        break;
    case 'k':
        pos.Black_King = Current_Rank;
        pos.Black_Pieces |= Current_Rank;
        if(!(Current_Rank & H_Pawn_Mask))
            Current_Rank *= 2;
        break;
    case 'Q':
        pos.White_Queens |= Current_Rank;
        pos.White_Pieces |= Current_Rank;
        if(!(Current_Rank & H_Pawn_Mask))
            Current_Rank *= 2;
        break;
    case 'q':
        pos.Black_Queens |= Current_Rank;
        pos.Black_Pieces |= Current_Rank;
        if(!(Current_Rank & H_Pawn_Mask))
            Current_Rank *= 2;
        break;
    case 'R':
        pos.White_Rooks |= Current_Rank;
        pos.White_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
            Current_Rank *= 2;
        break;
    case 'r':
        pos.Black_Rooks |= Current_Rank;
        pos.Black_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
            Current_Rank *= 2;
        break;
    case 'B':
        pos.White_Bishops |= Current_Rank;
        pos.White_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
            Current_Rank *= 2;
        break;
    case 'b':
        pos.Black_Bishops |= Current_Rank;
        pos.Black_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
            Current_Rank *= 2;
        break;
    case 'N':
        pos.White_Knights |= Current_Rank;
        pos.White_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
            Current_Rank *= 2;
        break;
    case 'n':
        pos.Black_Knights |= Current_Rank;
        pos.Black_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
            Current_Rank *= 2;
        break;
    case 'P':
        pos.White_Pawns |= Current_Rank;
        pos.White_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
            Current_Rank *= 2;
        break;
    case 'p':
        pos.Black_Pawns |= Current_Rank;
        pos.Black_Pieces |= Current_Rank;
        if((!(Current_Rank & H_Pawn_Mask)) && ((Current_Rank != 9223372036854775808ULL)))
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
    while(true)
    {
    	Move m;
    	//TT.save(0, 0, m, Exact, Get_Current_Hash_Key());
        cin.get();
        cin.get(First_Part, 3);
        Log << ">> " << First_Part;
        string F = "go";
        //cin.get();
        if(First_Part == F)
        {
            cin.putback('o');
            cin.putback('g');
            break;
        }
        string f = "pe";
        if(First_Part == f)
        {
            cin.putback('e');
            cin.putback('p');
            //string ucicommand;
            //cin >> ucicommand;
            //cout << ucicommand;
            return 0;
        }
        string g = "be";
        if(First_Part == g)
        {
        	cin.putback('e');
            cin.putback('b');
            return 0;
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
        Bitboard Fr = 0;;
        Bitboard T_o = 0;;
        for(int i = 0; i < 64; i++)
        {
            if(First_Part == PlayerMoves[i])
            {
            	Fr = GeneralBoard[i];
            }
        }
        for(int i = 0; i < 64; i++)
        {
            if(Second_Part == PlayerMoves[i])
            {
            	T_o = GeneralBoard[i];
            }
        }
        if(((T_o & Eigth_Rank_White) && (Fr & Seventh_Rank_White) && (Fr & pos.White_Pawns)) || ((T_o & Eigth_Rank_Black) && (Fr & Seventh_Rank_Black) && (Fr & pos.Black_Pawns)))
        {
            cin >> Promotion_Type;
            Log << Promotion_Type << endl;
            Parse_Moves(First_Part, Second_Part, Promotion_Type);
        }
        else
            Parse_Moves(First_Part, Second_Part);
        pos.Current_Turn ^= 1;
    }
	return 0;
}

int Parse_Moves(string First, string Second)
{
    Bitboard From = 0;
    Bitboard To = 0;
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
    if(pos.Current_Turn)
    {
        pos.White_Pieces ^= From;
        pos.White_Pieces |= To;
        if(pos.White_Rooks & From)
        {
            pos.White_Rooks ^= From;
            pos.White_Rooks |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
            if(From == 1)
            {
                pos.WhiteCanCastleQ = false;
            }
            if(From == 128)
            {
                pos.WhiteCanCastleK = false;
            }
        }
        if(pos.White_Knights & From)
        {
            pos.White_Knights ^= From;
            pos.White_Knights |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
        if(pos.White_Bishops & From)
        {
            pos.White_Bishops ^= From;
            pos.White_Bishops |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
        if(pos.White_Pawns & From)
        {
            pos.White_Pawns ^= From;
            pos.White_Pawns |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
                return 0;
            }
            if(((pos.Black_Pawns << 8) & To) && (From & 1095216660480))
            {
                pos.Black_Pawns ^= (To >> 8);
                pos.Black_Pieces ^= (To >> 8);
            }
        }
        if(pos.White_King & From)
        {
            pos.White_King ^= From;
            pos.White_King |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
            if((To == 64) && From == 16)
            {
                pos.White_Pieces |= 64;
                pos.White_Pieces |= 32;
                pos.White_Pieces ^= 128;
                pos.White_Rooks |= 32;
                pos.White_Rooks ^= 128;
            }
            if(To == 4 && From == 16)
            {
                pos.White_Pieces |= 4;
                pos.White_Pieces |= 8;
                pos.White_Pieces ^= 1;
                pos.White_Rooks |= 8;
                pos.White_Rooks ^= 1;
            }
            pos.WhiteCanCastleK = false;
            pos.WhiteCanCastleQ = false;
        }
        if(pos.White_Queens & From)
        {
            pos.White_Queens ^= From;
            pos.White_Queens |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }

        }
    }
    else
    {
        pos.Black_Pieces ^= From;
        pos.Black_Pieces |= To;
        if(pos.Black_Rooks & From)
        {
            pos.Black_Rooks ^= From;
            pos.Black_Rooks |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
            if(From == 72057594037927936)
            {
                pos.BlackCanCastleQ = false;
            }
            if(From == 9223372036854775808ULL)
            {
                pos.BlackCanCastleK = false;
            }
        }
        if(pos.Black_Knights & From)
        {
            pos.Black_Knights ^= From;
            pos.Black_Knights |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }
        if(pos.Black_Bishops & From)
        {
            pos.Black_Bishops ^= From;
            pos.Black_Bishops |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }
        if(pos.Black_Pawns & From)
        {
            pos.Black_Pawns ^= From;
            pos.Black_Pawns |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
                return 0;
            }
            if(((pos.White_Pawns >> 8) & To) && (From & 4278190080))
            {
                pos.White_Pawns ^= (To << 8);
                pos.White_Pieces ^= (To << 8);
            }
        }
        if(pos.Black_King & From)
        {
            pos.Black_King ^= From;
            pos.Black_King |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
            if((To == 4611686018427387904) && From == 1152921504606846976)
            {
                pos.Black_Pieces |= 4611686018427387904;
                pos.Black_Pieces |= 2305843009213693952;
                pos.Black_Pieces ^= 9223372036854775808ULL;
                pos.Black_Rooks |= 2305843009213693952;
                pos.Black_Rooks ^= 9223372036854775808ULL;
            }
            if(To == 288230376151711744 && From == 1152921504606846976)
            {
                pos.Black_Pieces |= 288230376151711744;
                pos.Black_Pieces |= 576460752303423488;
                pos.Black_Pieces ^= 72057594037927936;
                pos.Black_Rooks |= 576460752303423488;
                pos.Black_Rooks ^= 72057594037927936;
            }
            pos.BlackCanCastleK = false;
            pos.BlackCanCastleQ = false;
        }
        if(pos.Black_Queens & From)
        {
            pos.Black_Queens ^= From;
            pos.Black_Queens |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }

        }

    }
    return 0;
}




int Parse_Moves(string First, string Second, string Promotion_Type)
{
    Bitboard From = 0;
    Bitboard To = 0;
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
    if(pos.Current_Turn)
    {
        pos.White_Pieces ^= From;
        pos.White_Pieces |= To;
        if(pos.White_Rooks & From)
        {
            pos.White_Rooks ^= From;
            pos.White_Rooks |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
        if(pos.White_Knights & From)
        {
            pos.White_Knights ^= From;
            pos.White_Knights |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
        if(pos.White_Bishops & From)
        {
            pos.White_Bishops ^= From;
            pos.White_Bishops |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
        if(pos.White_Pawns & From)
        {
            pos.White_Pawns ^= From;
            //White_Pawns |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
        if(pos.White_King & From)
        {
            pos.White_King ^= From;
            pos.White_King |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
        if(pos.White_Queens & From)
        {
            pos.White_Queens ^= From;
            pos.White_Queens |= To;
            if(pos.Black_Pieces & To)
            {
                pos.Black_Pieces ^= To;
                pos.Black_Queens |= To;
                pos.Black_Queens ^= To;
                pos.Black_Rooks |= To;
                pos.Black_Rooks ^= To;
                pos.Black_Bishops |= To;
                pos.Black_Bishops ^= To;
                pos.Black_Knights |= To;
                pos.Black_Knights ^= To;
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= To;
            }
        }
    }
    else
    {
        pos.Black_Pieces ^= From;
        pos.Black_Pieces |= To;
        if(pos.Black_Rooks & From)
        {
            pos.Black_Rooks ^= From;
            pos.Black_Rooks |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }
        if(pos.Black_Knights & From)
        {
            pos.Black_Knights ^= From;
            pos.Black_Knights |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }
        if(pos.Black_Bishops & From)
        {
            pos.Black_Bishops ^= From;
            pos.Black_Bishops |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }
        if(pos.Black_Pawns & From)
        {
            pos.Black_Pawns ^= From;
            //Black_Pawns |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }
        if(pos.Black_King & From)
        {
            pos.Black_King ^= From;
            pos.Black_King |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }
        if(pos.Black_Queens & From)
        {
            pos.Black_Queens ^= From;
            pos.Black_Queens |= To;
            if(pos.White_Pieces & To)
            {
                pos.White_Pieces ^= To;
                pos.White_Queens |= To;
                pos.White_Queens ^= To;
                pos.White_Rooks |= To;
                pos.White_Rooks ^= To;
                pos.White_Bishops |= To;
                pos.White_Bishops ^= To;
                pos.White_Knights |= To;
                pos.White_Knights ^= To;
                pos.White_Pawns |= To;
                pos.White_Pawns ^= To;
            }
        }

    }
    string Queen = "q";
    string Rook = "r";
    string Bishop = "b";
    string Knight = "n";
    if(Promotion_Type == Queen)
    {
        if(pos.Current_Turn)
            pos.White_Queens |= To;
        else
            pos.Black_Queens |= To;
    }
    if(Promotion_Type == Rook)
    {
        if(pos.Current_Turn)
            pos.White_Rooks |= To;
        else
            pos.Black_Rooks |= To;
    }
    if(Promotion_Type == Bishop)
    {
        if(pos.Current_Turn)
            pos.White_Bishops |= To;
        else
            pos.Black_Bishops |= To;
    }
    if(Promotion_Type == Knight)
    {
        if(pos.Current_Turn)
            pos.White_Knights |= To;
        else
            pos.Black_Knights |= To;
    }
    return 0;
}
string Engine_Info()
{
    string Version = "";
    const string months("Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec");
    string month, day, year;
    stringstream ss, date(__DATE__); // From compiler, format is "Sep 21 2008"
    cout << "Chess " << Version << setfill('0');
    if (Version.empty())
    {
        date >> month >> day >> year;
        cout << setw(2) << day << setw(2) << (1 + months.find(month) / 4) << year.substr(2);
    }
    return Version;
}
void Uci_Pv(int depth, int seldepth, Move best, int* matemoves, int time, int nodes)
{
		output.lock();
		cout << "info multipv 1 depth " << depth << " seldepth " << depth + seldepth << " score ";
        Log << "<< info multipv 1 depth " << depth << " seldepth " << depth + seldepth << " score ";
        if(best.Score == 10000)
        {
        	if(depth + 1 < *matemoves)
                {
                	cout << "mate " << ((depth + 1) / 2) - 1;
                    Log << "mate " << ((depth + 1) / 2) - 1;
                    *matemoves = depth + 1;
                }
            else
                {
                    cout << "mate " << (*matemoves / 2) - 1;
                    Log << "mate " << (*matemoves / 2) - 1;
                }
        }
        else if(best.Score == -10000)
        {
        	if(depth + 1 < *matemoves)
                {
                	cout << "mate " << -(((depth + 1) / 2) - 1);
                    Log << "mate " << -(((depth + 1) / 2) - 1);
                    *matemoves = depth + 1;
                }
            else
                {
                    cout << "mate " << -((*matemoves / 2) - 1);
                    Log << "mate " << -((*matemoves / 2) - 1);
                }
    	}
        else
        {
        cout << "cp " << best.Score;
        Log << "cp " << best.Score;
    	}
    	cout << " hashfull " << int((TT.count / 8388608.0) * 1000);
        cout << " pv " << ::PVline.Output() /*<< line.Output()*/;
        Log << " pv " << ::PVline.Output() /*<< line.Output()*/;
        cout << "time " << time << " nodes " << nodes << " nps " << (1000 *(nodes / (time + 1))) << endl;
        Log << "time " << time << " nodes " << nodes << " nps " << (1000 *(nodes / (time + 1))) << endl;
		output.unlock();
}
