using namespace std;
#include "Bitboard.h"
#include "MoveGen.h"
#include "magicmoves.h"

int White_Knight_Spacer = 0; 
int Black_Knight_Spacer = 0;
int White_King_Spacer = 0;
int Black_King_Spacer = 0;
int White_Pawn_Spacer = 0;
int Black_Pawn_Spacer = 0;
int White_Rook_Spacer = 0;
int Black_Rook_Spacer = 0;
int White_Bishop_Spacer = 0;
int Black_Bishop_Spacer = 0;
int White_Queen_Spacer = 0;
int Black_Queen_Spacer = 0;
Bitboard WhiteKingCount[8];//Array which is large enough to contain as many legal moves at a time for all of the pieces of that type as possible
Bitboard BlackKingCount[8];
Bitboard WhiteKnightCount[40];
Bitboard BlackKnightCount[40];
Bitboard WhitePawnCount[20];
Bitboard BlackPawnCount[20];
Bitboard WhiteRookCount[20];
Bitboard BlackRookCount[20];
Bitboard WhiteBishopCount[20];
Bitboard BlackBishopCount[20];
Bitboard WhiteQueenCount[28];
Bitboard BlackQueenCount[28];
bool Current_Turn = true;
bool White_Turn = true;
Bitboard White_Move_From_Stack[70];//Move stack is just an array of Bitboards(64-bit integers) containing only one bit set in each--the from square or the to square
Bitboard White_Move_To_Stack[70];
Bitboard Black_Move_From_Stack[70];
Bitboard Black_Move_To_Stack[70];
int White_Move_Types[70];//Array of normal integers that keeps track of the type of each move
int Black_Move_Types[70];
int White_Move_Spacer = 0; // Keeps a "record" of the last move put on the stack so that it knows which index of the array to put the next move in
int Black_Move_Spacer = 0;
bool Is_Legal;
bool WhiteHasCastled = false;
bool BlackHasCastled = false;
// White Knight Move generation

