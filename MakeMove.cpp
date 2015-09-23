#include "MoveGen.h"
#include "MakeMove.h"
//*****************************************************************************************************************************************
		//White MakeMove
	
		int MakeWhiteMove(Move Best_Move)
{
	
  //The following few lines simply generate a random number between 0 and White or Black MoveSpacer and put this value into the variable q
	/*	  srand(static_cast<unsigned int>(time(0)));
		int q;
        int randomNumber = rand();
		if(White_Move_Spacer > 1)//We must choose a number smaller than the number of legal moves found
        q = (randomNumber % (White_Move_Spacer - 1));
        
        if(White_Move_Spacer == 1)//If there is only one mve, then force the program to play it
        q = 0; 
        if(White_Move_Spacer == 0)//If q = 0, then white loses
         return 0; //To let the user know that the game finished
        for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & White_Move_From_Stack[q])//Get the index in GeneralBoard[] of the square the current pieces is moving from
        	{
        	cout << "bestmove " << PlayerMoves[h];//Cout it to the user, but don't endl because we have to display the whole move squashed togather, e.g. d2d4
        	//Log << "bestmove " << PlayerMoves[h];//Put it out to the text file
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & White_Move_To_Stack[q])//For each to square found
        	{
        	cout << PlayerMoves[h] << endl;//cout it and
        	//Log << PlayerMoves[h] << endl;//Put it into the text file; now we can do a new line because we are done with the current move
        }
		}	
		*/	
               // Update Bitboards
  Bitboard From = Best_Move.From;             
  Bitboard To = Best_Move.To;
  int Move_Type = Best_Move.Move_Type;

	switch(Move_Type)//This switch evaluates the type of move that accompanies the index of the move stack that q refers to
               { 
               
               case 1://A (white) pawn capture
               	White_Pieces |= To;//Move white's pieces to the to square and from the from square
               	White_Pieces ^= From;
               	White_Pawns |= To;
               	White_Pawns ^= From;
               	Black_Pieces |= To;//Do the same for the black pieces because it is a capture: we have to remove a black piece
				Black_Pieces ^= To;
				Black_Queens |= To; 
				Black_Queens ^= To; 
				Black_Rooks |= To; 
				Black_Rooks ^= To; 
				Black_Bishops |= To; 
				Black_Bishops ^= To; 
				Black_Knights |= To; 
				Black_Knights ^= To; 
				Black_Pawns |= To;  
				Black_Pawns ^= To; 
				break;
				
               	
               	case 2://"Plain" pawn push: one square
                White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Pawns |= To;
               	White_Pawns ^= From;
               	break;	
               	
               	
               	case 3://Knight Capture
               	White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Knights |= To;
               	White_Knights ^= From;
               	Black_Pieces |= To;
				Black_Pieces ^= To;
				Black_Queens |= To; 
				Black_Queens ^= To; 
				Black_Rooks |= To; 
				Black_Rooks ^= To; 
				Black_Bishops |= To; 
				Black_Bishops ^= To; 
				Black_Knights |= To; 
				Black_Knights ^= To; 
				Black_Pawns |= To;  
				Black_Pawns  ^= To; 
				break;
				
				case 4://Plain knight move
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Knights |= To;
               	White_Knights ^= From;
               	break;
				   
			    case 5://Bishop capture
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Bishops |= To;
               	White_Bishops ^= From;
               	Black_Pieces |= To;
				Black_Pieces ^= To;
				Black_Queens |= To; 
				Black_Queens ^= To; 
				Black_Rooks |= To; 
				Black_Rooks ^= To; 
				Black_Bishops |= To; 
				Black_Bishops ^= To; 
				Black_Knights |= To; 
				Black_Knights ^= To; 
				Black_Pawns |= To;  
				Black_Pawns  ^= To; 
				break;	
				
				case 6://"Plain" bishop move
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Bishops |= To;
               	White_Bishops ^= From;
               	break;
				   
				case 7://Rook capture
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Rooks |= To;
               	White_Rooks ^= From;
               	Black_Pieces |= To;
				Black_Pieces ^= To;
				Black_Queens |= To; 
				Black_Queens ^= To; 
				Black_Rooks |= To; 
				Black_Rooks ^= To; 
				Black_Bishops |= To; 
				Black_Bishops ^= To; 
				Black_Knights |= To; 
				Black_Knights ^= To; 
				Black_Pawns |= To;  
				Black_Pawns  ^= To; 
				break;
				
				case 8://"Plain" rook move
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Rooks |= To;
               	White_Rooks ^= From;
               	break;
               	
               	case 9://Queen capture
               	White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Queens |= To;
               	White_Queens ^= From;
               	Black_Pieces |= To;
				Black_Pieces ^= To;
				Black_Queens |= To; 
				Black_Queens ^= To; 
				Black_Rooks |= To; 
				Black_Rooks ^= To; 
				Black_Bishops |= To; 
				Black_Bishops ^= To; 
				Black_Knights |= To; 
				Black_Knights ^= To; 
				Black_Pawns |= To;  
				Black_Pawns  ^= To; 
				break;
				
				case 10://"Plain" queen move
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Queens |= To;
               	White_Queens ^= From;
               	break;
				
				case 11://King capture
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_King |= To;
               	White_King ^= From;
               	Black_Pieces |= To;
				Black_Pieces ^= To;
				Black_Queens |= To; 
				Black_Queens ^= To; 
				Black_Rooks |= To; 
				Black_Rooks ^= To; 
				Black_Bishops |= To; 
				Black_Bishops ^= To; 
				Black_Knights |= To; 
				Black_Knights ^= To; 
				Black_Pawns |= To;  
				Black_Pawns  ^= To; 
				break; 
				
				case 12://"Plain" king move
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_King |= To;
               	White_King ^= From;
               	break;
				   
				case 13://Pawn promotion with capture; automatically promotes to queen
			    White_Pawns ^= From;
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Queens |= To;
               	Black_Pieces |= To;
				Black_Pieces ^= To;
				Black_Queens |= To; 
				Black_Queens ^= To; 
				Black_Rooks |= To; 
				Black_Rooks ^= To; 
				Black_Bishops |= To; 
				Black_Bishops ^= To; 
				Black_Knights |= To; 
				Black_Knights ^= To; 
				break; 
				
				case 14://"Plain" pawn promotion
			    White_Pawns ^= From;
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Queens |= To;
               	break;
				   
				case 15://White king kingside castling
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Pieces |= 32;
               	White_Pieces ^= 128;
               	White_Rooks |= 32;
               	White_Rooks ^= 128;
               	White_King |= To;
               	White_King ^= From;
               	WhiteHasCastled = true;
               	break;
				   	
               	
			   }
                 
                 //Tidy up for the next call of the move generation functions
				 for(int t = 0; t < White_Move_Spacer; t++)               
               {
               	 White_Move_From_Stack[t] = 0;//Clear the move from stack
               	 White_Move_To_Stack[t] = 0;//Clear the move to stack
               	 White_Move_Types[t] = 0;//Clear the move types associated with the moves
			   }
			    White_Knight_Spacer = 0;//Clear all of the piece spacers
			    White_King_Spacer = 0;
			    White_Pawn_Spacer = 0;
			    White_Rook_Spacer = 0;
			    White_Bishop_Spacer = 0;
			    White_Queen_Spacer = 0;
			    White_Move_Spacer = 0;
		
			    Current_Turn = false;
			    White_Turn = false;
			    return 0;

}
				 
		//*****************************************************************************************************************************************
		//Black MakeMove
		
		//Pretty much the same as White's MakeMove()
		int MakeBlackMove(Move Best_Move)
		{	
		  /*srand(static_cast<unsigned int>(time(0)));

        int randomNumber = rand();
		int q;
		if(Black_Move_Spacer > 1)
        q = (randomNumber % (Black_Move_Spacer - 1));
        if(Black_Move_Spacer == 1)
        q = 0;
        if(Black_Move_Spacer == 0)
        cin >> q;
        for(int y = 0; y < 64; y++)
        {
        	if(GeneralBoard[y] & Black_Move_From_Stack[q])
        	{
        	cout << "bestmove " << PlayerMoves[y]; 
        	//Log << "bestmove " << PlayerMoves[h];
        }
		}
		for(int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & Black_Move_To_Stack[q])
        	{
        	cout << PlayerMoves[h] << endl; 
        	//Log << PlayerMoves[h] << endl;
        }
		}	    
		*/  
		Bitboard From = Best_Move.From;            
  		Bitboard To = Best_Move.To;
  		int Move_Type = Best_Move.Move_Type;
     
			  switch(Move_Type)//This switch evaluates the type of move that accompanies the index of the move stack that Move_Type refers to
               { 
               
               case 1://A (white) pawn capture
               	Black_Pieces |= To;//Move white's pieces to the to square and from the from square
               	Black_Pieces ^= From;
               	Black_Pawns |= To;
               	Black_Pawns ^= From;
               	White_Pieces |= To;//Do the same for the black pieces because it is a capture: we have to remove a black piece
				White_Pieces ^= To;
				White_Queens |= To; 
				White_Queens ^= To; 
				White_Rooks |= To; 
				White_Rooks ^= To; 
				White_Bishops |= To; 
				White_Bishops ^= To; 
				White_Knights |= To; 
				White_Knights ^= To; 
				White_Pawns |= To;  
				White_Pawns  ^= To; 
				break;
				
               	
               	case 2://"Plain" pawn push: one square
                Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Pawns |= To;
               	Black_Pawns ^= From;
               	break;	
               	
               	
               	case 3://Knight Capture
               	Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Knights |= To;
               	Black_Knights ^= From;
               	White_Pieces |= To;
				White_Pieces ^= To;
				White_Queens |= To;
				White_Queens ^= To; 
				White_Rooks |= To; 
				White_Rooks ^= To; 
				White_Bishops |= To; 
				White_Bishops ^= To; 
				White_Knights |= To; 
				White_Knights ^= To; 
				White_Pawns |= To;  
				White_Pawns  ^= To; 
				break;
				
				case 4://"Plain" knight move
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Knights |= To;
               	Black_Knights ^= From;
               	break;
				   
			    case 5://Bishop capture
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Bishops |= To;
               	Black_Bishops ^= From;
               	White_Pieces |= To;
				White_Pieces ^= To;
				White_Queens |= To; 
				White_Queens ^= To; 
				White_Rooks |= To; 
				White_Rooks ^= To; 
				White_Bishops |= To; 
				White_Bishops ^= To; 
				White_Knights |= To; 
				White_Knights ^= To; 
				White_Pawns |= To;  
				White_Pawns  ^= To; 
				break;	
				
				case 6://"Plain" bishop move
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Bishops |= To;
               	Black_Bishops ^= From;
               	break;
				   
				case 7://Rook capture
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Rooks |= To;
               	Black_Rooks ^= From;
               	White_Pieces |= To;
				White_Pieces ^= To;
				White_Queens |= To; 
				White_Queens ^= To; 
				White_Rooks |= To; 
				White_Rooks ^= To; 
				White_Bishops |= To; 
				White_Bishops ^= To; 
				White_Knights |= To; 
				White_Knights ^= To; 
				White_Pawns |= To;  
				White_Pawns  ^= To; 
				break;
				
				case 8://"Plain" rook move
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Rooks |= To;
               	Black_Rooks ^= From;
               	break;
               	
               	case 9://Queen capture
               	Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Queens |= To;
               	Black_Queens ^= From;
               	White_Pieces |= To;
				White_Pieces ^= To;
				White_Queens |= To; 
				White_Queens ^= To; 
				White_Rooks |= To; 
				White_Rooks ^= To; 
				White_Bishops |= To; 
				White_Bishops ^= To; 
				White_Knights |= To; 
				White_Knights ^= To; 
				White_Pawns |= To;  
				White_Pawns  ^= To; 
				break;
				
				case 10://"Plain" queen move
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Queens |= To;
               	Black_Queens ^= From;
               	break;
				
				case 11://King capture
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_King |= To;
               	Black_King ^= From;
               	White_Pieces |= To;
				White_Pieces ^= To;
				White_Queens |= To; 
				White_Queens ^= To; 
				White_Rooks |= To; 
				White_Rooks ^= To; 
				White_Bishops |= To; 
				White_Bishops ^= To; 
				White_Knights |= To; 
				White_Knights ^= To; 
				White_Pawns |= To;  
				White_Pawns  ^= To; 
				break; 
				
				case 12://"Plain" king move
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_King |= To;
               	Black_King ^= From;
               	break;
				   
				case 13://Pawn promotion with capture; automatically promotes to queen
			    Black_Pawns ^= From;
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Queens |= To;
               	White_Pieces |= To;
				White_Pieces ^= To;
				White_Queens |= To; 
				White_Queens ^= To; 
				White_Rooks |= To; 
				White_Rooks ^= To; 
				White_Bishops |= To; 
				White_Bishops ^= To; 
				White_Knights |= To; 
				White_Knights ^= To; 
				break; 
				
				case 14://"Plain" pawn promotion
			    Black_Pawns ^= From;
				Black_Pieces |= To;
               	Black_Pieces ^= From;
               	Black_Queens |= To;
               	break;
				   
				case 15: 			
				Black_Pieces |= To;
            	Black_Pieces ^= From;
            	Black_Pieces |= 4611686018427387904;
            	Black_Pieces ^= 1152921504606846976;
            	Black_Rooks |= 2305843009213693952;
            	Black_Rooks ^= 9223372036854775808ULL;
            	Black_King |= To;
            	Black_King ^= From;	
            	break;
				   	
               	
			   }
                 
                 //Tidy up for the next call of the move generation functions
				 for(int t = 0; t < Black_Move_Spacer; t++)               
               {
               	 Black_Move_From_Stack[t] = 0;//Clear the move from stack
               	 Black_Move_To_Stack[t] = 0;//Clear the move to stack
               	 Black_Move_Types[t] = 0;//Clear the move types associated with the moves
			   }
			    Black_Knight_Spacer = 0;//Clear all of the piece spacers
			    Black_King_Spacer = 0;
			    Black_Pawn_Spacer = 0;
			    Black_Rook_Spacer = 0;
			    Black_Bishop_Spacer = 0;
			    Black_Queen_Spacer = 0;
			    Black_Move_Spacer = 0;
		
			    Current_Turn  = true;
			    White_Turn = true;
			    return 0;

}

