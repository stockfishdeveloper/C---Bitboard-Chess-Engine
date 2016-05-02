#ifndef Make_Move_H_Included
#define Make_Move_H_Included
#include "Bitboard.h"
#include <iostream>
extern bool Current_Turn;
void Generate_White_Moves(const bool caps);
void Generate_Black_Moves(const bool caps);
bool White_Is_Legal(const Bitboard& From_Square, const Bitboard& To_Square, const int Move_Type);//Tests for legality
bool Black_Is_Legal(const Bitboard& From_Square, const Bitboard& To_Square, const int Move_Type);//Tests for legality
extern bool Is_Legal;
extern Bitboard White_Move_From_Stack[100];//Move stack is just an array of Bitboards(64-bit integers) containing only one bit set in each--the from square or the to square
extern Bitboard White_Move_To_Stack[100];
extern Bitboard Black_Move_From_Stack[100];
extern Bitboard Black_Move_To_Stack[100];
extern int White_Move_Types[100];//Array of normal integers that keeps track of the type of each move
extern int Black_Move_Types[100];

extern int White_Move_Spacer; // Keeps a "record" of the last move put on the stack so that it knows which index of the array to put the next move in
extern int Black_Move_Spacer;
extern bool WhiteCanCastleK;
extern bool WhiteCanCastleQ;
extern bool BlackCanCastleK;
extern bool BlackCanCastleQ;

#endif
