#include "Bitboard.h"
#include "UCI.h"
#include <thread> //For multithreading--must be using C++11 compiler
#include "Thread.h"//Threading header file
#include "Search.h"
#include "Perft.h"
#include "Zobrist.h"
#include "Nalimov\TBINDEX.h"
#include "MoveGen.h"
#include "Util.h"
#include "TransTable.h"
#include "Position.h"
using namespace std;
int CheckUci();
string UciCommand;
Bitboard Current_Rank = 72057594037927936;
ofstream Log("Log.txt");//For writing to a text file
int wtime = 0;
int btime = 0;
int Time_Usage = 0;
LINE PVline;
#include "Pawns.h"
int CheckUci()
{
    bool Is_Fen = false;
    
	while (cin >> UciCommand)
    {
        Log << ">> " << UciCommand << endl;
        if(UciCommand == "uci")
        {
            cout << "id name ";
            Engine_Info();
            cout << "\n";
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
        else if(UciCommand == "mate")
        {
        	int depth = 0;
        	cin >> depth;
        	cout << Search::MateSearch(&pos, -1, 1, depth) << endl;
		}
		else if(UciCommand == "bench")
        {
        	Benchmark();
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
        	string temp = UciCommand + " ";
        	string a = " ";
        	for(int i = 0; i < 5; i++)
        	{
        		cin >> a;
        		if(i != 4)
        			a += " ";
        		temp += a;
        	}
            Parse_Fen(temp);
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
        else if(UciCommand == "tb")
            {
            	string option;
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
            	while(pos.White_Pawns)
            	{
            		int b = Convert_Bitboard(pos.White_Pawns);
            		wpieces[wc++] = b;
            		pos.White_Pawns ^= GeneralBoard[b];
				}
				while(pos.White_Knights)
            	{
            		int b = Convert_Bitboard(pos.White_Knights);
            		wpieces[wc++] = b;
            		pos.White_Knights ^= GeneralBoard[b];
				}
				while(pos.White_Bishops)
            	{
            		int b = Convert_Bitboard(pos.White_Bishops);
            		wpieces[wc++] = b;
            		pos.White_Bishops ^= GeneralBoard[b];
				}
				while(pos.White_Rooks)
            	{
            		int b = Convert_Bitboard(pos.White_Rooks);
            		wpieces[wc++] = b;
            		pos.White_Rooks ^= GeneralBoard[b];
				}
				while(pos.White_Queens)
            	{
            		int b = Convert_Bitboard(pos.White_Queens);
            		wpieces[wc++] = b;
            		pos.White_Queens ^= GeneralBoard[b];
				}
				
				while(pos.Black_Pawns)
            	{
            		int b = Convert_Bitboard(pos.Black_Pawns);
            		bpieces[bc++] = b;
            		pos.Black_Pawns ^= GeneralBoard[b];
				}
				while(pos.Black_Knights)
            	{
            		int b = Convert_Bitboard(pos.Black_Knights);
            		bpieces[bc++] = b;
            		pos.Black_Knights ^= GeneralBoard[b];
				}
				while(pos.White_Bishops)
            	{
            		int b = Convert_Bitboard(pos.Black_Bishops);
            		bpieces[bc++] = b;
            		pos.Black_Bishops ^= GeneralBoard[b];
				}
				while(pos.Black_Rooks)
            	{
            		int b = Convert_Bitboard(pos.Black_Rooks);
            		bpieces[bc++] = b;
            		pos.Black_Rooks ^= GeneralBoard[b];
				}
				while(pos.Black_Queens)
            	{
            		int b = Convert_Bitboard(pos.Black_Queens);
            		bpieces[bc++] = b;
            		pos.Black_Queens ^= GeneralBoard[b];
				}
				wpieces[15] = Convert_Bitboard(pos.White_King);
				bpieces[15] = Convert_Bitboard(pos.Black_King);
				unsigned long tbindex = PfnIndCalcFun(tbid, pos.Current_Turn);
            	cout << "Index " << tbindex << endl;
            	cout << "Score is " << TbtProbeTable(tbid, 1, tbindex) << endl;
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
        	//Print_Board();
        }
    }

    return 0;
}


int Parse_Fen(string Fen)
{
	cout << Fen << endl;
	string str = Fen;
	string temp = str;
	string hold[6];
	int processed = 0;
	for(int j = 0; j < 6; j++)
	{
		int a = temp.find(" ") + 1;
		for(int i = 0; i < a; i++)
			hold[j] += temp[i];
		processed += a;
		temp = "";
		for(unsigned int p = processed; p < str.length(); p++)
			temp += str[p];	
	}
	hold[5] = "";
	for(unsigned int i = str.find_last_of(" ") + 1; i <= str.length(); i++)
		hold[5] += str[i];
		
	Search::Clear();
	//pos.Reset();
    
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
    for(unsigned int h = 0; h < (hold[0].length()); h++)
    {
        Current_Square = hold[0][h];
        Read_Fen(Current_Square);
    }
    Current_Rank = 72057594037927936;
    string Curr_Turn = hold[1];
    Log << Curr_Turn << endl;
    if(Curr_Turn.find("w") != string::npos)
    {
        pos.Current_Turn = true;
    }
    else
    {
        pos.Current_Turn = false;
    }
    string Legal_Castling = hold[2];
    Log << Legal_Castling << endl;
    pos.WhiteCanCastleK = false;
    pos.BlackCanCastleK = false;
    pos.WhiteCanCastleQ = false;
    pos.BlackCanCastleQ = false;
    for(unsigned int i = 0; i < Legal_Castling.length(); i++)
    {
    	if(Legal_Castling.find("K") != string::npos)
    		pos.WhiteCanCastleK = true;
    	if(Legal_Castling.find("k") != string::npos)
    		pos.BlackCanCastleK = true;
    	if(Legal_Castling.find("Q") != string::npos)
    		pos.WhiteCanCastleQ = true;
    	if(Legal_Castling.find("q") != string::npos)
    		pos.BlackCanCastleQ = true;
    }
     
    /*string En_Passant;
    cin >> En_Passant;
    Log << En_Passant << endl;
    int Pawn_Moves;
    cin >> Pawn_Moves;
    Log << Pawn_Moves << endl;
    int Move_Count;
    cin >> Move_Count;
    Log << Move_Count << endl;*/
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
	//pos.Reset();
    char First_Part[5];
    char Second_Part[5];
    string Promotion_Type;
    while(true)
    {
    	Move m;
    	cin.get();
        cin.get(First_Part, 3);
        Log << ">> " << First_Part;
        string F = "go";
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
        Bitboard Fr = 0;
        Bitboard T_o = 0;
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
        //pos.Current_Turn ^= 1;
    }
	return 0;
}

int Parse_Moves(string First, string Second, string PromotionType = "")
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
    Piece p = pos.Get_Piece_From_Bitboard(From);
    assert(p != NONE);
    Piece Captured = NONE;
    bool Castling = (From & (pos.White_King | pos.Black_King)) && (From & 1152921504606846992) && (To & 4899916394579099716);
    bool Promotion = ((From & pos.White_Pawns) && From & Seventh_Rank_White) || ((From & pos.Black_Pawns) && (From & Seventh_Rank_Black));
    if(pos.Current_Turn == true)
    {
    	if(To & pos.Black_Pieces)
    	{
    		Captured = pos.Get_Piece_From_Bitboard(To);
    		assert(Captured != NONE);
    	}
	}
	else
	{
		if(To & pos.White_Pieces)
		{
    		Captured = pos.Get_Piece_From_Bitboard(To);
    		assert(Captured != NONE);
    	}
	}
	if(pos.Current_Turn == true)
	{
		if(((pos.Black_Pawns << 8) & To) && (From & 1095216660480) && (pos.White_Pawns & From) && (!(pos.Black_Pieces & To)))
            {
                pos.Black_Pawns ^= (To >> 8);
                pos.Black_Pieces ^= (To >> 8);
                pos.White_Pawns |= To;
                pos.White_Pawns ^= From;
                pos.White_Pieces |= To;
                pos.White_Pieces ^= From;
                pos.Current_Turn ^= 1;
                return 0;
            }
    }
	else if(pos.Current_Turn == false)
	{
    	if(((pos.White_Pawns >> 8) & To) && (From & 4278190080) && (pos.Black_Pawns & From) && (!(pos.White_Pieces & To)))
            {
                pos.White_Pawns ^= (To << 8);
                pos.White_Pieces ^= (To << 8);
                pos.Black_Pawns |= To;
                pos.Black_Pawns ^= From;
                pos.Black_Pieces |= To;
                pos.Black_Pieces ^= From;
                pos.Current_Turn ^= 1;
                return 0;
            }
    }
    if(p == WK)
	{ 
		pos.WhiteCanCastleK = false;
		pos.WhiteCanCastleQ = false;
	}
	else if(p == BK)
	{ 
		pos.BlackCanCastleK = false;
		pos.BlackCanCastleQ = false;
	}
	if(p == WR && From == 1) pos.WhiteCanCastleQ = false;
	if(p == WR && From == 128) pos.WhiteCanCastleK = false;
	if(p == BR && From == 72057594037927936) pos.BlackCanCastleQ = false;
	if(p == BR && From == 9223372036854775808) pos.BlackCanCastleK = false;
	Move m(p, Captured, From, To, Castling, Promotion);
    if(PromotionType != "")
    {
    	if(PromotionType.find("q") != string::npos)
    		m.PromotionType = pos.Current_Turn ? WQ : BK;
    	else if(PromotionType.find("r") != string::npos)
    		m.PromotionType = pos.Current_Turn ? WR : BR;
    	else if(PromotionType.find("b") != string::npos)
    		m.PromotionType = pos.Current_Turn ? WB : BB;
    	else if(PromotionType.find("n") != string::npos)
    		m.PromotionType = pos.Current_Turn ? WN : BN;
	}
    pos.Make_Move(m);
	
    return 0;
}




void Engine_Info()
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
