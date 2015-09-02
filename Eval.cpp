using namespace std;
#include "Bitboard.h"
#include "Eval.h"

int White_Score = 0;
int Black_Score = 0;

int Evaluate_Position()
{
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & White_Pawns)
		White_Score += 1;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & White_Knights)
		White_Score += 3;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & White_Bishops)
		White_Score += 3;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & White_Rooks)
		White_Score += 5;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & White_Queens)
		White_Score += 8;
	}
	
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & Black_Pawns)
		Black_Score += 1;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & Black_Knights)
		Black_Score += 3;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & Black_Bishops)
		Black_Score += 3;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & Black_Rooks)
		Black_Score += 5;
	}
	for(register int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & Black_Queens)
		Black_Score += 8;
	}
	return (White_Score - Black_Score);
}
