#ifndef Position_H_
#define Position_H_
#include "Bitboard.h"

enum Piece { WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK, NONE };

class Move
{
	public:
	Piece P;
	Piece C;
	Bitboard From;
	Bitboard To;
	int Score;
	bool Castling;
	bool Promotion;
	Piece PromotionType;
	Move();
	Move(Piece piece, Piece captured, Bitboard from, Bitboard to, bool castling, bool promotion);
};
class Position
{
	public:
	Bitboard White_Pieces;
	Bitboard Black_Pieces;
	Bitboard White_King;
	Bitboard Black_King;
	Bitboard White_Queens;
	Bitboard White_Rooks;
	Bitboard White_Bishops;
	Bitboard White_Knights;
	Bitboard White_Pawns;
	Bitboard Black_Queens;
	Bitboard Black_Rooks;
	Bitboard Black_Bishops;
	Bitboard Black_Knights;
	Bitboard Black_Pawns;
	bool WhiteCanCastleK;
	bool WhiteCanCastleQ;
	bool BlackCanCastleK;
	bool BlackCanCastleQ;
	bool Current_Turn;
	Bitboard hashkey;
	int numlegalmoves;
	Bitboard WhiteAttacks;
	Bitboard BlackAttacks;
	Move LegalMoves[100];
	Position();
	Position(Position* position);
	void Reset();
	void Make_Move(Move m);
	void Undo_Move(Move m);
	void Update_White_Attacks();
	void Update_Black_Attacks();
	Bitboard* Get_Bitboard_From_Piece(Piece p);
	Piece Get_Piece_From_Bitboard(Bitboard b);
};
int Get_Cp_Value(Piece piece);
extern Position pos;
#endif