// *****************************************************************************************************************************************
int Generate_White_Knight_Moves()
{
    if(White_Knights)//If there are any white knights on the board
    {
        
   for(int i = 0; i < 64; i++)
{
    if(White_Knights & (GeneralBoard[i])) // If a knight is found
    {
           WhiteKnightCount[White_Knight_Spacer] = GeneralBoard[i]; // Put the Knight on the Knight Stack; Call the knight a "number" of knights e.g. the "first" knight
           White_Knight_Spacer++;//Increment the knight move spacer 
    }
}        
         White_Knight_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }    
    int j = 0;//Holds the index of the current knight
    int w = 0; // Use it in a for loop to keep track of the number of iterations
        for(int w = 0; w <= White_Knight_Spacer; w++) // For eack knight found on KnightCount[]; at the beginning of the game it is 2
    {
        
    for( int i = 0; i < 64; i++)
    {
        if(WhiteKnightCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
     
    Bitboard Spare = (Knight_Lookup_Table[j] | WhiteKnightCount[w]);// Spare is a bitboard with all legal squares the knight can move to and the original square of the knight
    Bitboard Spare2 = White_Pieces & Knight_Lookup_Table[j]; // Spare2 has all moves that do not capture one of white's own pieces    
    Bitboard Spare3 = ((Spare ^ Spare2) ^ GeneralBoard[j]); // Knight_Pos is the final result
        for(int r = 0; r < 64; r++) // For each legal square found in Spare3 for the current knight
    {
        if(GeneralBoard[r] & Spare3)//If the for loop index of GeneralBoard  is a square the knight can move to 
        { 
        int y = 4;//This move will be a "Normal" knight move
        if(GeneralBoard[r] & Black_Pieces)//If the move captures a black piece, it is a knight capture
        y--;//So, decrement y to tell the MakeMove function that this move is a knight capture
                if(White_Is_Legal(WhiteKnightCount[w], GeneralBoard[r], y))//Pass the move to the Is_Legal() function and if it returns true, then the move is legal, otherwise, the move is ditched
                {
                White_Move_From_Stack[White_Move_Spacer] = WhiteKnightCount[w];  // Move_From_Stack gets original position of knight(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        White_Move_Types[White_Move_Spacer - 1] = y;//Make it a "plain" move
           
    }
     
}

    }  
    }
    for(int u = 0; u < 40; u++) // Tidy up for the next person by emptying the KnightCount array
    {
        WhiteKnightCount[u] = 0;
        }

White_Knight_Spacer = 0; // Reset the knight count of the current position so that if called again, the function can start from scratch
    return 0;
}

//****************************************************************************************************************************************************
// Black Knight Move Generation

int Generate_Black_Knight_Moves()
{
    if(Black_Knights)//If there are any black knights
    {
        
   for(int i = 0; i < 64; i++)
{
    if(Black_Knights & (GeneralBoard[i])) // If a knight is found
    {
           BlackKnightCount[Black_Knight_Spacer] = GeneralBoard[i]; // Put the Knight on the Knight Stack; Call the knight a "number of knights" e.g. the "first" knight
           Black_Knight_Spacer++;//Increment the Knight spacer so that the program knows to put the next move into en empty array index  
    }
}        
        Black_Knight_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }
    
    int j = 0;//Used for the index of the current knight
    int w = 0; // Use it in a for loop to keep track of the number of iterations
        for(int w = 0; w <= Black_Knight_Spacer; w++) // For eack knight found on KnightCount[]; at the beginning of the game it is 2
    {        
    for( int i = 0; i < 64; i++)//For each legal square for the current knight...
    {
    if(BlackKnightCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
     
    Bitboard Spare = (Knight_Lookup_Table[j] | BlackKnightCount[w]);// Spare is a bitboard with all legal squares the knight can move to and the original square of the knight
    Bitboard Spare2 = Black_Pieces & Knight_Lookup_Table[j]; // Spare2 has all moves that do not capture one of white's own pieces    
    Bitboard Spare3 = ((Spare ^ Spare2) ^ GeneralBoard[j]); // Knight_Pos is the final result
        for(int r = 0; r < 64; r++) // For each legal square found in Spare3 for the current knight
    {
        if(GeneralBoard[r] & Spare3)//If the current iteration has the square value that the knight can got to 
        { 
        int y = 4;//The move as of right now is a "normal" knight move
        if(GeneralBoard[r] & White_Pieces)//If it captures the opponent's piece, then we must make the move a capture knight move
        y--;
        if(Black_Is_Legal(BlackKnightCount[w], GeneralBoard[r], y))//If Is_Legal returns true, then the move is legal; if false, the current move is trashed
                {
                Black_Move_From_Stack[Black_Move_Spacer] = BlackKnightCount[w];  // Move_From_Stack gets original position of knight(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to        
        Black_Move_Types[Black_Move_Spacer - 1] = y;//Or else is is called a "normal" kight move
           
    }
}

    }
        
  
    }
    for(int u = 0; u < 40; u++) // Tidy up for the next person
    {
        BlackKnightCount[u] = 0;
        }
Black_Knight_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}
//****************************************************************************************************************************************************


//*************************************************************************************************
//White King Move Generation


int Generate_White_King_Moves()
{
     
   for(int i = 0; i < 64; i++)
{
    if(White_King & (GeneralBoard[i])) // If a king is found
    {
           WhiteKingCount[White_King_Spacer] = GeneralBoard[i]; // Put the King on the King move Stack; Call the king a "number of kings" e.g. the "first" king
           White_King_Spacer++;   
    }
}        
         White_King_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    
    
    int j = 0;//Used in a for loop to index the current king
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_King_Spacer; w++)// For each king found on KnightCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteKingCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
    //Kingside castling functionality
	/*Bitboard first = (WhiteKingCount[w] & 16);
	Bitboard second = ((White_Pieces | Black_Pieces) & 96);
	Bitboard e1 = 16, f1 = 32, g1 = 64, a0 = 0;
	bool canmovetof1 = White_Is_Legal(e1, f1, 15);
	bool canmovetog1 = White_Is_Legal(f1, g1, 15);
	bool canmovetoe1 = White_Is_Legal(a0, e1, 15); 
    if(first && (!second) && canmovetof1 && canmovetog1 && canmovetoe1 && (!WhiteHasCastled))
    {
		White_Move_From_Stack[White_Move_Spacer] = WhiteKingCount[w];
		Bitboard too = 64;	
		White_Move_To_Stack[White_Move_Spacer++] = too;
		White_Move_Types[White_Move_Spacer - 1] = 15;
	}*/
    Bitboard Spare = (King_Lookup_Table[j] | WhiteKingCount[w]);// Spare is a bitboard with all legal squares the king can move to and the original square of the knight
    Bitboard Spare2 = White_Pieces & King_Lookup_Table[j]; // Spare2 has all moves that do not capture one of white's own pieces    
    Bitboard Spare3 = ((Spare ^ Spare2) ^ GeneralBoard[j]); // Spare3 is the final result
        for(int r = 0; r < 64; r++) // For each legal square found in Spare3 for the current king
    {
        if(GeneralBoard[r] & Spare3)//If it finds a square the king can legally move to
        { 
        int y = 12;//It is a king "normal" move
        if(GeneralBoard[r] & Black_Pieces)//If it is a capture move, we have to decrement the move type accordingly
        y--;
                if(White_Is_Legal(WhiteKingCount[w], GeneralBoard[r], y))//If the move is legal, e.g. does not leave the white king in check, then put it on the move stack
                {
        White_Move_From_Stack[White_Move_Spacer] = WhiteKingCount[w];  // Move_From_Stack gets original position of the white king
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a single square it can move to
        White_Move_Types[White_Move_Spacer - 1] = y;//Else it is just a "normal" king move
            
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 8; u++) // Tidy up for the next person
    {
        WhiteKingCount[u] = 0;
        }
White_King_Spacer = 0; // Reset the king count of the current position so that if called again, the function can start from scratch
    return 0;
}
//****************************************************************************************************************************************************

int Generate_Black_King_Moves()
{
    for(int i = 0; i < 64; i++)
{
    if(Black_King & (GeneralBoard[i])) // If a king is found
    {
           BlackKingCount[Black_King_Spacer] = GeneralBoard[i]; // Put the King on the King move Stack; Call the king a "number of kings" e.g. the "first" king
           Black_King_Spacer++;   
    }
}        
         Black_King_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    
    
    int j = 0;//Used to help control the for loops
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_King_Spacer; w++)// For each king found on KingCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackKingCount[w] & (GeneralBoard[i])) // Find the index of the current king(1-63) and assign this value to j
        {
            j = i;
        }
    } 
	//Kingside castling functionality
	/*Bitboard first = (BlackKingCount[w] & 16);
	Bitboard second = ((White_Pieces | Black_Pieces) & 6917529027641081856);
	Bitboard e8 = 1152921504606846976, f8 = 2305843009213693952, g8 = 4611686018427387904, a0 = 0;
	bool canmovetof8 = Black_Is_Legal(e8, f8, 15);
	bool canmovetog8 = Black_Is_Legal(f8, g8, 15);
	bool canmovetoe8 = Black_Is_Legal(a0, e8, 15); 
    if(first && (!second) && canmovetof8 && canmovetog8 && canmovetoe8 && (!BlackHasCastled))
    {
		Black_Move_From_Stack[Black_Move_Spacer] = BlackKingCount[w];
		Bitboard too = 4611686018427387904;	
		Black_Move_To_Stack[Black_Move_Spacer++] = too;
		Black_Move_Types[Black_Move_Spacer - 1] = 15;
	}*/   
     
    Bitboard Spare = (King_Lookup_Table[j] | BlackKingCount[w]);// Spare is a bitboard with all legal empty squares the king can move to and the original square of the king
    Bitboard Spare2 = Black_Pieces & King_Lookup_Table[j]; // Spare2 has all moves that do not capture one of black's own pieces    
    Bitboard Spare3 = ((Spare ^ Spare2) ^ GeneralBoard[j]); // Spare3 is the final result
        for(int r = 0; r < 10; r++) // For each legal square found in Spare3 for the current king
    {
        if(GeneralBoard[r] & Spare3)//If a square is found that the king can legally move to 
        { 
        int y = 12;//It is automatically called a "normal" king move 
        if(GeneralBoard[r] & White_Pieces)//If it captures a white piece, then we have to decrement y which tells MakeMove() that the move is a king capture
        y--;
                if(Black_Is_Legal(BlackKingCount[w], GeneralBoard[r], y))//If the move is legal
                {
        Black_Move_From_Stack[Black_Move_Spacer] = BlackKingCount[w];  // Move_From_Stack gets original position of king
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        Black_Move_Types[Black_Move_Spacer - 1] = y;//Or else it is just a "normal" move
           
    }
    
        }
    }
        
    }
    
     // Tidy up for the next time this function is called
     for(int u = 0; u < 8; u++) // Tidy up for the next function call
    {
        BlackKingCount[u] = 0;
        }
        

Black_King_Spacer = 0; // Reset the king count of the current position so that if called again, the function can start from scratch
    return 0;
}

/********************************************************************************************************************************************
Pawn Move Generation
*********************************************************************************************************************************************/

int Generate_White_Pawn_Moves()
{
        if(White_Pawns)//If there are any white pawns
        {
                for(int i = 0; i < 64; i++)
{
    if(White_Pawns & (GeneralBoard[i])) // If a pawn is found
    {
           WhitePawnCount[White_Pawn_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the pawn a "number of pawns" e.g. the "first" pawn
           White_Pawn_Spacer++;   
    }
}        
         White_Pawn_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
        
    }
           
    int j = 0;//Used to keep track of iteration in a for loop
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Pawn_Spacer; w++)// For each pawn found on PawnCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhitePawnCount[w] & (GeneralBoard[i])) // Find the index of the current pawn(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    
        Bitboard Spare1 = (GeneralBoard[j] << 8);//Spare1 is a bitboard containing the current pawn shifted the the left 8; this is the suqare directly "above" it
        Bitboard Spare2 = (White_Pieces | Black_Pieces);//We have to make sure that the pawn does not move into one of white's or black's pieces when moving straight ahead
        Spare1 |= Spare2;//See above note
        Spare1 ^= Spare2; //Spare1 has one square ahead of the current pawn(if legal to move ahead)
        Bitboard Second_Rank = 65280;//Mask containing the bits set in the second rank for double pawn pushes
        Bitboard Swat = Second_Rank & GeneralBoard[j];//If a pawn is in the second rank, then it is eligible for a two-square push
        Swat <<= 8;//Various bit twiddling follows to give a bitboard containing all legal moves the current pawn can make
        Swat |= Spare2;
        Swat ^= Spare2; 
    	Swat <<= 8;
        Swat |= Spare2;
        Swat ^= Spare2; 
        Spare1 |= Swat;
        
        Bitboard Spare4 = GeneralBoard[j];
        Spare4 |= A_Pawn_Mask;
        Spare4 ^= A_Pawn_Mask;
        if(Spare4)
        {
        Spare4 = (GeneralBoard[j] << 7);
}
        
        if (Spare4 & Black_Pieces)
        {
     
     Spare1 |= Spare4;
 }
    Bitboard Spare5 = GeneralBoard[j];
        Spare5 |= H_Pawn_Mask;
        Spare5 ^= H_Pawn_Mask;
        if(Spare5)
        {
        Spare5 = (GeneralBoard[j] << 9);
}
                if (Spare5 & Black_Pieces)
        {
     
     Spare1 |= Spare5;
 }
         
            for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 2;//The move is first considered a "normal" pawn move
        if(GeneralBoard[r] & Black_Pieces)//But if is captures one of black's pieces,
        y--;//makeMove must be told that the move is a capture
        if(GeneralBoard[r] & Eigth_Rank_White)//If the move is a push to the eights rank,
        y = 14;//Then tell MakeMove by changing the move type
        if((GeneralBoard[r] & Eigth_Rank_White) & Black_Pieces)//If a pawn captures its way onto the eighth rank, 
        y = 13;//Tell MakeMove
        if(White_Is_Legal(WhitePawnCount[w], GeneralBoard[r], y))//If the move is legal,
                {
        White_Move_From_Stack[White_Move_Spacer] = WhitePawnCount[w];  // Move_From_Stack gets original position of pawn(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        White_Move_Types[White_Move_Spacer - 1] = 2;//It is a normal pawn move
        if((White_Move_To_Stack[White_Move_Spacer - 1]) & Black_Pieces)
        White_Move_Types[White_Move_Spacer - 1] = 1;//Or, if it captures, it is a capture move
            if((White_Move_To_Stack[White_Move_Spacer - 1]) & Eigth_Rank_White)//If it pusehes its way to promotion,
            White_Move_Types[White_Move_Spacer - 1] = 14;//Tel MakeMove()
                if((White_Move_To_Stack[White_Move_Spacer - 1] & Eigth_Rank_White) & Black_Pieces)//Or if it captures its way onto the eighth rank,
            White_Move_Types[White_Move_Spacer - 1] = 13;//Then tell MakeMove()
        }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) //Clear WhitePawnCount[]
    {
        WhitePawnCount[u] = 0;
        }
White_Pawn_Spacer = 0; // Reset the pawn count of the current position so that if called again, the function can start from scratch
    return 0;
}

int Generate_Black_Pawn_Moves()
{
        if(Black_Pawns)//If there are any black pawns
        {
                for(int i = 0; i < 64; i++)
{
    if(Black_Pawns & (GeneralBoard[i])) // If a pawn is found
    {
           BlackPawnCount[Black_Pawn_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the pawn a "number of pawns" e.g. the "first" pawn
           Black_Pawn_Spacer++;   
    }
}        
         Black_Pawn_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }
        
    int j = 0;//Used in a for loop
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Pawn_Spacer; w++)// For each pawn found on PawnCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackPawnCount[w] & (GeneralBoard[i])) // Find the index of the current pawn(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
   
        Bitboard Spare1 = (GeneralBoard[j] >> 8);//The square straight ahead of the current pawn
        Bitboard Spare2 = (Black_Pieces | White_Pieces);
        Spare1 |= Spare2;
        Spare1 ^= Spare2; //Spare1 has one square ahead of the current pawn(if legal to move ahead)
        Bitboard Second_Rank = 71776119061217280;//Used to determine whether a pawn can move two spaces at once
        Bitboard Swat = Second_Rank & GeneralBoard[j];//Much bit twiddling follows to get a bitboard containing the squares the current pawn can move to
        Swat >>= 8;//Some of the twiddling is actually quite ingenious
        Swat |= Spare2;
        Swat ^= Spare2; 
    Swat >>= 8;
        Swat |= Spare2;
        Swat ^= Spare2; 
        Spare1 |= Swat;
        
        Bitboard Spare4 = GeneralBoard[j];
        Spare4 |= H_Pawn_Mask;
        Spare4 ^= H_Pawn_Mask;
        if(Spare4)
        {
        Spare4 = (GeneralBoard[j] >> 7);
}
        
        if (Spare4 & White_Pieces)
        {
     
     Spare1 |= Spare4;
 }
    Bitboard Spare5 = GeneralBoard[j];
        Spare5 |= A_Pawn_Mask;
        Spare5 ^= A_Pawn_Mask;
        if(Spare5)
        {
        Spare5 = (GeneralBoard[j] >> 9);
}
                if (Spare5 & White_Pieces)
        {
     
     Spare1 |= Spare5;
 }       
            for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 2;//It is assumed to bea regular pawn move
        if(GeneralBoard[r] & White_Pieces)//But if it captures,
        y--;//Tell MakeMove()
        if(GeneralBoard[r] & Eigth_Rank_Black)//If it pushes to the eighth rank,
        y = 14;//Tell MakeMove()       
        if((GeneralBoard[r] & Eigth_Rank_Black) & White_Pieces)//If it captures one of white's pieces and promotes, then
        y = 13;//Tell MakeMove()
        if(Black_Is_Legal(BlackPawnCount[w], GeneralBoard[r], y))
                {
        //cout << "It can move to " << PlayerMoves[r] << endl;
        Black_Move_From_Stack[Black_Move_Spacer] = BlackPawnCount[w];  // Move_From_Stack gets original position of knight(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        Black_Move_Types[Black_Move_Spacer - 1] = 2;
        if((Black_Move_To_Stack[Black_Move_Spacer - 1]) & White_Pieces)
        Black_Move_Types[Black_Move_Spacer - 1] = 1;
            if((Black_Move_To_Stack[Black_Move_Spacer - 1]) & Eigth_Rank_Black)
            Black_Move_Types[Black_Move_Spacer - 1] = 14;
                if((Black_Move_To_Stack[Black_Move_Spacer - 1] & Eigth_Rank_Black) & White_Pieces)
            Black_Move_Types[Black_Move_Spacer - 1] = 13;
                    
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) // Claer BlackPawnCount[]
    {
        BlackPawnCount[u] = 0;
        }

Black_Pawn_Spacer = 0; // Reset the pawn count of the current position so that if called again, the function can start from scratch
    return 0;
}

int Generate_White_Rook_Moves()
{
        if(White_Rooks)//If there are any white rooks
        {
                for(int i = 0; i < 64; i++)
{
    if(White_Rooks & (GeneralBoard[i])) // If a rook is found
    {
           WhiteRookCount[White_Rook_Spacer] = GeneralBoard[i]; // Put the rook on the rook Stack; Call the rook a "number of rooks" e.g. the "first" rook
           White_Rook_Spacer++;   
    }
}        
         White_Rook_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }   
    int j = 0;//Used i a for loop
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Rook_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteRookCount[w] & (GeneralBoard[i])) // Find the index of the current rook(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Rmagic(j, (White_Pieces | Black_Pieces));//Pradu's rook movegen
    Spare1 |= White_Pieces;//Make sure that it doesn't capture one of white's own pieces
    Spare1 ^= White_Pieces;//See above note
         
            for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current rook
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 8;//It is assumed to be a "normal" rook move
        if(GeneralBoard[r] & Black_Pieces)//But if it captures a black piece,
        y--;//Tell MakeMove()
                if(White_Is_Legal(WhiteRookCount[w], GeneralBoard[r], y))//If the current move is legal,
                {
        White_Move_From_Stack[White_Move_Spacer] = WhiteRookCount[w];  // Move_From_Stack gets original position of rook(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        White_Move_Types[White_Move_Spacer - 1] = y;//Else it is a "plain" sliding move
            
    }
    }
    
    }
}
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) // Clear WhiteRookCount[]
    {
        WhiteRookCount[u] = 0;
        }
