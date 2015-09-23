#ifndef Make_Move_H_Included
#define Make_Move_H_Included
#include "Bitboard.h"
extern bool Current_Turn;
extern bool White_Turn;
int Generate_White_Knight_Moves();
int Generate_Black_Knight_Moves();
int Generate_White_King_Moves();
int Generate_Black_King_Moves();
int Generate_White_Pawn_Moves();
int Generate_Black_Pawn_Moves();
int Generate_White_Rook_Moves();
int Generate_Black_Rook_Moves();
int Generate_White_Bishop_Moves();
int Generate_Black_Bishop_Moves();
int Generate_White_Queen_Moves();
int Generate_Black_Queen_Moves();
bool White_Is_Legal(Bitboard& From_Square, Bitboard& To_Square, int Move_Type);//Tests for legality
bool Black_Is_Legal(Bitboard& From_Square, Bitboard& To_Square, int Move_Type);//Tests for legality
extern bool Is_Legal;
extern Bitboard White_Move_From_Stack[70];//Move stack is just an array of Bitboards(64-bit integers) containing only one bit set in each--the from square or the to square
extern Bitboard White_Move_To_Stack[70];
extern Bitboard Black_Move_From_Stack[70];
extern Bitboard Black_Move_To_Stack[70];
extern int White_Move_Types[70];//Array of normal integers that keeps track of the type of each move
extern int Black_Move_Types[70];

extern Bitboard WhiteKingCount[8];//Array which is large enough to contain as many legal moves at a time for all of the pieces of that type as possible
extern Bitboard BlackKingCount[8];
extern Bitboard WhiteKnightCount[40];
extern Bitboard BlackKnightCount[40];
extern Bitboard WhitePawnCount[20];
extern Bitboard BlackPawnCount[20];
extern Bitboard WhiteRookCount[20];
extern Bitboard BlackRookCount[20];
extern Bitboard WhiteBishopCount[20];
extern Bitboard BlackBishopCount[20];
extern Bitboard WhiteQueenCount[28];
extern Bitboard BlackQueenCount[28];

extern int White_Knight_Spacer;//Keeps track of the number of psuedo legal moves for each type of piece
extern int Black_Knight_Spacer;
extern int White_King_Spacer;
extern int Black_King_Spacer;
extern int White_Pawn_Spacer;
extern int Black_Pawn_Spacer;
extern int White_Rook_Spacer;
extern int Black_Rook_Spacer;
extern int White_Bishop_Spacer;
extern int Black_Bishop_Spacer;
extern int White_Queen_Spacer;
extern int Black_Queen_Spacer;

int Stack_White_Knight_Moves();//Function declarations
int Stack_Black_Knight_Moves();
int Stack_White_King_Moves();
int Stack_Black_King_Moves();
int Stack_White_Pawn_Moves();
int Stack_Black_Pawn_Moves();
int Stack_White_Rook_Moves();
int Stack_Black_Rook_Moves();
int Stack_White_Bishop_Moves();
int Stack_Black_Bishop_Moves();
int Stack_White_Queen_Moves();
int Stack_Black_Queen_Moves();

extern int White_Move_Spacer; // Keeps a "record" of the last move put on the stack so that it knows which index of the array to put the next move in
extern int Black_Move_Spacer;
extern bool WhiteHasCastled;
extern bool BlackHasCastled;

#endif
