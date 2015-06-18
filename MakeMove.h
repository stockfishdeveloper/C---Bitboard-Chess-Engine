#ifndef The_Three_Stooges 
#define The_Three_Stooges 

//*****************************************************************************************************************************************
		//White MakeMove
		
		int MakeWhiteMove()
{
	
  //The following few lines simply generate a random number between 0 and White or Black MoveSpacer and put this value into the variable q
		  srand(static_cast<unsigned int>(time(0)));
		int q;
        int randomNumber = rand();
		if(White_Move_Spacer > 1)//We must choose a number smaller than the number of legal moves found
        q = (randomNumber % (White_Move_Spacer - 1));
        if(White_Move_Spacer == 1)//If there is only one mve, then force the program to play it
        q = 0; 
        if(White_Move_Spacer == 0)//If q = 0, then white loses
         cin >> q; //To let the user know that the game finished
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
               // Update Bitboards
               switch(White_Move_Types[q])//This switch evaluates the type of move that accompanies the index of the move stack that q refers to
               { 
               
               case 1://A (white) pawn capture
               	White_Pieces |= White_Move_To_Stack[q];//Move white's pieces to the to square and from the from square
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Pawns |= White_Move_To_Stack[q];
               	White_Pawns ^= White_Move_From_Stack[q];
               	Black_Pieces |= White_Move_To_Stack[q];//Do the same for the black pieces because it is a capture: we have to remove a black piece
				Black_Pieces ^= White_Move_To_Stack[q];
				Black_Queens |= White_Move_To_Stack[q]; 
				Black_Queens ^= White_Move_To_Stack[q]; 
				Black_Rooks |= White_Move_To_Stack[q]; 
				Black_Rooks ^= White_Move_To_Stack[q]; 
				Black_Bishops |= White_Move_To_Stack[q]; 
				Black_Bishops ^= White_Move_To_Stack[q]; 
				Black_Knights |= White_Move_To_Stack[q]; 
				Black_Knights ^= White_Move_To_Stack[q]; 
				Black_Pawns |= White_Move_To_Stack[q];  
				Black_Pawns  ^= White_Move_To_Stack[q]; 
				break;
				
               	
               	case 2://"Plain" pawn push: one square
                White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Pawns |= White_Move_To_Stack[q];
               	White_Pawns ^= White_Move_From_Stack[q];
               	break;	
               	
               	
               	case 3://Knight Capture
               	White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Knights |= White_Move_To_Stack[q];
               	White_Knights ^= White_Move_From_Stack[q];
               	Black_Pieces |= White_Move_To_Stack[q];
				Black_Pieces ^= White_Move_To_Stack[q];
				Black_Queens |= White_Move_To_Stack[q]; 
				Black_Queens ^= White_Move_To_Stack[q]; 
				Black_Rooks |= White_Move_To_Stack[q]; 
				Black_Rooks ^= White_Move_To_Stack[q]; 
				Black_Bishops |= White_Move_To_Stack[q]; 
				Black_Bishops ^= White_Move_To_Stack[q]; 
				Black_Knights |= White_Move_To_Stack[q]; 
				Black_Knights ^= White_Move_To_Stack[q]; 
				Black_Pawns |= White_Move_To_Stack[q];  
				Black_Pawns  ^= White_Move_To_Stack[q]; 
				break;
				
				case 4://"Plain" knight move
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Knights |= White_Move_To_Stack[q];
               	White_Knights ^= White_Move_From_Stack[q];
               	break;
				   
			    case 5://Bishop capture
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Bishops |= White_Move_To_Stack[q];
               	White_Bishops ^= White_Move_From_Stack[q];
               	Black_Pieces |= White_Move_To_Stack[q];
				Black_Pieces ^= White_Move_To_Stack[q];
				Black_Queens |= White_Move_To_Stack[q]; 
				Black_Queens ^= White_Move_To_Stack[q]; 
				Black_Rooks |= White_Move_To_Stack[q]; 
				Black_Rooks ^= White_Move_To_Stack[q]; 
				Black_Bishops |= White_Move_To_Stack[q]; 
				Black_Bishops ^= White_Move_To_Stack[q]; 
				Black_Knights |= White_Move_To_Stack[q]; 
				Black_Knights ^= White_Move_To_Stack[q]; 
				Black_Pawns |= White_Move_To_Stack[q];  
				Black_Pawns  ^= White_Move_To_Stack[q]; 
				break;	
				
				case 6://"Plain" bishop move
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Bishops |= White_Move_To_Stack[q];
               	White_Bishops ^= White_Move_From_Stack[q];
               	break;
				   
				case 7://Rook capture
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Rooks |= White_Move_To_Stack[q];
               	White_Rooks ^= White_Move_From_Stack[q];
               	Black_Pieces |= White_Move_To_Stack[q];
				Black_Pieces ^= White_Move_To_Stack[q];
				Black_Queens |= White_Move_To_Stack[q]; 
				Black_Queens ^= White_Move_To_Stack[q]; 
				Black_Rooks |= White_Move_To_Stack[q]; 
				Black_Rooks ^= White_Move_To_Stack[q]; 
				Black_Bishops |= White_Move_To_Stack[q]; 
				Black_Bishops ^= White_Move_To_Stack[q]; 
				Black_Knights |= White_Move_To_Stack[q]; 
				Black_Knights ^= White_Move_To_Stack[q]; 
				Black_Pawns |= White_Move_To_Stack[q];  
				Black_Pawns  ^= White_Move_To_Stack[q]; 
				break;
				
				case 8://"Plain" rook move
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Rooks |= White_Move_To_Stack[q];
               	White_Rooks ^= White_Move_From_Stack[q];
               	break;
               	
               	case 9://Queen capture
               	White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Queens |= White_Move_To_Stack[q];
               	White_Queens ^= White_Move_From_Stack[q];
               	Black_Pieces |= White_Move_To_Stack[q];
				Black_Pieces ^= White_Move_To_Stack[q];
				Black_Queens |= White_Move_To_Stack[q]; 
				Black_Queens ^= White_Move_To_Stack[q]; 
				Black_Rooks |= White_Move_To_Stack[q]; 
				Black_Rooks ^= White_Move_To_Stack[q]; 
				Black_Bishops |= White_Move_To_Stack[q]; 
				Black_Bishops ^= White_Move_To_Stack[q]; 
				Black_Knights |= White_Move_To_Stack[q]; 
				Black_Knights ^= White_Move_To_Stack[q]; 
				Black_Pawns |= White_Move_To_Stack[q];  
				Black_Pawns  ^= White_Move_To_Stack[q]; 
				break;
				
				case 10://"Plain" queen move
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Queens |= White_Move_To_Stack[q];
               	White_Queens ^= White_Move_From_Stack[q];
               	break;
				
				case 11://King capture
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_King |= White_Move_To_Stack[q];
               	White_King ^= White_Move_From_Stack[q];
               	Black_Pieces |= White_Move_To_Stack[q];
				Black_Pieces ^= White_Move_To_Stack[q];
				Black_Queens |= White_Move_To_Stack[q]; 
				Black_Queens ^= White_Move_To_Stack[q]; 
				Black_Rooks |= White_Move_To_Stack[q]; 
				Black_Rooks ^= White_Move_To_Stack[q]; 
				Black_Bishops |= White_Move_To_Stack[q]; 
				Black_Bishops ^= White_Move_To_Stack[q]; 
				Black_Knights |= White_Move_To_Stack[q]; 
				Black_Knights ^= White_Move_To_Stack[q]; 
				Black_Pawns |= White_Move_To_Stack[q];  
				Black_Pawns  ^= White_Move_To_Stack[q]; 
				break; 
				
				case 12://"Plain" king move
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_King |= White_Move_To_Stack[q];
               	White_King ^= White_Move_From_Stack[q];
               	break;
				   
				case 13://Pawn promotion with capture; automatically promotes to queen
			    White_Pawns ^= White_Move_From_Stack[q];
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Queens |= White_Move_To_Stack[q];
               	Black_Pieces |= White_Move_To_Stack[q];
				Black_Pieces ^= White_Move_To_Stack[q];
				Black_Queens |= White_Move_To_Stack[q]; 
				Black_Queens ^= White_Move_To_Stack[q]; 
				Black_Rooks |= White_Move_To_Stack[q]; 
				Black_Rooks ^= White_Move_To_Stack[q]; 
				Black_Bishops |= White_Move_To_Stack[q]; 
				Black_Bishops ^= White_Move_To_Stack[q]; 
				Black_Knights |= White_Move_To_Stack[q]; 
				Black_Knights ^= White_Move_To_Stack[q]; 
				break; 
				
				case 14://"Plain" pawn promotion
			    White_Pawns ^= White_Move_From_Stack[q];
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Queens |= White_Move_To_Stack[q];
               	break;	
				   	
               	
			   }
                 
                 //Tidy up for the next call of the move generation functions
				 for(int t = 0; t < 71; t++)               
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
		int MakeBlackMove()
		{	
		Bitboard White_Pieces2 = White_Pieces; 
		Bitboard Black_Pieces2 = Black_Pieces; 
		Bitboard White_King2 = White_King;
		Bitboard Black_King2 = Black_King;
		Bitboard White_Queens2 = White_Queens;
		Bitboard White_Rooks2 = White_Rooks;
		Bitboard White_Bishops2 = White_Bishops;
		Bitboard White_Knights2 = White_Knights;
		Bitboard White_Pawns2 = White_Pawns;
		Bitboard Black_Queens2 = Black_Queens;
		Bitboard Black_Rooks2 = Black_Rooks;
		Bitboard Black_Bishops2 = Black_Bishops;
		Bitboard Black_Knights2 = Black_Knights;
		Bitboard Black_Pawns2 = Black_Pawns;
		
		for(int t = 0; t < Black_Move_Spacer; t++)
		{
			Bitboard From_Square = Black_Move_From_Stack[t];
			Bitboard To_Square = Black_Move_To_Stack[t];
			
			if(Black_Pawns & From_Square)
{
	
               	Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Pawns2 |= To_Square;
               	Black_Pawns2 ^= From_Square;
               	White_Pieces2 |= To_Square;
				White_Pieces2 ^= To_Square;
				White_Queens2 |= To_Square; 
				White_Queens2 ^= To_Square; 
				White_Rooks2 |= To_Square; 
				White_Rooks2 ^= To_Square; 
				White_Bishops2 |= To_Square; 
				White_Bishops2 ^= To_Square; 
				White_Knights2 |= To_Square; 
				White_Knights2 ^= To_Square; 
				White_Pawns2 |= To_Square;  
				White_Pawns2  ^= To_Square;
}
				
				
               	
               	
                Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Pawns2 |= To_Square;
               	Black_Pawns2 ^= From_Square;
               	
               	
             if(Black_Knights & From_Square)
			 {  	
               	Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Knights2 |= To_Square;
               	Black_Knights2 ^= From_Square;
               	White_Pieces2 |= To_Square;
				White_Pieces2 ^= To_Square;
				White_Queens2 |= To_Square; 
				White_Queens2 ^= To_Square; 
				White_Rooks2 |= To_Square; 
				White_Rooks2 ^= To_Square; 
				White_Bishops2 |= To_Square; 
				White_Bishops2 ^= To_Square; 
				White_Knights2 |= To_Square; 
				White_Knights2 ^= To_Square; 
				White_Pawns2 |= To_Square;  
				White_Pawns2  ^= To_Square;
			}
			
				
				
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Knights2 |= To_Square;
               	Black_Knights2 ^= From_Square;
               
				   
			   if(Black_Bishops & From_Square)
			   {
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Bishops2 |= To_Square;
               	Black_Bishops2 ^= From_Square;
               	White_Pieces2 |= To_Square;
				White_Pieces2 ^= To_Square;
				White_Queens2 |= To_Square; 
				White_Queens2 ^= To_Square; 
				White_Rooks2 |= To_Square; 
				White_Rooks2 ^= To_Square; 
				White_Bishops2 |= To_Square; 
				White_Bishops2 ^= To_Square; 
				White_Knights2 |= To_Square; 
				White_Knights2 ^= To_Square; 
				White_Pawns2 |= To_Square;  
				White_Pawns2  ^= To_Square;
			   }
			
				
				
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Bishops2 |= To_Square;
               	Black_Bishops2 ^= From_Square;
               	
				   
			if(Black_Rooks & From_Square)
			{
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Rooks2 |= To_Square;
               	Black_Rooks2 ^= From_Square;
               	White_Pieces2 |= To_Square;
				White_Pieces2 ^= To_Square;
				White_Queens2 |= To_Square; 
				White_Queens2 ^= To_Square; 
				White_Rooks2 |= To_Square; 
				White_Rooks2 ^= To_Square; 
				White_Bishops2 |= To_Square; 
				White_Bishops2 ^= To_Square; 
				White_Knights2 |= To_Square; 
				White_Knights2 ^= To_Square; 
				White_Pawns2 |= To_Square;  
				White_Pawns2  ^= To_Square;
			}
			
				
			
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Rooks2 |= To_Square;
               	Black_Rooks2 ^= From_Square;
               	
               	
               if(Black_Queens & From_Square)
               {
               	Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Queens2 |= To_Square;
               	Black_Queens2 ^= From_Square;
               	White_Pieces2 |= To_Square;
				White_Pieces2 ^= To_Square;
				White_Queens2 |= To_Square; 
				White_Queens2 ^= To_Square; 
				White_Rooks2 |= To_Square; 
				White_Rooks2 ^= To_Square; 
				White_Bishops2 |= To_Square; 
				White_Bishops2 ^= To_Square; 
				White_Knights2 |= To_Square; 
				White_Knights2 ^= To_Square; 
				White_Pawns2 |= To_Square;  
				White_Pawns2  ^= To_Square; 
			   }
			
				
				
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Queens2 |= To_Square;
               	Black_Queens2 ^= From_Square;
               
				
			if(Black_King & From_Square)
			{
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_King2 |= To_Square;
               	Black_King2 ^= From_Square;
               	White_Pieces2 |= To_Square;
				White_Pieces2 ^= To_Square;
				White_Queens2 |= To_Square; 
				White_Queens2 ^= To_Square; 
				White_Rooks2 |= To_Square; 
				White_Rooks2 ^= To_Square; 
				White_Bishops2 |= To_Square; 
				White_Bishops2 ^= To_Square; 
				White_Knights2 |= To_Square; 
				White_Knights2 ^= To_Square; 
				White_Pawns2 |= To_Square;  
				White_Pawns2  ^= To_Square;
			}
			
				
			
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_King2 |= To_Square;
               	Black_King2 ^= From_Square;
               	
               	
               	
               	
               	
               	Generate_White_Knight_Moves();
				Generate_White_King_Moves();
				Generate_White_Pawn_Moves();
				Generate_White_Rook_Moves();
				Generate_White_Bishop_Moves();
				Generate_White_Queen_Moves();
				
				if(White_Move_Spacer == 0)
				{
					for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & Black_Move_From_Stack[t])
        	{
        	cout << "bestmove " << PlayerMoves[h]; 
        	///Log << "bestmove " << PlayerMoves[h];
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & Black_Move_To_Stack[t])
        	{
        	cout << PlayerMoves[h] << endl; 
        	//Log << PlayerMoves[h] << endl;
        }
		}	           
				return 0;	
				}
		    
		    
		    	White_Pieces = White_Pieces2; 
				Black_Pieces = Black_Pieces2; 
		 		White_King = White_King2;
		 		Black_King = Black_King2;
		 		White_Queens = White_Queens2;
	 			White_Rooks = White_Rooks2;
			    White_Bishops = White_Bishops2;
		 		White_Knights = White_Knights2;
		 		White_Pawns = White_Pawns2;
		 		Black_Queens = Black_Queens2;
		 		Black_Rooks = Black_Rooks2;
		 		Black_Bishops = Black_Bishops2;
		 		Black_Knights = Black_Knights2;
		 		Black_Pawns = Black_Pawns2;
			
				
				
		}
		
				  srand(static_cast<unsigned int>(time(0)));

        int randomNumber = rand();
		int q;
		if(Black_Move_Spacer > 1)
        q = (randomNumber % (Black_Move_Spacer - 1));
        if(Black_Move_Spacer == 1)
        q = 0;
        if(Black_Move_Spacer == 0)
        cin >> q;
        for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & Black_Move_From_Stack[q])
        	{
        	cout << "bestmove " << PlayerMoves[h]; 
        	///Log << "bestmove " << PlayerMoves[h];
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & Black_Move_To_Stack[q])
        	{
        	cout << PlayerMoves[h] << endl; 
        	//Log << PlayerMoves[h] << endl;
        }
		}	           
			       // Update Bitboards               
               switch(Black_Move_Types[q])
               {                
               case 1:
               	Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Pawns |= Black_Move_To_Stack[q];
               	Black_Pawns ^= Black_Move_From_Stack[q];
				White_Pieces |= Black_Move_To_Stack[q];
				White_Pieces ^= Black_Move_To_Stack[q];
				White_Queens |= Black_Move_To_Stack[q]; 
				White_Queens ^= Black_Move_To_Stack[q]; 
				White_Rooks |= Black_Move_To_Stack[q]; 
				White_Rooks ^= Black_Move_To_Stack[q]; 
				White_Bishops |= Black_Move_To_Stack[q]; 
				White_Bishops ^= Black_Move_To_Stack[q]; 
				White_Knights |= Black_Move_To_Stack[q]; 
				White_Knights ^= Black_Move_To_Stack[q]; 
				White_Pawns |= Black_Move_To_Stack[q];  
				White_Pawns  ^= Black_Move_To_Stack[q]; 
               	break;
               	
               	case 2:
                Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Pawns |= Black_Move_To_Stack[q];
               	Black_Pawns ^= Black_Move_From_Stack[q];
               	break;	
               	
               	case 3:
               	Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Knights |= Black_Move_To_Stack[q];
               	Black_Knights ^= Black_Move_From_Stack[q];
				White_Pieces |= Black_Move_To_Stack[q];
				White_Pieces ^= Black_Move_To_Stack[q];
				White_Queens |= Black_Move_To_Stack[q]; 
				White_Queens ^= Black_Move_To_Stack[q]; 
				White_Rooks |= Black_Move_To_Stack[q]; 
				White_Rooks ^= Black_Move_To_Stack[q]; 
				White_Bishops |= Black_Move_To_Stack[q]; 
				White_Bishops ^= Black_Move_To_Stack[q]; 
				White_Knights |= Black_Move_To_Stack[q]; 
				White_Knights ^= Black_Move_To_Stack[q]; 
				White_Pawns |= Black_Move_To_Stack[q];  
				White_Pawns  ^= Black_Move_To_Stack[q]; 
               	break;
               	
               	case 4:
               	Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Knights |= Black_Move_To_Stack[q];
               	Black_Knights ^= Black_Move_From_Stack[q];
               	break;	
				   
				case 5:
				Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Bishops |= Black_Move_To_Stack[q];
               	Black_Bishops ^= Black_Move_From_Stack[q];
				White_Pieces |= Black_Move_To_Stack[q];
				White_Pieces ^= Black_Move_To_Stack[q];
				White_Queens |= Black_Move_To_Stack[q]; 
				White_Queens ^= Black_Move_To_Stack[q]; 
				White_Rooks |= Black_Move_To_Stack[q]; 
				White_Rooks ^= Black_Move_To_Stack[q]; 
				White_Bishops |= Black_Move_To_Stack[q]; 
				White_Bishops ^= Black_Move_To_Stack[q]; 
				White_Knights |= Black_Move_To_Stack[q]; 
				White_Knights ^= Black_Move_To_Stack[q]; 
				White_Pawns |= Black_Move_To_Stack[q];  
				White_Pawns  ^= Black_Move_To_Stack[q]; 
               	break;  	
               	
				case 6:
				Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Bishops |= Black_Move_To_Stack[q];
               	Black_Bishops ^= Black_Move_From_Stack[q];
               	break;	   	
               	
               	case 7:
               	Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Rooks |= Black_Move_To_Stack[q];
               	Black_Rooks ^= Black_Move_From_Stack[q];
				White_Pieces |= Black_Move_To_Stack[q];
				White_Pieces ^= Black_Move_To_Stack[q];
				White_Queens |= Black_Move_To_Stack[q]; 
				White_Queens ^= Black_Move_To_Stack[q]; 
				White_Rooks |= Black_Move_To_Stack[q]; 
				White_Rooks ^= Black_Move_To_Stack[q]; 
				White_Bishops |= Black_Move_To_Stack[q]; 
				White_Bishops ^= Black_Move_To_Stack[q]; 
				White_Knights |= Black_Move_To_Stack[q]; 
				White_Knights ^= Black_Move_To_Stack[q]; 
				White_Pawns |= Black_Move_To_Stack[q];  
				White_Pawns  ^= Black_Move_To_Stack[q]; 
               	break;  		
               	
               	case 8:
               	Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Rooks |= Black_Move_To_Stack[q];
               	Black_Rooks ^= Black_Move_From_Stack[q];
               	break;
				   
				case 9:	   		
                Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Queens |= Black_Move_To_Stack[q];
               	Black_Queens ^= Black_Move_From_Stack[q];
				White_Pieces |= Black_Move_To_Stack[q];
				White_Pieces ^= Black_Move_To_Stack[q];
				White_Queens |= Black_Move_To_Stack[q]; 
				White_Queens ^= Black_Move_To_Stack[q]; 
				White_Rooks |= Black_Move_To_Stack[q]; 
				White_Rooks ^= Black_Move_To_Stack[q]; 
				White_Bishops |= Black_Move_To_Stack[q]; 
				White_Bishops ^= Black_Move_To_Stack[q]; 
				White_Knights |= Black_Move_To_Stack[q]; 
				White_Knights ^= Black_Move_To_Stack[q]; 
				White_Pawns |= Black_Move_To_Stack[q];  
				White_Pawns  ^= Black_Move_To_Stack[q]; 
               	break;  		
				 
				case 10:
				Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_Queens |= Black_Move_To_Stack[q];
               	Black_Queens ^= Black_Move_From_Stack[q];
               	break; 	
               	
               	case 11:
               	Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_King |= Black_Move_To_Stack[q];
               	Black_King ^= Black_Move_From_Stack[q];
				White_Pieces |= Black_Move_To_Stack[q];
				White_Pieces ^= Black_Move_To_Stack[q];
				White_Queens |= Black_Move_To_Stack[q]; 
				White_Queens ^= Black_Move_To_Stack[q]; 
				White_Rooks |= Black_Move_To_Stack[q]; 
				White_Rooks ^= Black_Move_To_Stack[q]; 
				White_Bishops |= Black_Move_To_Stack[q]; 
				White_Bishops ^= Black_Move_To_Stack[q]; 
				White_Knights |= Black_Move_To_Stack[q]; 
				White_Knights ^= Black_Move_To_Stack[q]; 
				White_Pawns |= Black_Move_To_Stack[q];  
				White_Pawns  ^= Black_Move_To_Stack[q]; 
               	break; 
				   
				case 12:
				Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	Black_King |= Black_Move_To_Stack[q];
               	Black_King ^= Black_Move_From_Stack[q];
               	break; 
				   
				case 13: 
				Black_Pawns ^= Black_Move_From_Stack[q];
				Black_Queens |= Black_Move_To_Stack[q]; 
               	Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	White_Pieces |= Black_Move_To_Stack[q];
				White_Pieces ^= Black_Move_To_Stack[q];
				White_Queens |= Black_Move_To_Stack[q]; 
				White_Queens ^= Black_Move_To_Stack[q]; 
				White_Rooks |= Black_Move_To_Stack[q]; 
				White_Rooks ^= Black_Move_To_Stack[q]; 
				White_Bishops |= Black_Move_To_Stack[q]; 
				White_Bishops ^= Black_Move_To_Stack[q]; 
				White_Knights |= Black_Move_To_Stack[q]; 
				White_Knights ^= Black_Move_To_Stack[q]; 
				break;
				
				case 14: 
				Black_Pawns ^= Black_Move_From_Stack[q];
				Black_Queens |= Black_Move_To_Stack[q];
				Black_Pieces |= Black_Move_To_Stack[q];
               	Black_Pieces ^= Black_Move_From_Stack[q];
               	break;                 			
			   }
               	 for(int t = 0; t < 71; t++)               
               {
               	 Black_Move_From_Stack[t] = 0;
               	 Black_Move_To_Stack[t] = 0;
               	 Black_Move_Types[t] = 0;
			   }
			    Black_Knight_Spacer = 0;
			    Black_King_Spacer = 0;
			    Black_Pawn_Spacer = 0;
			    Black_Rook_Spacer = 0;
			    Black_Bishop_Spacer = 0;
			    Black_Queen_Spacer = 0;
			    Black_Move_Spacer = 0;
			    Current_Turn = true;
			    White_Turn = true;
			    return 0;
              }              
#endif
