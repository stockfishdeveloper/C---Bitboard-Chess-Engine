using namespace std;
#include "Eval.h"
#include "Bitboard.h"
#include "Endgame.h"
#include "Search.h"

//********************************************************************
//Piece Square Tables
//********************************************************************

//White Knights
const int Eval::WNpsqt[64] =
{
    -50,-40,-20,-30,-30,-20,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    50,-40,-30,-30,-30,-30,-40,-50
};

//Black Knights
const int Eval::BNpsqt[64] =
{
    50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-20,-30,-30,-20,-40,-50
};

//White Pawns
const int Eval::WPpsqt[64] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10,-25,-25, 10, 10,  5,
    5, -5,-10,  0,  0,-10, -5,  5,
    5,  5, 10, 27, 27, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0,  0,  0,  0,  0,  0,  0,  0
};

//Black Pawns
const int Eval::BPpsqt[64] =
{
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 27, 27, 10,  5,  5,
     0,  0,  0, 25, 25,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-25,-25, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

const int Eval::WKpsqt[64] =
{
    20,  30,  10,   0,   0,  10,  30,  20,
    20,  20,   0,   0,   0,   0,  20,  20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30
};
const int Eval::BKpsqt[64] =
{
  -30, -40, -40, -50, -50, -40, -40, -30,
  -30, -40, -40, -50, -50, -40, -40, -30,
  -30, -40, -40, -50, -50, -40, -40, -30,
  -30, -40, -40, -50, -50, -40, -40, -30,
  -20, -30, -30, -40, -40, -30, -30, -20,
  -10, -20, -20, -20, -20, -20, -20, -10,
   20,  20,   0,   0,   0,   0,  20,  20,
   20,  30,  10,   0,   0,  10,  30,  20
};

const int Eval::WBpsqt[64] =
{
	-20,-10,-40,-10,-10,-40,-10,-20,
	-10,  5,  0,  0,  0,  0,  5,-10,
	-10, 10, 10, 10, 10, 10, 10,-10,
	-10,  0, 10, 10, 10, 10,  0,-10,
	-10,  5,  5, 10, 10,  5,  5,-10,
	-10,  0,  5, 10, 10,  5,  0,-10,
	-10,  0,  0,  0,  0,  0,  0,-10,
	-20,-10,-10,-10,-10,-10,-10,-20
};
const int Eval::BBpsqt[64] = 
{
	-20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-40,-10,-10,-40,-10,-20
};
int White_Score = 0; //White's Score
int Black_Score = 0; //Black's Score
int wk = 0, bk = 0;
const int Doubled_Pawn_Penalty = 10;
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
        		White_Score += WPpsqt[i];
            if(GeneralBoard[i] & White_Knights)
        	    White_Score += WNpsqt[i];
        	if(GeneralBoard[i] & White_Bishops)
			    White_Score += WBpsqt[i];
			continue;    
        }
    	else if(GeneralBoard[i] & Black_Pieces)
    		{
        		if(GeneralBoard[i] & Black_Pawns) //For each black pawn on the board
        			Black_Score += BPpsqt[i];
                if(GeneralBoard[i] & Black_Knights)
                	Black_Score += BNpsqt[i];
                if(GeneralBoard[i] & Black_King)
        			bk = i;
        		if(GeneralBoard[i] & Black_Bishops)
                	Black_Score += BBpsqt[i];
				continue;		
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
    if(__builtin_popcountll(White_Pieces | Black_Pieces) <= 10)
                {
                	if(White_Score > Black_Score)
                	{
                	White_Score  += (Drive_To_Corner(false));
					White_Score -= Dist_Betw(White_King, Black_King);
					}
                	else
                	{
                	Black_Score  += (Drive_To_Corner(true));
					Black_Score -= Dist_Betw(White_King, Black_King);
					}
				}
	else
	{			
    White_Score += WKpsqt[wk];
    Black_Score += BKpsqt[bk];
	}
        
    return (White_Score - Black_Score); //Return the score from WHITE'S perspective
}
