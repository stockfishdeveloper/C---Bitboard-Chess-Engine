using namespace std;
#include <vector>
#include <algorithm>
#include "Bitboard.h"
#include "Search.h"
#include "Eval.h"
#include "UCI.h"
#include "magicmoves.h"
#include "Endgame.h"
#include "Zobrist.h"
#include "TransTable.h"
#include "Thread.h"

int Search::Time_Allocation = 0;
bool Search::Searching = false;
Bitboard Search::Nodes = 0;
int Search::Depth = 0;
int Search::Seldepth = 0;
bool Search::STOP_SEARCHING_NOW = false;
bool Search::Current_Turn = false;
Move m;

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
    for(int h = 0; h < White_Temp_Move_Spacer; h++)
    {
        White_Move_From_Stack[h] = Unconvert_Int(White_Temp_Move_From_Stack[h]);
        White_Move_To_Stack[h] = Unconvert_Int(White_Temp_Move_To_Stack[h]);
        White_Move_Types[h] = White_Temp_Move_Types[h];
    }
	Black_Move_Spacer = Black_Temp_Move_Spacer;
    for(int h = 0; h < Black_Temp_Move_Spacer; h++)
    {
        Black_Move_From_Stack[h] = Unconvert_Int(Black_Temp_Move_From_Stack[h]);
        Black_Move_To_Stack[h] = Unconvert_Int(Black_Temp_Move_To_Stack[h]);
        Black_Move_Types[h] = Black_Temp_Move_Types[h];
    }
	Search::Current_Turn ^= 1;
}

