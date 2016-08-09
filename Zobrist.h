#ifndef ZOBRIST_H_
#define ZOBRIST_H_
#include <cstdlib>
#include <ctime>
#include "Bitboard.h"
#include "Search.h"
extern Bitboard zobrist[64][12][2];
extern void Init_Zobrist();
extern Bitboard rand64();
Bitboard Get_Current_Hash_Key(Position* position);
#endif
