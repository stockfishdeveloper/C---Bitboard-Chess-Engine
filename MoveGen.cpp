using namespace std;
#include "Bitboard.h"
#include "MoveGen.h"
#include "Search.h"
#include "magicmoves.h"

#include "Experimental_Move_Generation.h"
Bitboard White_Move_From_Stack[100];//Move stack is just an array of Bitboards(64-bit integers) containing only one bit set in each--the from square or the to square
Bitboard White_Move_To_Stack[100];
Bitboard Black_Move_From_Stack[100];
Bitboard Black_Move_To_Stack[100];
int White_Move_Types[100];//Array of normal integers that keeps track of the type of each move
int Black_Move_Types[100];
int White_Move_Spacer = 0; // Keeps a "record" of the last move put on the stack so that it knows which index of the array to put the next move in
int Black_Move_Spacer = 0;
bool Is_Legal;
bool WhiteCanCastleK = true;
bool WhiteCanCastleQ = true;
bool BlackCanCastleK = true;
bool BlackCanCastleQ = true;

void Generate_White_Moves(const bool caps)
{
	Search::Clear();
    for(int i = 0; i < 64; i++)
	{
		if(White_Pawns & GeneralBoard[i])
		{
			if(!caps)
			{
				if(GeneralBoard[i] & 65280)
				{
					if(!((GeneralBoard[i] << 8) & (White_Pieces | Black_Pieces)))
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[i] << 8, 2))
							{
								White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
								White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[i] << 8;
								White_Move_Types[White_Move_Spacer++] = (GeneralBoard[i] & 71776119061217280 ? 14 : 2);
							}
						if(!((GeneralBoard[i] << 16) & (White_Pieces | Black_Pieces)))
						{
							if(White_Is_Legal(GeneralBoard[i], GeneralBoard[i] << 16, 2))
							{
								White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
								White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[i] << 16;
								White_Move_Types[White_Move_Spacer++] = 2;
							}
						}					
					}
				}
				else
				{
					if(!((GeneralBoard[i] << 8) & (White_Pieces | Black_Pieces)))
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[i] << 8, 2))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[i] << 8;
							White_Move_Types[White_Move_Spacer++] = (GeneralBoard[i] & 71776119061217280 ? 14 : 2);
						}
					}
				}
			}
			if(!(GeneralBoard[i] & A_Pawn_Mask))
			{
				if((GeneralBoard[i] << 7) & Black_Pieces)
				{
					if(White_Is_Legal(GeneralBoard[i], GeneralBoard[i] << 7, 1))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[i] << 7;
							White_Move_Types[White_Move_Spacer++] = (GeneralBoard[i] & 71776119061217280 ? 13 : 1);
						}
				}
			}
			if(!(GeneralBoard[i] & H_Pawn_Mask))
			{
				if((GeneralBoard[i] << 9) & Black_Pieces)
				{
					if(White_Is_Legal(GeneralBoard[i], GeneralBoard[i] << 9, 1))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[i] << 9;
							White_Move_Types[White_Move_Spacer++] = (GeneralBoard[i] & 71776119061217280 ? 13 : 1);
						}
				}
			}
		}
		if(GeneralBoard[i] & White_Knights)
		{
			Bitboard k = Knight_Lookup_Table[i];
			k |= White_Pieces;
			Bitboard b = k ^ White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & Black_Pieces)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 3))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
							White_Move_Types[White_Move_Spacer++] = 3;
						}
					}
				else
				{
					if(!caps)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 4))
							{
								White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
								White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
								White_Move_Types[White_Move_Spacer++] = 4;
							}
					}
				}	
									
			}
		}
		if(GeneralBoard[i] & White_Bishops)
		{
			Bitboard bi = Bmagic(i, White_Pieces | Black_Pieces);
			bi |= White_Pieces;
			Bitboard b = bi ^ White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & Black_Pieces)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 5))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
							White_Move_Types[White_Move_Spacer++] = 5;
						}
					}
				else
				{
					if(!caps)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 6))
							{
								White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
								White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
								White_Move_Types[White_Move_Spacer++] = 6;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & White_Rooks)
		{
			Bitboard r = Rmagic(i, White_Pieces | Black_Pieces);
			r |= White_Pieces;
			Bitboard b = r ^ White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & Black_Pieces)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 7))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
							White_Move_Types[White_Move_Spacer++] = 7;
						}
					}
				else
				{
					if(!caps)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 8))
							{
								White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
								White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
								White_Move_Types[White_Move_Spacer++] = 8;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & White_Queens)
		{
			Bitboard q = Rmagic(i, White_Pieces | Black_Pieces);
			Bitboard qu = (Bmagic(i, White_Pieces | Black_Pieces) | q);
			qu |= White_Pieces;
			Bitboard b = qu ^ White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & Black_Pieces)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 9))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
							White_Move_Types[White_Move_Spacer++] = 9;
						}
					}
				else
				{
					if(!caps)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 10))
							{
								White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
								White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
								White_Move_Types[White_Move_Spacer++] = 10;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & White_King)
		{
			Bitboard k = King_Lookup_Table[i];
			k |= White_Pieces;
			Bitboard b = k ^ White_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & Black_Pieces)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 11))
						{
							White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
							White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
							White_Move_Types[White_Move_Spacer++] = 11;
						}
					}
				else
				{
					if(!caps)
					{
						if(White_Is_Legal(GeneralBoard[i], GeneralBoard[j], 12))
							{
								White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
								White_Move_To_Stack[White_Move_Spacer] = GeneralBoard[j];
								White_Move_Types[White_Move_Spacer++] = 12;
							}
					}
				}	
									
			}
			if(!caps)
			{
				Bitboard first = (GeneralBoard[i] & 16);
        		Bitboard second = ((White_Pieces | Black_Pieces) & 96);
        		Bitboard e1 = 16, f1 = 32, g1 = 64, a0 = 0;
        		bool canmovetof1 = White_Is_Legal(e1, f1, 12);
        		bool canmovetog1 = White_Is_Legal(e1, g1, 12);
        		bool canmovetoe1 = White_Is_Legal(a0, e1, 12);
        		bool Rookonh1 = (White_Rooks & 128);
        		int notincheck = Search::Is_Mate();
        		if(first && (!second) && canmovetof1 && canmovetog1 && canmovetoe1 && (WhiteCanCastleK) && Rookonh1 && (notincheck != -10000))
        		{
		            White_Move_From_Stack[White_Move_Spacer] = GeneralBoard[i];
		            Bitboard too = 64;
		            White_Move_To_Stack[White_Move_Spacer++] = too;
		            White_Move_Types[White_Move_Spacer - 1] = 15;
		        }
	    	}
		}
	}
