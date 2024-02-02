#ifndef PERFT_H_INCLUDED
#define PERFT_H_INCLUDED
#include "Position.h"

void Print_Move_List(int i);
int Root_Perft(int depth);
int Perft(Position& posit, int depth);
#endif
