using namespace std;
#include <iostream>
#include <cstring>
#include <cassert>
#include "Bitboard.h"
#include "Search.h"
#include "Eval.h"
#include "UCI.h"
#include <chrono>
#include "magicmoves.h"

int Search::Time_Allocation = 0;
bool Search::Searching = false;
Bitboard Search::Nodes = 0;
int Search::Depth = 0;
int Search::Seldepth = 0;
bool Search::STOP_SEARCHING_NOW = false;
bool Search::Current_Turn = false;
bool Search::White_Turn = false;
void Move::Undo_Move()
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
                                White_Move_From_Stack[h] = Unconvert_Int(White_Temp_Move_From_Stack[h]);
                                White_Move_To_Stack[h] = Unconvert_Int(White_Temp_Move_To_Stack[h]);
                                White_Move_Types[h] = White_Temp_Move_Types[h];
                        }
                        
                for(int h = 0; h < Black_Temp_Move_Spacer; h++)
                {
                Black_Move_From_Stack[h] = Unconvert_Int(Black_Temp_Move_From_Stack[h]);
                Black_Move_To_Stack[h] = Unconvert_Int(Black_Temp_Move_To_Stack[h]);
                Black_Move_Types[h] = Black_Temp_Move_Types[h];
                }
                Search::Current_Turn ^= 1;
                Search::White_Turn ^= 1;
}

Move Search::Think(int wtime, int btime, int winc, int binc)
{
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();
    
    int Wtime = wtime;
	int Btime = btime;
	int Winc = winc;
	int Binc = binc;
	Move blank;
	Move Spar;
	Spar.Score = -100000;
 	Move Spar2;
 	Spar2.Score = 100000; 
	const int MAXDEPTH = 30;
	int Plies_Searched = 0;
		
	for(int q = 0; q < MAXDEPTH; q++)
		{
			if(White_Turn == true)
				{
					Time_Allocation = wtime;
					assert(Time_Allocation > 0);
					Depth = q;
    				blank = Search::SearchMax(Spar, Spar2, (q - Plies_Searched) + 1, &PVline);
    				auto t1 = Time::now();
					fsec fs = t1 - t0;
					ms d = std::chrono::duration_cast<ms>(fs);
					//Time_Usage is the parameter value: if((d.count() * Tine_Usage) > Wtime)
						if((d.count() * 30) > Wtime)
							{
								return blank;
							}
				}
				
    		else
    			{
    				Time_Allocation = btime;
    				assert(Time_Allocation > 0);
    				blank = Search::SearchMin(Spar, Spar2, (q - Plies_Searched) + 1, &PVline);
    				auto t1 = Time::now();
					fsec fs = t1 - t0;
					ms d = std::chrono::duration_cast<ms>(fs);
					Depth = q;
					//Time_Usage is the parameter value
					if((d.count() * 30) > Btime)
						{
							return blank;
						}
				}
	
			LINE* f = new LINE;
			f->cmove = 0;
			::PVline = *f;
			delete f;
			
			Search::Clear();//Clear search stacks, variables, etc.
			
			if(STOP_SEARCHING_NOW)
			{
				Time_Allocation = 0;
				return blank;
			}
			if ((blank.Score <= Spar.Score) || (blank.Score >= Spar2.Score))
			{
				Spar.Score = -100000;
				Spar2.Score = 100000;
			}
			else
			{
			Spar.Score = blank.Score - 50;
			Spar2.Score = blank.Score + 50;
			}
			//STOP_SEARCHING_NOW = false;
			}
		
	return blank;
}