Move Search::Think(int wtime, int btime, int winc, int binc)
{
    Move Best;
    Timer timer;
    timer.Start_Clock();
    int Wtime = wtime;
    int Btime = btime;
    int Winc = winc;
    int Binc = binc;
    Move move;
    int rootAlpha = -100000;
    int rootBeta = 100000;
    const int MAXDEPTH = 60;
    int Plies_Searched = 0;
    LINE line;
    vector<Move>rootstack;
    int count = 0;
    int matemoves = 1000;
    for(int q = 1; q < MAXDEPTH; q++)
    {
    	Search::Depth = q;
    	output.lock();
		cout << "info depth " << Search::Depth << endl;
		output.unlock();
		Time_Allocation = (Current_Turn ? wtime : btime);
        if(q == 1) (Current_Turn ? Generate_White_Moves(false) : Generate_Black_Moves(false));
        Move wh;
        move = wh;
        Current_Turn ? (wh.White_Temp_Move_Spacer = White_Move_Spacer) : (wh.Black_Temp_Move_Spacer = Black_Move_Spacer);
        if(q == 1)
            {
            	for(int h = 0; h < (Current_Turn ? White_Move_Spacer : Black_Move_Spacer); h++)
                	{
                    	move.From = Current_Turn ? White_Move_From_Stack[h] : Black_Move_From_Stack[h];
                    	move.To = Current_Turn ? White_Move_To_Stack[h] : Black_Move_To_Stack[h];
                    	move.Move_Type = Current_Turn ? White_Move_Types[h] : Black_Move_Types[h];
                    	move.Score = -AlphaBeta(-rootBeta, -rootAlpha, (2), &line, false);
                    	rootstack.push_back(move);
                    	count++;
                	}
            }
        for(int i = 0; i < count; i++)
			{
				if((rootstack[i].From == Best.From) && (rootstack[i].To == Best.To))
					rootstack[i].Score += 1000;
				if((rootstack[i].Move_Type % 2) > 0)
					rootstack[i].Score += 20;
				if((rootstack[i].Move_Type == 13) || (rootstack[i].Move_Type == 14))
					rootstack[i].Score += 40;
				if(Get_Move_Score(rootstack[i], Current_Turn) > 0)
				{
					rootstack[i].Score += 50;
				}
			}
        std::sort(rootstack.begin(), rootstack.end(), [](const Move& lhs, const Move& rhs){ return (lhs.Score > rhs.Score);});
        for(int i = 0; i < (Current_Turn ? White_Move_Spacer : Black_Move_Spacer); i++)
            {
            	Nodes++;
                move.From = rootstack[i].From;
                move.To = rootstack[i].To;
                move.Move_Type = rootstack[i].Move_Type;
                if((Current_Turn ? White_Move_Spacer : Black_Move_Spacer) == 1)
                {
                    Best = move;
                    return Best;
                }
                if(q >= 2 && timer.Get_Time() > 1000)
                {
                    output.lock();
                    cout << "info currmove " << PlayerMoves[(move.Convert_Bitboard(move.From))] << PlayerMoves[(move.Convert_Bitboard(move.To))];
                    Log << "<< info currmove " << PlayerMoves[(move.Convert_Bitboard(move.From))] << PlayerMoves[(move.Convert_Bitboard(move.To))];
                    cout << " currmovenumber " << (i + 1) << endl;
                    Log << " currmovenumber " << (i + 1) << endl;
                    output.unlock();
                }
                Current_Turn ? Make_White_Search_Move(move.From, move.To, move.Move_Type) : Make_Black_Search_Move(move.From, move.To, move.Move_Type);
                int score = -AlphaBeta(-rootBeta, -rootAlpha, (q - 1), &line, true);
                (rootstack[i]).Score = score;
                //cout << " " << score << endl;
                move.Undo_Move();
                if((score >= rootBeta) && (rootBeta < 100000))
                {
                	cout << "score was " << score << " rootBeta was " << rootBeta << endl;
                	while(true)
                	{
                		rootBeta += 50;
                		Current_Turn ? Make_White_Search_Move(move.From, move.To, move.Move_Type) : Make_Black_Search_Move(move.From, move.To, move.Move_Type);
                		int rscore = AlphaBeta(rootAlpha, rootBeta, (q - 1), &line, true);
                		(rootstack[i]).Score = rscore;
                		move.Undo_Move();
                		//cout << rootBeta << " " << score << endl;
                		if(rscore >= rootBeta)
                			continue;
                		break;
                	}
                	cout << "successfully researched" << endl;
                }
                if(score > rootAlpha)
                {
                	LINE* f = new LINE;
                    f->cmove = 0;
                    ::PVline = *f;
                    delete f;
                    ::PVline.argmove[0] = move;
                    ::PVline.score = score;
                    ::PVline.cmove = line.cmove + 1;
                    memcpy(::PVline.argmove + 1, line.argmove, line.cmove * sizeof(Move));
                    Best = move;
                    Best.Score = score;
                    rootAlpha = score;
                }
                if(timer.Get_Time() >= (Search::Time_Allocation / 30))
        			{
            			Search::STOP_SEARCHING_NOW = true;
            			return Best;
        			}
            }
		output.lock();
		cout << "info multipv 1 depth " << q << " seldepth " << q + Search::Seldepth << " score ";
        Log << "<< info multipv 1 depth " << q << " seldepth " << q + Search::Seldepth << " score ";
        if(Best.Score == 10000)
        {
        	if(q + 1 < matemoves)
                {
                	cout << "mate " << ((q + 1) / 2) - 1;
                    Log << "mate " << ((q + 1) / 2) - 1;
                    matemoves = q + 1;
                }
            else
                {
                    cout << "mate " << (matemoves / 2) - 1;
                    Log << "mate " << (matemoves / 2) - 1;
                }
        }
        else if(Best.Score == -10000)
        {
        	if(q + 1 < matemoves)
                {
                	cout << "mate " << -(((q + 1) / 2) - 1);
                    Log << "mate " << -(((q + 1) / 2) - 1);
                    matemoves = q + 1;
                }
            else
                {
                    cout << "mate " << -((matemoves / 2) - 1);
                    Log << "mate " << -((matemoves / 2) - 1);
                }
    	}
        else
        {
        cout << "cp " << Best.Score;
        Log << "cp " << Best.Score;
    	}
    	cout << " hashfull " << int((TT.count / 33554432.0) * 1000);
        cout << " pv " << ::PVline.Output() /*<< line.Output()*/;
        Log << " pv " << ::PVline.Output() /*<< line.Output()*/;
        cout << "time " << timer.Get_Time() << " nodes " << Search::Nodes << " nps " << (1000 *(Search::Nodes / (timer.Get_Time() + 1))) << endl;
        Log << "time " << timer.Get_Time() << " nodes " << Search::Nodes << " nps " << (1000 *(Search::Nodes / (timer.Get_Time() + 1))) << endl;
		output.unlock();
        LINE* f = new LINE;
        f->cmove = 0;
        //::PVline = *f;
        line = *f;
        delete f;

        if(STOP_SEARCHING_NOW)
        {
            Time_Allocation = 0;
            return Best;
        }
        //rootAlpha = rootAlpha - 50;
        //rootBeta = rootBeta + 50;
        rootAlpha = -100000;
    	rootBeta = 100000;
    }

    return Best;
}

