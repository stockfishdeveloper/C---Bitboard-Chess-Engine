using namespace std;
#include <iostream>
#include <cstring>
#include "Bitboard.h"
#include "Search.h"
#include "Eval.h"
#include "UCI.h"
#include "MakeMove.h"
#include <chrono>

int White_Move_Score = 0;
int White_Static_Score = 0; 
int Black_Move_Score = 0;
int Black_Static_Score = 0;
Bitboard Move_From = 0;
Bitboard Move_To = 0;
int Leaf_Score = 0;
int Best_Move = 0;
int Nodes = 0;
bool Searching = false;
int Depthy = 1000;
bool Time_Out = false;
int Depth = 0;
int Seldepth = 0;

Move Think(int wtime, int btime, int winc, int binc)
{
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();
    
    int Wtime = wtime;
	int Btime = Btime;
	int Winc = winc;
	int Binc = binc;
	Move blank;
	Move Spar;
	Spar.Score = -100.0;
 	Move Spar2;
 	Spar2.Score = 100.0;
	const int MAXDEPTH = 50;
	int Plies_Searched = 0;
	
	for(int q = 4; q < MAXDEPTH; q++)
	{
	if(White_Turn == true)
	{
    blank = SearchMax(Spar, Spar2, (q - Plies_Searched) + 1, &line);
    //Plies_Searched = q;
    auto t1 = Time::now();
	fsec fs = t1 - t0;
	ms d = std::chrono::duration_cast<ms>(fs);
	Depth = q;
	if((d.count() * 3) > (Wtime / 30))
	{
		return blank;
	}
	}
    else
    {
    blank = SearchMin(Spar, Spar2, (q - Plies_Searched) + 1, &line);
    //Plies_Searched = q;
    auto t1 = Time::now();
	fsec fs = t1 - t0;
	ms d = std::chrono::duration_cast<ms>(fs);
	Depth = q;
	if((d.count() * 3) > (Btime / 30))
	{
		return blank;
	}
	}
	
		LINE* f = new LINE;
		f->cmove = 0;
		::line = *f;
		delete f;
	
	}
	return blank;
}

