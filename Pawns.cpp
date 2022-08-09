#include "Pawns.h"
PawnHash pawnhash;

PawnEntry * PawnHash::probe(const Bitboard key1)
{
	int index = key1 % 16777216;
	if(pawnhash.table[index].key == key1)
	return &table[index];
	else
	return NULL;
}

void PawnHash::save(int scorewhite, int scoreblack, Bitboard hashkey)
{
	int index = hashkey % 16777216;
	PawnEntry p;
	p.score_white = scorewhite;
	p.score_black = scoreblack;
	p.key = hashkey;
	pawnhash.table[index] = p;
}

void PawnHash::clear()
{
	PawnEntry p = PawnEntry();
	for(int i = 0; i < 16777216; i++)
	{
		pawnhash.table[i] = p;
	}
}

Bitboard Get_Pawn_Hash(Position* position)
{
	return (position->White_Pawns | position->Black_Pawns);
}

int hashhits = 0;
int hashmisses = 0;
