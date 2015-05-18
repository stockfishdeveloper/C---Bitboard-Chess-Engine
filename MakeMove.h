#ifndef The_Three_Stooges 
#define The_Three_Stooges 

//*****************************************************************************************************************************************
		//White MakeMove
		
		
int MakeWhiteMove()
{
	
  
		  srand(static_cast<unsigned int>(time(0)));
		int q;
        int randomNumber = rand();
		if(White_Move_Spacer > 1)
        q = (randomNumber % (White_Move_Spacer - 1));
        if(White_Move_Spacer == 1)
        q = 0; 
        if(White_Move_Spacer == 0)
         cin >> q; 
        for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & White_Move_From_Stack[q])
        	{
        	cout << "MY MOVE IS " << PlayerMoves[h]; 
        	Dave << PlayerMoves[h];
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & White_Move_To_Stack[q])
        	{
        	cout << PlayerMoves[h] << endl; 
        	Dave << PlayerMoves[h] << endl;
        }
		}
		
               // Update Bitboards
               switch(White_Move_Types[q])
               { 
               
               case 1:
               	White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Pawns |= White_Move_To_Stack[q];
               	White_Pawns ^= White_Move_From_Stack[q];
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
				
               	
               	case 2:
                White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Pawns |= White_Move_To_Stack[q];
               	White_Pawns ^= White_Move_From_Stack[q];
               	break;	
               	
               	
               	case 3:
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
				
				case 4:
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Knights |= White_Move_To_Stack[q];
               	White_Knights ^= White_Move_From_Stack[q];
               	break;
				   
			    case 5:
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
				
				case 6:
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Bishops |= White_Move_To_Stack[q];
               	White_Bishops ^= White_Move_From_Stack[q];
               	break;
				   
				case 7:
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
				
				case 8:
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Rooks |= White_Move_To_Stack[q];
               	White_Rooks ^= White_Move_From_Stack[q];
               	break;
               	
               	case 9:
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
				
				case 10:
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Queens |= White_Move_To_Stack[q];
               	White_Queens ^= White_Move_From_Stack[q];
               	break;
				
				case 11:
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
				
				case 12:
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_King |= White_Move_To_Stack[q];
               	White_King ^= White_Move_From_Stack[q];
               	break;
				   
				case 13:
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
				
				case 14:
			    White_Pawns ^= White_Move_From_Stack[q];
				White_Pieces |= White_Move_To_Stack[q];
               	White_Pieces ^= White_Move_From_Stack[q];
               	White_Queens |= White_Move_To_Stack[q];
               	break;	
				   	
               	
			   }
                 
				 for(int t = 0; t < 71; t++)               
               {
               	 White_Move_From_Stack[t] = 0;
               	 White_Move_To_Stack[t] = 0;
               	 White_Move_Types[t] = 0;
			   }
			    White_Knight_Spacer = 0;
			    White_King_Spacer = 0;
			    White_Pawn_Spacer = 0;
			    White_Rook_Spacer = 0;
			    White_Bishop_Spacer = 0;
			    White_Queen_Spacer = 0;
			    White_Move_Spacer = 0;
			    return 0;
			   
            }
            
            	 
				 
		//*****************************************************************************************************************************************
		//Black MakeMove
		
		int MakeBlackMove()
		{		 
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
        	cout << "MY MOVE IS " << PlayerMoves[h]; 
        	Dave << PlayerMoves[h];
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & Black_Move_To_Stack[q])
        	{
        	cout << PlayerMoves[h] << endl; 
        	Dave << PlayerMoves[h] << endl;
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
               		//Dave << Black_Move_From_Stack[q] << " " << Black_Move_To_Stack[q] << endl;
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
				   
				case 13: // Promotion and a capture
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
				
				case 14: // Plain promotion
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
			    return 0;
               
            }
              
#endif
