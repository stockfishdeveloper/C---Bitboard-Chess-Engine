#include "Bitboard.h"
#include "Search.h"
#include "TransTable.h"

TranspositionTable TT;
TTEntry * TranspositionTable::probe(const Bitboard key1)
{
	int index = key1 % 100000;
	if(TT.table[index].key == key1)
	return &table[index];
	else
	return NULL;
}
void TranspositionTable::save(int depth1, int score1, Move best1, NodeType n, Bitboard hashkey)
{
	int index = hashkey % 100000;
	if(TT.table[index].depth < depth1)
	{
		TTEntry tt;
		tt.depth = depth1;
		tt.score = score1;
		tt.best = best1;
		tt.key = hashkey;
		tt.nodetype = n;
		TT.table[index] = tt;
		TT.count++;
	}
}
void TranspositionTable::clear()
{
	//std::memset(TT.table, 0, 1000 * sizeof(TTEntry));
}
