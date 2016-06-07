#include "Util.h"
int lsb(const Bitboard& b)
{
	for(int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & b)
		return i;
	}
}
