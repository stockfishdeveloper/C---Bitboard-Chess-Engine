#include "Util.h"
int lsb(const Bitboard& b)
{
	for(int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & b)
		return i;
	}
}
Movetype Get_Move_Type(Move& m)
{
	if(m.Promotion)
		return Promotion;
	if(m.C != NONE)
		return Capture;
	else
		return Normal;
}
const int Convert_Bitboard(const Bitboard& board)
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
const Bitboard Unconvert_Int(const int& number)
	{
        return GeneralBoard[number];
    }
