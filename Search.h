#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include "Bitboard.h"
#include "MoveGen.h"
#include "Position.h"
#include <cassert>
#include <iostream>
#include <chrono>
#include <string>

//const int INF = 2147483647;
const int INF = 10000000;
typedef std::chrono::milliseconds::rep TimePoint; // A value in milliseconds

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
                }
            }
            for( int h = 0; h < 64; h++)
            {
                if(GeneralBoard[h] & argmove[i].To)
                {
                    f += PlayerMoves[h];
                    if(argmove[i].PromotionType != NONE)
                    {
                    	switch(argmove[i].PromotionType)
                    	{
                    		case WN:
                    			f += "n";
                    			break;
                    		case WB:
                    			f += "b";
                    			break;
                    		case WR:
                    			f += "r";
                    			break;
                    		case WQ:
                    			f += "q";
                    			break;
                    		case BN:
                    			f += "n";
                    			break;
							case BB:
                    			f += "b";
                    			break;
                    		case BR:
                    			f += "r";
                    			break;
                    		case BQ:
                    			f += "q";
                    			break;
                    		default:
                    			break;
						}
					}
                    f += " ";
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
Move Think(int wtime, int btime, int winc, int binc, int Maxdepth = 60);
int AlphaBeta(Position* position, int alpha, int beta, int depth, LINE * pline, bool PvNode);
int QuiescenceSearch(Position* posit, int alpha, int beta, int depth);
int MateSearch(Position* posit, int alpha, int beta, int depth);
int Get_Move_Score(Move& m);
extern Bitboard Nodes;
extern bool Searching;
extern LINE line;
extern int Depth;
extern int Seldepth;
int Is_Mate(Position* position);
void Clear();
extern bool Output_Pv;
extern int Time_Allocation;
extern bool STOP_SEARCHING_NOW;
}

#endif
