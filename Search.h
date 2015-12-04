#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include "Bitboard.h"
#include "MoveGen.h"
#include <iostream>

class Move
{
	public:
		Bitboard From;
		Bitboard To;
		int Move_Type;
		float Score;
		Bitboard White_Temp_Move_From_Stack[70];
		Bitboard White_Temp_Move_To_Stack[70];
		Bitboard Black_Temp_Move_From_Stack[70];
		Bitboard Black_Temp_Move_To_Stack[70];
		int White_Temp_Move_Types[70];
		int Black_Temp_Move_Types[70];
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
		
		void Undo_Move()
		{
		White_Pieces = White_Pieces2; 
		Black_Pieces = Black_Pieces2; 
		White_King = White_King2;
		Black_King = Black_King2;
		White_Queens = White_Queens2;
		White_Rooks = White_Rooks2;
		White_Bishops = White_Bishops2;
		White_Knights = White_Knights2;
		White_Pawns = White_Pawns2;
		Black_Queens = Black_Queens2;
		Black_Rooks = Black_Rooks2;
		Black_Bishops = Black_Bishops2;
		Black_Knights = Black_Knights2;
		Black_Pawns = Black_Pawns2;
		White_Move_Spacer = White_Temp_Move_Spacer;
		Black_Move_Spacer = Black_Temp_Move_Spacer;
		for(int h = 0; h < White_Temp_Move_Spacer; h++)
			{
				White_Move_From_Stack[h] = White_Temp_Move_From_Stack[h];
				White_Move_To_Stack[h] = White_Temp_Move_To_Stack[h];
				White_Move_Types[h] = White_Temp_Move_Types[h];
			}
			
		for(int h = 0; h < Black_Temp_Move_Spacer; h++)
		{
		Black_Move_From_Stack[h] = Black_Temp_Move_From_Stack[h];
		Black_Move_To_Stack[h] = Black_Temp_Move_To_Stack[h];
		Black_Move_Types[h] = Black_Temp_Move_Types[h];
		}
		Current_Turn ^= 1;
		White_Turn ^= 1;
}
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
		Score = 0.0;
		White_Temp_Move_Spacer = 0; 
		Black_Temp_Move_Spacer = 0;
		}		
};

class LINE
{
public:
	int cmove = 0;// Number of moves in the line.
    Move argmove[15];  // The line.
    float score = 0.0;
};

#include "Movegen.h"
Move Think(int wtime, int btime, int winc, int binc);
Move SearchMax(Move alpha, Move beta, int depth, LINE * pline);
Move SearchMin(Move alpha, Move beta, int depth, LINE * pline);
int Make_White_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type);
int Make_Black_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type);
extern bool Fake_Current_Turn;
extern bool Fake_Whte_Turn; 
extern int White_Move_Score;
extern int White_Static_Score;
extern int Black_Move_Score;
extern int Black_Static_Score;
extern Bitboard Move_From;
extern Bitboard Move_To;
extern int Leaf_Score;
extern int Best_Move;
extern int Nodes;
extern bool Searching;
extern LINE line;
extern int Depth;
extern int Seldepth;
extern void Order_Moves(bool White_Turn);
extern float Is_Mate();
extern int Time_Allocation;
extern bool STOP_SEARCHING_NOW;

#endif
