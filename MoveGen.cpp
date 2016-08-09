using namespace std;
#include "Bitboard.h"
#include "MoveGen.h"
#include "Search.h"
#include "magicmoves.h"
#include "Util.h"

bool Is_Legal;

void Generate_White_Moves(const bool caps, Position* position)
{
	int spacer = 0;
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
						if(White_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
						if(!((GeneralBoard[i] << 16) & (position->White_Pieces | position->Black_Pieces)))
						{
							Move m(WP, NONE, GeneralBoard[i], GeneralBoard[i] << 16, false, false);
							if(White_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
						}					
					}
				}
				else
				{
					if((!((GeneralBoard[i] << 8) & (position->White_Pieces | position->Black_Pieces))) && (!(GeneralBoard[i] & 71776119061217280)))
					{
						Move m(WP, NONE, GeneralBoard[i], GeneralBoard[i] << 8, false, false);
						if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				}
			}
			if((GeneralBoard[i] & 71776119061217280) && (!(GeneralBoard[i] << 8 & (position->White_Pieces | position->Black_Pieces))))
			{
				Move m(WP, NONE, GeneralBoard[i], GeneralBoard[i] << 8, false, true);
				for(int p = 1; p < 5; p++)
					{
						m.PromotionType = WP + p;
						if(White_Is_Legal(position, m))
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
							m.PromotionType = WP + p;
							if(White_Is_Legal(position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				}
				else if((GeneralBoard[i] << 7) & position->Black_Pieces)
				{
					Move m(WP, position->Get_Piece_From_Bitboard(GeneralBoard[i] << 7), GeneralBoard[i], GeneralBoard[i] << 7, false, false);
					if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
				}
			}
			if(!(GeneralBoard[i] & H_Pawn_Mask))
			{
				if((GeneralBoard[i] << 9) & position->Black_Pieces && (GeneralBoard[i]  & 71776119061217280))
				{
					Move m(WP, position->Get_Piece_From_Bitboard(GeneralBoard[i] << 9), GeneralBoard[i], GeneralBoard[i] << 9, false, true);
					for(int p = 1; p < 5; p++)
						{
							m.PromotionType = WP + p;
							if(White_Is_Legal(position, m))
							position->LegalMoves[position->numlegalmoves++] = m;
						}
				}
				else if((GeneralBoard[i] << 9) & position->Black_Pieces)
				{
					Move m(WP, position->Get_Piece_From_Bitboard(GeneralBoard[i] << 9), GeneralBoard[i], GeneralBoard[i] << 9, false, false);
					if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
				}
			}
		}
		if(GeneralBoard[i] & position->White_Knights)
		{
			Bitboard k = Knight_Lookup_Table[i];
			k |= position->White_Pieces;
			Bitboard b = k ^ position->White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WN, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(WN, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
									
			}
		}
		if(GeneralBoard[i] & position->White_Bishops)
		{
			Bitboard bi = Bmagic(i, position->White_Pieces | position->Black_Pieces);
			bi |= position->White_Pieces;
			Bitboard b = bi ^ position->White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WB, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(WB, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & position->White_Rooks)
		{
			Bitboard r = Rmagic(i, position->White_Pieces | position->Black_Pieces);
			r |= position->White_Pieces;
			r ^= position->White_Pieces;
			Bitboard b = r;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WR, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(WR, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & position->White_Queens)
		{
			Bitboard q = Rmagic(i, position->White_Pieces | position->Black_Pieces);
			Bitboard qu = (Bmagic(i, position->White_Pieces | position->Black_Pieces) | q);
			qu |= position->White_Pieces;
			Bitboard b = qu ^ position->White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WQ, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(WQ, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & position->White_King)
		{
			Bitboard k = King_Lookup_Table[i];
			k |= position->White_Pieces;
			Bitboard b = k ^ position->White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->Black_Pieces)
					{
						Move m(WK, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(WK, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(White_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
									
			}
			if(!caps)
			{
				Bitboard first = (GeneralBoard[i] & 16);
        		Bitboard second = ((position->White_Pieces | position->Black_Pieces) & 96);
        		Bitboard e1 = 16, f1 = 32, g1 = 64, a0 = 0;
        		bool canmovetof1 = !(f1 & (position->White_Pieces | position->Black_Pieces));
        		bool canmovetog1 = !(g1 & (position->White_Pieces | position->Black_Pieces));
        		if(canmovetof1 && canmovetog1)
        		{
        			Move m(WK, NONE, GeneralBoard[i], 32, false, false);
        			bool safetomovetof1 = White_Is_Legal(position, m);
        			Move m1(WK, NONE, GeneralBoard[i], 64, false, false);
        			bool safetomovetog1 = White_Is_Legal(position, m1);
        			Move m2(WK, NONE, GeneralBoard[i], 16, false, false);
        			bool safetomovetoe1 = Search::Is_Mate(position) >= 0 ? true : false;
        			bool Rookonh1 = (position->White_Rooks & 128);
        			int notincheck = Search::Is_Mate(position);
        			if(first && (!second) && safetomovetof1 && safetomovetog1 && safetomovetoe1 && (position->WhiteCanCastleK) && Rookonh1 && (notincheck != -10000))
        			{
        				m1.Castling = true;
        				position->LegalMoves[position->numlegalmoves++] = m1;
		        	}
		    	}
	    	}
		}
	}
return;	
}

void Generate_Black_Moves(const bool caps, Position* position)
{
	int spacer = 0;
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
						if(Black_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
						if(!((GeneralBoard[i] >> 16) & (position->White_Pieces | position->Black_Pieces)))
						{
							Move m(BP, NONE, GeneralBoard[i], GeneralBoard[i] >> 16, false, false);
							if(Black_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
						}	
					}
				}
				else
				{
					if((!((GeneralBoard[i] >> 8) & (position->White_Pieces | position->Black_Pieces))) && (!(GeneralBoard[i] & 65280)))
					{
						Move m(BP, NONE, GeneralBoard[i], GeneralBoard[i] >> 8, false, false);
						if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				}
			}
			if(GeneralBoard[i] & 65280 && (!(GeneralBoard[i] >> 8 & (position->White_Pieces | position->Black_Pieces))))
			{
				Move m(BP, NONE, GeneralBoard[i], GeneralBoard[i] >> 8, false, true);
				for(int p = 1; p < 5; p++)
					{
						m.PromotionType = WB + p;
						if(Black_Is_Legal(position, m))
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
								m.PromotionType = BP + p;
								if(Black_Is_Legal(position, m))
								position->LegalMoves[position->numlegalmoves++] = m;
							}
				}
				else if((GeneralBoard[i] >> 7) & position->White_Pieces)
				{
					Move m(BP, position->Get_Piece_From_Bitboard(GeneralBoard[i] >> 7), GeneralBoard[i], GeneralBoard[i] >> 7, false, false);
					if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
				}
			}
			if(!(GeneralBoard[i] & A_Pawn_Mask))
			{
				if(((GeneralBoard[i] >> 9) & position->White_Pieces) && (GeneralBoard[i]  & 65280))
				{
					Move m(BP, position->Get_Piece_From_Bitboard(GeneralBoard[i] >> 9), GeneralBoard[i], GeneralBoard[i] >> 9, false, true);
					if(Black_Is_Legal(position, m))
						{
							for(int p = 1; p < 5; p++)
							{
								m.PromotionType = BP + p;
								position->LegalMoves[position->numlegalmoves++] = m;
							}
						}
				}
				else if((GeneralBoard[i] >> 9) & position->White_Pieces)
				{
					Move m(BP, position->Get_Piece_From_Bitboard(GeneralBoard[i] >> 9), GeneralBoard[i], GeneralBoard[i] >> 9, false, false);
					if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
				}
			}
		}
		if(GeneralBoard[i] & position->Black_Knights)
		{
			Bitboard k = Knight_Lookup_Table[i];
			k |= position->Black_Pieces;
			Bitboard b = k ^ position->Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BN, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(BN, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
									
			}
		}
		if(GeneralBoard[i] & position->Black_Bishops)
		{
			Bitboard bi = Bmagic(i, position->White_Pieces | position->Black_Pieces);
			bi |= position->Black_Pieces;
			Bitboard b = bi ^ position->Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BB, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(BB, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & position->Black_Rooks)
		{
			Bitboard r = Rmagic(i, position->White_Pieces | position->Black_Pieces);
			r |= position->Black_Pieces;
			Bitboard b = r ^ position->Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BR, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(BR, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & position->Black_Queens)
		{
			Bitboard q = Rmagic(i, position->White_Pieces | position->Black_Pieces);
			Bitboard qu = (Bmagic(i, position->White_Pieces | position->Black_Pieces) | q);
			qu |= position->Black_Pieces;
			Bitboard b = qu ^ position->Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BQ, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(BQ, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & position->Black_King)
		{
			Bitboard k = King_Lookup_Table[i];
			k |= position->Black_Pieces;
			Bitboard b = k ^ position->Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & position->White_Pieces)
					{
						Move m(BK, position->Get_Piece_From_Bitboard(GeneralBoard[j]), GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
						{
							position->LegalMoves[position->numlegalmoves++] = m;
						}
					}
				else
				{
					if(!caps)
					{
						Move m(BK, NONE, GeneralBoard[i], GeneralBoard[j], false, false);
						if(Black_Is_Legal(position, m))
							{
								position->LegalMoves[position->numlegalmoves++] = m;
							}
					}
				}	
									
			}
			if(!caps)
			{
				Bitboard first = (GeneralBoard[i] & 1152921504606846976);
        		Bitboard second = ((position->White_Pieces | position->Black_Pieces) & 6917529027641081856);
        		Bitboard e8 = 1152921504606846976, f8 = 2305843009213693952, g8 = 4611686018427387904, a0 = 0;
        		bool canmovetof8 = !(f8 & (position->White_Pieces | position->Black_Pieces));
        		bool canmovetog8 = !(g8 & (position->White_Pieces | position->Black_Pieces));
        		if(canmovetof8 && canmovetog8)
        		{
        			Move m(BK, NONE, GeneralBoard[i], 2305843009213693952, false, false);
        			bool safetomovetof1 = Black_Is_Legal(position, m);
        			Move m1(BK, NONE, GeneralBoard[i], 4611686018427387904, false, false);
        			bool safetomovetog1 = Black_Is_Legal(position, m1);
        			Move m2(BK, NONE, GeneralBoard[i], 1152921504606846976, false, false);
        			bool safetomovetoe1 = Search::Is_Mate(position) <= 0 ? true : false;
        			bool Rookonh1 = (position->Black_Rooks & 9223372036854775808);
        			int notincheck = Search::Is_Mate(position);
        			if(first && (!second) && safetomovetof1 && safetomovetog1 && safetomovetoe1 && (position->BlackCanCastleK) && Rookonh1 && (notincheck != 10000))
        			{
        				m1.Castling = true;
        				position->LegalMoves[position->numlegalmoves++] = m1;
		        	}
		    	}
	    	}
	    }
	}
return;	
}
