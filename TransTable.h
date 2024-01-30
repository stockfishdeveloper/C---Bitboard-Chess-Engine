#ifndef TRANS_TABLE_H_
#define TRANS_TABLE_H_
#include "Bitboard.h"
#include "Search.h"

enum NodeType {
	Alpha, Exact, Beta
};

class TTMove {
public:
	Bitboard From;
	Bitboard To;
};

class TTEntry {
public:
	int depth;
	int score;
	Bitboard key;
	TTMove best;
	NodeType nodetype;
};

class TranspositionTable {
public:
	int count = 0;
	TTEntry table[8388608];

	void save(int depth, int score, Move best, NodeType n, Bitboard haskkey);
	void clear();
	TTEntry* probe(const Bitboard key);
};

extern TranspositionTable TT;
#endif