Move Search::SearchMax(Move alpha, Move beta, int depth, LINE * pline)
{
	Seldepth = depth;
	LINE line;
	
	if(STOP_SEARCHING_NOW)
	return alpha;
	
	if(depth == 1)
		{ 	
			Move Best;
			++Nodes;
			Best.Score = Eval::Evaluate_Position();
			pline->cmove = 0;
			pline->score = Best.Score;
			return Best;
		}
		
	Generate_White_Moves();
	Search::Order_Moves(Current_Turn);
	register Move move;
	move.White_Temp_Move_Spacer = White_Move_Spacer;
	for(int h = 0; h < White_Move_Spacer; h++)
		{
			move.White_Temp_Move_From_Stack[h] = move.Convert_Bitboard(White_Move_From_Stack[h]);
			move.White_Temp_Move_To_Stack[h] = move.Convert_Bitboard(White_Move_To_Stack[h]);
			move.White_Temp_Move_Types[h] = White_Move_Types[h];
		}
			
	if(White_Move_Spacer == 0)
		{
			alpha.Score = Is_Mate();
			pline->score = alpha.Score;
			pline->cmove = depth;
			return alpha;			
		}
					
	for(int i = 0; i < White_Move_Spacer; i++)
		{ 
		Nodes++;
		if(STOP_SEARCHING_NOW)
		return alpha;
			move.From = White_Move_From_Stack[i];
			move.To = White_Move_To_Stack[i];
			move.Move_Type = White_Move_Types[i];
			Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]);
			
			Move Temp_Move = SearchMin(alpha, beta, depth - 1, &line);
			move.Undo_Move();
			if(Temp_Move.Score >= beta.Score)
				{
					return beta;
				}
			
			if(Temp_Move.Score > alpha.Score)
				{
					pline->argmove[0] = move;
					::PVline.score = Temp_Move.Score;
            		memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
					pline->cmove = line.cmove + 1;


				alpha = move;
				alpha.Score = Temp_Move.Score;
				}
			
		}
		
		return alpha;
}
	
	
Move Search::SearchMin(Move alpha, Move beta, int depth, LINE * pline)
	{
		Seldepth = depth;
		LINE line;
		
		if(STOP_SEARCHING_NOW)
		return beta;
			
		if(depth == 1)
			{ 
			Move Best;
			++Nodes;
			Best.Score = Eval::Evaluate_Position();
			pline->cmove = 0;
			pline->score = Best.Score;
			return Best;
			}
			
		Generate_Black_Moves();
		Search::Order_Moves(Current_Turn);
		register Move move;
		move.Black_Temp_Move_Spacer = Black_Move_Spacer;
		for(int h = 0; h < Black_Move_Spacer; h++)
			{
				move.Black_Temp_Move_From_Stack[h] = move.Convert_Bitboard(Black_Move_From_Stack[h]);
				move.Black_Temp_Move_To_Stack[h] = move.Convert_Bitboard(Black_Move_To_Stack[h]);
				move.Black_Temp_Move_Types[h] = Black_Move_Types[h];
			}
			
			if(Black_Move_Spacer == 0)
		{
			beta.Score = Is_Mate();
			pline->score = beta.Score;
			pline->cmove = depth;
			return beta;			
		}
		
		for(int i = 0; i < Black_Move_Spacer; i++)
		{ if(STOP_SEARCHING_NOW)
		return beta;
			move.From = Black_Move_From_Stack[i];
			move.To = Black_Move_To_Stack[i];
			move.Move_Type = Black_Move_Types[i];
			
			Nodes++;
			Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
			Move Temp_Move = SearchMax(alpha, beta, depth - 1, &line);
			move.Undo_Move();
			if(Temp_Move.Score <= alpha.Score)
			{
				return alpha;
			}
			
			if(Temp_Move.Score < beta.Score)
			{
				pline->argmove[0] = move;
				::PVline.score = Temp_Move.Score;
            memcpy(pline->argmove + 1, line.argmove,

                line.cmove * sizeof(Move));

            pline->cmove = line.cmove + 1;
				beta = move;
				beta.Score = Temp_Move.Score;
			}
			
		}
		
		return beta;	

}

Search::Make_White_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type)
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
		
			    Search::Current_Turn = false;
			    Search::White_Turn = false;
			    return 0;

}


Search::Make_Black_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type)
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
		
			    Search::Current_Turn  = true;
			    Search::White_Turn = true;
			    return 0;

}

void Search::Order_Moves(bool Whites_Turn)
{
	Bitboard White_Move_From_Stack2[70];//Move stack is just an array of Bitboards(64-bit integers) containing only one bit set in each--the from square or the to square
	Bitboard White_Move_To_Stack2[70];
	Bitboard Black_Move_From_Stack2[70];
	Bitboard Black_Move_To_Stack2[70];
	Bitboard White_Move_Types2[70];
	Bitboard Black_Move_Types2[70];
	int count = 0;
	for(int i = 0; i < 70; i++)
	White_Move_From_Stack2[i] = 0;
	for(int i = 0; i < 70; i++)
	White_Move_To_Stack2[i] = 0;
	for(int i = 0; i < 70; i++)
	Black_Move_From_Stack2[i] = 0;
	for(int i = 0; i < 70; i++)
	Black_Move_To_Stack2[i] = 0;
	for(int i = 0; i < 70; i++)
	White_Move_Types2[i] = 0;
	for(int i = 0; i < 70; i++)
	Black_Move_Types2[i] = 0;
	
	if(Whites_Turn == true)
	{
		for(int i = 0; i < White_Move_Spacer; i++)
		{
			if(White_Move_Types[i] % 2)
			{
				White_Move_From_Stack2[count++] = White_Move_From_Stack[i];
				White_Move_To_Stack2[count] = White_Move_To_Stack[i];
				White_Move_Types2[count] = White_Move_Types[i];
				White_Move_From_Stack[i] = 0;
				White_Move_To_Stack[i] = 0;
				White_Move_Types[i] = 0;
			}
		}
		for(int i = 0; i < White_Move_Spacer; i++)
		{
			if(White_Move_From_Stack[i] != 0)
			{
				White_Move_From_Stack2[count++] = White_Move_From_Stack[i];
				White_Move_To_Stack2[count] = White_Move_To_Stack[i];
				White_Move_Types2[count] = White_Move_Types[i];	
			}
		}
		
		for(int i = 0; i < 70; i++)
		White_Move_From_Stack[i] = White_Move_From_Stack2[i];
		for(int i = 0; i < 70; i++)
		White_Move_To_Stack[i] = White_Move_To_Stack2[i];
		for(int i = 0; i < 70; i++)
		White_Move_Types[i] = White_Move_Types2[i];
		
		
	}
	
	else
	{
		for(int i = 0; i < Black_Move_Spacer; i++)
		{
			if(Black_Move_Types[i] % 2)
			{
				Black_Move_From_Stack2[count++] = Black_Move_From_Stack[i];
				Black_Move_To_Stack2[count] = Black_Move_To_Stack[i];
				Black_Move_Types2[count] = Black_Move_Types[i];
				Black_Move_From_Stack[i] = 0;
				Black_Move_To_Stack[i] = 0;
				Black_Move_Types[i] = 0;
			}
		}
		for(int i = 0; i < Black_Move_Spacer; i++)
		{
			if(Black_Move_From_Stack[i] != 0)
			{
				Black_Move_From_Stack2[count++] = Black_Move_From_Stack[i];
				Black_Move_To_Stack2[count] = Black_Move_To_Stack[i];
				Black_Move_Types2[count] = Black_Move_Types[i];	
			}
		}
		
		for(int i = 0; i < 70; i++)
		Black_Move_From_Stack[i] = Black_Move_From_Stack2[i];
		for(int i = 0; i < 70; i++)
		Black_Move_To_Stack[i] = Black_Move_To_Stack2[i];
		for(int i = 0; i < 70; i++)
		{
		Black_Move_Types[i] = Black_Move_Types2[i];
		Log << Black_Move_Types[i] << " ";
		if(i == 68)
		Log << endl;
		}
	}
	return;
}