Move SearchMax(Move alpha, Move beta, int depth, LINE * pline)
{
	
//if(depth > Depth)
//{

Seldepth = depth;
//}
/*else
		{
			Depth = depth;
		}*/
	
	//Best.Score = -100;
	
	LINE line;
	
		    if(depth == 1)
			{ 	
			Move Best;
			++Nodes;
			Best.Score = Evaluate_Position();
			pline->cmove = 0;
			pline->score = Best.Score;
			//Log << "Depth is 1, score is " << Temp << endl;
			return Best;
			}
		Generate_White_Knight_Moves();
		Generate_White_King_Moves();
		Generate_White_Pawn_Moves();
		Generate_White_Rook_Moves();
		Generate_White_Bishop_Moves();
		Generate_White_Queen_Moves();
		register Move move;
		move.White_Temp_Move_Spacer = White_Move_Spacer;
		for(int h = 0; h < White_Move_Spacer; h++)
			{
				move.White_Temp_Move_From_Stack[h] = White_Move_From_Stack[h];
				move.White_Temp_Move_To_Stack[h] = White_Move_To_Stack[h];
				move.White_Temp_Move_Types[h] = White_Move_Types[h];
			}
		for(int i = 0; i < White_Move_Spacer; i++)
		{ 
			move.From = White_Move_From_Stack[i];
			move.To = White_Move_To_Stack[i];
			move.Move_Type = White_Move_Types[i];
			Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]);
			
			//int Temp = Evaluate_Position();
			
			Move Temp_Move = SearchMin(alpha, beta, depth - 1, &line);
			float Curr_Move_Score = Evaluate_Position();
			move.Undo_Move();
			if(Temp_Move.Score >= beta.Score)
			{
				return beta;
			}
			
			//if(Best.Score < Temp_Move.Score)
			//{
				//Best = move;
				//Best.Score = Temp_Move.Score;
			//}
			if(Temp_Move.Score  > alpha.Score)
			{
				pline->argmove[0] = move;
				::line.score = Curr_Move_Score;
            memcpy(pline->argmove + 1, line.argmove,

                line.cmove * sizeof(Move));

            pline->cmove = line.cmove + 1;


				alpha = move;
				alpha.Score = Temp_Move.Score;
			}
			
		}
		
		return alpha;
}
	
	
	Move SearchMin(Move alpha, Move beta, int depth, LINE * pline)
	{
		Seldepth = depth;
		/*if(depth < Depthy)
		{
		cout << "info depth " << depth << endl;
		Depthy = depth;
		}
		else
		{
			cout << "seldepth " << depth << endl;
		}*/
		
		//Best.Score = 100;
		
		LINE line;
		
		if(depth == 1)
			{ 
			Move Best;
			++Nodes;
			Best.Score = Evaluate_Position();
			pline->cmove = 0;
			pline->score = Best.Score;
			//Log << "Depth is 1, score is " << Temp << endl;
			return Best;
			}
		Generate_Black_Knight_Moves();
		Generate_Black_King_Moves();
		Generate_Black_Pawn_Moves();
		Generate_Black_Rook_Moves();
		Generate_Black_Bishop_Moves();
		Generate_Black_Queen_Moves();
		register Move move;
		move.Black_Temp_Move_Spacer = Black_Move_Spacer;
		
		for(int h = 0; h < Black_Move_Spacer; h++)
			{
				move.Black_Temp_Move_From_Stack[h] = Black_Move_From_Stack[h];
				move.Black_Temp_Move_To_Stack[h] = Black_Move_To_Stack[h];
				move.Black_Temp_Move_Types[h] = Black_Move_Types[h];
			}
		for(int i = 0; i < Black_Move_Spacer; i++)
		{ 
			//Log << "Making black's " << i << "th move" << endl; 
			move.From = Black_Move_From_Stack[i];
			move.To = Black_Move_To_Stack[i];
			move.Move_Type = Black_Move_Types[i];
				/******************************************************************************/
			/*for( int h = 0; h < 64; h++)
			{
        	if(GeneralBoard[h] & move.From)
        	{
        	//Log << PlayerMoves[h];
        	
        }
		}
		for( int h = 0; h < 64; h++)
        {
        	if(GeneralBoard[h] & move.To)
        	{
        	//Log << PlayerMoves[h] << endl;
        	
        }
		}*/		
			/*********************************************************************************/
			
			Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
			
			Move Temp_Move = SearchMax(alpha, beta, depth - 1, &line);
			float Curr_Move_Score = Evaluate_Position();
			move.Undo_Move();
			//Log << "Branch score: " << Temp_Move.Score << endl; 
			if(Temp_Move.Score <= alpha.Score)
			{
				return alpha;
			}
			
			//if(Best.Score > Temp_Move.Score)
			//{
				//Best = move;
				//Best.Score = Temp_Move.Score;
			//}
			if(Temp_Move.Score < beta.Score)
			{
				pline->argmove[0] = move;
				::line.score = Curr_Move_Score;
            memcpy(pline->argmove + 1, line.argmove,

                line.cmove * sizeof(Move));

            pline->cmove = line.cmove + 1;
				beta = move;
				beta.Score = Temp_Move.Score;
			}
			
		}
		return beta;
	

}

int Make_White_Search_Move(Bitboard& From, Bitboard& To, int Move_Type)
{

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
               	
               	/*case 15://White king kingside castling
				White_Pieces |= To;
               	White_Pieces ^= From;
               	White_Pieces |= 32;
               	White_Pieces ^= 128;
               	White_Rooks |= 32;
               	White_Rooks ^= 128;
               	White_King |= To;
               	White_King ^= From;
               	break;*/
				   	
               	
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


int Make_Black_Search_Move(Bitboard& From, Bitboard& To, int Move_Type)
{
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
				 
				/*case 15: 			
				Black_Pieces |= To;
            	Black_Pieces ^= From;
            	Black_Pieces |= 4611686018427387904;
            	Black_Pieces ^= 1152921504606846976;
            	Black_Rooks |= 2305843009213693952;
            	Black_Rooks ^= 9223372036854775808ULL;
            	Black_King |= To;
            	Black_King ^= From;
            	break;*/
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
