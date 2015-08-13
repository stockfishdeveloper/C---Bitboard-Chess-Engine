#ifndef Food
#define Food
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
		int White_Temp_Move_Spacer; 
		int Black_Temp_Move_Spacer;
		
		Bitboard White_Pieces3; 
		Bitboard Black_Pieces3; 
		Bitboard White_King3;
		Bitboard Black_King3;
		Bitboard White_Queens3;
		Bitboard White_Rooks3;
		Bitboard White_Bishops3;
		Bitboard White_Knights3;
		Bitboard White_Pawns3;
		Bitboard Black_Queens3;
		Bitboard Black_Rooks3;
		Bitboard Black_Bishops3;
		Bitboard Black_Knights3;
		Bitboard Black_Pawns3;
		int Undo_Move();
		Move()
		{
		White_Pieces3 = White_Pieces2; 
		Black_Pieces3 = Black_Pieces2; 
		White_King3 = White_King2;
		Black_King3 = Black_King2;
		White_Queens3 = White_Queens2;
		White_Rooks3 = White_Rooks2;
		White_Bishops3 = White_Bishops2;
		White_Knights3 = White_Knights2;
		White_Pawns3 = White_Pawns2;
		Black_Queens3 = Black_Queens2;
		Black_Rooks3 = Black_Rooks2;
		Black_Bishops3 = Black_Bishops2;
		Black_Knights3 = Black_Knights2;
		Black_Pawns3 = Black_Pawns2;
		}		
};


int Move::Undo_Move()
{
	White_Pieces2 = White_Pieces3; 
	Black_Pieces2 = Black_Pieces3; 
	White_King2 = White_King3;
	Black_King2 = Black_King3;
	White_Queens2 = White_Queens3;
	White_Rooks2 = White_Rooks3;
	White_Bishops2 = White_Bishops3;
	White_Knights2 = White_Knights3;
	White_Pawns2 = White_Pawns3;
	Black_Queens2 = Black_Queens3;
	Black_Rooks2 = Black_Rooks3;
	Black_Bishops2 = Black_Bishops3;
	Black_Knights2 = Black_Knights3;
	Black_Pawns2 = Black_Pawns3;
	White_Move_Spacer = White_Temp_Move_Spacer;
	Black_Move_Spacer = Black_Temp_Move_Spacer;
	for(int h = 0; h < White_Temp_Move_Spacer; h++)
			{
				White_Move_From_Stack[h] = White_Temp_Move_From_Stack[h];
				White_Move_To_Stack[h] = White_Temp_Move_To_Stack[h];
				White_Move_Types[h] = White_Temp_Move_Types[h];
				cout << "Restoring white.... " << h << endl;
			}
			cout << "In between!" << endl;
	for(int h = 0; h < Black_Temp_Move_Spacer; h++)
	{
		Black_Move_From_Stack[h] = Black_Temp_Move_From_Stack[h];
		Black_Move_To_Stack[h] = Black_Temp_Move_To_Stack[h];
		Black_Move_Types[h] = Black_Temp_Move_Types[h];
		cout << "Restoring black...." << endl;
	}
	Current_Turn ^= 1;
	White_Turn ^= 1;
	cout << "Undoing move...." << endl;
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
	
	//depth--;
	if(White_Turn)
	{cout << "In white search!" << endl;
		Generate_White_Knight_Moves();
		Generate_White_King_Moves();
		Generate_White_Pawn_Moves();
		Generate_White_Rook_Moves();
		Generate_White_Bishop_Moves();
		Generate_White_Queen_Moves();
		for(int i = 0; i < White_Move_Spacer; i++)
		{//cout << ++Nodes << endl;
			Move move;
			move.From = White_Move_From_Stack[i];
			move.To = White_Move_To_Stack[i];
			move.Move_Type = White_Move_Types[i];
			move.White_Temp_Move_Spacer = White_Move_Spacer;
			for(int h = 0; h < White_Move_Spacer; h++)
			{
				move.White_Temp_Move_From_Stack[h] = White_Move_From_Stack[h];
				move.White_Temp_Move_To_Stack[h] = White_Move_To_Stack[h];
				move.White_Temp_Move_Types[h] = White_Move_Types[h];
			}
			Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]);
			
			if(depth == 1)
			{cout << "Hit white bottom!" << endl;
			int Temp = Evaluate_Position();
			if(Temp > Pos_Score)
			{
				Best_Move = i;
			}
			move.Undo_Move();
			cout << "Made it!" << endl;
			return 0;
			}
			
			Search(depth - 1);
			move.Undo_Move();
			cout << "Undid white move!" << endl;	
		
		
		}
		
	}
	
	else
	{
	
	cout << "In black search!" << endl;
		Generate_Black_Knight_Moves();
		Generate_Black_King_Moves();
		Generate_Black_Pawn_Moves();
		Generate_Black_Rook_Moves();
		Generate_Black_Bishop_Moves();
		Generate_Black_Queen_Moves();
		for(int i = 0; i < Black_Move_Spacer; i++)
		{//cout << ++Nodes << endl;
			Move move;
			move.From = Black_Move_From_Stack[i];
			move.To = Black_Move_To_Stack[i];
			move.Move_Type = Black_Move_Types[i];
			move.Black_Temp_Move_Spacer = Black_Move_Spacer;
			for(int h = 0; h < Black_Move_Spacer; h++)
			{
				move.Black_Temp_Move_From_Stack[h] = Black_Move_From_Stack[h];
				move.Black_Temp_Move_To_Stack[h] = Black_Move_To_Stack[h];
				move.Black_Temp_Move_Types[h] = Black_Move_Types[h];
			}
			Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
			
						
			if(depth == 1)
			{
				cout << "Hit black bottom!" << endl;
			int Temp = Evaluate_Position();
			if(Temp > Pos_Score)
			{
				Best_Move = i;
			}
			move.Undo_Move();
			cout << "Made it!" << endl;
			return 0;
			}
			Search(depth - 1);
			move.Undo_Move();	
		cout << "Undid black move!" << endl;
			
		
		}
		
	}
	return 0;
}