int Search::AlphaBeta(int alpha, int beta, int depth, LINE * pline, bool donullmove)
{
    if(depth <= 1)
    {
        ++Nodes;
        pline->cmove = 0;
        return QuiescenceSearch(alpha, beta, depth + 1);
    }
    LINE line;

    /*NULLMOVE PRUNING*******************************************************
    *************************************************************************
    *************************************************************************/
    if(((Search::Is_Mate() != -10000) || (Search::Is_Mate() != 10000)) && (donullmove) && (depth > 3))
    {
        Search::Current_Turn ^= 1;
        int score = -AlphaBeta(-beta, -beta + 1, depth - 3, &line, false);
        if(score >= beta)
            {
                Search::Current_Turn ^= 1;
                return beta;
            }
		Search::Current_Turn ^= 1;
    }
    /************************************************************************
    *************************************************************************
    *************************************************************************/
    Current_Turn ? Generate_White_Moves(false) : Generate_Black_Moves(false);
    Move move;
    NodeType node = Alpha;
    if((Current_Turn ? White_Move_Spacer : Black_Move_Spacer) == 0)
    {
        alpha = Is_Mate();
        pline->score = alpha;
        pline->cmove = 0;
        return alpha;
	}
	TTEntry* tt = TT.probe(Get_Current_Hash_Key());
	if(tt!= NULL)
	{
		//if(tt->visited >= 2) return 0;
		if(tt->nodetype == Alpha) if(tt->score <= alpha) return alpha;
		if(tt->nodetype == Beta) if(tt->score >= beta) return beta;
		if(tt->nodetype == Exact) 
		{
			if(tt->depth > depth)
			{
				return tt->score;
			}
		}
	}
	for(int i = 0; i < (Current_Turn ? White_Move_Spacer : Black_Move_Spacer); i++)
    {
        Nodes++;
        move.From = Current_Turn ? White_Move_From_Stack[i] : Black_Move_From_Stack[i];
        move.To = Current_Turn ? White_Move_To_Stack[i] : Black_Move_To_Stack[i];
        move.Move_Type = Current_Turn ? White_Move_Types[i] : Black_Move_Types[i];
        Current_Turn ? Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]) : Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
        int score = -AlphaBeta(-beta, -alpha, depth - 1, &line, true);
        move.Undo_Move();
        if(score >= beta)
        {
        	return beta;
        }
        if(score > alpha)
        {
        	pline->argmove[0] = move;
            pline->score = score;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
            pline->cmove = line.cmove + 1;
            alpha = score;
            node = Exact;
		}
    }
    TT.save(depth, pline->score, pline->argmove[0], node, Get_Current_Hash_Key());
    return alpha;
}

