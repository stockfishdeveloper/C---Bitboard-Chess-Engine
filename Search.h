#ifndef Food
#define Food
/*Bitboard White_Pieces2 = White_Pieces; 
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
Bitboard Black_Pawns2 = Black_Pawns;*/
class Move
{
	public:
		Bitboard From;
		Bitboard To;
		int Move_Type;
		int Depth;
		
		Bitboard White_Temp_Move_From_Stack[70];
		Bitboard White_Temp_Move_To_Stack[70];
		Bitboard Black_Temp_Move_From_Stack[70];
		Bitboard Black_Temp_Move_To_Stack[70];
		int White_Temp_Move_Types[70];
		int Black_Temp_Move_Types[70];
		int White_Temp_Move_Spacer = 0; 
		int Black_Temp_Move_Spacer = 0;
		
		Bitboard White_Pieces2; 
		Bitboard Black_Pieces2; 
		Bitboard White_King2;
		Bitboard Black_King2;
		Bitboard White_Queens2;
		Bitboard White_Rooks2;
		Bitboard White_Bishops2;
		Bitboard White_Knights2;
		Bitboard White_Pawns2;
		Bitboard Black_Queens2;
		Bitboard Black_Rooks2;
		Bitboard Black_Bishops2;
		Bitboard Black_Knights2;
		Bitboard Black_Pawns2;
		int Undo_Move();
		Move()
		{
		White_Pieces2 = White_Pieces; 
		Black_Pieces2 = Black_Pieces; 
		White_King2 = White_King;
		Black_King2 = Black_King;
		White_Queens2 = White_Queens;
		White_Rooks2 = White_Rooks;
		White_Bishops2 = White_Bishops;
		White_Knights2 = White_Knights;
		White_Pawns2 = White_Pawns;
		Black_Queens2 = Black_Queens;
		Black_Rooks2 = Black_Rooks;
		Black_Bishops2 = Black_Bishops;
		Black_Knights2 = Black_Knights;
		Black_Pawns2 = Black_Pawns;
		}		
};


int Move::Undo_Move()
{
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
	White_Move_Spacer = White_Temp_Move_Spacer;
	Black_Move_Spacer = Black_Temp_Move_Spacer;
	for(int h = 0; h < White_Temp_Move_Spacer; h++)
			{
				White_Move_From_Stack[h] = White_Temp_Move_From_Stack[h];
				White_Move_To_Stack[h] = White_Temp_Move_To_Stack[h];
				White_Move_Types[h] = White_Temp_Move_Types[h];
				//cout << "Restoring white.... " << h << endl;
			}
			
	for(int h = 0; h < Black_Temp_Move_Spacer; h++)
	{
		Black_Move_From_Stack[h] = Black_Temp_Move_From_Stack[h];
		Black_Move_To_Stack[h] = Black_Temp_Move_To_Stack[h];
		Black_Move_Types[h] = Black_Temp_Move_Types[h];
		//cout << "Restoring black...." << h << endl;
	}
	Current_Turn ^= 1;
	White_Turn ^= 1;
	//cout << "Undoing move...." << endl;
	return 0;
}


int Search(int depth);
int Evaluate_Position();
int Valuate_Bitboards(Bitboard Any_Bitboard);
int Make_White_Search_Move(Bitboard From, Bitboard To, int Move_Type);
int Make_Black_Search_Move(Bitboard From, Bitboard To, int Move_Type);
bool Fake_Current_Turn = Current_Turn;
bool Fake_Whte_Turn = White_Turn; 
int White_Move_Score = 0;
int White_Static_Score = 0;
int Black_Move_Score = 0;
int Black_Static_Score = 0;
Bitboard Move_From;
Bitboard Move_To;
int Pos_Score;
int Best_Move;
int Nodes;



