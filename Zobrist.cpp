#include "Bitboard.h"
#include "Zobrist.h"
Bitboard zobrist[64][12][2];
Bitboard rand64() 
{
    static Bitboard next = 1;
    next = next * 1103515245 + 12345;
    return next;
}
void Init_Zobrist()
{
	srand(time(0));
	for(int i = 0; i < 64; i++)
	{
		zobrist[i][0][0] = rand64();
		for(int j = 0; j < 6; j++)
			{
				zobrist[i][j][0] = rand64();
				for(int h = 0; h < 2; h++)
					{
						zobrist[i][j][h] = rand64();
					}
			}
	}
}
Bitboard Get_Current_Hash_Key()
{
	Bitboard key = 0;
	for(int i = 0; i < 64; i++)
	{
		if(White_Pawns & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(White_Knights & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(White_Bishops & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(White_Rooks & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(White_Queens & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(White_King & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(Black_Pawns & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(Black_Knights & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(Black_Bishops & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(Black_Rooks & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(Black_Queens & GeneralBoard[i])
		key ^= GeneralBoard[i];
		if(Black_King & GeneralBoard[i])
		key ^= GeneralBoard[i];
	}
	key ^= Search::Current_Turn;
	return key;
}
