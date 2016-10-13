using namespace std;
#include "Eval.h"
#include "Bitboard.h"
#include "Endgame.h"
#include "Search.h"
#include "Pawns.h"

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
    0,  0, 25, 25, 25,  10,  0,  0,
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
     0,  0, 25, 25, 25,  10,  0,  0,
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
const int PassedPawnBonus = 75;
//********************************************************************
//Material
//********************************************************************

//Evaluates the current position based on the bitboards in Bitboard.cpp
int Eval::Lazy_Eval(Position* position)
{
	White_Score = 0;
    Black_Score = 0;
	White_Score += 100 * __builtin_popcountll(position->White_Pawns);
    White_Score += 300 * __builtin_popcountll(position->White_Knights);
    White_Score += 300 * __builtin_popcountll(position->White_Bishops);
    White_Score += 500 * __builtin_popcountll(position->White_Rooks);
    White_Score += 800 * __builtin_popcountll(position->White_Queens);
    Black_Score += 100 * __builtin_popcountll(position->Black_Pawns);
    Black_Score += 300 * __builtin_popcountll(position->Black_Knights);
    Black_Score += 300 * __builtin_popcountll(position->Black_Bishops);
    Black_Score += 500 * __builtin_popcountll(position->Black_Rooks);
    Black_Score += 800 * __builtin_popcountll(position->Black_Queens);
    return (White_Score - Black_Score);
}
const int Eval::Evaluate_Position(Position* position)
{
    
	White_Score = 0; //White's Score
    Black_Score = 0; //Black's Score
    wk = 0;
	bk = 0;
    White_Score += 100 * __builtin_popcountll(position->White_Pawns);
    White_Score += 300 * __builtin_popcountll(position->White_Knights);
    White_Score += 300 * __builtin_popcountll(position->White_Bishops);
    White_Score += 500 * __builtin_popcountll(position->White_Rooks);
    White_Score += 800 * __builtin_popcountll(position->White_Queens);
    
    Black_Score += 100 * __builtin_popcountll(position->Black_Pawns);
    Black_Score += 300 * __builtin_popcountll(position->Black_Knights);
    Black_Score += 300 * __builtin_popcountll(position->Black_Bishops);
    Black_Score += 500 * __builtin_popcountll(position->Black_Rooks);
    Black_Score += 800 * __builtin_popcountll(position->Black_Queens);
    
	     for(int i = 0; i < 64; i++)
    	{
    	if(!(GeneralBoard[i] & (position->White_Pieces | position->Black_Pieces))) continue;
    	
    	if(GeneralBoard[i] & pos.White_Pieces)
    	{
        	if(GeneralBoard[i] & position->White_King)
        		wk = i;
        	if(GeneralBoard[i] & position->White_Pawns) //For each white pawn on the board
        		White_Score += WPpsqt[i];
            if(GeneralBoard[i] & position->White_Knights)
        	    White_Score += WNpsqt[i];
        	if(GeneralBoard[i] & position->White_Bishops)
			    White_Score += WBpsqt[i];
			continue;    
        }
    	else
    		{
        		if(GeneralBoard[i] & position->Black_Pawns) //For each black pawn on the board
        			Black_Score += BPpsqt[i];
                if(GeneralBoard[i] & position->Black_Knights)
                	Black_Score += BNpsqt[i];
                if(GeneralBoard[i] & position->Black_King)
        			bk = i;
        		if(GeneralBoard[i] & position->Black_Bishops)
                	Black_Score += BBpsqt[i];
				continue;		
    		}
        
    	}
    int wpona = __builtin_popcountll(position->White_Pawns & A_Pawn_Mask);
	int wponb = __builtin_popcountll(position->White_Pawns & B_Pawn_Mask);
	int wponc = __builtin_popcountll(position->White_Pawns & C_Pawn_Mask);
	int wpond = __builtin_popcountll(position->White_Pawns & D_Pawn_Mask);
	int wpone = __builtin_popcountll(position->White_Pawns & E_Pawn_Mask);
	int wponf = __builtin_popcountll(position->White_Pawns & F_Pawn_Mask);
	int wpong = __builtin_popcountll(position->White_Pawns & G_Pawn_Mask);
	int wponh = __builtin_popcountll(position->White_Pawns & H_Pawn_Mask);
	int bpona = __builtin_popcountll(position->Black_Pawns & A_Pawn_Mask);
    int bponb = __builtin_popcountll(position->Black_Pawns & B_Pawn_Mask);
    int bponc = __builtin_popcountll(position->Black_Pawns & C_Pawn_Mask);
    int bpond = __builtin_popcountll(position->Black_Pawns & D_Pawn_Mask);
    int bpone = __builtin_popcountll(position->Black_Pawns & E_Pawn_Mask);
    int bponf = __builtin_popcountll(position->Black_Pawns & F_Pawn_Mask);
    int bpong = __builtin_popcountll(position->Black_Pawns & G_Pawn_Mask);
    int bponh = __builtin_popcountll(position->Black_Pawns & H_Pawn_Mask);
    PawnEntry* p = pawnhash.probe(Get_Pawn_Hash(position));
    if(p != NULL)
    {
    	//hashhits++;
    	White_Score += p->score_white;
    	Black_Score += p->score_black;
	}
    else
	{	//hashmisses++;
		int wscore = 0;
		int bscore = 0;	    
	    wscore -= (wpona > 1 ? Doubled_Pawn_Penalty * (wpona - 1) : 0);
	    wscore -= (wponb > 1 ? Doubled_Pawn_Penalty * (wponb - 1) : 0);
	    wscore -= (wponc > 1 ? Doubled_Pawn_Penalty * (wponc - 1) : 0);
	    wscore -= (wpond > 1 ? Doubled_Pawn_Penalty * (wpond - 1) : 0);
	    wscore -= (wpone > 1 ? Doubled_Pawn_Penalty * (wpone - 1) : 0);
	    wscore -= (wponf > 1 ? Doubled_Pawn_Penalty * (wponf - 1) : 0);
	    wscore -= (wpong > 1 ? Doubled_Pawn_Penalty * (wpong - 1) : 0);
	    wscore -= (wponh > 1 ? Doubled_Pawn_Penalty * (wponh - 1) : 0);
	    bscore -= (bpona > 1 ? Doubled_Pawn_Penalty * (bpona - 1) : 0);
	    bscore -= (bponb > 1 ? Doubled_Pawn_Penalty * (bponb - 1) : 0);
	    bscore -= (bponc > 1 ? Doubled_Pawn_Penalty * (bponc - 1) : 0);
	    bscore -= (bpond > 1 ? Doubled_Pawn_Penalty * (bpond - 1) : 0);
	    bscore -= (bpone > 1 ? Doubled_Pawn_Penalty * (bpone - 1) : 0);
	    bscore -= (bponf > 1 ? Doubled_Pawn_Penalty * (bponf - 1) : 0);
	    bscore -= (bpong > 1 ? Doubled_Pawn_Penalty * (bpong - 1) : 0);
	    bscore -= (bponh > 1 ? Doubled_Pawn_Penalty * (bponh - 1) : 0);
	    pawnhash.save(wscore, bscore, Get_Pawn_Hash(position));
	}
    if((wpona + bpona) < 2) 
    {
		if(position->White_Rooks & A_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & A_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponb + bponb) < 2) 
    {
		if(position->White_Rooks & B_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & B_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponc + bponc) < 2) 
    {
		if(position->White_Rooks & C_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & C_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wpond + bpond) < 2) 
    {
		if(position->White_Rooks & D_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & D_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wpone + bpone) < 2) 
    {
		if(position->White_Rooks & E_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & E_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponf + bponf) < 2) 
    {
		if(position->White_Rooks & F_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & F_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wpong + bpong) < 2) 
    {
		if(position->White_Rooks & G_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & G_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
	if((wponh + bponh) < 2) 
    {
		if(position->White_Rooks & H_Pawn_Mask)
			White_Score += Open_File_Bonus;
		if(position->Black_Rooks & H_Pawn_Mask)
			Black_Score += Open_File_Bonus;
	}
    
    if(position->White_Pawns & Seventh_Rank_White)
    	White_Score += PassedPawnBonus;
    if(position->Black_Pawns & Seventh_Rank_Black)
    	Black_Score += PassedPawnBonus;
    if(__builtin_popcountll(position->White_Pieces | position->Black_Pieces) <= 10)
                {
                	if(White_Score > Black_Score)
                	{
                	White_Score  += (Drive_To_Corner(position->White_King));
					White_Score -= Dist_Betw(position->White_King, position->Black_King);
					}
                	else
                	{
                	Black_Score  += (Drive_To_Corner(position->Black_King));
					Black_Score -= Dist_Betw(position->White_King, position->Black_King);
					}
				}
	else
	{			
    White_Score += WKpsqt[wk];
    Black_Score += BKpsqt[bk];
	}
    return (White_Score - Black_Score); //Return the score from WHITE'S perspective
}
