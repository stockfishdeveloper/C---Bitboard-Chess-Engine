#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include "Bitboard.h"
#include "MoveGen.h"
#include <cassert>
#include <iostream>
#include <chrono>
#include <string>

typedef std::chrono::milliseconds::rep TimePoint; // A value in milliseconds
class Move
{
public:
    Bitboard From;
    Bitboard To;
    int Move_Type;
    int Score;
    int White_Temp_Move_From_Stack[100];
    int White_Temp_Move_To_Stack[100];
    int Black_Temp_Move_From_Stack[100];
    int Black_Temp_Move_To_Stack[100];
    int White_Temp_Move_Types[100];
    int Black_Temp_Move_Types[100];
    int White_Temp_Move_Spacer;
    int Black_Temp_Move_Spacer;

    Bitboard White_Pieces2;
    Bitboard Black_Pieces2;
    Bitboard White_King2;
    Bitboard Black_King2;
    Bitboard White_Queens2;
    Bitboard White_Rooks2;
    Bitboard White_Bishops2;
    Bitboard White_Knights2;
    Bitboard White_Pawns2;
    Bitboard Black_Queens2;
    Bitboard Black_Rooks2;
    Bitboard Black_Bishops2;
    Bitboard Black_Knights2;
    Bitboard Black_Pawns2;

	Bitboard Zobrist;
	const int Convert_Bitboard(const Bitboard& board) const
    {
        if(board == 0)
            return 0;
        for(int i = 0; i < 64; i++)
        {
            if(board & GeneralBoard[i])
                return i;
        }
        return 0;
    }
	const Bitboard Unconvert_Int(const int& number) const
	{
        return GeneralBoard[number];
    }
	void Undo_Move();
	Move(int){};
    Move()
    {
        White_Pieces2 = White_Pieces;
        Black_Pieces2 = Black_Pieces;
        White_King2 = White_King;
        Black_King2 = Black_King;
        White_Queens2 = White_Queens;
        White_Rooks2 = White_Rooks;
        White_Bishops2 = White_Bishops;
        White_Knights2 = White_Knights;
        White_Pawns2 = White_Pawns;
        Black_Queens2 = Black_Queens;
        Black_Rooks2 = Black_Rooks;
        Black_Bishops2 = Black_Bishops;
        Black_Knights2 = Black_Knights;
        Black_Pawns2 = Black_Pawns;
        From = 0;
        To = 0;
        Move_Type = 0;
        Score = 0;
        White_Temp_Move_Spacer = White_Move_Spacer;
			for(int h = 0; h < White_Move_Spacer; h++)
    		{
        		White_Temp_Move_From_Stack[h] = Convert_Bitboard(White_Move_From_Stack[h]);
        		White_Temp_Move_To_Stack[h] = Convert_Bitboard(White_Move_To_Stack[h]);
        		White_Temp_Move_Types[h] = White_Move_Types[h];
    		}
    	Black_Temp_Move_Spacer = Black_Move_Spacer;
    	for(int h = 0; h < Black_Move_Spacer; h++)
    		{
        		Black_Temp_Move_From_Stack[h] = Convert_Bitboard(Black_Move_From_Stack[h]);
        		Black_Temp_Move_To_Stack[h] = Convert_Bitboard(Black_Move_To_Stack[h]);
        		Black_Temp_Move_Types[h] = Black_Move_Types[h];
    		}
    	
		
    }
};

class LINE
{
public:
    int cmove;// Number of moves in the line.
    Move argmove[20];  // The line.
    int score;
    LINE()
    {
    	cmove = 0;
    	score = 0;
	}
    string Output()
    {
        string f = "";
        for(int i = 0; i < cmove; i++)
        {
            for( int h = 0; h < 64; h++)
            {
                if(GeneralBoard[h] & argmove[i].From)
                {
                    f += PlayerMoves[h];
                    //cout << PlayerMoves[h];
                    //Log << PlayerMoves[h];
                }
            }
            for( int h = 0; h < 64; h++)
            {
                if(GeneralBoard[h] & argmove[i].To)
                {
                    f += PlayerMoves[h];
                    f += " ";
                    //cout << PlayerMoves[h] << " ";
                    //Log << PlayerMoves[h] << " ";
                }
            }
        }
        return f;
    }
};
class Timer
{
	public:
    TimePoint begin_time;
    TimePoint end_time;
    Timer()
    {
        begin_time = std::chrono::duration_cast<std::chrono::milliseconds>
                     (std::chrono::steady_clock::now().time_since_epoch()).count();
        end_time = std::chrono::duration_cast<std::chrono::milliseconds>
                   (std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    ~Timer(){};
    void Start_Clock()
    {
        begin_time = std::chrono::duration_cast<std::chrono::milliseconds>
                     (std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    int Stop_Clock()
    {
        end_time = std::chrono::duration_cast<std::chrono::milliseconds>
                   (std::chrono::steady_clock::now().time_since_epoch()).count();
                   return end_time;
    }
    int Get_Time()
    {
        return (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::steady_clock::now().time_since_epoch()).count() - begin_time);
    }
};

namespace Search
{
Move Think(int wtime, int btime, int winc, int binc);
int AlphaBeta(int alpha, int beta, int depth, LINE * pline, bool donullmove);
int QuiescenceSearch(int alpha, int beta, int depth);
//int SearchMax(int alpha, int beta, int depth, LINE * pline, bool donullmove);
//int SearchMin(int alpha, int beta, int depth, LINE * pline, bool donullmove);
//int QuiesceMax(int alpha, int beta, int depth);
//int QuiesceMin(int alpha, int beta, int depth);
int Make_White_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type);
int Make_Black_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type);
int Get_Move_Score(Move& m, bool turn);
extern Bitboard Nodes;
extern bool Searching;
extern LINE line;
extern int Depth;
extern int Seldepth;
int Is_Mate();
void Clear();
extern bool Output_Pv;
extern int Time_Allocation;
extern bool STOP_SEARCHING_NOW;
extern bool Current_Turn;
}

#endif
