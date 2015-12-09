using namespace std;
#include "Eval.h"
#include "Bitboard.h"


//********************************************************************
//Piece Square Tables
//********************************************************************

//White Knights
int WNpsqt[64] =
            {
                -20, -5, -7, -2, -2, -7, -5, -25,
                -15, -2,  0,  0,  0,  0, -3, -5,
                -1,  -1,  2,  0,  0,  3,  0, -1,
                 1,   2,  5,  5,  5,  5,  4,  1,
                         1,   3,  6,  10, 10, 5,  5,  2,
                        -2,   -1, 0,  25, 25, 0, -1, -3
                        -10,  -8, -5, -3, -2, -2, -6, -8,
                        -15, -13, -11, -9, -9, -11, -13, -15
                };
        
//Black Knights         
int BNpsqt[64] =
                {                       
                        -15, -13, -11, -9, -9, -11, -13, -15,
                        -10,  -8, -5,  -3, -2, -2,  -6,  -8,
                        -2,   -1,  0,  25, 25,  0,  -1,  -3,
                        1,   3,   6,  10, 10,  5,   5,   2,
                         1,   2,  5,  5,  5,  5,  4,  1,
                        -1,  -1,  2,  0,  0,  3,  0, -1,
                        -15, -2,  0,  0,  0,  0, -3, -5,
                        -20, -5, -7, -2, -2, -7, -5, -25
                };
        
//White Pawns   
int WPpsqt[64] =
                {
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        2, 2, 3, 4, 4, 3, 2, 2,
                        3, 4, 5, 6, 6, 5, 4, 3,
                        5, 6, 7, 8, 8, 7, 6, 5,
                        25, 23, 22, 21, 21, 22, 23, 25,  
                        0, 0, 0, 0, 0, 0, 0, 0        
                };
        
//Black Pawns   
int BPpsqt[64] =
                {
                        0, 0, 0, 0, 0, 0, 0, 0,
                        25, 23, 22, 21, 21, 22, 23, 25,
                        2, 2, 3, 4, 4, 3, 2, 2,
                        3, 4, 5, 6, 6, 5, 4, 3,
                        5, 6, 7, 8, 8, 7, 6, 5,
                        2, 2, 3, 4, 4, 3, 2, 2,  
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0
                };
        
                
//********************************************************************
//Material
//********************************************************************
                
//Evaluates the current position based on the bitboards in Bitboard.cpp         
float Evaluate_Position() 
        {
                float White_Score = 0.0; //White's Score
                float Black_Score = 0.0; //Black's Score
        
            register int i = 0; //A little optimization
        for(i = 0; i < 64; i++)
                {
                bool IsWhitePawns = GeneralBoard[i] & White_Pawns;
                bool IsWhiteKnights = GeneralBoard[i] & White_Knights;
                bool IsWhiteBishops = GeneralBoard[i] & White_Bishops;
                bool IsWhiteRooks = GeneralBoard[i] & White_Rooks;
                bool IsWhiteQueens = GeneralBoard[i] & White_Queens;

                if(IsWhitePawns) //For each white pawn on the board
                {
                        White_Score += 1.0; //Add one point to the score
                }
                if(IsWhiteKnights)
                {
                        White_Score += 3.0;
                }
                if(IsWhiteBishops)
                {
                        White_Score += 3.0;
                }
                if(IsWhiteRooks)
                {
                        White_Score += 5.0;
                }
                if(IsWhiteQueens)
                {
                        White_Score += 8.0;
                }
                }
        
        for(i = 0; i < 64; i++)
                {
                bool IsBlackPawns = GeneralBoard[i] & Black_Pawns;
                bool IsBlackKnights = GeneralBoard[i] & Black_Knights;
                bool IsBlackBishops = GeneralBoard[i] & Black_Bishops;
                bool IsBlackRooks = GeneralBoard[i] & Black_Rooks;
                bool IsBlackQueens = GeneralBoard[i] & Black_Queens;

                if(IsBlackPawns) //For each black pawn on the board
                {
                        Black_Score += 1.0; //Add one point to the score
                }
                if(IsBlackKnights)
                {
                        Black_Score += 3.0;
                }
                if(IsBlackBishops)
                {
                        Black_Score += 3.0;
                }
                if(IsBlackRooks)
                {
                        Black_Score += 5.0;
                }
                if(IsBlackQueens)
                {
                        Black_Score += 8.0;
                }
                }

        //********************************************************************
                //Assign scores to the pieces with the piece square tables
            //********************************************************************
            
            for(i = 0; i < 64; i++)
                {
                	bool HasWhiteKnight = GeneralBoard[i] & White_Knights;
                	bool HasBlackKnight = GeneralBoard[i] & Black_Knights;
                	bool HasWhitePawn = GeneralBoard[i] & White_Pawns;
                	bool HasBlackPawn = GeneralBoard[i] & Black_Pawns;
                	if(HasWhiteKnight)
                	White_Score += float(float(WNpsqt[i]) / 100);
                	if(HasBlackKnight)
                	Black_Score += float(float(BNpsqt[i]) / 100);
                	if(HasWhitePawn)
                	White_Score += float(float(WPpsqt[i]) / 100);
                	if(HasBlackPawn)
                	Black_Score += float(float(BPpsqt[i]) / 100);
                        
                }
            
                return (White_Score - Black_Score); //Return the score from WHITE'S perspective
        }