White_Rook_Spacer = 0; // Reset the rook count of the current position so that if called again, the function can start from scratch
    return 0;
}

int Generate_Black_Rook_Moves()
{
        if(Black_Rooks)//If there are any black rooks, 
        {
                for(int i = 0; i < 64; i++)
{
    if(Black_Rooks & (GeneralBoard[i])) // If a rook is found
    {
           BlackRookCount[Black_Rook_Spacer] = GeneralBoard[i]; // Put the rook on the pawn Stack; Call the rook a "number of rooks" e.g. the "first" rook
           Black_Rook_Spacer++;   
    }
}        
         Black_Rook_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }
        
    int j = 0;//Used in a for loop
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Rook_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackRookCount[w] & (GeneralBoard[i])) // Find the index of the current rook1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Rmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= Black_Pieces;
    Spare1 ^= Black_Pieces;
         
            for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current rook
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 8;
        if(GeneralBoard[r] & White_Pieces)
        y--;
                if(Black_Is_Legal(BlackRookCount[w], GeneralBoard[r], y))
                {
        Black_Move_From_Stack[Black_Move_Spacer] = BlackRookCount[w];  // Move_From_Stack gets original position of rook(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        Black_Move_Types[Black_Move_Spacer - 1] = y;
            
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) //Clear BlackRookCount[]
    {
        BlackRookCount[u] = 0;
        }
        Black_Rook_Spacer = 0; // Reset the rook count of the current position so that if called again, the function can start from scratch
    return 0;
}

