#include "Bitboard.h"
#include "Endgame.h"
#include "Position.h"

const int Center_Distance[64] =
{
  6, 5, 4, 3, 3, 4, 5, 6,
  5, 4, 3, 2, 2, 3, 4, 5,
  4, 3, 2, 1, 1, 2, 3, 4,
  3, 2, 1, 0, 0, 1, 2, 3,
  3, 2, 1, 0, 0, 1, 2, 3,
  4, 3, 2, 1, 1, 2, 3, 4,
  5, 4, 3, 2, 2, 3, 4, 5,
  6, 5, 4, 3, 3, 4, 5, 6
};

int Drive_To_Corner(Bitboard Losing_King)
{
	for(int i = 0; i < 64; i++)
		{
			if(Losing_King & GeneralBoard[i])
			{
				return Center_Distance[i];
			}		
		}
	return 0;
}

int Dist_Betw(Bitboard sq1, Bitboard sq2)
{
	int wk = 0, bk = 0;
	for(int i = 0; i < 64; i++)
		{
			if(sq2 & GeneralBoard[i])
			{
				bk = i;
			}		
		}
		for(int i = 0; i < 64; i++)
		{
			if(sq1 & GeneralBoard[i])
			{
				wk = i;
			}		
		}
   int file1, file2, rank1, rank2;
   int rankDistance, fileDistance;
   file1 = wk  & 7;
   file2 = bk  & 7;
   rank1 = wk >> 3;
   rank2 = bk >> 3;
   rankDistance = abs (rank2 - rank1);
   fileDistance = abs (file2 - file1);
   return rankDistance + fileDistance;
}
