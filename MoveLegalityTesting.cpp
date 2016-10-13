#include "MoveLegalityTesting.h"
#include "Position.h"
#include "magicmoves.h"

/* This function takes a bitboard called To_Square that has only the bit set that the move moves to; it takes a From_Square that is the same,
and it has the bit set that the piece in the move moves to. It also takes a Move_Type, which tells it which way to update its bitboards
*/
bool White_Is_Legal(Position* position, Move move)
{
	position->Make_Move(move);
    int h;
    for(int j = 0; j < 64; j++)
    {
        if(position->White_King & GeneralBoard[j])//Get the index (0-63) of White's king
        {
            h = j;
            break;
        }
    }
    Bitboard BAttacks = Bmagic(h, (position->White_Pieces | position->Black_Pieces));
    Bitboard RAttacks = Rmagic(h, (position->White_Pieces | position->Black_Pieces));
    Bitboard QAttacks = BAttacks | RAttacks;
    if(QAttacks & (position->Black_Queens))
        {
    	position->Undo_Move(move);
    	return false;
    	}
    if(BAttacks & (position->Black_Bishops))
    {
    	position->Undo_Move(move);
    	return false;
    }
    if(Knight_Lookup_Table[h] & position->Black_Knights)
        {
    	position->Undo_Move(move);
    	return false;
    	}
    Bitboard Spare = position->Black_Pawns;
    Spare |= H_Pawn_Mask;
    Spare ^= H_Pawn_Mask;
    if((Spare >> 7) & position->White_King)
    	{
    	position->Undo_Move(move);
    	return false;
    	}
    Bitboard Spare2 = position->Black_Pawns;
    Spare2 |= A_Pawn_Mask;
    Spare2 ^= A_Pawn_Mask;
    if((Spare2 >> 9) & position->White_King)
        {
    	position->Undo_Move(move);
        return false;
    	}
    if(RAttacks & (position->Black_Rooks))
    	{
    	position->Undo_Move(move);
    	return false;
    	}
    if(King_Lookup_Table[h] & position->Black_King)
        {
    	position->Undo_Move(move);
    	return false;
    	}
    Bitboard b = position->Black_Pawns;
    b |= A_Pawn_Mask;
    b ^= A_Pawn_Mask;
    b |= H_Pawn_Mask;
    b ^= H_Pawn_Mask;
    if(((b >> 7) | (b >> 9)) & position->White_King)
        {
    	position->Undo_Move(move);
        return false;
    	}

    else
        {
    	position->Undo_Move(move);
    	return true;
    	}
}


bool Black_Is_Legal(Position* position, Move move)
{
	position->Make_Move(move);
    int h;
    for(int j = 0; j < 64; j++)
    {
        if(position->Black_King & GeneralBoard[j])//Get the index(0-63) of the black king
        {
            h = j;
            break;
        }
    }
    Bitboard BAttacks = Bmagic(h, (position->White_Pieces | position->Black_Pieces));
    Bitboard RAttacks = Rmagic(h, (position->White_Pieces | position->Black_Pieces));
    Bitboard QAttacks = BAttacks | RAttacks;
	if(QAttacks & (position->White_Queens))
        {
    	position->Undo_Move(move);
        return false;
    	}
    if(BAttacks & (position->White_Bishops))
        {
    	position->Undo_Move(move);
        return false;
    	}
    if(Knight_Lookup_Table[h] & position->White_Knights)
        {
    	position->Undo_Move(move);
        return false;
    	}
    Bitboard Spare2 = position->White_Pawns;
    Spare2 |= A_Pawn_Mask;
    Spare2 ^= A_Pawn_Mask;
    if((Spare2 << 7) & position->Black_King)
        {
    	position->Undo_Move(move);
        return false;
    	}
    Bitboard Spare = position->White_Pawns;
    Spare |= H_Pawn_Mask;
    Spare ^= H_Pawn_Mask;
    if((Spare << 9) & position->Black_King)
        {
    	position->Undo_Move(move);
        return false;
    	}
    if(RAttacks & (position->White_Rooks))
        {
    	position->Undo_Move(move);
        return false;
    	}
    if(King_Lookup_Table[h] & position->White_King)
        {
    	position->Undo_Move(move);
        return false;
    	}
    Bitboard w = position->White_Pawns;
    w |= A_Pawn_Mask;
    w ^= A_Pawn_Mask;
    w |= H_Pawn_Mask;
    w ^= H_Pawn_Mask;
    if(((w << 7) | (w << 9)) & position->Black_King)
        {
    	position->Undo_Move(move);
        return false;
    	}
    else
        {
    	position->Undo_Move(move);
        return true;
    	}
}