int Generate_White_Bishop_Moves()//Exactly the same as the Rook, Pawn, and King movegen. For notes on the following functions, see the previous piece movegen functions
{
        if(White_Bishops)
        {
                for(int i = 0; i < 64; i++)
{
    if(White_Bishops & (GeneralBoard[i])) // If a bishop is found
    {
           WhiteBishopCount[White_Bishop_Spacer] = GeneralBoard[i]; // Put the bishop on the pawn Stack; Call the bishop a "number of bishops" e.g. the "first" bishop
           White_Bishop_Spacer++;   
    }
}        
         White_Bishop_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Bishop_Spacer; w++)// For each rook found on BishopCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteBishopCount[w] & (GeneralBoard[i])) // Find the index of the current bishop(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Bmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= White_Pieces;
    Spare1 ^= White_Pieces;
         
            for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current bishop
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 6;
        if(GeneralBoard[r] & Black_Pieces)
        y--;
                if(White_Is_Legal(WhiteBishopCount[w], GeneralBoard[r], y))
                {
        White_Move_From_Stack[White_Move_Spacer] = WhiteBishopCount[w];  // Move_From_Stack gets original position of bishop(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        White_Move_Types[White_Move_Spacer - 1] = y;
            
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) //Clear WhiteBishopCount[]
    {
        WhiteBishopCount[u] = 0;
        }
        

White_Bishop_Spacer = 0; // Reset the bishop count of the current position so that if called again, the function can start from scratch
    return 0;
}