int Search(int depth)
{
	//cout << "\b\b\b\b\b\b\b\b\b" << ++Nodes;
	//depth--;
	if(White_Turn)
	{//cout << "In white search!" << endl;
		Generate_White_Knight_Moves();
		Generate_White_King_Moves();
		Generate_White_Pawn_Moves();
		Generate_White_Rook_Moves();
		Generate_White_Bishop_Moves();
		Generate_White_Queen_Moves();
		Move move;
		move.White_Temp_Move_Spacer = White_Move_Spacer;
		//cout << move.White_Temp_Move_Spacer << endl;
		for(int h = 0; h < White_Move_Spacer; h++)
			{
				move.White_Temp_Move_From_Stack[h] = White_Move_From_Stack[h];
				move.White_Temp_Move_To_Stack[h] = White_Move_To_Stack[h];
				move.White_Temp_Move_Types[h] = White_Move_Types[h];
			}
		for(int i = 0; i < White_Move_Spacer; i++)
		{ //++Nodes;
			Log << cout << "Making white's " << i << "th move" << endl; 
			move.From = White_Move_From_Stack[i];
			move.To = White_Move_To_Stack[i];
			move.Move_Type = White_Move_Types[i];
			/******************************************************************************/
			for( int h = 0; h < 64; h++)
			{
        	if(GeneralBoard[h] & move.From)//Get the index in GeneralBoard[] of the square the current pieces is moving from
        	{
        	Log << PlayerMoves[h];//Cout it to the user, but don't endl because we have to display the whole move squashed togather, e.g. d2d4
        	//Log << "bestmove " << PlayerMoves[h];//Put it out to the text file
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & move.To)//For each to square found
        	{
        	Log << PlayerMoves[h] << endl;//cout it and
        	//Log << PlayerMoves[h] << endl;//Put it into the text file; now we can do a new line because we are done with the current move
        }
		}		
			/*********************************************************************************/
			Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]);
			
			if(depth == 1)
			{ ++Nodes;//cout << "Hit white bottom!" << endl;
			int Temp = Evaluate_Position();
			if(Temp > Pos_Score)
			{
				Best_Move = i;
				Pos_Score = Temp;
			}
			move.Undo_Move();
			continue;
			}
			
			Search(depth - 1);
			move.Undo_Move();
			//cout << "Undid white move!" << endl;	
		
		
		}
		
	}
	
	else
	{
	//cout << "\b\b\b\b\b\b\b\b\b" << Nodes;
	//cout << "In black search!" << endl;
		Generate_Black_Knight_Moves();
		Generate_Black_King_Moves();
		Generate_Black_Pawn_Moves();
		Generate_Black_Rook_Moves();
		Generate_Black_Bishop_Moves();
		Generate_Black_Queen_Moves();
		Move move;
		move.Black_Temp_Move_Spacer = Black_Move_Spacer;
		
		for(int h = 0; h < Black_Move_Spacer; h++)
			{
				move.Black_Temp_Move_From_Stack[h] = Black_Move_From_Stack[h];
				move.Black_Temp_Move_To_Stack[h] = Black_Move_To_Stack[h];
				move.Black_Temp_Move_Types[h] = Black_Move_Types[h];
			}
		for(int i = 0; i < Black_Move_Spacer; i++)
		{ //++Nodes;
			Log << "Making black's " << i << "th move" << endl; 
			move.From = Black_Move_From_Stack[i];
			move.To = Black_Move_To_Stack[i];
			move.Move_Type = Black_Move_Types[i];
				/******************************************************************************/
			for( int h = 0; h < 64; h++)
			{
        	if(GeneralBoard[h] & move.From)//Get the index in GeneralBoard[] of the square the current pieces is moving from
        	{
        	Log << PlayerMoves[h];//Cout it to the user, but don't endl because we have to display the whole move squashed togather, e.g. d2d4
        	//Log << "bestmove " << PlayerMoves[h];//Put it out to the text file
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & move.To)//For each to square found
        	{
        	Log << PlayerMoves[h] << endl;//cout it and
        	//Log << PlayerMoves[h] << endl;//Put it into the text file; now we can do a new line because we are done with the current move
        }
		}		
			/*********************************************************************************/
			
			Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
			
						
			if(depth == 1)
			{ ++Nodes;
				//cout << "Hit black bottom!" << endl;
			int Temp = Evaluate_Position();
			if(Temp < Pos_Score)
			{
				Best_Move = i;
				Pos_Score = Temp;
			}
			move.Undo_Move();
			continue;
			}
			Search(depth - 1);
			move.Undo_Move();	
		//cout << "Undid black move!" << endl;
			
		
		}
		
	}
	return 0;
}

int Make_White_Search_Move(Bitboard From, Bitboard To, int Move_Type)
{//cout << "Making white move..." << endl;
//cout << "\b\b\b\b\b\b\b\b\b" << ++Nodes;
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
		
			    Current_Turn ^= 1;
			    White_Turn ^= 1;
			    return 0;

}


int Make_Black_Search_Move(Bitboard From, Bitboard To, int Move_Type)
{//cout << "Making black move..." << endl;
//cout << "\b\b\b\b\b\b\b\b\b" << ++Nodes;
	switch(Move_Type)//This switch evaluates the type of move that accompanies the index of the move stack that q refers to
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
		
			    Current_Turn ^= 1;
			    White_Turn ^= 1;
			    return 0;

}

int Evaluate_Position()
{
	int Value = (Valuate_Bitboards(White_Pieces) - Valuate_Bitboards(Black_Pieces));
	return Value;
}



int Valuate_Bitboards(Bitboard Any_Bitboard)
{
	int Num = 0;
	for(int i = 0; i < 64; i++)
	{
		if(GeneralBoard[i] & Any_Bitboard)
		Num++;
	}
	return Num;
}

#endif