Search::Is_Mate()
{
	int h; 
        for(int j = 0; j < 64; j++) 
        {
                if(White_King & GeneralBoard[j])//Get the index (0-63) of White's king
                {
                	h = j;
                	break;
            	}
        }
	Bitboard BAttacks = Bmagic(h, (White_Pieces | Black_Pieces));
    Bitboard RAttacks = Rmagic(h, (White_Pieces | Black_Pieces));
    Bitboard QAttacks = Qmagic(h, (White_Pieces | Black_Pieces));
    	
		if(BAttacks & (Black_Bishops))
        return -10000;
        if(RAttacks & (Black_Rooks))
        return -10000;
        if(QAttacks & (Black_Queens))
        return -10000;
        if(Knight_Lookup_Table[h] & Black_Knights)
        return -10000;
        if(King_Lookup_Table[h] & Black_King)
        return -10000;
        
        Bitboard Spare = Black_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare >> 7) & White_King)
        return -10000;
        
        Bitboard Spare2 = Black_Pawns;
        Spare2 |= H_Pawn_Mask;
        Spare2 ^= H_Pawn_Mask;
        if((Spare2 >> 9) & White_King)
        return -10000;
        
        Bitboard Black_Pawns5 = Black_Pawns;
        Black_Pawns5 |= A_Pawn_Mask;
        Black_Pawns5 ^= A_Pawn_Mask; 
        Black_Pawns5 |= H_Pawn_Mask;
        Black_Pawns5 ^= H_Pawn_Mask;
        if(((Black_Pawns5 >> 7) | (Black_Pawns5 >> 9)) & White_King)
        return -10000;
                
        
        for(int j = 0; j < 64; j++)
        {
                if(Black_King & GeneralBoard[j])//Get the index(0-63) of the black king
                {
                	h = j;
                	break;
            	}
        }
        BAttacks = Bmagic(h, (White_Pieces | Black_Pieces));
    	RAttacks = Rmagic(h, (White_Pieces | Black_Pieces));
		QAttacks = Qmagic(h, (White_Pieces | Black_Pieces));
        
        if(BAttacks & (White_Bishops))
        return 10000;
        if(RAttacks & (White_Rooks))
        return 10000;
        if(QAttacks & (White_Queens))
        return 10000;
        if(Knight_Lookup_Table[h] & White_Knights)
        return 10000;
        if(King_Lookup_Table[h] & White_King)
        return 10000;
        
    	Spare = White_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare << 9) & Black_King)
        return 10000;
        
        Bitboard Spare7 = White_Pawns;
        Spare7 |= H_Pawn_Mask;
        Spare7 ^= H_Pawn_Mask;
        if((Spare7 << 7) & Black_King)
        return 10000;
        
    	Bitboard White_Pawns2 = 0;
		White_Pawns2 |= A_Pawn_Mask;
        White_Pawns2 ^= A_Pawn_Mask; 
        White_Pawns2 |= H_Pawn_Mask;
        White_Pawns2 ^= H_Pawn_Mask;
        if(((White_Pawns << 7) | (White_Pawns << 9)) & GeneralBoard[h])
        return 10000;
        
        else
        return 0;
}

void Search::Clear()
{
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
			
			Search::Nodes = 0;
}

