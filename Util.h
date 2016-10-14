#ifndef UTIL_H
#define UTIL_H
#include "Bitboard.h"
#include "Search.h"
short lsb(Bitboard b);
int test_lsb(Bitboard b);
enum Movetype { Capture, Promotion, Normal };
Movetype Get_Move_Type(Move& m);
const short Convert_Bitboard(const Bitboard& board);
const Bitboard Unconvert_Int(const int& number);
void Benchmark();
#endif