int Make_White_Search_Move(Bitboard From, Bitboard To, int Move_Type)
{cout << "Making white move..." << endl;
	switch(Move_Type)//This switch evaluates the type of move that accompanies the index of the move stack that q refers to
               { 
               
               case 1://A (white) pawn capture
               	White_Pieces2 |= To;//Move white's pieces to the to square and from the from square
               	White_Pieces2 ^= From;
               	White_Pawns2 |= To;
               	White_Pawns2 ^= From;
               	Black_Pieces2 |= To;//Do the same for the black pieces because it is a capture: we have to remove a black piece
				Black_Pieces2 ^= To;
				Black_Queens2 |= To; 
				Black_Queens2 ^= To; 
				Black_Rooks2 |= To; 
				Black_Rooks2 ^= To; 
				Black_Bishops2 |= To; 
				Black_Bishops2 ^= To; 
				Black_Knights2 |= To; 
				Black_Knights2 ^= To; 
				Black_Pawns2 |= To;  
				Black_Pawns2  ^= To; 
				break;
				
               	
               	case 2://"Plain" pawn push: one square
                White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Pawns2 |= To;
               	White_Pawns2 ^= From;
               	break;	
               	
               	
               	case 3://Knight Capture
               	White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Knights2 |= To;
               	White_Knights2 ^= From;
               	Black_Pieces2 |= To;
				Black_Pieces2 ^= To;
				Black_Queens2 |= To; 
				Black_Queens2 ^= To; 
				Black_Rooks2 |= To; 
				Black_Rooks2 ^= To; 
				Black_Bishops2 |= To; 
				Black_Bishops2 ^= To; 
				Black_Knights2 |= To; 
				Black_Knights2 ^= To; 
				Black_Pawns2 |= To;  
				Black_Pawns2  ^= To; 
				break;
				
				case 4://Plain knight move
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Knights2 |= To;
               	White_Knights2 ^= From;
               	break;
				   
			    case 5://Bishop capture
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Bishops2 |= To;
               	White_Bishops2 ^= From;
               	Black_Pieces2 |= To;
				Black_Pieces2 ^= To;
				Black_Queens2 |= To; 
				Black_Queens2 ^= To; 
				Black_Rooks2 |= To; 
				Black_Rooks2 ^= To; 
				Black_Bishops2 |= To; 
				Black_Bishops2 ^= To; 
				Black_Knights2 |= To; 
				Black_Knights2 ^= To; 
				Black_Pawns2 |= To;  
				Black_Pawns2  ^= To; 
				break;	
				
				case 6://"Plain" bishop move
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Bishops2 |= To;
               	White_Bishops2 ^= From;
               	break;
				   
				case 7://Rook capture
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Rooks2 |= To;
               	White_Rooks2 ^= From;
               	Black_Pieces2 |= To;
				Black_Pieces2 ^= To;
				Black_Queens2 |= To; 
				Black_Queens2 ^= To; 
				Black_Rooks2 |= To; 
				Black_Rooks2 ^= To; 
				Black_Bishops2 |= To; 
				Black_Bishops2 ^= To; 
				Black_Knights2 |= To; 
				Black_Knights2 ^= To; 
				Black_Pawns2 |= To;  
				Black_Pawns2  ^= To; 
				break;
				
				case 8://"Plain" rook move
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Rooks2 |= To;
               	White_Rooks2 ^= From;
               	break;
               	
               	case 9://Queen capture
               	White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Queens2 |= To;
               	White_Queens2 ^= From;
               	Black_Pieces2 |= To;
				Black_Pieces2 ^= To;
				Black_Queens2 |= To; 
				Black_Queens2 ^= To; 
				Black_Rooks2 |= To; 
				Black_Rooks2 ^= To; 
				Black_Bishops2 |= To; 
				Black_Bishops2 ^= To; 
				Black_Knights2 |= To; 
				Black_Knights2 ^= To; 
				Black_Pawns2 |= To;  
				Black_Pawns2  ^= To; 
				break;
				
				case 10://"Plain" queen move
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Queens2 |= To;
               	White_Queens2 ^= From;
               	break;
				
				case 11://King capture
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_King2 |= To;
               	White_King2 ^= From;
               	Black_Pieces2 |= To;
				Black_Pieces2 ^= To;
				Black_Queens2 |= To; 
				Black_Queens2 ^= To; 
				Black_Rooks2 |= To; 
				Black_Rooks2 ^= To; 
				Black_Bishops2 |= To; 
				Black_Bishops2 ^= To; 
				Black_Knights2 |= To; 
				Black_Knights2 ^= To; 
				Black_Pawns2 |= To;  
				Black_Pawns2  ^= To; 
				break; 
				
				case 12://"Plain" king move
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_King2 |= To;
               	White_King2 ^= From;
               	break;
				   
				case 13://Pawn promotion with capture; automatically promotes to queen
			    White_Pawns2 ^= From;
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Queens2 |= To;
               	Black_Pieces2 |= To;
				Black_Pieces2 ^= To;
				Black_Queens2 |= To; 
				Black_Queens2 ^= To; 
				Black_Rooks2 |= To; 
				Black_Rooks2 ^= To; 
				Black_Bishops2 |= To; 
				Black_Bishops2 ^= To; 
				Black_Knights2 |= To; 
				Black_Knights2 ^= To; 
				break; 
				
				case 14://"Plain" pawn promotion
			    White_Pawns2 ^= From;
				White_Pieces2 |= To;
               	White_Pieces2 ^= From;
               	White_Queens2 |= To;
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
{cout << "Making black move..." << endl;
	switch(Move_Type)//This switch evaluates the type of move that accompanies the index of the move stack that q refers to
               { 
               
               case 1://A (white) pawn capture
               	Black_Pieces2 |= To;//Move white's pieces to the to square and from the from square
               	Black_Pieces2 ^= From;
               	Black_Pawns2 |= To;
               	Black_Pawns2 ^= From;
               	White_Pieces2 |= To;//Do the same for the black pieces because it is a capture: we have to remove a black piece
				White_Pieces2 ^= To;
				White_Queens2 |= To; 
				White_Queens2 ^= To; 
				White_Rooks2 |= To; 
				White_Rooks2 ^= To; 
				White_Bishops2 |= To; 
				White_Bishops2 ^= To; 
				White_Knights2 |= To; 
				White_Knights2 ^= To; 
				White_Pawns2 |= To;  
				White_Pawns2  ^= To; 
				break;
				
               	
               	case 2://"Plain" pawn push: one square
                Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Pawns2 |= To;
               	Black_Pawns2 ^= From;
               	break;	
               	
               	
               	case 3://Knight Capture
               	Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Knights2 |= To;
               	Black_Knights2 ^= From;
               	White_Pieces2 |= To;
				White_Pieces2 ^= To;
				White_Queens2 |= To;
				White_Queens2 ^= To; 
				White_Rooks2 |= To; 
				White_Rooks2 ^= To; 
				White_Bishops2 |= To; 
				White_Bishops2 ^= To; 
				White_Knights2 |= To; 
				White_Knights2 ^= To; 
				White_Pawns2 |= To;  
				White_Pawns2  ^= To; 
				break;
				
				case 4://"Plain" knight move
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Knights2 |= To;
               	Black_Knights2 ^= From;
               	break;
				   
			    case 5://Bishop capture
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Bishops2 |= To;
               	Black_Bishops2 ^= From;
               	White_Pieces2 |= To;
				White_Pieces2 ^= To;
				White_Queens2 |= To; 
				White_Queens2 ^= To; 
				White_Rooks2 |= To; 
				White_Rooks2 ^= To; 
				White_Bishops2 |= To; 
				White_Bishops2 ^= To; 
				White_Knights2 |= To; 
				White_Knights2 ^= To; 
				White_Pawns2 |= To;  
				White_Pawns2  ^= To; 
				break;	
				
				case 6://"Plain" bishop move
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Bishops2 |= To;
               	Black_Bishops2 ^= From;
               	break;
				   
				case 7://Rook capture
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Rooks2 |= To;
               	Black_Rooks2 ^= From;
               	White_Pieces2 |= To;
				White_Pieces2 ^= To;
				White_Queens2 |= To; 
				White_Queens2 ^= To; 
				White_Rooks2 |= To; 
				White_Rooks2 ^= To; 
				White_Bishops2 |= To; 
				White_Bishops2 ^= To; 
				White_Knights2 |= To; 
				White_Knights2 ^= To; 
				White_Pawns2 |= To;  
				White_Pawns2  ^= To; 
				break;
				
				case 8://"Plain" rook move
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Rooks2 |= To;
               	Black_Rooks2 ^= From;
               	break;
               	
               	case 9://Queen capture
               	Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Queens2 |= To;
               	Black_Queens2 ^= From;
               	White_Pieces2 |= To;
				White_Pieces2 ^= To;
				White_Queens2 |= To; 
				White_Queens2 ^= To; 
				White_Rooks2 |= To; 
				White_Rooks2 ^= To; 
				White_Bishops2 |= To; 
				White_Bishops2 ^= To; 
				White_Knights2 |= To; 
				White_Knights2 ^= To; 
				White_Pawns2 |= To;  
				White_Pawns2  ^= To; 
				break;
				
				case 10://"Plain" queen move
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Queens2 |= To;
               	Black_Queens2 ^= From;
               	break;
				
				case 11://King capture
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_King2 |= To;
               	Black_King2 ^= From;
               	White_Pieces2 |= To;
				White_Pieces2 ^= To;
				White_Queens2 |= To; 
				White_Queens2 ^= To; 
				White_Rooks2 |= To; 
				White_Rooks2 ^= To; 
				White_Bishops2 |= To; 
				White_Bishops2 ^= To; 
				White_Knights2 |= To; 
				White_Knights2 ^= To; 
				White_Pawns2 |= To;  
				White_Pawns2  ^= To; 
				break; 
				
				case 12://"Plain" king move
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_King2 |= To;
               	Black_King2 ^= From;
               	break;
				   
				case 13://Pawn promotion with capture; automatically promotes to queen
			    Black_Pawns2 ^= From;
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Queens2 |= To;
               	White_Pieces2 |= To;
				White_Pieces2 ^= To;
				White_Queens2 |= To; 
				White_Queens2 ^= To; 
				White_Rooks2 |= To; 
				White_Rooks2 ^= To; 
				White_Bishops2 |= To; 
				White_Bishops2 ^= To; 
				White_Knights2 |= To; 
				White_Knights2 ^= To; 
				break; 
				
				case 14://"Plain" pawn promotion
			    Black_Pawns2 ^= From;
				Black_Pieces2 |= To;
               	Black_Pieces2 ^= From;
               	Black_Queens2 |= To;
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
	int Value = (Valuate_Bitboards(White_Pieces2) - Valuate_Bitboards(Black_Pieces2));
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