Search::Make_White_Search_Move(const Bitboard& From, const Bitboard& To, const int Move_Type)
{
	switch(Move_Type)//This switch evaluates the type of move that accompanies the index of the move stack that q refers to
    {

    case 1://A (white) pawn capture
    {
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
	}

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

    case 15://Kigside castling
        White_Pieces |= To;
        White_Pieces ^= From;
        White_Rooks |= 32;
        White_Rooks ^= 128;
        White_King |= 64;
        White_King ^= 16;
        break;


    }

    //Tidy up for the next call of the move generation functions
    for(int t = 0; t < White_Move_Spacer; t++)
    {
        White_Move_From_Stack[t] = 0;//Clear the move from stack
        White_Move_To_Stack[t] = 0;//Clear the move to stack
        White_Move_Types[t] = 0;//Clear the move types associated with the moves
    }
    White_Move_Spacer = 0;
	Search::Current_Turn = false;
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

    case 15://Kigside castling
        Black_Pieces |= To;
        Black_Pieces ^= From;
        Black_Rooks |= 2305843009213693952;
        Black_Rooks ^= 9223372036854775808ULL;
        Black_King |= 4611686018427387904;
        Black_King ^= 1152921504606846976;
        break;
    }

    //Tidy up for the next call of the move generation functions
    for(int t = 0; t < Black_Move_Spacer; t++)
    {
        Black_Move_From_Stack[t] = 0;//Clear the move from stack
        Black_Move_To_Stack[t] = 0;//Clear the move to stack
        Black_Move_Types[t] = 0;//Clear the move types associated with the moves
    }
    Black_Move_Spacer = 0;

    Search::Current_Turn  = true;
    return 0;

}

Search::Is_Mate()
{
	int score = 0;
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
            score = -1;
        if(RAttacks & (Black_Rooks))
            score = -1;
        if(QAttacks & (Black_Queens))
            score = -1;
        if(Knight_Lookup_Table[h] & Black_Knights)
            score = -1;
        if(King_Lookup_Table[h] & Black_King)
            score = -1;
        Bitboard Spare = Black_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare >> 7) & White_King)
            score = -1;
        Bitboard Spare2 = Black_Pawns;
        Spare2 |= H_Pawn_Mask;
        Spare2 ^= H_Pawn_Mask;
        if((Spare2 >> 9) & White_King)
            score = -1;
        Bitboard Black_Pawns5 = Black_Pawns;
        Black_Pawns5 |= A_Pawn_Mask;
        Black_Pawns5 ^= A_Pawn_Mask;
        Black_Pawns5 |= H_Pawn_Mask;
        Black_Pawns5 ^= H_Pawn_Mask;
        if(((Black_Pawns5 >> 7) | (Black_Pawns5 >> 9)) & White_King)
            score = -1;
    	if(score != 0)
    	{
    		if(score < 0)
    		{
    			if(Current_Turn)
    				return -10000;
    			else
    				return 10000;
			}
			if(score > 0)
    		{
    			if(Current_Turn)
    				return 10000;
    			else
    				return -10000;
			}
		}
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
            score = 1;
        if(RAttacks & (White_Rooks))
            score = 1;
        if(QAttacks & (White_Queens))
            score = 1;
        if(Knight_Lookup_Table[h] & White_Knights)
            score = 1;
        if(King_Lookup_Table[h] & White_King)
            score = 1;
        Spare = White_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare << 9) & Black_King)
            score = 1;
        Bitboard Spare7 = White_Pawns;
        Spare7 |= H_Pawn_Mask;
        Spare7 ^= H_Pawn_Mask;
        if((Spare7 << 7) & Black_King)
            score = 1;
        Bitboard White_Pawns2 = 0;
        White_Pawns2 |= A_Pawn_Mask;
        White_Pawns2 ^= A_Pawn_Mask;
        White_Pawns2 |= H_Pawn_Mask;
        White_Pawns2 ^= H_Pawn_Mask;
        if(((White_Pawns << 7) | (White_Pawns << 9)) & GeneralBoard[h])
            score = 1;
        if(score != 0)
    	{
    		if(score < 0)
    		{
    			if(Current_Turn)
    				return -10000;
    			else
    				return 10000;
			}
			if(score > 0)
    		{
    			if(Current_Turn)
    				return 10000;
    			else
    				return -10000;
			}
		}
    return 0;
}

