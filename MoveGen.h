#ifndef Make_Move_H_Included
#define Make_Move_H_Included
#include "Bitboard.h"
#include "Position.h"
#include <iostream>
void Generate_White_Moves(const bool caps, Position* position);
void Generate_Black_Moves(const bool caps, Position* position);
bool White_Is_Legal(Position& position, Move move);//Tests for legality
bool Black_Is_Legal(Position& position, Move move);//Tests for legality
extern bool Is_Legal;
#endif