return;	
}

void Generate_Black_Moves(const bool caps)
{
	Search::Clear();
    for(int i = 0; i < 64; i++)
	{
		if(Black_Pawns & GeneralBoard[i])
		{
			if(!caps)
			{
				if(GeneralBoard[i] & 71776119061217280)
				{
					if(!((GeneralBoard[i] >> 8) & (White_Pieces | Black_Pieces)))
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[i] >> 8, 2))
							{
								Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
								Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[i] >> 8;
								Black_Move_Types[Black_Move_Spacer++] = (GeneralBoard[i] & 65280 ? 14 : 2);
							}
						if(!((GeneralBoard[i] >> 16) & (White_Pieces | Black_Pieces)))
						{
							if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[i] >> 16, 2))
							{
								Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
								Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[i] >> 16;
								Black_Move_Types[Black_Move_Spacer++] = 2;
							}
						}	
					}
				}
				else
				{
					if(!((GeneralBoard[i] >> 8) & (White_Pieces | Black_Pieces)))
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[i] >> 8, 2))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[i] >> 8;
							Black_Move_Types[Black_Move_Spacer++] = (GeneralBoard[i] & 65280 ? 14 : 2);
						}
					}
				}
			}
			if(!(GeneralBoard[i] & H_Pawn_Mask))
			{
				if((GeneralBoard[i] >> 7) & White_Pieces)
				{
					if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[i] >> 7, 1))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[i] >> 7;
							Black_Move_Types[Black_Move_Spacer++] = (GeneralBoard[i] & 65280 ? 13 : 1);
						}
				}
			}
			if(!(GeneralBoard[i] & A_Pawn_Mask))
			{
				if((GeneralBoard[i] >> 9) & White_Pieces)
				{
					if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[i] >> 9, 1))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[i] >> 9;
							Black_Move_Types[Black_Move_Spacer++] = (GeneralBoard[i] & 65280 ? 13 : 1);
						}
				}
			}
		}
		if(GeneralBoard[i] & Black_Knights)
		{
			Bitboard k = Knight_Lookup_Table[i];
			k |= Black_Pieces;
			Bitboard b = k ^ Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & White_Pieces)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 3))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
							Black_Move_Types[Black_Move_Spacer++] = 3;
						}
					}
				else
				{
					if(!caps)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 4))
							{
								Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
								Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
								Black_Move_Types[Black_Move_Spacer++] = 4;
							}
					}
				}	
									
			}
		}
		if(GeneralBoard[i] & Black_Bishops)
		{
			Bitboard bi = Bmagic(i, White_Pieces | Black_Pieces);
			bi |= Black_Pieces;
			Bitboard b = bi ^ Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & White_Pieces)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 5))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
							Black_Move_Types[Black_Move_Spacer++] = 5;
						}
					}
				else
				{
					if(!caps)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 6))
							{
								Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
								Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
								Black_Move_Types[Black_Move_Spacer++] = 6;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & Black_Rooks)
		{
			Bitboard r = Rmagic(i, White_Pieces | Black_Pieces);
			r |= Black_Pieces;
			Bitboard b = r ^ Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & White_Pieces)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 7))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
							Black_Move_Types[Black_Move_Spacer++] = 7;
						}
					}
				else
				{
					if(!caps)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 8))
							{
								Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
								Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
								Black_Move_Types[Black_Move_Spacer++] = 8;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & Black_Queens)
		{
			Bitboard q = Rmagic(i, White_Pieces | Black_Pieces);
			Bitboard qu = (Bmagic(i, White_Pieces | Black_Pieces) | q);
			qu |= Black_Pieces;
			Bitboard b = qu ^ Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & White_Pieces)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 9))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
							Black_Move_Types[Black_Move_Spacer++] = 9;
						}
					}
				else
				{
					if(!caps)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 10))
							{
								Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
								Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
								Black_Move_Types[Black_Move_Spacer++] = 10;
							}
					}
				}	
			}
		}
		if(GeneralBoard[i] & Black_King)
		{
			Bitboard k = King_Lookup_Table[i];
			k |= Black_Pieces;
			Bitboard b = k ^ Black_Pieces;
			int p = __builtin_popcountll(b);
			for(int m = 0; m < p; m++)
			{
				int j = lsb(b);
				b ^= GeneralBoard[j];
				if(GeneralBoard[j] & White_Pieces)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 11))
						{
							Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
							Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
							Black_Move_Types[Black_Move_Spacer++] = 11;
						}
					}
				else
				{
					if(!caps)
					{
						if(Black_Is_Legal(GeneralBoard[i], GeneralBoard[j], 12))
							{
								Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
								Black_Move_To_Stack[Black_Move_Spacer] = GeneralBoard[j];
								Black_Move_Types[Black_Move_Spacer++] = 12;
							}
					}
				}	
									
			}
			if(!caps)
			{
				Bitboard first = (GeneralBoard[i] & 1152921504606846976);
        		Bitboard second = ((White_Pieces | Black_Pieces) & 6917529027641081856);
        		Bitboard e8 = 1152921504606846976, f8 = 2305843009213693952, g8 = 4611686018427387904, a0 = 0;
        		bool canmovetof1 = Black_Is_Legal(e8, f8, 12);
        		bool canmovetog1 = Black_Is_Legal(e8, g8, 12);
        		bool canmovetoe1 = Black_Is_Legal(a0, e8, 12);
        		bool Rookonh1 = (Black_Rooks & 9223372036854775808ULL);
        		int notincheck = Search::Is_Mate();
        		if(first && (!second) && canmovetof1 && canmovetog1 && canmovetoe1 && (BlackCanCastleK) && Rookonh1 && (notincheck != 10000))
        		{
		            Black_Move_From_Stack[Black_Move_Spacer] = GeneralBoard[i];
		            Bitboard too = 4611686018427387904;
		            Black_Move_To_Stack[Black_Move_Spacer++] = too;
		            Black_Move_Types[Black_Move_Spacer - 1] = 15;
		        }
	    	}
		}
	}
return;	
}
