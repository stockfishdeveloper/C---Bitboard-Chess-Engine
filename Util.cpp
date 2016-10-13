#include "Util.h"
short lsb(register Bitboard b)
{
	if(b == 0) return 0;
	register short temp = 0;
	while(!(b & 1))
	{
		b >>= 1;
		++temp;
	}
	return temp;
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
const short Convert_Bitboard(const Bitboard& board)
    {
        if(board == 0)
            return 0;
        for(short i = 0; i < 64; i++)
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
int test_lsb(Bitboard b)
{
	if(b == 0) return 0;
	int temp = 0;
	while(!(b & 1))
	{
		b >>= 1;
		++temp;
	}
	return temp;
}
