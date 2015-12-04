#include "MoveLegalityTesting.h" 
#include "magicmoves.h"

/* This function takes a bitboard called To_Square that has only the bit set that the move moves to; it takes a From_Square that is the same, 
and it has the bit set that the piece in the move moves to. It also takes a Move_Type, which tells it which way to update its bitboards
*/
bool White_Is_Legal(const Bitboard& From_Square, const Bitboard& To_Square, const int Move_Type) 
{
        int h; 
        for(int j = 0; j < 64; j++) 
        {
                if(White_King & GeneralBoard[j])//Get the index (0-63) of White's king
                h = j;
                break;
        }
Bitboard BAttacks = Bmagic(h, (White_Pieces | Black_Pieces));
Bitboard RAttacks = Rmagic(h, (White_Pieces | Black_Pieces));
Bitboard QAttacks = Qmagic(h, (White_Pieces | Black_Pieces));
        
        
Bitboard White_Pieces2 = White_Pieces; //Make a copy of all normal bitboards to use in this function
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
				case 1://Pawn capture
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
                                
                
                case 2://Pawn single push
                White_Pieces2 |= To_Square;
                White_Pieces2 ^= From_Square;
                White_Pawns2 |= To_Square;
                White_Pawns2 ^= From_Square;
                break;  
                
                
                case 3://Knight capture
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
                                
                case 4://Knight plain move
                White_Pieces2 |= To_Square;
                White_Pieces2 ^= From_Square;
                White_Knights2 |= To_Square;
                White_Knights2 ^= From_Square;
                break;
                                   
                case 5://Bishop capture
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
                                
                case 6://Bishop normal move
                White_Pieces2 |= To_Square;
                White_Pieces2 ^= From_Square;
                White_Bishops2 |= To_Square;
                White_Bishops2 ^= From_Square;
                break;
                                   
                case 7://Rook capture
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
                                
                case 8://Rook normal move
                White_Pieces2 |= To_Square;
                White_Pieces2 ^= From_Square;
                White_Rooks2 |= To_Square;
                White_Rooks2 ^= From_Square;
                break;
                
                case 9://Queen capture
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
                                
                case 10://Queen nrmal move
                White_Pieces2 |= To_Square;
                White_Pieces2 ^= From_Square;
                White_Queens2 |= To_Square;
                White_Queens2 ^= From_Square;
                break;
                                
                case 11://King capture
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
                                
                case 12://King normal move
                White_Pieces2 |= To_Square;
                White_Pieces2 ^= From_Square;
                White_King2 |= To_Square;
                White_King2 ^= From_Square;
                break;
                
                case 13://Pawn promotion with a capture
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
                                
                case 14://Plain pawn promotion
                White_Pawns2 ^= From_Square;
                White_Pieces2 |= To_Square;
                White_Pieces2 ^= From_Square;
                White_Queens2 |= To_Square;
                break;  
        }
        
        
        
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
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare >> 7) & White_King2)
        	return false;
        
        Bitboard Spare2 = Black_Pawns2;
        Spare2 |= H_Pawn_Mask;
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


bool Black_Is_Legal(const Bitboard& From_Square, const Bitboard& To_Square, const int Move_Type)
{
        int h; 
        for(int j = 0; j < 64; j++)
        {
                if(Black_King & GeneralBoard[j])//Get the index(0-63) of the black king
                h = j;
                break;
        }
        
                        
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

Bitboard BAttacks = Bmagic(h, (White_Pieces2 | Black_Pieces2));
Bitboard RAttacks = Rmagic(h, (White_Pieces2 | Black_Pieces2));
Bitboard QAttacks = Qmagic(h, (White_Pieces2 | Black_Pieces2));
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
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare << 9) & Black_King2)
        	return false;
        
        Bitboard Spare2 = White_Pawns2;
        Spare2 |= H_Pawn_Mask;
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
