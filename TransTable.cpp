#include "Bitboard.h"
#include "Search.h"
#include "TransTable.h"
#include <cstdlib>
#include <ctime>
enum NodeType { Alpha, Exact, Beta };
class TTEntry
{
	Bitboard key;
	int depth;
	int score;
	Move best;
};
class TranspositionTable
{
	TTEntry table[100000];
	TTEntry * probe(const Bitboard key);
};

Bitboard zobrist[64][6][2];
//TODO: Castling added to Zobrist hashing
void Init_Zobrist()
{
	srand(time(0));
	for(int i = 0; i < 64; i++)
	{
		zobrist[i][0][0] = rand();
	
	for(int j = 0; j < 6; j++)
	{
		zobrist[0][j][0] = rand();
	for(int h = 0; h < 2; h++)
	{
		zobrist[0][0][h] = rand();
	}
	}
	}
}

//TranspositionTable TT;

