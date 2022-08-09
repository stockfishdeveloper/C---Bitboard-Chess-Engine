#ifndef PAWNS_H_
#define PAWNS_H_
#include "Bitboard.h"
#include "Position.h"

class PawnEntry
{
	public:

	PawnEntry() {
		key = 0;
		score_white = 0;
		score_black = 0;
	}
	Bitboard key;
	int score_white;
	int score_black;
};

class PawnHash
{
	public:
	PawnEntry table[16777216];
	PawnEntry * probe(const Bitboard key);
	void save(int scorewhite, int scoreblack, Bitboard haskkey);
	void clear();
};

extern PawnHash pawnhash;
Bitboard Get_Pawn_Hash(Position* position);

extern int hashhits;
extern int hashmisses;

#endif
