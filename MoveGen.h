#ifndef H_Stooge
#define H_Stooge
int Generate_White_Knight_Moves();//Function declarations
int Generate_Black_Knight_Moves();
int Generate_White_King_Moves();
int Generate_Black_King_Moves();
int Generate_White_Pawn_Moves();
int Generate_Black_Pawn_Moves();
int Generate_White_Rook_Moves();
int Generate_Black_Rook_Moves();
int Generate_White_Bishop_Moves();
int Generate_Black_Bishop_Moves();
int Generate_White_Queen_Moves();
int Generate_Black_Queen_Moves();
bool White_Is_Legal(Bitboard From_Square, Bitboard To_Square, int Move_Type);//Tests for legality
bool Black_Is_Legal(Bitboard From_Square, Bitboard To_Square, int Move_Type);//Tests for legality

Bitboard White_Move_From_Stack[70];//Move stack is just an array of Bitboards(64-bit integers) containing only one bit set in each--the from square or the to square
Bitboard White_Move_To_Stack[70];
Bitboard Black_Move_From_Stack[70];
Bitboard Black_Move_To_Stack[70];

int White_Move_Types[70];//Array of normal integers that keeps track of the type of each move
int Black_Move_Types[70];

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

int White_Knight_Spacer = 0;//Keeps track of the number of psuedo legal moves for each type of piece
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

int Stack_White_Knight_Moves();//Function declarations
int Stack_Black_Knight_Moves();
int Stack_White_King_Moves();
int Stack_Black_King_Moves();
int Stack_White_Pawn_Moves();
int Stack_Black_Pawn_Moves();
int Stack_White_Rook_Moves();
int Stack_Black_Rook_Moves();
int Stack_White_Bishop_Moves();
int Stack_Black_Bishop_Moves();
int Stack_White_Queen_Moves();
int Stack_Black_Queen_Moves();

int White_Move_Spacer = 0; // Keeps a "record" of the last move put on the stack so that it knows which index of the array to put the next move in
int Black_Move_Spacer = 0;

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
           WhiteKnightCount[White_Knight_Spacer] = GeneralBoard[i]; // Put the Knight on the Knight Stack; Call the knight a "number of knights" e.g. the "first" knight
           White_Knight_Spacer++;//Increment the knight move spacer 
    }
}        
         White_Knight_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_White_Knight_Moves(); // Puts all legal knight moves on stack
    }    
return 0;
}

int Stack_White_Knight_Moves() // Puts all the legal knight moves on move stack 
{ 
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
		if(White_Is_Legal(WhiteKnightCount[w], GeneralBoard[r], y))
		{
		//cout << "It can move to " << PlayerMoves[r] << endl;
        White_Move_From_Stack[White_Move_Spacer] = WhiteKnightCount[w];  // Move_From_Stack gets original position of knight(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
       if((White_Move_To_Stack[White_Move_Spacer - 1]) & Black_Pieces)
       { 
	   White_Move_Types[White_Move_Spacer - 1] = 3;
	   }
	   
	   else
	   {
	   	White_Move_Types[White_Move_Spacer - 1] = 4;
	   }
    }
}

    }
        
  
    }
    for(int u = 0; u < 40; u++) // Tidy up for the next person
    {
    	WhiteKnightCount[u] = 0;
	}

White_Knight_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

//****************************************************************************************************************************************************
//****************************************************************************************************************************************************
//****************************************************************************************************************************************************
//****************************************************************************************************************************************************
//****************************************************************************************************************************************************
// Generate Black Knight Moves


int Generate_Black_Knight_Moves()
{
    if(Black_Knights)
    {
        
   for(int i = 0; i < 64; i++)
{
    if(Black_Knights & (GeneralBoard[i])) // If a knight is found
    {
        
        //cout << "Knight is on " << PlayerMoves[i] << endl; // cout which square it is on
              BlackKnightCount[Black_Knight_Spacer] = GeneralBoard[i]; // Put the Knight on the Knight Stack; Call the knight a "number of knights" e.g. the "first" knight
           Black_Knight_Spacer++;   
    }
}        
        Black_Knight_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_Black_Knight_Moves(); // Puts all legal knight moves on stack
    }
    
return 0;

}

