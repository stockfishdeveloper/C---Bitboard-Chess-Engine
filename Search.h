#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include "Bitboard.h"

class Move
{
	public:
		Bitboard From = 0;
		Bitboard To = 0;
		int Move_Type = 0;
		int Score = 0;
		Bitboard White_Temp_Move_From_Stack[70];
		Bitboard White_Temp_Move_To_Stack[70];
		Bitboard Black_Temp_Move_From_Stack[70];
		Bitboard Black_Temp_Move_To_Stack[70];
		int White_Temp_Move_Types[70];
		int Black_Temp_Move_Types[70];
		int White_Temp_Move_Spacer = 0; 
		int Black_Temp_Move_Spacer = 0;
		
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
		int Undo_Move();
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
		}		
};

#include "Movegen.h"
Move Search(int depth, Move& Best_So_Far);
int Make_White_Search_Move(Bitboard& From, Bitboard& To, int Move_Type);
int Make_Black_Search_Move(Bitboard& From, Bitboard& To, int Move_Type);
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

#endif