int Generate_Black_Bishop_Moves()
{
        if(Black_Bishops)
        {
                for(int i = 0; i < 64; i++)
{
    if(Black_Bishops & (GeneralBoard[i])) // If a bishop is found
    {
           BlackBishopCount[Black_Bishop_Spacer] = GeneralBoard[i]; // Put the bishop on the bishop Stack; Call the bishop a "number of bishops" e.g. the "first" bishop
           Black_Bishop_Spacer++;   
    }
}        
         Black_Bishop_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }   
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Bishop_Spacer; w++)// For each rook found on BishopCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackBishopCount[w] & (GeneralBoard[i])) // Find the index of the current bishop(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Bmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= Black_Pieces;
    Spare1 ^= Black_Pieces;
         
            for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current bishop
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 6;
        if(GeneralBoard[r] & White_Pieces)
        y--;
                if(Black_Is_Legal(BlackBishopCount[w], GeneralBoard[r], y))
                {
        Black_Move_From_Stack[Black_Move_Spacer] = BlackBishopCount[w];  // Move_From_Stack gets original position of bishop(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
    	Black_Move_Types[Black_Move_Spacer - 1] = y;
            
    }
    }
    
    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) //Clear BlackBishopCount[]
    {
        BlackBishopCount[u] = 0;
        }
        Black_Bishop_Spacer = 0; // Reset the bishop count of the current position so that if called again, the function can start from scratch
    return 0;
}

