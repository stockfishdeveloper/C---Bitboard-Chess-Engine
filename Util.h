#ifndef UTIL_H
#define UTIL_H
#include "Bitboard.h"
#include "Search.h"
int lsb(const Bitboard& b);
enum Movetype { Capture, Promotion, Normal };
Movetype Get_Move_Type(Move& m);
const int Convert_Bitboard(const Bitboard& board);
const Bitboard Unconvert_Int(const int& number);
#endif
