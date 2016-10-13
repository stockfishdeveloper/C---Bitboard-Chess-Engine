	#include "Position.h"
	Position pos;
	
	Move::Move()
	{
		P = NONE;
		C = NONE;
		From = 0;
		To = 0;
		Score = 0;
		Castling = false;
		Promotion = false;
		PromotionType = NONE;
	}
	Move::Move(Piece piece, Piece captured, Bitboard from, Bitboard to, bool castling, bool promotion)
	{
		P = piece;
		C = captured;
		From = from;
		To = to;
		Castling = castling;
		Promotion = promotion;
		PromotionType = NONE;
		Score = 0;
	}
	Position::Position()
	{
		White_Pieces = 0;
		Black_Pieces = 0;
		White_King = 0;
		Black_King = 0;
		White_Queens = 0;
		White_Rooks = 0;
		White_Bishops = 0;
		White_Knights = 0;
		White_Pawns = 0;
		Black_Queens = 0;
		Black_Rooks = 0;
		Black_Bishops = 0;
		Black_Knights = 0;
		Black_Pawns = 0;
		numlegalmoves = 0;
		WhiteCanCastleK = false;
		WhiteCanCastleQ = false;
		BlackCanCastleK = false;
		BlackCanCastleQ = false;
		Current_Turn = true;
		hashkey = 0;
		numlegalmoves = 0;
	}
	Position::Position(Position* position)
	{
		Current_Turn = position->Current_Turn;
		White_Pieces = position->White_Pieces;
		Black_Pieces = position->Black_Pieces;
		White_King = position->White_King;
		Black_King = position->Black_King;
		White_Queens = position->White_Queens;
		White_Rooks = position->White_Rooks;
		White_Bishops = position->White_Bishops;
		White_Knights = position->White_Knights;
		White_Pawns = position->White_Pawns;
		Black_Queens = position->Black_Queens;
		Black_Rooks = position->Black_Rooks;
		Black_Bishops = position->Black_Bishops;
		Black_Knights = position->Black_Knights;
		Black_Pawns = position->Black_Pawns;
		WhiteCanCastleK = position->WhiteCanCastleK;
		WhiteCanCastleQ = position->WhiteCanCastleQ;
		BlackCanCastleK = position->BlackCanCastleK;
		BlackCanCastleQ = position->BlackCanCastleQ;
		hashkey = position->hashkey;
		numlegalmoves = 0;
	}
	void Position::Reset()
	{
		White_Pieces = 65535;
        Black_Pieces = 18446462598732840960ULL;
        White_King = 16;
        Black_King = 1152921504606846976;
        White_Queens = 8;
        White_Rooks = 129;
        White_Bishops = 36;
        White_Knights = 66;
        White_Pawns = 65280;
        Black_Queens = 576460752303423488;
        Black_Rooks = 9295429630892703744ULL;
        Black_Bishops = 2594073385365405696;
        Black_Knights = 4755801206503243776;
        Black_Pawns = 71776119061217280;
        WhiteCanCastleK = true;
		WhiteCanCastleQ = true;
		BlackCanCastleK = true;
		BlackCanCastleQ = true;
        Current_Turn = true;
        numlegalmoves = 0;
        hashkey = 18446462598732906494;
	}
	Bitboard* Position::Get_Bitboard_From_Piece(Piece p)
	{
		switch(p)
		{
			case WP:
				return &White_Pawns;
				break;
			case WN:
				return &White_Knights;
				break;	
			case WB:
				return &White_Bishops;
				break;
			case WR:
				return &White_Rooks;
				break;
			case WQ:
				return &White_Queens;
				break;
			case WK:
				return &White_King;
				break;
			case BP:
				return &Black_Pawns;
				break;
			case BN:
				return &Black_Knights;
				break;
			case BB:
				return &Black_Bishops;
				break;
			case BR:
				return &Black_Rooks;
				break;
			case BQ:
				return &Black_Queens;
				break;
			case BK:
				return &Black_King;
				break;
			default:
				return NULL;										
		}
	}
	Piece Position::Get_Piece_From_Bitboard(Bitboard b)
	{
		if(b & White_Pawns)
			return WP;
		if(b & White_Knights)
			return WN;
		if(b & White_Bishops)
			return WB;
		if(b & White_Rooks)
			return WR;
		if(b & White_Queens)
			return WQ;
		if(b & White_King)
			return WK;
		if(b & Black_Pawns)
			return BP;
		if(b & Black_Knights)
			return BN;
		if(b & Black_Bishops)
			return BB;
		if(b & Black_Rooks)
			return BR;
		if(b & Black_Queens)
			return BQ;
		if(b & Black_King)
			return BK;
		return NONE;
	}
	void Position::Make_Move(Move m)
	{
		if(m.Castling)
		{
			if(m.To & 64)
			{
				White_Rooks |= 32;
				White_Rooks ^= 128;
				White_King |= 64;
				White_King ^= 16;
				White_Pieces ^= 144;
				White_Pieces |= 96;
			}
			else if(m.To & 4611686018427387904)
			{
				Black_Rooks |= 2305843009213693952;
				Black_Rooks ^= 9223372036854775808;
				Black_King |= 4611686018427387904;
				Black_King ^= 1152921504606846976;
				Black_Pieces ^= 10376293541461622784;
				Black_Pieces |= 6917529027641081856;
			}
			else if(m.To & 4)
			{
				White_Rooks |= 8;
				White_Rooks ^= 1;
				White_King |= 4;
				White_King ^= 16;
				White_Pieces ^= 17;
				White_Pieces |= 12;
			}
			else if(m.To & 288230376151711744)
			{
				Black_Rooks |= 576460752303423488;
				Black_Rooks ^= 72057594037927936;
				Black_King |= 288230376151711744;
				Black_King ^= 1152921504606846976;
				Black_Pieces ^= 1224979098644774912;
				Black_Pieces |= 864691128455135232;
			}
			Current_Turn ^= 1;
			return;
		}
		Bitboard* bb = Get_Bitboard_From_Piece(m.P);
		*bb ^= m.From;
		*bb |= m.To;
		if(m.P > WK)
		{
			Black_Pieces |= m.To;
			Black_Pieces ^= m.From;
		}
		else
		{
			White_Pieces |= m.To;
			White_Pieces ^= m.From;
		}
		if(m.C != NONE)
		{
			bb = Get_Bitboard_From_Piece(m.C);
			*bb ^= m.To;
			if(m.C > WK)
				Black_Pieces ^= m.To;
			else
				White_Pieces ^= m.To;
		}
		if(m.Promotion)
		{
			bb = Get_Bitboard_From_Piece(m.PromotionType);
			*bb |= m.To;
			bb = Get_Bitboard_From_Piece(m.P);
			*bb ^= m.To;
		}
		Current_Turn ^= 1;
	}
	void Position::Undo_Move(Move m)
	{
		if(m.Castling)
		{
			if(m.To & 64)
			{
				White_Rooks ^= 32;
				White_Rooks |= 128;
				White_King ^= 64;
				White_King |= 16;
				White_Pieces |= 144;
				White_Pieces ^= 96;
			}
			else if(m.To & 4611686018427387904)
			{
				Black_Rooks ^= 2305843009213693952;
				Black_Rooks |= 9223372036854775808;
				Black_King ^= 4611686018427387904;
				Black_King |= 1152921504606846976;
				Black_Pieces |= 10376293541461622784;
				Black_Pieces ^= 6917529027641081856;
			}
			else if(m.To & 4)
			{
				White_Rooks ^= 8;
				White_Rooks |= 1;
				White_King ^= 4;
				White_King |= 16;
				White_Pieces |= 17;
				White_Pieces ^= 12;
			}
			else if(m.To & 288230376151711744)
			{
				Black_Rooks ^= 576460752303423488;
				Black_Rooks |= 72057594037927936;
				Black_King ^= 288230376151711744;
				Black_King |= 1152921504606846976;
				Black_Pieces |= 1224979098644774912;
				Black_Pieces ^= 864691128455135232;
			}
			Current_Turn ^= 1;
			return;
		}
		Bitboard* bb = Get_Bitboard_From_Piece(m.P);
		*bb |= m.From;
		*bb ^= m.To;
		if(m.P > WK)
		{
			Black_Pieces ^= m.To;
			Black_Pieces |= m.From;
		}
		else
		{
			White_Pieces ^= m.To;
			White_Pieces |= m.From;
		}
		if(m.C != NONE)
		{
			bb = Get_Bitboard_From_Piece(m.C);
			*bb |= m.To;
			if(m.C > WK)
				Black_Pieces |= m.To;
			else
				White_Pieces |= m.To;
		}
		if(m.Promotion)
		{
			bb = Get_Bitboard_From_Piece(m.PromotionType);
			*bb ^= m.To;
			bb = Get_Bitboard_From_Piece(m.P);
			*bb ^= m.To;
		}
		Current_Turn ^= 1;
	}