int Generate_White_Queen_Moves()
{
        if(White_Queens)
        {
                for(int i = 0; i < 64; i++)
{
    if(White_Queens & (GeneralBoard[i])) // If a queen is found
    {
           WhiteQueenCount[White_Queen_Spacer] = GeneralBoard[i]; // Put the queen on the queen Stack; Call the queen a "number of queens" e.g. the "first" queen
           White_Queen_Spacer++;   
    }
}        
         White_Queen_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }

    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Queen_Spacer; w++)// For each queen found on QueenCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteQueenCount[w] & (GeneralBoard[i])) // Find the index of the current queen(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Rmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= White_Pieces;
    Spare1 ^= White_Pieces;
    Bitboard Spare2 = Bmagic(j, (White_Pieces | Black_Pieces));
    Spare2 |= White_Pieces;
    Spare2 ^= White_Pieces;
    Bitboard Spare3 = (Spare1 | Spare2);
         
            for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current queen
    {
        if(GeneralBoard[r] & Spare3)
        { 
        int y = 10;
        if(GeneralBoard[r] & Black_Pieces)
        y--;
                if(White_Is_Legal(WhiteQueenCount[w], GeneralBoard[r], y))
                {
        White_Move_From_Stack[White_Move_Spacer] = WhiteQueenCount[w];  // Move_From_Stack gets original position of queen(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        White_Move_Types[White_Move_Spacer - 1] = y;
            
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 40; u++) //Clear WhiteQueenCount[]
    {
        WhiteQueenCount[u] = 0;
        }
        

White_Queen_Spacer = 0; // Reset the queen count of the current position so that if called again, the function can start from scratch
    return 0;
}

int Generate_Black_Queen_Moves()
{
        if(Black_Queens)
        {
                for(int i = 0; i < 64; i++)
{
    if(Black_Queens & (GeneralBoard[i])) // If a queen is found
    {
           BlackQueenCount[Black_Queen_Spacer] = GeneralBoard[i]; // Put the queen on the queen Stack; Call the queen a "number of queens" e.g. the "first" queen
           Black_Queen_Spacer++;   
    }
}        
         Black_Queen_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         
    }
        
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Queen_Spacer; w++)// For each queen found on QueenCount[]
    	{    
    for( int i = 0; i < 64; i++)
    {
        if(BlackQueenCount[w] & (GeneralBoard[i])) // Find the index of the current queen(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Rmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= Black_Pieces;
    Spare1 ^= Black_Pieces;
    Bitboard Spare2 = Bmagic(j, (White_Pieces | Black_Pieces));
    Spare2 |= Black_Pieces;
    Spare2 ^= Black_Pieces;
    Bitboard Spare3 = (Spare1 | Spare2);
                                                                
        for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current queen
    {
        if(GeneralBoard[r] & Spare3)
        { 
        int y = 10;                                                                                                                                                                                                        
        if(GeneralBoard[r] & White_Pieces)
        y--;
                if(Black_Is_Legal(BlackQueenCount[w], GeneralBoard[r], y))
                {
        Black_Move_From_Stack[Black_Move_Spacer] = BlackQueenCount[w];  // Move_From_Stack gets original position of queen(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        Black_Move_Types[Black_Move_Spacer - 1] = y;
            
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 40; u++) //Clear BlackQueenCount
    {
        BlackQueenCount[u] = 0;
        }
        

Black_Queen_Spacer = 0; // Reset the queen count of the current position so that if called again, the function can start from scratch
    return 0;
}

