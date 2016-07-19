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
    -50, 0,-20,-30,-30,-20, 0,-50,
    -40,-20,  0,  10,  10,  0,-20,-40,
    -30,  5, 15, 15, 15, 15,  5,-30,
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
    -30,  5, 15, 15, 15, 15,  5,-30,
    -40,-20,  0,  10,  10,  0,-20,-40,
    -50, 0,-20,-30,-30,-20, 0,-50
};

//White Pawns
const int Eval::WPpsqt[64] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 0, -5, -5, -5, -5, 0, 5,
    5, 5, -10, -5, -5, -10, 5, 5,
    0,  0, 25, 25, 25,  20,  0,  0,
    5,  5, 15, 27, 27, 10,  5,  5,
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
     5,  5, 15, 27, 27, 10,  5,  5,
     0,  0, 25, 25, 25,  20,  0,  0,
     5, 5, -10, -5, -5, -10, 5, 5,
     5, 0, -5, -5, -5, -5, 0, 5,
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
	-20,-10,  0,-10,-10,  0,-10,-20,
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
    -20,-10,  0,-10,-10,  0,-10,-20
};
int White_Score = 0; //White's Score
int Black_Score = 0; //Black's Score
int wk = 0, bk = 0;
const int Doubled_Pawn_Penalty = 10;
const int Open_File_Bonus = 20;
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
    	else
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
    
    int wpona = __builtin_popcountll(White_Pawns & A_Pawn_Mask);
    int wponb = __builtin_popcountll(White_Pawns & B_Pawn_Mask);
    int wponc = __builtin_popcountll(White_Pawns & C_Pawn_Mask);
    int wpond = __builtin_popcountll(White_Pawns & D_Pawn_Mask);
    int wpone = __builtin_popcountll(White_Pawns & E_Pawn_Mask);
    int wponf = __builtin_popcountll(White_Pawns & F_Pawn_Mask);
    int wpong = __builtin_popcountll(White_Pawns & G_Pawn_Mask);
    int wponh = __builtin_popcountll(White_Pawns & H_Pawn_Mask);
    
    White_Score -= (wpona > 1 ? Doubled_Pawn_Penalty * (wpona - 1) : 0);
    White_Score -= (wponb > 1 ? Doubled_Pawn_Penalty * (wponb - 1) : 0);
    White_Score -= (wponc > 1 ? Doubled_Pawn_Penalty * (wponc - 1) : 0);
    White_Score -= (wpond > 1 ? Doubled_Pawn_Penalty * (wpond - 1) : 0);
    White_Score -= (wpone > 1 ? Doubled_Pawn_Penalty * (wpone - 1) : 0);
    White_Score -= (wponf > 1 ? Doubled_Pawn_Penalty * (wponf - 1) : 0);
    White_Score -= (wpong > 1 ? Doubled_Pawn_Penalty * (wpong - 1) : 0);
    White_Score -= (wponh > 1 ? Doubled_Pawn_Penalty * (wponh - 1) : 0);
    
    int bpona = (__builtin_popcountll(Black_Pawns & A_Pawn_Mask) - 1);
    int bponb = (__builtin_popcountll(Black_Pawns & B_Pawn_Mask) - 1);
    int bponc = (__builtin_popcountll(Black_Pawns & C_Pawn_Mask) - 1);
    int bpond = (__builtin_popcountll(Black_Pawns & D_Pawn_Mask) - 1);
    int bpone = (__builtin_popcountll(Black_Pawns & E_Pawn_Mask) - 1);
    int bponf = (__builtin_popcountll(Black_Pawns & F_Pawn_Mask) - 1);
    int bpong = (__builtin_popcountll(Black_Pawns & G_Pawn_Mask) - 1);
    int bponh = (__builtin_popcountll(Black_Pawns & H_Pawn_Mask) - 1);
    
    Black_Score -= (bpona > 1 ? Doubled_Pawn_Penalty * (bpona - 1) : 0);
    Black_Score -= (bponb > 1 ? Doubled_Pawn_Penalty * (bponb - 1) : 0);
    Black_Score -= (bponc > 1 ? Doubled_Pawn_Penalty * (bponc - 1) : 0);
    Black_Score -= (bpond > 1 ? Doubled_Pawn_Penalty * (bpond - 1) : 0);
    Black_Score -= (bpone > 1 ? Doubled_Pawn_Penalty * (bpone - 1) : 0);
    Black_Score -= (bponf > 1 ? Doubled_Pawn_Penalty * (bponf - 1) : 0);
    Black_Score -= (bpong > 1 ? Doubled_Pawn_Penalty * (bpong - 1) : 0);
    Black_Score -= (bponh > 1 ? Doubled_Pawn_Penalty * (bponh - 1) : 0);
    
    if((wpona + bpona) < 2) 
    {
		if(White_Rooks & A_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & A_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponb + bponb) < 2) 
    {
		if(White_Rooks & B_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & B_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponc + bponc) < 2) 
    {
		if(White_Rooks & C_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & C_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wpond + bpond) < 2) 
    {
		if(White_Rooks & D_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & D_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wpone + bpone) < 2) 
    {
		if(White_Rooks & E_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & E_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponf + bponf) < 2) 
    {
		if(White_Rooks & F_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & F_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wpong + bpong) < 2) 
    {
		if(White_Rooks & G_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & G_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponh + bponh) < 2) 
    {
		if(White_Rooks & H_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(Black_Rooks & H_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
    
    
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
        
    return (!Search::Current_Turn ? (White_Score - Black_Score) : (Black_Score - White_Score)); //Return the score from WHITE'S perspective
}
