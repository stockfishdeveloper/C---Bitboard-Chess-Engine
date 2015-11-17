using namespace std;
#include "Eval.h"
#include "Bitboard.h"

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
	
	int WPpsqt[64] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		2, 2, 3, 4, 4, 3, 2, 2,
		3, 4, 5, 6, 6, 5, 4, 3,
		5, 6, 7, 8, 8, 7, 6, 5,
		4, 5, 6, 7, 7, 6, 5, 4,
		25, 23, 22, 21, 21, 22, 23, 25 		
	};
	
	int BPpsqt[64] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		2, 2, 3, 4, 4, 3, 2, 2,
		3, 4, 5, 6, 6, 5, 4, 3,
		5, 6, 7, 8, 8, 7, 6, 5,
		4, 5, 6, 7, 7, 6, 5, 4,
		25, 23, 22, 21, 21, 22, 23, 25 	
	};
float Evaluate_Position() 
{
	float White_Score = 0.0; 
	float Black_Score = 0.0;
	
	//********************************************************************
	//Material
	//********************************************************************
        register int i = 0;
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & White_Pawns)
                White_Score += 1.0;
        }
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & White_Knights)
                White_Score += 3.0;
        }
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & White_Bishops)
                White_Score += 3.0;
        }
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & White_Rooks)
                White_Score += 5.0;
        }
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & White_Queens)
                White_Score += 8.0;
        }
        
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & Black_Pawns)
                Black_Score += 1.0;
        }
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & Black_Knights)
                Black_Score += 3.0;
        }
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & Black_Bishops)
                Black_Score += 3.0;
        }
        for(i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & Black_Rooks)
                Black_Score += 5.0;
        }
        for(int i = 0; i < 64; i++)
        {
                if(GeneralBoard[i] & Black_Queens)
                Black_Score += 8.0;
        }
        
        //********************************************************************
		//End Material
	    //********************************************************************
	    
	    
		
		for(int i = 0; i < 64; i++)
		{
			if(GeneralBoard[i] & White_Knights)
			{
				White_Score += float(float(WNpsqt[i]) / 100);
			}
		}
		
		for(int i = 0; i < 64; i++)
		{
			if(GeneralBoard[i] & Black_Knights)
			{
				Black_Score += float(float(BNpsqt[i]) / 100);
			}
		}
	    	
	    	for(int i = 0; i < 64; i++)
		{
			if(GeneralBoard[i] & White_Pawns)
			{
				White_Score += float(float(WPpsqt[i]) / 100);
			}
		}
		
		for(int i = 0; i < 64; i++)
		{
			if(GeneralBoard[i] & Black_Pawns)
			{
				Black_Score += float(float(BPpsqt[i]) / 100);
			}
		}
		return (White_Score - Black_Score);
}
