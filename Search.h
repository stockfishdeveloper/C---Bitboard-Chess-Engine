#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include "Bitboard.h"
#include "MoveGen.h"
#include <iostream>
#include <chrono>
typedef std::chrono::milliseconds::rep TimePoint; // A value in milliseconds

class Move
{
        public:
                Bitboard From;
                Bitboard To;
                int Move_Type;
                int Score;
                int White_Temp_Move_From_Stack[60];
                int White_Temp_Move_To_Stack[60];
                int Black_Temp_Move_From_Stack[60];
                int Black_Temp_Move_To_Stack[60];
                int White_Temp_Move_Types[60];
                int Black_Temp_Move_Types[60];
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
                
                int Convert_Bitboard(Bitboard board)
                {
                	if(board == 0)
                    return 0;
                    for(int i = 0; i < 64; i++)
                    {
                            if(board & GeneralBoard[i])
                            return i;
                    }
                }
                
                Bitboard Unconvert_Int(int number)
                {
                        return GeneralBoard[number];
                }
                
                void Undo_Move();
                
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
                White_Temp_Move_Spacer = 0; 
                Black_Temp_Move_Spacer = 0;
                }               
};

class LINE
{
public:
    int cmove = 0;// Number of moves in the line.
    Move argmove[15];  // The line.
    int score = 0;
};
class Timer
{
		 /* return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now().time_since_epoch()).count();*/
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
	void Start_Clock()
	{
		begin_time = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now().time_since_epoch()).count();
	}
	int Stop_Clock()
	{
		end_time = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now().time_since_epoch()).count();
		return end_time - begin_time;
	}
};

namespace Search
{ 
Move Think(int wtime, int btime, int winc, int binc);
Move SearchMax(Move alpha, Move beta, int depth, LINE * pline);
Move SearchMin(Move alpha, Move beta, int depth, LINE * pline);
int Make_White_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type);
int Make_Black_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type);
//extern bool Fake_Current_Turn;
//extern bool Fake_Whte_Turn; 
//extern int White_Move_Score;
//extern int Black_Move_Score;
//extern Bitboard Move_From;
//extern Bitboard Move_To;
//extern int Best_Move;
extern Bitboard Nodes;
extern bool Searching;
extern LINE line;
extern int Depth;
extern int Seldepth;
void Order_Moves(bool White_Turn);
int Is_Mate();
void Clear();
extern int Time_Allocation;
extern bool STOP_SEARCHING_NOW;
extern bool Current_Turn;
extern bool White_Turn;
}

#endif
