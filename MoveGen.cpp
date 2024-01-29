using namespace std;
#include "Bitboard.h"
#include "MoveGen.h"
#include "Search.h"
#include "magicmoves.h"
#include "Util.h"

bool Is_Legal;
void Generate_White_Moves(const bool caps, Position* position)
{
	bool inCheck = Search::Is_Mate(position) < 0;
	Bitboard blockers = Qmagic(lsb(position->White_King), position->White_Pieces | position->Black_Pieces) & position->White_Pieces;
	position->numlegalmoves = 0;
    for(int i = 0; i < 64; i++)
	{
		if(position->White_Pawns & GeneralBoard[i])
		{
			if(!caps)
			{
				if(GeneralBoard[i] & 65280)
				{
					if(!((GeneralBoard[i] << 8) & (position->White_Pieces | position->Black_Pieces)))
					{
						Move m(WP, NONE, GeneralBoard[i], GeneralBoard[i] << 8, false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
						if(!((GeneralBoard[i] << 16) & (position->White_Pieces | position->Black_Pieces)))
						{
							Move m(WP, NONE, GeneralBoard[i], GeneralBoard[i] << 16, false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
						}					
					}
				}
				else
				{
					if((!((GeneralBoard[i] << 8) & (position->White_Pieces | position->Black_Pieces))) && (!(GeneralBoard[i] & 71776119061217280)))
					{
						Move m(WP, NONE, GeneralBoard[i], GeneralBoard[i] << 8, false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}
			}
			if((GeneralBoard[i] & 71776119061217280) && (!(GeneralBoard[i] << 8 & (position->White_Pieces | position->Black_Pieces))))
			{
				Move m(WP, NONE, GeneralBoard[i], GeneralBoard[i] << 8, false, true);
				for(int p = 1; p < 5; p++)
					{
						m.PromotionType = Piece(int(WP) + p);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
			}
			if(!(GeneralBoard[i] & A_Pawn_Mask))
			{
				if((GeneralBoard[i] << 7) & position->Black_Pieces && (GeneralBoard[i]  & 71776119061217280))
				{
					Move m(WP, position->Get_Piece_From_Bitboard(GeneralBoard[i] << 7), GeneralBoard[i], GeneralBoard[i] << 7, false, true);
					{
						for(int p = 1; p < 5; p++)
						{
							m.PromotionType = Piece(int(WP) + p);
							if(inCheck || (m.From & blockers))
							{
								if(White_Is_Legal(*position, m))
									position->LegalMoves[position->numlegalmoves++] = m;
							}
							else
								position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				}
				else if((GeneralBoard[i] << 7) & position->Black_Pieces)
				{
					Move m(WP, position->Get_Piece_From_Bitboard(GeneralBoard[i] << 7), GeneralBoard[i], GeneralBoard[i] << 7, false, false);
					if(inCheck || (m.From & blockers))
					{
						if(White_Is_Legal(*position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
					}
					else
						position->LegalMoves[position->numlegalmoves++] = m;
				}
			}
			if(!(GeneralBoard[i] & H_Pawn_Mask))
			{
				if((GeneralBoard[i] << 9) & position->Black_Pieces && (GeneralBoard[i]  & 71776119061217280))
				{
					Move m(WP, position->Get_Piece_From_Bitboard(GeneralBoard[i] << 9), GeneralBoard[i], GeneralBoard[i] << 9, false, true);
					for(int p = 1; p < 5; p++)
						{
							m.PromotionType = Piece(int(WP) + p);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
						}
				}
				else if((GeneralBoard[i] << 9) & position->Black_Pieces)
				{
					Move m(WP, position->Get_Piece_From_Bitboard(GeneralBoard[i] << 9), GeneralBoard[i], GeneralBoard[i] << 9, false, false);
					if(inCheck || (m.From & blockers))
					{
						if(White_Is_Legal(*position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
					}
					else
						position->LegalMoves[position->numlegalmoves++] = m;
				}
			}
		continue;
		}
		if(GeneralBoard[i] & position->White_Knights)
		{
			Bitboard b = Knight_Lookup_Table[i];
			b |= position->White_Pieces;
			b ^= position->White_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WN, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(WN, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
			}
		continue;
		}
		if(GeneralBoard[i] & position->White_Bishops)
		{
			Bitboard b = Bmagic(i, position->White_Pieces | position->Black_Pieces);
			b |= position->White_Pieces;
			b ^= position->White_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WB, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(WB, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
			}
		continue;
		}
		if(GeneralBoard[i] & position->White_Rooks)
		{
			Bitboard b = Rmagic(i, position->White_Pieces | position->Black_Pieces);
			b |= position->White_Pieces;
			b ^= position->White_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WR, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(WR, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
			}
		continue;
		}
		if(GeneralBoard[i] & position->White_Queens)
		{
			Bitboard b = Qmagic(i, position->White_Pieces | position->Black_Pieces);
			b |= position->White_Pieces;
			b ^= position->White_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WQ, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(WQ, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(White_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
			}
		continue;
		}
		if(GeneralBoard[i] & position->White_King)
		{
			Bitboard b = King_Lookup_Table[i];
			b |= position->White_Pieces;
			b ^= position->White_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WK, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(*position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(WK, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(*position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
									
			}
			if(!caps && position->WhiteCanCastleK)
			{
				Bitboard first = (GeneralBoard[i] & 16);
        		Bitboard second = ((position->White_Pieces | position->Black_Pieces) & 96);
        		Bitboard e1 = 16, f1 = 32, g1 = 64;
        		bool Rookonh1 = position->White_Rooks & 128;
        		if(first && !second && Rookonh1)
        		{
        			Move m(WK, NONE, GeneralBoard[i], f1, false, false);
        			bool safetomovetof1 = White_Is_Legal(*position, m);
        			Move m1(WK, NONE, GeneralBoard[i], g1, false, false);
        			bool safetomovetog1 = White_Is_Legal(*position, m1);
        			Move m2(WK, NONE, GeneralBoard[i], e1, false, false);
        			bool safetomovetoe1 = Search::Is_Mate(position) >= 0;
        			if(safetomovetof1 && safetomovetog1 && safetomovetoe1)
        			{
        				m1.Castling = true;
        				position->LegalMoves[position->numlegalmoves++] = m1;
		        	}
		    	}
	    	}
	    	if(!caps && position->WhiteCanCastleQ)
			{
				Bitboard first = (GeneralBoard[i] & 16);
        		Bitboard second = ((position->White_Pieces | position->Black_Pieces) & 14);
        		Bitboard e1 = 16, d1 = 8, c1 = 4;
        		bool Rookona1 = position->White_Rooks & 1;
        		if(first && !second && Rookona1)
        		{
        			Move m(WK, NONE, GeneralBoard[i], d1, false, false);
        			bool safetomovetod1 = White_Is_Legal(*position, m);
        			Move m1(WK, NONE, GeneralBoard[i], c1, false, false);
        			bool safetomovetoc1 = White_Is_Legal(*position, m1);
        			Move m2(WK, NONE, GeneralBoard[i], e1, false, false);
        			bool safetomovetoe1 = Search::Is_Mate(position) >= 0;
        			if(safetomovetoc1 && safetomovetod1 && safetomovetoe1)
        			{
        				m1.Castling = true;
        				position->LegalMoves[position->numlegalmoves++] = m1;
		        	}
		    	}
	    	}
		}
	}
}

void Generate_Black_Moves(const bool caps, Position* position)
{
	bool inCheck = Search::Is_Mate(position) < 0;
	Bitboard blockers = Qmagic(lsb(position->Black_King), position->White_Pieces | position->Black_Pieces) & position->Black_Pieces;
	position->numlegalmoves = 0;
	for(int i = 0; i < 64; i++)
	{
		if(position->Black_Pawns & GeneralBoard[i])
		{
			if(!caps)
			{
				if(GeneralBoard[i] & 71776119061217280)
				{
					if(!((GeneralBoard[i] >> 8) & (position->White_Pieces | position->Black_Pieces)))
					{
						Move m(BP, NONE, GeneralBoard[i], GeneralBoard[i] >> 8, false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
						if(!((GeneralBoard[i] >> 16) & (position->White_Pieces | position->Black_Pieces)))
						{
							Move m(BP, NONE, GeneralBoard[i], GeneralBoard[i] >> 16, false, false);
							if(inCheck || (m.From & blockers))
							{
								if(Black_Is_Legal(*position, m))
									position->LegalMoves[position->numlegalmoves++] = m;
							}
							else
								position->LegalMoves[position->numlegalmoves++] = m;
						}	
					}
				}
				else
				{
					if((!((GeneralBoard[i] >> 8) & (position->White_Pieces | position->Black_Pieces))) && (!(GeneralBoard[i] & 65280)))
					{
						Move m(BP, NONE, GeneralBoard[i], GeneralBoard[i] >> 8, false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}
			}
			if(GeneralBoard[i] & 65280 && (!(GeneralBoard[i] >> 8 & (position->White_Pieces | position->Black_Pieces))))
			{
				Move m(BP, NONE, GeneralBoard[i], GeneralBoard[i] >> 8, false, true);
				for(int p = 1; p < 5; p++)
					{
						m.PromotionType = Piece(int(BP) + p);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
			}
			if(!(GeneralBoard[i] & H_Pawn_Mask))
			{
				if(((GeneralBoard[i] >> 7) & position->White_Pieces) && (GeneralBoard[i]  & 65280))
				{
					Move m(BP, position->Get_Piece_From_Bitboard(GeneralBoard[i] >> 7), GeneralBoard[i], GeneralBoard[i] >> 7, false, true);
				 for(int p = 1; p < 5; p++)
							{
								m.PromotionType = Piece(int(BP) + p);
								if(inCheck || (m.From & blockers))
								{
									if(Black_Is_Legal(*position, m))
									position->LegalMoves[position->numlegalmoves++] = m;
								}
								else
									position->LegalMoves[position->numlegalmoves++] = m;
							}
				}
				else if((GeneralBoard[i] >> 7) & position->White_Pieces)
				{
					Move m(BP, position->Get_Piece_From_Bitboard(GeneralBoard[i] >> 7), GeneralBoard[i], GeneralBoard[i] >> 7, false, false);
					if(inCheck || (m.From & blockers))
					{
						if(Black_Is_Legal(*position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
					}
					else
						position->LegalMoves[position->numlegalmoves++] = m;
				}
			}
			if(!(GeneralBoard[i] & A_Pawn_Mask))
			{
				if(((GeneralBoard[i] >> 9) & position->White_Pieces) && (GeneralBoard[i]  & 65280))
				{
					Move m(BP, position->Get_Piece_From_Bitboard(GeneralBoard[i] >> 9), GeneralBoard[i], GeneralBoard[i] >> 9, false, true);
					for(int p = 1; p < 5; p++)
						{
							m.PromotionType = Piece(int(BP) + p);
							if(inCheck || (m.From & blockers))
							{
								if(Black_Is_Legal(*position, m))
									position->LegalMoves[position->numlegalmoves++] = m;
							}
							else
								position->LegalMoves[position->numlegalmoves++] = m;
						}
				}
				else if((GeneralBoard[i] >> 9) & position->White_Pieces)
				{
					Move m(BP, position->Get_Piece_From_Bitboard(GeneralBoard[i] >> 9), GeneralBoard[i], GeneralBoard[i] >> 9, false, false);
					if(inCheck || (m.From & blockers))
					{
						if(Black_Is_Legal(*position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
					}
					else
						position->LegalMoves[position->numlegalmoves++] = m;
				}
			}
		continue;
		}
		if(GeneralBoard[i] & position->Black_Knights)
		{
			Bitboard b = Knight_Lookup_Table[i];
			b |= position->Black_Pieces;
			b ^= position->Black_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BN, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(BN, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
									
			}
		continue;
		}
		if(GeneralBoard[i] & position->Black_Bishops)
		{
			Bitboard b = Bmagic(i, position->White_Pieces | position->Black_Pieces);
			b |= position->Black_Pieces;
			b ^= position->Black_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BB, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(BB, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
			}
		continue;
		}
		if(GeneralBoard[i] & position->Black_Rooks)
		{
			Bitboard b = Rmagic(i, position->White_Pieces | position->Black_Pieces);
			b |= position->Black_Pieces;
			b ^= position->Black_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BR, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(BR, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
			}
		continue;
		}
		if(GeneralBoard[i] & position->Black_Queens)
		{
			Bitboard b = Qmagic(i, position->White_Pieces | position->Black_Pieces);
			b |= position->Black_Pieces;
			b ^= position->Black_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BQ, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				else
				{
					if(!caps)
					{
						Move m(BQ, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(inCheck || (m.From & blockers))
						{
							if(Black_Is_Legal(*position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
						}
						else
							position->LegalMoves[position->numlegalmoves++] = m;
					}
				}	
			}
		continue;
		}
		if(GeneralBoard[i] & position->Black_King)
		{
			Bitboard b = King_Lookup_Table[i];
			b |= position->Black_Pieces;
			b ^= position->Black_Pieces;
			int p = __popcnt64(b);
			for(int m = 0; m < p; m++)
			{
				short j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BK, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(*position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(BK, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(*position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
									
			}
			if(!caps && position->BlackCanCastleK)
			{
				Bitboard first = (GeneralBoard[i] & 1152921504606846976);
        		Bitboard second = ((position->White_Pieces | position->Black_Pieces) & 6917529027641081856);
        		Bitboard e8 = 1152921504606846976, f8 = 2305843009213693952, g8 = 4611686018427387904;
        		bool Rookonh8 = (position->Black_Rooks & 9223372036854775808ULL);
        		if(first && !second && Rookonh8)
        		{
        			Move m(BK, NONE, GeneralBoard[i], f8, false, false);
        			bool safetomovetof8 = Black_Is_Legal(*position, m);
        			Move m1(BK, NONE, GeneralBoard[i], g8, false, false);
        			bool safetomovetog8 = Black_Is_Legal(*position, m1);
        			Move m2(BK, NONE, GeneralBoard[i], e8, false, false);
        			bool safetomovetoe8 = Search::Is_Mate(position) >= 0;
        			if(safetomovetof8 && safetomovetog8 && safetomovetoe8)
        			{
        				m1.Castling = true;
        				position->LegalMoves[position->numlegalmoves++] = m1;
		        	}
		    	}
	    	}
	    	if(!caps && position->BlackCanCastleQ)
			{
				Bitboard first = (GeneralBoard[i] & 1152921504606846976);
        		Bitboard second = ((position->White_Pieces | position->Black_Pieces) & 1008806316530991104);
        		Bitboard e8 = 1152921504606846976, d8 = 576460752303423488, c8 = 288230376151711744;
        		bool Rookona8 = (position->Black_Rooks & 72057594037927936);
        		if(first && !second && Rookona8)
        		{
        			Move m(BK, NONE, GeneralBoard[i], d8, false, false);
        			bool safetomovetod8 = Black_Is_Legal(*position, m);
        			Move m1(BK, NONE, GeneralBoard[i], c8, false, false);
        			bool safetomovetoc8 = Black_Is_Legal(*position, m1);
        			Move m2(BK, NONE, GeneralBoard[i], e8, false, false);
        			bool safetomovetoe8 = Search::Is_Mate(position) >= 0;
        			if(safetomovetod8 && safetomovetoc8 && safetomovetoe8)
        			{
        				m1.Castling = true;
        				position->LegalMoves[position->numlegalmoves++] = m1;
		        	}
		    	}
	    	}
	    }
	}
}
