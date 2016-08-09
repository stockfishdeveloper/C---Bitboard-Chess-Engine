#ifndef TRANS_TABLE_H_
#define TRANS_TABLE_H_
#include "Bitboard.h"
#include "Search.h"
enum NodeType { Alpha, Exact, Beta };
class TTMove
{
	public:
		Bitboard From;
		Bitboard To;
};
class TTEntry
{
	public:
	//TTEntry() : key(0), depth(0), score(0), nodetype(Exact), visited(0) {}
	Bitboard key;
	int depth;
	int score;
	TTMove best;
	NodeType nodetype;
};
class TranspositionTable
{
	public:
	TTEntry table[8388608];
	int count = 0;
	TTEntry * probe(const Bitboard key);
	void save(int depth, int score, Move best, NodeType n, Bitboard haskkey);
	void clear();
};
extern TranspositionTable TT;
#endif
