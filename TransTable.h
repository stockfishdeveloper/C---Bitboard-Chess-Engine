#ifndef TRANS_TABLE_H_
#define TRANS_TABLE_H_
#include "Bitboard.h"
#include "Search.h"
enum NodeType { Alpha, Exact, Beta };
class TTEntry
{
	public:
	Bitboard key;
	int depth;
	int score;
	Move best;
	NodeType nodetype;
};
class TranspositionTable
{
	public:
	TTEntry table[100000];
	int count = 0;
	TTEntry * probe(const Bitboard key);
	void save(int depth, int score, Move best, NodeType n, Bitboard haskkey);
	void clear();
};
extern TranspositionTable TT;
#endif