void Search::Clear()
{
    for(int t = 0; t < 100; t++)
    {
        White_Move_From_Stack[t] = 0;//Clear the move from stack
        White_Move_To_Stack[t] = 0;//Clear the move to stack
        White_Move_Types[t] = 0;//Clear the move types associated with the moves
    }
	Search::Depth = 0;
    for(int t = 0; t < 100; t++)
    {
        Black_Move_From_Stack[t] = 0;//Clear the move from stack
        Black_Move_To_Stack[t] = 0;//Clear the move to stack
        Black_Move_Types[t] = 0;//Clear the move types associated with the moves
    }

    White_Move_Spacer = 0;
    Black_Move_Spacer = 0;

}

int Search::QuiescenceSearch(int alpha, int beta, int depth)
{
	int stand_pat = Current_Turn ? Eval::Evaluate_Position() : -Eval::Evaluate_Position();
	Search::Seldepth = (depth > Search::Seldepth ? depth : Search::Seldepth);
	Nodes++;
    if(stand_pat >= beta)
        return beta;
    if(stand_pat > alpha)
        alpha = stand_pat;
	Current_Turn ? Generate_White_Moves(true) : Generate_Black_Moves(true);
	if((Current_Turn ? White_Move_Spacer :  Black_Move_Spacer) == 0)
    {
    	Current_Turn ? Generate_White_Moves(false) : Generate_Black_Moves(false);
		if(Current_Turn ? White_Move_Spacer : Black_Move_Spacer == 0)
		{
			if(Search::Is_Mate() != 0)
			return Search::Is_Mate();
			return 0;
		}
        return stand_pat;
    }
    Move move;
    Move Best(0);
    vector<Move>stack;
    int count = 0;
    for(int i = 0; i < (Current_Turn ? White_Move_Spacer : Black_Move_Spacer); i++)
    	{
    		Move m(0);
    		m.From = Current_Turn ? White_Move_From_Stack[i] : Black_Move_From_Stack[i];
    		m.To = Current_Turn ? White_Move_To_Stack[i] : Black_Move_To_Stack[i]; 
    		m.Move_Type = Current_Turn ? White_Move_Types[i] : Black_Move_Types[i]; 
    		m.Score = Get_Move_Score(m, Current_Turn);
    		stack.push_back(m);
		}
	std::sort(stack.begin(), stack.end(), [](const Move& lhs, const Move& rhs){ return lhs.Score > rhs.Score; });
	NodeType n = Alpha;
	for(int i = 0; i < (Current_Turn ? White_Move_Spacer : Black_Move_Spacer); i++)
    {
    	if(stack[i].Score > 0)
    	{
        Nodes++;
        move.From = stack[i].From;
        move.To = stack[i].To;
        move.Move_Type = stack[i].Move_Type;
        Current_Turn ? Make_White_Search_Move(stack[i].From, stack[i].To, stack[i].Move_Type) : Make_Black_Search_Move(stack[i].From, stack[i].To, stack[i].Move_Type);
        int score = -QuiescenceSearch(-beta, -alpha, depth + 1);
        move.Undo_Move();
        if(score >= beta)
        {
        	NodeType node = Beta;
			TT.save(depth, score, move, node, Get_Current_Hash_Key());
            return beta;
        }
        if(score > alpha)
        {
        	n = Exact;
        	Best = move;
        	Best.Score = score;
        	alpha = score;
        }
    	}
	}
    TT.save(depth, Best.Score, Best, n, Get_Current_Hash_Key());
    return alpha;
}

int Search::Get_Move_Score(Move& m, bool turn)
{
	int capturedtype = 0;
	int movedtype = m.Move_Type;
	if(m.To & (turn ? Black_Pawns : White_Pawns))
		capturedtype = 1;
	if(m.To & (turn ? Black_Knights : White_Knights))
		capturedtype = 3;
	if(m.To & (turn ? Black_Bishops : White_Bishops))
		capturedtype = 5;
	if(m.To & (turn ? Black_Rooks : White_Rooks))
		capturedtype = 7;
	if(m.To & (turn ? Black_Queens : White_Queens))
		capturedtype = 9;
	return capturedtype - movedtype; 
}