int Stack_Black_Knight_Moves() // Puts all the legal knight moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
        for(int w = 0; w <= Black_Knight_Spacer; w++) // For eack knight found on KnightCount[]; at the beginning of the gAme it is only 2
    {
        
    for( int i = 0; i < 64; i++)
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
        if(GeneralBoard[r] & Spare3)
        { 
        int y = 4;
        if(GeneralBoard[r] & White_Pieces)
        y--;
        if(Black_Is_Legal(BlackKnightCount[w], GeneralBoard[r], y))
		{
		//cout << "It can move to " << PlayerMoves[r] << endl;
        Black_Move_From_Stack[Black_Move_Spacer] = BlackKnightCount[w];  // Move_From_Stack gets original position of knight(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to        
       if((Black_Move_To_Stack[Black_Move_Spacer - 1]) & White_Pieces)
       { 
	   Black_Move_Types[Black_Move_Spacer - 1] = 3;
	   }
	   
	   else
	   {
	   	Black_Move_Types[Black_Move_Spacer - 1] = 4;
	   	
	   }
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


/*************************************************************************************************
KING MOVEGENERATION
*************************************************************************************************/

int Generate_White_King_Moves()
{
    if(White_King)
    {
        
   for(int i = 0; i < 64; i++)
{
    if(White_King & (GeneralBoard[i])) // If a king is found
    {
        
        //cout << "King is on " << PlayerMoves[i] << endl; // cout which square it is on
              WhiteKingCount[White_King_Spacer] = GeneralBoard[i]; // Put the Knight on the Knight Stack; Call the knight a "number of knights" e.g. the "first" knight
           White_King_Spacer++;   
    }
}        
         White_King_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_White_King_Moves(); // Puts all legal knight moves on stack
    }
    
return 0;

}

int Stack_White_King_Moves() // Puts all the legal knight moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_King_Spacer; w++)// For each knight found on KnightCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteKingCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
     
    Bitboard Spare = (King_Lookup_Table[j] | WhiteKingCount[w]);// Spare is a bitboard with all legal squares the king can move to and the original square of the knight
    Bitboard Spare2 = White_Pieces & King_Lookup_Table[j]; // Spare2 has all moves that do not capture one of white's own pieces    
    Bitboard Spare3 = ((Spare ^ Spare2) ^ GeneralBoard[j]); // Spare3 is the final result
        for(int r = 0; r < 64; r++) // For each legal square found in Spare3 for the current king
    {
        if(GeneralBoard[r] & Spare3)
        { 
        int y = 12;
        if(GeneralBoard[r] & Black_Pieces)
        y--;
		if(White_Is_Legal(WhiteKingCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
        White_Move_From_Stack[White_Move_Spacer] = WhiteKingCount[w];  // Move_From_Stack gets original position of knight(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        if((White_Move_To_Stack[White_Move_Spacer - 1]) & Black_Pieces)
        { 
	    White_Move_Types[White_Move_Spacer - 1] = 11;
	    }
	   
	    else
	    {
	   	White_Move_Types[White_Move_Spacer - 1] = 12;
	    }
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 8; u++) // Tidy up for the next person
    {
    	WhiteKingCount[u] = 0;
	}
	

White_King_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}








int Generate_Black_King_Moves()
{
    if(Black_King)
    {
        
   for(int i = 0; i < 64; i++)
{
    if(Black_King & (GeneralBoard[i])) // If a king is found
    {
        
        //cout << "King is on " << PlayerMoves[i] << endl; // cout which square it is on
              BlackKingCount[Black_King_Spacer] = GeneralBoard[i]; // Put the Knight on the Knight Stack; Call the knight a "number of knights" e.g. the "first" knight
           Black_King_Spacer++;   
    }
}        
         Black_King_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_Black_King_Moves(); // Puts all legal knight moves on stack
    }
    
return 0;

}

int Stack_Black_King_Moves() // Puts all the legal knight moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_King_Spacer; w++)// For each knight found on KnightCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackKingCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
     
    Bitboard Spare = (King_Lookup_Table[j] | BlackKingCount[w]);// Spare is a bitboard with all legal squares the king can move to and the original square of the knight
    Bitboard Spare2 = Black_Pieces & King_Lookup_Table[j]; // Spare2 has all moves that do not capture one of white's own pieces    
    Bitboard Spare3 = ((Spare ^ Spare2) ^ GeneralBoard[j]); // Spare3 is the final result
        for(int r = 0; r < 64; r++) // For each legal square found in Spare3 for the current king
    {
        if(GeneralBoard[r] & Spare3)
        { 
        int y = 12;
        if(GeneralBoard[r] & White_Pieces)
        y--;
		if(Black_Is_Legal(BlackKingCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
       Black_Move_From_Stack[Black_Move_Spacer] = BlackKingCount[w];  // Move_From_Stack gets original position of knight(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
       if((Black_Move_To_Stack[Black_Move_Spacer - 1]) & White_Pieces)
       { 
	   Black_Move_Types[Black_Move_Spacer - 1] = 11;
	   }
	   
	   else
	   {
	   	Black_Move_Types[Black_Move_Spacer - 1] = 12;
	   }
    }
    
        }
    

    }
        
    }
    
     // Tidy up for the next person
     for(int u = 0; u < 8; u++) // Tidy up for the next person
    {
    	BlackKingCount[u] = 0;
	}
	

Black_King_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

/********************************************************************************************************************************************
Pawn Move Generation
*********************************************************************************************************************************************/

int Generate_White_Pawn_Moves()
{
	if(White_Pawns)
	{
		for(int i = 0; i < 64; i++)
{
    if(White_Pawns & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Pawn is on " << PlayerMoves[i] << endl; // cout which square it is on
              WhitePawnCount[White_Pawn_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           White_Pawn_Spacer++;   
    }
}        
         White_Pawn_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_White_Pawn_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_White_Pawn_Moves() // Puts all the legal knight moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Pawn_Spacer; w++)// For each knight found on KnightCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhitePawnCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    
	Bitboard Spare1 = (GeneralBoard[j] << 8);
	Bitboard Spare2 = (White_Pieces | Black_Pieces);
	Spare1 |= Spare2;
	Spare1 ^= Spare2; //Spare1 has one square ahead of the current pawn(if legal to move ahead)
	/*Bitboard Spare3 = (Spare1 << 8);
	Spare3 |= Spare2;
	Spare3 ^= Spare2;
	Spare1 |= Spare3;
	*/
	Bitboard Second_Rank = 65280;
	Bitboard Swat = Second_Rank & GeneralBoard[j];
	Swat <<= 8;
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
        int y = 2;
        if(GeneralBoard[r] & Black_Pieces)
        y--;
        if(GeneralBoard[r] & Eigth_Rank_White)
        y = 14;
        if((GeneralBoard[r] & Eigth_Rank_White) & Black_Pieces)
        y = 13;
        
		if(White_Is_Legal(WhitePawnCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
        White_Move_From_Stack[White_Move_Spacer] = WhitePawnCount[w];  // Move_From_Stack gets original position of knight(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        White_Move_Types[White_Move_Spacer - 1] = 2;
        if((White_Move_To_Stack[White_Move_Spacer - 1]) & Black_Pieces)
        White_Move_Types[White_Move_Spacer - 1] = 1;
	    if((White_Move_To_Stack[White_Move_Spacer - 1]) & Eigth_Rank_White)
	    White_Move_Types[White_Move_Spacer - 1] = 14;		
		if((White_Move_To_Stack[White_Move_Spacer - 1] & Eigth_Rank_White) & Black_Pieces)
	    White_Move_Types[White_Move_Spacer - 1] = 13;
	    	    
	        
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) // Tidy up for the next person
    {
    	WhitePawnCount[u] = 0;
	}
	

White_Pawn_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

int Generate_Black_Pawn_Moves()
{
	if(Black_Pawns)
	{
		for(int i = 0; i < 64; i++)
{
    if(Black_Pawns & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Pawn is on " << PlayerMoves[i] << endl; // cout which square it is on
              BlackPawnCount[Black_Pawn_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           Black_Pawn_Spacer++;   
    }
}        
         Black_Pawn_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_Black_Pawn_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_Black_Pawn_Moves() // Puts all the legal knight moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Pawn_Spacer; w++)// For each knight found on KnightCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackPawnCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
   
	Bitboard Spare1 = (GeneralBoard[j] >> 8);
	Bitboard Spare2 = (Black_Pieces | White_Pieces);
	Spare1 |= Spare2;
	Spare1 ^= Spare2; //Spare1 has one square ahead of the current pawn(if legal to move ahead)
	/*Bitboard Spare3 = (Spare1 >> 8);
	Spare3 |= Spare2;
	Spare3 ^= Spare2;
	Spare1 |= Spare3;*/
	Bitboard Second_Rank = 71776119061217280;
	Bitboard Swat = Second_Rank & GeneralBoard[j];
	Swat >>= 8;
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
        int y = 2;
        if(GeneralBoard[r] & White_Pieces)
        y--;
        if(GeneralBoard[r] & Eigth_Rank_Black)
        y = 14;       
        if((GeneralBoard[r] & Eigth_Rank_Black) & White_Pieces)
        y = 13;
        
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
     for(int u = 0; u < 20; u++) // Tidy up for the next person
    {
    	BlackPawnCount[u] = 0;
	}

Black_Pawn_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

int Generate_White_Rook_Moves()
{
	if(White_Rooks)
	{
		for(int i = 0; i < 64; i++)
{
    if(White_Rooks & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Rook is on " << PlayerMoves[i] << endl; // cout which square it is on
              WhiteRookCount[White_Rook_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           White_Rook_Spacer++;   
    }
}        
         White_Rook_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_White_Rook_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_White_Rook_Moves() // Puts all the legal rook moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Rook_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteRookCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Rmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= White_Pieces;
    Spare1 ^= White_Pieces;
	 
	    for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 8;
        if(GeneralBoard[r] & Black_Pieces)
        y--;
		if(White_Is_Legal(WhiteRookCount[w], GeneralBoard[r], y))
		{
       // cout << "It can move to " << PlayerMoves[r] << endl;
        White_Move_From_Stack[White_Move_Spacer] = WhiteRookCount[w];  // Move_From_Stack gets original position of knight(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        if((White_Move_To_Stack[White_Move_Spacer - 1]) & Black_Pieces)
        { 
	    White_Move_Types[White_Move_Spacer - 1] = 7;
	    }
	   
	    else
	    {
	   	White_Move_Types[White_Move_Spacer - 1] = 8;
	    }
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) // Tidy up for the next person
    {
    	WhiteRookCount[u] = 0;
	}
	

White_Rook_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

int Generate_Black_Rook_Moves()
{
	if(Black_Rooks)
	{
		for(int i = 0; i < 64; i++)
{
    if(Black_Rooks & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Rook is on " << PlayerMoves[i] << endl; // cout which square it is on
              BlackRookCount[Black_Rook_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           Black_Rook_Spacer++;   
    }
}        
         Black_Rook_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_Black_Rook_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_Black_Rook_Moves() // Puts all the legal rook moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Rook_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackRookCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Rmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= Black_Pieces;
    Spare1 ^= Black_Pieces;
	 
	    for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 8;
        if(GeneralBoard[r] & White_Pieces)
        y--;
		if(Black_Is_Legal(BlackRookCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
        Black_Move_From_Stack[Black_Move_Spacer] = BlackRookCount[w];  // Move_From_Stack gets original position of knight(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        if((Black_Move_To_Stack[Black_Move_Spacer - 1]) & White_Pieces)
        { 
	    Black_Move_Types[Black_Move_Spacer - 1] = 7;
	    }
	   
	    else
	    {
	   	Black_Move_Types[Black_Move_Spacer - 1] = 8;
	    }
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) // Tidy up for the next person
    {
    	BlackRookCount[u] = 0;
	}
	

Black_Rook_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

int Generate_White_Bishop_Moves()
{
	if(White_Bishops)
	{
		for(int i = 0; i < 64; i++)
{
    if(White_Bishops & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Bishop is on " << PlayerMoves[i] << endl; // cout which square it is on
              WhiteBishopCount[White_Bishop_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           White_Bishop_Spacer++;   
    }
}        
         White_Bishop_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_White_Bishop_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_White_Bishop_Moves() // Puts all the legal rook moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Bishop_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteBishopCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Bmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= White_Pieces;
    Spare1 ^= White_Pieces;
	 
	    for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 6;
        if(GeneralBoard[r] & Black_Pieces)
        y--;
		if(White_Is_Legal(WhiteBishopCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
        White_Move_From_Stack[White_Move_Spacer] = WhiteBishopCount[w];  // Move_From_Stack gets original position of knight(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        if((White_Move_To_Stack[White_Move_Spacer - 1]) & Black_Pieces)
        { 
	    White_Move_Types[White_Move_Spacer - 1] = 5;
	    }
	   
	    else
	    {
	   	White_Move_Types[White_Move_Spacer - 1] = 6;
	    }
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) // Tidy up for the next person
    {
    	WhiteBishopCount[u] = 0;
	}
	

White_Bishop_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

int Generate_Black_Bishop_Moves()
{
	if(Black_Bishops)
	{
		for(int i = 0; i < 64; i++)
{
    if(Black_Bishops & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Bishop is on " << PlayerMoves[i] << endl; // cout which square it is on
              BlackBishopCount[Black_Bishop_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           Black_Bishop_Spacer++;   
    }
}        
         Black_Bishop_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_Black_Bishop_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_Black_Bishop_Moves() // Puts all the legal rook moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Bishop_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackBishopCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
        {
            j = i;
        }
    }        
        
    Bitboard Spare1 = Bmagic(j, (White_Pieces | Black_Pieces));
    Spare1 |= Black_Pieces;
    Spare1 ^= Black_Pieces;
	 
	    for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare1)
        { 
        int y = 6;
        if(GeneralBoard[r] & White_Pieces)
        y--;
		if(Black_Is_Legal(BlackBishopCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
        Black_Move_From_Stack[Black_Move_Spacer] = BlackBishopCount[w];  // Move_From_Stack gets original position of knight(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        if((Black_Move_To_Stack[Black_Move_Spacer - 1]) & White_Pieces)
        { 
	    Black_Move_Types[Black_Move_Spacer - 1] = 5;
	    }
	   
	    else
	    {
	   	Black_Move_Types[Black_Move_Spacer - 1] = 6;
	    }
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 20; u++) // Tidy up for the next person
    {
    	BlackBishopCount[u] = 0;
	}
	

Black_Bishop_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

int Generate_White_Queen_Moves()
{
	if(White_Queens)
	{
		for(int i = 0; i < 64; i++)
{
    if(White_Queens & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Queen is on " << PlayerMoves[i] << endl; // cout which square it is on
              WhiteQueenCount[White_Queen_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           White_Queen_Spacer++;   
    }
}        
         White_Queen_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_White_Queen_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_White_Queen_Moves() // Puts all the legal rook moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= White_Queen_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(WhiteQueenCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
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
	 
	    for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare3)
        { 
        int y = 10;
        if(GeneralBoard[r] & Black_Pieces)
        y--;
		if(White_Is_Legal(WhiteQueenCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
        White_Move_From_Stack[White_Move_Spacer] = WhiteQueenCount[w];  // Move_From_Stack gets original position of knight(s)
        White_Move_To_Stack[White_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        if((White_Move_To_Stack[White_Move_Spacer - 1]) & Black_Pieces)
        { 
	    White_Move_Types[White_Move_Spacer - 1] = 9;
	    }
	   
	    else
	    {
	   	White_Move_Types[White_Move_Spacer - 1] = 10;
	    }
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 28; u++) // Tidy up for the next person
    {
    	WhiteQueenCount[u] = 0;
	}
	

White_Queen_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

int Generate_Black_Queen_Moves()
{
	if(Black_Queens)
	{
		for(int i = 0; i < 64; i++)
{
    if(Black_Queens & (GeneralBoard[i])) // If a pawn is found
    {
        
        //cout << "Queen is on " << PlayerMoves[i] << endl; // cout which square it is on
              BlackQueenCount[Black_Queen_Spacer] = GeneralBoard[i]; // Put the pawn on the pawn Stack; Call the knight a "number of pawns" e.g. the "first" pawn
           Black_Queen_Spacer++;   
    }
}        
         Black_Queen_Spacer--; // Outside the loop, make sure that I don't get mixed up; I have to make the Spacer one smaller
         Stack_Black_Queen_Moves(); // Puts all legal pawn moves on stack
    }
	
	return 0;
	
	
}


int Stack_Black_Queen_Moves() // Puts all the legal rook moves on move stack 
{ 
    int j = 0;
    int w = 0; // Use it in a for loop to keep track of the number of iterations
    for(int w = 0; w <= Black_Queen_Spacer; w++)// For each rook found on RookCount[]
    {    
    for( int i = 0; i < 64; i++)
    {
        if(BlackQueenCount[w] & (GeneralBoard[i])) // Find the index of the current knight(1-63) and assign this value to j
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
	 
	    for(int r = 0; r < 64; r++) // For each legal square found in Spare1 for the current pawn
    {
        if(GeneralBoard[r] & Spare3)
        { 
        int y = 10;
        if(GeneralBoard[r] & White_Pieces)
        y--;
		if(Black_Is_Legal(BlackQueenCount[w], GeneralBoard[r], y))
		{
        //cout << "It can move to " << PlayerMoves[r] << endl;
        Black_Move_From_Stack[Black_Move_Spacer] = BlackQueenCount[w];  // Move_From_Stack gets original position of knight(s)
        Black_Move_To_Stack[Black_Move_Spacer++] = GeneralBoard[r]; // Move_To_Stack gets a square it can move to
        if((Black_Move_To_Stack[Black_Move_Spacer - 1]) & White_Pieces)
        { 
	   Black_Move_Types[Black_Move_Spacer - 1] = 9;
	    }
	   
	    else
	    {
	   Black_Move_Types[Black_Move_Spacer - 1] = 10;
	    }
    }
    }
    

    }
}
    
    
     // Tidy up for the next person
     for(int u = 0; u < 28; u++) // Tidy up for the next person
    {
    	BlackQueenCount[u] = 0;
	}
	

Black_Queen_Spacer = 0; // Reset the knight count of the current position so that if called twice, the function can start from scratch
    return 0;
}

bool White_Is_Legal(Bitboard From_Square, Bitboard To_Square, int Move_Type)
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
switch(Move_Type)	
{
case 1:
               	White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Pawns2 |= To_Square;
               	White_Pawns2 ^= From_Square;
               	Black_Pieces2 |= To_Square;
				Black_Pieces2 ^= To_Square;
				Black_Queens2 |= To_Square; 
				Black_Queens2 ^= To_Square; 
				Black_Rooks2 |= To_Square; 
				Black_Rooks2 ^= To_Square; 
				Black_Bishops2 |= To_Square; 
				Black_Bishops2 ^= To_Square; 
				Black_Knights2 |= To_Square; 
				Black_Knights2 ^= To_Square; 
				Black_Pawns2 |= To_Square;  
				Black_Pawns2  ^= To_Square; 
				break;
				
               	
               	case 2:
                White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Pawns2 |= To_Square;
               	White_Pawns2 ^= From_Square;
               	break;	
               	
               	
               	case 3:
               	White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Knights2 |= To_Square;
               	White_Knights2 ^= From_Square;
               	Black_Pieces2 |= To_Square;
				Black_Pieces2 ^= To_Square;
				Black_Queens2 |= To_Square; 
				Black_Queens2 ^= To_Square; 
				Black_Rooks2 |= To_Square; 
				Black_Rooks2 ^= To_Square; 
				Black_Bishops2 |= To_Square; 
				Black_Bishops2 ^= To_Square; 
				Black_Knights2 |= To_Square; 
				Black_Knights2 ^= To_Square; 
				Black_Pawns2 |= To_Square;  
				Black_Pawns2  ^= To_Square; 
				break;
				
				case 4:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Knights2 |= To_Square;
               	White_Knights2 ^= From_Square;
               	break;
				   
			    case 5:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Bishops2 |= To_Square;
               	White_Bishops2 ^= From_Square;
               	Black_Pieces2 |= To_Square;
				Black_Pieces2 ^= To_Square;
				Black_Queens2 |= To_Square; 
				Black_Queens2 ^= To_Square; 
				Black_Rooks2 |= To_Square; 
				Black_Rooks2 ^= To_Square; 
				Black_Bishops2 |= To_Square; 
				Black_Bishops2 ^= To_Square; 
				Black_Knights2 |= To_Square; 
				Black_Knights2 ^= To_Square; 
				Black_Pawns2 |= To_Square;  
				Black_Pawns2  ^= To_Square; 
				break;	
				
				case 6:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Bishops2 |= To_Square;
               	White_Bishops2 ^= From_Square;
               	break;
				   
				case 7:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Rooks2 |= To_Square;
               	White_Rooks2 ^= From_Square;
               	Black_Pieces2 |= To_Square;
				Black_Pieces2 ^= To_Square;
				Black_Queens2 |= To_Square; 
				Black_Queens2 ^= To_Square; 
				Black_Rooks2 |= To_Square; 
				Black_Rooks2 ^= To_Square; 
				Black_Bishops2 |= To_Square; 
				Black_Bishops2 ^= To_Square; 
				Black_Knights2 |= To_Square; 
				Black_Knights2 ^= To_Square; 
				Black_Pawns2 |= To_Square;  
				Black_Pawns2  ^= To_Square; 
				break;
				
				case 8:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Rooks2 |= To_Square;
               	White_Rooks2 ^= From_Square;
               	break;
               	
               	case 9:
               	White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Queens2 |= To_Square;
               	White_Queens2 ^= From_Square;
               	Black_Pieces2 |= To_Square;
				Black_Pieces2 ^= To_Square;
				Black_Queens2 |= To_Square; 
				Black_Queens2 ^= To_Square; 
				Black_Rooks2 |= To_Square; 
				Black_Rooks2 ^= To_Square; 
				Black_Bishops2 |= To_Square; 
				Black_Bishops2 ^= To_Square; 
				Black_Knights2 |= To_Square; 
				Black_Knights2 ^= To_Square; 
				Black_Pawns2 |= To_Square;  
				Black_Pawns2  ^= To_Square; 
				break;
				
				case 10:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Queens2 |= To_Square;
               	White_Queens2 ^= From_Square;
               	break;
				
				case 11:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_King2 |= To_Square;
               	White_King2 ^= From_Square;
               	Black_Pieces2 |= To_Square;
				Black_Pieces2 ^= To_Square;
				Black_Queens2 |= To_Square; 
				Black_Queens2 ^= To_Square; 
				Black_Rooks2 |= To_Square; 
				Black_Rooks2 ^= To_Square; 
				Black_Bishops2 |= To_Square; 
				Black_Bishops2 ^= To_Square; 
				Black_Knights2 |= To_Square; 
				Black_Knights2 ^= To_Square; 
				Black_Pawns2 |= To_Square;  
				Black_Pawns2  ^= To_Square; 
				break; 
				
				case 12:
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_King2 |= To_Square;
               	White_King2 ^= From_Square;
               	break;
               	
               	case 13:
			    White_Pawns2 ^= From_Square;
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Queens2 |= To_Square;
               	Black_Pieces2 |= To_Square;
				Black_Pieces2 ^= To_Square;
				Black_Queens2 |= To_Square; 
				Black_Queens2 ^= To_Square; 
				Black_Rooks2 |= To_Square; 
				Black_Rooks2 ^= To_Square; 
				Black_Bishops2 |= To_Square; 
				Black_Bishops2 ^= To_Square; 
				Black_Knights2 |= To_Square; 
				Black_Knights2 ^= To_Square; 
				break; 
				
				case 14:
			    White_Pawns2 ^= From_Square;
				White_Pieces2 |= To_Square;
               	White_Pieces2 ^= From_Square;
               	White_Queens2 |= To_Square;
               	break;	
		}
	int h; 
	for(int j = 0; j < 64; j++)
	{
		if(White_King2 & GeneralBoard[j])
		h = j;
	}
	
	Bitboard BAttacks = Bmagic(h, (White_Pieces2 | Black_Pieces2));
	Bitboard RAttacks = Rmagic(h, (White_Pieces2 | Black_Pieces2));
	Bitboard QAttacks = Qmagic(h, (White_Pieces2 | Black_Pieces2));
	if(BAttacks & (Black_Bishops2))
	return false;
	if(RAttacks & (Black_Rooks2))
	return false;
	if(QAttacks & (Black_Queens2))
	return false;
	if(Knight_Lookup_Table[h] & Black_Knights2)
	return false;
	if(King_Lookup_Table[h] & Black_King2)
	return false;
	
	Bitboard Spare = Black_Pawns2;
	Spare ^= A_Pawn_Mask;
	Spare ^= A_Pawn_Mask;
	if((Spare >> 7) & White_King2)
	return false;
	
	Bitboard Spare2 = Black_Pawns2;
	Spare2 ^= H_Pawn_Mask;
	Spare2 ^= H_Pawn_Mask;
	if((Spare2 >> 9) & White_King2)
	return false;
	
	Black_Pawns2 |= A_Pawn_Mask;
	Black_Pawns2 ^= A_Pawn_Mask; 
	Black_Pawns2 |= H_Pawn_Mask;
	Black_Pawns2 ^= H_Pawn_Mask;
	if(((Black_Pawns2 >> 7) | (Black_Pawns2 >> 9)) & White_King2)
	return false;
	
	else
	return true;
} 
bool Black_Is_Legal(Bitboard From_Square, Bitboard To_Square, int Move_Type)
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
switch(Move_Type)
               { 
               
               case 1:
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
               	break;
               	
               	case 2:
                Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Pawns2 |= To_Square;
               	Black_Pawns2 ^= From_Square;
               	break;	
               	
               	case 3:
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
               	break;
               	
               	case 4:
               	Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Knights2 |= To_Square;
               	Black_Knights2 ^= From_Square;
               	break;	
				   
				case 5:
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
               	break;  	
               	
				case 6:
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Bishops2 |= To_Square;
               	Black_Bishops2 ^= From_Square;
               	break;	   	
               	
               	case 7:
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
               	break;  		
               	
               	case 8:
               	Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Rooks2 |= To_Square;
               	Black_Rooks2 ^= From_Square;
               	break;
				   
				case 9:	   		
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
               	break;  		
				 
				case 10:
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_Queens2 |= To_Square;
               	Black_Queens2 ^= From_Square;
               	break; 	
               	
               	case 11:
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
               	break; 
				   
				case 12:
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	Black_King2 |= To_Square;
               	Black_King2 ^= From_Square;
               	break; 
				   
				case 13: // Promotion and a capture
				Black_Pawns2 ^= From_Square;
				Black_Queens2 |= To_Square; 
               	Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
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
				break;
				
				case 14: // Plain promotion
				Black_Pawns2 ^= From_Square;
				Black_Queens2 |= To_Square;
				Black_Pieces2 |= To_Square;
               	Black_Pieces2 ^= From_Square;
               	break;  		
               			
			   }
			   
			   int h; 
	for(int j = 0; j < 64; j++)
	{
		if(Black_King2 & GeneralBoard[j])
		h = j;
	}
	
	Bitboard BAttacks = Bmagic(h, (White_Pieces2 | Black_Pieces2));
	Bitboard RAttacks = Rmagic(h, (White_Pieces2 | Black_Pieces2));
	Bitboard QAttacks = Qmagic(h, (White_Pieces2 | Black_Pieces2));
	if(BAttacks & (White_Bishops2))
	return false;
	if(RAttacks & (White_Rooks2))
	return false;
	if(QAttacks & (White_Queens2))
	return false;
	if(Knight_Lookup_Table[h] & White_Knights2)
	return false;
	if(King_Lookup_Table[h] & White_King2)
	return false;
	
	Bitboard Spare = White_Pawns2;
	Spare ^= A_Pawn_Mask;
	Spare ^= A_Pawn_Mask;
	if((Spare << 9) & Black_King2)
	return false;
	
	Bitboard Spare2 = White_Pawns2;
	Spare2 ^= H_Pawn_Mask;
	Spare2 ^= H_Pawn_Mask;
	if((Spare2 << 7) & Black_King2)
	return false;
	
    White_Pawns2 |= A_Pawn_Mask;
	White_Pawns2 ^= A_Pawn_Mask; 
	White_Pawns2 |= H_Pawn_Mask;
	White_Pawns2 ^= H_Pawn_Mask;
	if(((White_Pawns2 << 7) | (White_Pawns2 << 9)) & GeneralBoard[h])
	return false;
	else
	return true;
} 



	
#endif

