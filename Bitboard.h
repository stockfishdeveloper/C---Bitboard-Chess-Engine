#ifndef Bitboard_h_
#define Bitboard_h_
#include <string>
#include <iostream>

typedef unsigned long long int Bitboard;
using namespace std;

//This is an array containing one bit set in each bitboard corresponding to the index of the array; the square A1 is the first (0th) element
extern const Bitboard GeneralBoard[64];

extern Bitboard Eigth_Rank_White;//For masking out pawn pushes to the eigth rank for each side--white and black
extern Bitboard Eigth_Rank_Black;
extern Bitboard Seventh_Rank_White;
extern Bitboard Seventh_Rank_Black;
extern Bitboard CurrZobkey;

//Contains the squares that a knight on a given index can move to. For example, the 0th element has the bits of b3 and c2 set
extern const Bitboard Knight_Lookup_Table[64];

//This one is the same as the Knight_Lookup_Table except that this one is for kings
extern const Bitboard King_Lookup_Table[64];

extern Bitboard H_Pawn_Mask;//For masking out A and H pawns so that they cannot capture off of the end of the board
extern Bitboard A_Pawn_Mask;
extern Bitboard G_Pawn_Mask;
extern Bitboard B_Pawn_Mask;
extern Bitboard F_Pawn_Mask;
extern Bitboard C_Pawn_Mask;
extern Bitboard E_Pawn_Mask;
extern Bitboard D_Pawn_Mask;

//Contains a string representation of the squares of the chess board; for example, the 0th element in the array is "a1"
extern string PlayerMoves[64];

void Print_Board();
#endif

