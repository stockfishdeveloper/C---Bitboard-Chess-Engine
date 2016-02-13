using namespace std;
#include "Eval.h"
#include "Bitboard.h"
#include "Search.h"

//********************************************************************
//Piece Square Tables
//********************************************************************

//White Knights
const int Eval::WNpsqt[64] =
{
    -20, -5, -7, -2, -2, -7, -5, -25,
    -15, -2,  0,  0,  0,  0, -3, -5,
    -1,  -1,  7,  0,  0,  7,  0, -1,
    1,   2,  5,  5,  5,  5,  4,  1,
    1,   3,  6,  10, 10, 5,  5,  2,
    -2,   -1, 0,  25, 25, 0, -1, -3
    -10,  -8, -5, -3, -2, -2, -6, -8,
    -15, -13, -11, -9, -9, -11, -13, -15
};

//Black Knights
const int Eval::BNpsqt[64] =
{
    -15, -13, -11, -9, -9, -11, -13, -15,
    -10,  -8, -5,  -3, -2, -2,  -6,  -8,
    -2,   -1,  0,  25, 25,  0,  -1,  -3,
    1,   3,   6,  10, 10,  5,   5,   2,
    1,   2,  5,  5,  5,  5,  4,  1,
    -1,  -1,  7,  0,  0,  7,  0, -1,
    -15, -2,  0,  0,  0,  0, -3, -5,
    -20, -5, -7, -2, -2, -7, -5, -25
};

//White Pawns
const int Eval::WPpsqt[64] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 4, 6, 6, 4, 2, 2,
    3, 7, 9, 15, 15, 9, 7, 3,
    5, 6, 7, 8, 8, 7, 6, 5,
    25, 23, 22, 21, 21, 22, 23, 25,
    0, 0, 0, 0, 0, 0, 0, 0
};

//Black Pawns
const int Eval::BPpsqt[64] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    25, 23, 22, 21, 21, 22, 23, 25,
    2, 2, 3, 4, 4, 3, 2, 2,
    3, 4, 5, 6, 6, 5, 4, 3,
    5, 6, 9, 15, 15, 9, 6, 5,
    2, 2, 5, 8, 8, 5, 2, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

const int Eval::WKpsqt[64] =
{
    5, 25, -3, -10, -5, -5, 15, 5,
    -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};
const int Eval::BKpsqt[64] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5,
    5, 15, -5, -5, -10, -3, 25, 5
};
int White_Score = 0; //White's Score
int Black_Score = 0; //Black's Score
int wk = 0, bk = 0;
const int Doubled_Pawn_Penalty = 20;
//********************************************************************
//Material
//********************************************************************

//Evaluates the current position based on the bitboards in Bitboard.cpp
const int Eval::Evaluate_Position()
{
    
	White_Score = 0; //White's Score
    Black_Score = 0; //Black's Score
    wk = 0;
	bk = 0;
    //register int i = 0; //A little optimization
    White_Score += 100 * __builtin_popcountll(White_Pawns);
    White_Score += 300 * __builtin_popcountll(White_Knights);
    White_Score += 300 * __builtin_popcountll(White_Bishops);
    White_Score += 500 * __builtin_popcountll(White_Rooks);
    White_Score += 800 * __builtin_popcountll(White_Queens);
    
    Black_Score += 100 * __builtin_popcountll(Black_Pawns);
    Black_Score += 300 * __builtin_popcountll(Black_Knights);
    Black_Score += 300 * __builtin_popcountll(Black_Bishops);
    Black_Score += 500 * __builtin_popcountll(Black_Rooks);
    Black_Score += 800 * __builtin_popcountll(Black_Queens);
    
	     for(int i = 0; i < 64; i++)
    	{
    	if(!(GeneralBoard[i] & (White_Pieces | Black_Pieces))) continue;
    	
    	if(GeneralBoard[i] & White_Pieces)
    	{
        if(GeneralBoard[i] & White_King)
        wk = i;
        if(GeneralBoard[i] & White_Pawns) //For each white pawn on the board
        {
            White_Score += WPpsqt[i];
        }
        if(GeneralBoard[i] & White_Knights)
        {
            White_Score += WNpsqt[i];
        }
    }
    	else if(GeneralBoard[i] & Black_Pieces)
    	{
        if(GeneralBoard[i] & Black_Pawns) //For each black pawn on the board
        {
            Black_Score += BPpsqt[i];
        }
        if(GeneralBoard[i] & Black_Knights)
        {
            Black_Score += BNpsqt[i];
        }
        if(GeneralBoard[i] & Black_King)
        bk = i;
    }
        
    }
    
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & A_Pawn_Mask) - 1));
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & B_Pawn_Mask) - 1));
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & C_Pawn_Mask) - 1));
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & D_Pawn_Mask) - 1));
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & E_Pawn_Mask) - 1));
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & F_Pawn_Mask) - 1));
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & G_Pawn_Mask) - 1));
    White_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(White_Pawns & H_Pawn_Mask) - 1));
    
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & A_Pawn_Mask) - 1));
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & B_Pawn_Mask) - 1));
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & C_Pawn_Mask) - 1));
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & D_Pawn_Mask) - 1));
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & E_Pawn_Mask) - 1));
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & F_Pawn_Mask) - 1));
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & G_Pawn_Mask) - 1));
    Black_Score -= (Doubled_Pawn_Penalty * (__builtin_popcountll(Black_Pawns & H_Pawn_Mask) - 1));
    
    White_Score += WKpsqt[wk];
    Black_Score += BKpsqt[bk];
        
    return (White_Score - Black_Score); //Return the score from WHITE'S perspective
}
