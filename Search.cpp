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
#include "Util.h"

int Search::Time_Allocation = 0;
bool Search::Searching = false;
Bitboard Search::Nodes = 0;
int Search::Depth = 0;
int Search::Seldepth = 0;
bool Search::STOP_SEARCHING_NOW = false;

Move Search::Think(int wtime, int btime, int winc, int binc)
{
    Move Best;
    Best.Score = -100000;
    Timer timer;
    timer.Start_Clock();
    Time_Allocation = (pos.Current_Turn ? wtime : btime);
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
		if(q == 1)
		{
			pos.Current_Turn ? Generate_White_Moves(false, &pos) : Generate_Black_Moves(false, &pos);
			if(pos.numlegalmoves == 1)
            {
            	return pos.LegalMoves[0];
            }
		}
		if(q == 1)
            {
            	for(int h = 0; h < pos.numlegalmoves; h++)
                	{
                    	pos.LegalMoves[h].Score = Get_Move_Score(pos.LegalMoves[h]);
                    	rootstack.push_back(pos.LegalMoves[h]);
                    	count++;
                	}
            }
        for(int i = 0; i < count; i++)
			{
				if((rootstack[i].From == Best.From) && (rootstack[i].To == Best.To))
					rootstack[i].Score += 1000;
				if(rootstack[i].C != NONE)
					rootstack[i].Score += 20;
				if(rootstack[i].Promotion == true)
					rootstack[i].Score += 100;
				/*if(Get_Move_Score(rootstack[i], pos.Current_Turn) > 0)
				{
					rootstack[i].Score += 50;
				}*/
			}
        std::sort(rootstack.begin(), rootstack.end(), [](const Move& lhs, const Move& rhs){ return (lhs.Score > rhs.Score);});
        for(int i = 0; i < pos.numlegalmoves; i++)
            {
            	Nodes++;
                if(q >= 2 && timer.Get_Time() > 1000)
                {
                    output.lock();
                    cout << "info currmove " << PlayerMoves[(Convert_Bitboard(rootstack[i].From))] << PlayerMoves[(Convert_Bitboard(rootstack[i].To))];
                    Log << "<< info currmove " << PlayerMoves[(Convert_Bitboard(rootstack[i].From))] << PlayerMoves[(Convert_Bitboard(rootstack[i].To))];
                    cout << " currmovenumber " << (i + 1) << endl;
                    Log << " currmovenumber " << (i + 1) << endl;
                    output.unlock();
                }
                pos.Make_Move(rootstack[i]);
                int score = -AlphaBeta(&pos, -rootBeta, -rootAlpha, (q - 1), &line, true);
                (rootstack[i]).Score = score;
                //cout << " " << score << endl;
                if((score > rootBeta) || (score < rootAlpha))
                {
                	rootAlpha = -100000;
                	rootBeta = 100000;
                	score = -AlphaBeta(&pos, -rootBeta, -rootAlpha, (q - 1), &line, true);
                }
                pos.Undo_Move(rootstack[i]);
                if(score > rootAlpha)
                {
                	LINE* f = new LINE;
                    f->cmove = 0;
                    ::PVline = *f;
                    delete f;
                    ::PVline.argmove[0] = rootstack[i];
                    ::PVline.score = score;
                    ::PVline.cmove = line.cmove + 1;
                    memcpy(::PVline.argmove + 1, line.argmove, line.cmove * sizeof(Move));
                    Best = rootstack[i];
                    Best.Score = score;
                    Uci_Pv(q, Seldepth, Best, &matemoves, timer.Get_Time(), Nodes);
                    rootAlpha = score;
                }
                if((timer.Get_Time() >= (Search::Time_Allocation / 30)) && q > 3)
        			{
            			Search::STOP_SEARCHING_NOW = true;
            			return Best;
        			}
            }
        Uci_Pv(q, Seldepth, Best, &matemoves, timer.Get_Time(), Nodes);
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
        //rootAlpha -= 50;
        //rootBeta += 50;
        rootAlpha = -100000;
    	rootBeta = 100000;
    }

    return Best;
}

int Search::AlphaBeta(Position* posit, int alpha, int beta, int depth, LINE * pline, bool donullmove)
{
	if(depth <= 1)
    {
        ++Nodes;
        pline->cmove = 0;
        return QuiescenceSearch(posit, alpha, beta, depth + 1);
    }
    Position position(posit);
    LINE line;
    bool inCheck = (position.Current_Turn ? (Search::Is_Mate(&position) == -10000) : (Search::Is_Mate(&position) == 10000));
	/*NULLMOVE PRUNING*******************************************************
    *************************************************************************
    *************************************************************************/
    if((!inCheck) && (donullmove) && (depth > 3))
    {
        position.Current_Turn ^= 1;
        int score = -AlphaBeta(&position, -beta, -beta + 1, depth - 3, &line, false);
        if(score >= beta)
            {
                position.Current_Turn ^= 1;
                return beta;
            }
		position.Current_Turn ^= 1;
    }
    /************************************************************************
    *************************************************************************
    *************************************************************************/
    position.Current_Turn ? Generate_White_Moves(false, &position) : Generate_Black_Moves(false, &position);
    if(position.numlegalmoves == 0)
    {
        alpha = Is_Mate(&position);
        pline->score = alpha;
        pline->cmove = 0;
        return alpha;
	}
	TTEntry* tt = TT.probe(Get_Current_Hash_Key(&position));
	if(tt!= NULL)
	{
		if(tt->depth >= depth)
		{
			if(tt->nodetype == Alpha) if(tt->score <= alpha) return alpha;
			if(tt->nodetype == Beta) if(tt->score >= beta) return beta;
			if(tt->nodetype == Exact) 
				{
					return tt->score;
				}
		}
	}
	NodeType node = Alpha;
    vector<Move> moves;
    //moves.reserve(Current_Turn ? White_Move_Spacer : Black_Move_Spacer);
    for(int i = 0; i < position.numlegalmoves; i++)
    	{
    		if(tt != NULL) if(tt->best.From == position.LegalMoves[i].From && tt->best.To == position.LegalMoves[i].To) position.LegalMoves[i].Score += 1000;
    		if(position.LegalMoves[i].C != NONE)
    			position.LegalMoves[i].Score += Get_Move_Score(position.LegalMoves[i]);
    		if(position.LegalMoves[i].Promotion)
				position.LegalMoves[i].Score += 64 * 8;
    		moves.push_back(position.LegalMoves[i]);
		}
	std::sort(moves.begin(), moves.end(), [](const Move& lhs, const Move& rhs){ return lhs.Score > rhs.Score; });
	bool pvfound = false;
	for(int i = 0; i < position.numlegalmoves; i++)
    {
        Nodes++;
        position.Make_Move(moves[i]);
        int score;
        if(i < 3)
        	score = -AlphaBeta(&position, -beta, -alpha, depth - 1, &line, true);
        else
        	{
        		if(depth > 2
		   		&& i > 2
		   		//&& (!(mt == Capture))
		   		//&& (!(mt == Promotion))
				&& !inCheck)
		   		{
		   			score = -AlphaBeta(&position, -(alpha + 1), -alpha, depth - 2, &line, true);
		   			if(score > alpha)
				   		score = -AlphaBeta(&position, -(alpha + 1), -alpha, depth - 1, &line, true);
				   	if(score > alpha && score < beta)
          				score = -AlphaBeta(&position, -beta, -alpha, depth - 1, &line, true);
          		}
		   		else
		   			score = -AlphaBeta(&position, -beta, -alpha, depth - 1, &line, true);
		   	}
		/*else if((pvfound == true) && (dofullsearch == 0))
        {
			score = -AlphaBeta(-(alpha-1), -alpha, depth - 1, &line, true);
			if(score > alpha)
            	score = -AlphaBeta(-beta, -alpha, depth - 1, &line, true);
        }*/
        position.Undo_Move(moves[i]);
        if(score >= beta)
        {
        	TT.save(depth, beta, pline->argmove[0], Beta, Get_Current_Hash_Key(&position));
        	return beta;
        }
        if(score > alpha)
        {
        	pline->argmove[0] = moves[i];
            pline->score = score;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
            pline->cmove = line.cmove + 1;
            alpha = score;
            node = Exact;
            pvfound = true;
		}
    }
    TT.save(depth, alpha, pline->argmove[0], node, Get_Current_Hash_Key(&position));
    return alpha;
}

Search::Is_Mate(Position* position)
{
	int score = 0;
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
        Bitboard QAttacks = Qmagic(h, (position->White_Pieces | position->Black_Pieces));

        if(BAttacks & (position->Black_Bishops))
            score = -1;
        if(RAttacks & (position->Black_Rooks))
            score = -1;
        if(QAttacks & (position->Black_Queens))
            score = -1;
        if(Knight_Lookup_Table[h] & position->Black_Knights)
            score = -1;
        if(King_Lookup_Table[h] & position->Black_King)
            score = -1;
        Bitboard Spare = position->Black_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare >> 7) & position->White_King)
            score = -1;
        Bitboard Spare2 = position->Black_Pawns;
        Spare2 |= H_Pawn_Mask;
        Spare2 ^= H_Pawn_Mask;
        if((Spare2 >> 9) & position->White_King)
            score = -1;
        Bitboard Black_Pawns5 = position->Black_Pawns;
        Black_Pawns5 |= A_Pawn_Mask;
        Black_Pawns5 ^= A_Pawn_Mask;
        Black_Pawns5 |= H_Pawn_Mask;
        Black_Pawns5 ^= H_Pawn_Mask;
        if(((Black_Pawns5 >> 7) | (Black_Pawns5 >> 9)) & position->White_King)
            score = -1;
        if(score != 0)
    	{
    		if(score < 0)
    		{
    			if(position->Current_Turn)
    				return -10000;
    			else
    				return 10000;
			}
			if(score > 0)
    		{
    			if(position->Current_Turn)
    				return 10000;
    			else
    				return -10000;
			}
		}
        for(int j = 0; j < 64; j++)
        {
            if(position->Black_King & GeneralBoard[j])//Get the index(0-63) of the black king
            {
                h = j;
                break;
            }
        }
        BAttacks = Bmagic(h, (position->White_Pieces | position->Black_Pieces));
        RAttacks = Rmagic(h, (position->White_Pieces | position->Black_Pieces));
        QAttacks = Qmagic(h, (position->White_Pieces | position->Black_Pieces));
        if(BAttacks & (position->White_Bishops))
            score = 1;
        if(RAttacks & (position->White_Rooks))
            score = 1;
        if(QAttacks & (position->White_Queens))
            score = 1;
        if(Knight_Lookup_Table[h] & position->White_Knights)
            score = 1;
        if(King_Lookup_Table[h] & position->White_King)
            score = 1;
        Spare = position->White_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare << 9) & position->Black_King)
            score = 1;
        Bitboard Spare7 = position->White_Pawns;
        Spare7 |= H_Pawn_Mask;
        Spare7 ^= H_Pawn_Mask;
        if((Spare7 << 7) & position->Black_King)
            score = 1;
        Bitboard White_Pawns2 = position->White_Pawns;
        White_Pawns2 |= A_Pawn_Mask;
        White_Pawns2 ^= A_Pawn_Mask;
        White_Pawns2 |= H_Pawn_Mask;
        White_Pawns2 ^= H_Pawn_Mask;
        if(((White_Pawns2 << 7) | (White_Pawns2 << 9)) & GeneralBoard[h])
            score = 1;
        if(score != 0)
    	{
    		if(score < 0)
    		{
    			if(position->Current_Turn)
    				return -10000;
    			else
    				return 10000;
			}
			if(score > 0)
    		{
    			if(position->Current_Turn)
    				return 10000;
    			else
    				return -10000;
			}
		}
    return 0;
}

void Search::Clear()
{
    Search::Depth = 0;
}

int Search::QuiescenceSearch(Position* posit, int alpha, int beta, int depth)
{
	int stand_pat = posit->Current_Turn ? Eval::Evaluate_Position(posit) : -Eval::Evaluate_Position(posit);
	Search::Seldepth = std::max(depth, Search::Seldepth);
	Nodes++;
    if(stand_pat >= beta)
        return beta;
    if(stand_pat > alpha)
        alpha = stand_pat;
    Position position(posit);
    position.Current_Turn ? Generate_White_Moves(true, &position) : Generate_Black_Moves(true, &position);
	if(position.numlegalmoves == 0)
    {
    	position.Current_Turn ? Generate_White_Moves(false, &position) : Generate_Black_Moves(false, &position);
		if(position.numlegalmoves == 0)
		{
			return Search::Is_Mate(&position);
		}
        return stand_pat;
    }
    TTEntry* tt = TT.probe(Get_Current_Hash_Key(&position));
	if(tt!= NULL)
	{
		if(tt->depth >= depth)
		{
			if(tt->nodetype == Alpha) if(tt->score <= alpha) return alpha;
			if(tt->nodetype == Beta) if(tt->score >= beta) return beta;
			if(tt->nodetype == Exact) 
				{
					return tt->score;
				}
		}
	}
    Move move;
    Move Best;
    vector<Move>stack;
    //stack.reserve(Current_Turn ? White_Move_Spacer: Black_Move_Spacer);
    int count = 0;
    for(int i = 0; i < position.numlegalmoves; i++)
    	{
    		Move m = position.LegalMoves[i];
    		m.Score = Get_Move_Score(m);
    		if(tt != NULL) if(tt->best.From == m.From && tt->best.To == m.To) m.Score += 100;
    		if(m.Score > 0) stack.push_back(m);
    	}
	std::sort(stack.begin(), stack.end(), [](const Move& lhs, const Move& rhs){ return lhs.Score > rhs.Score; });
	NodeType n = Alpha;
	for(int i = 0; i < (stack.size()); i++)
    {
    	Nodes++;
        position.Make_Move(stack[i]);
        int score = -QuiescenceSearch(&position, -beta, -alpha, depth + 1);
        position.Undo_Move(stack[i]);
        if(score >= beta)
        {
        	TT.save(depth, beta, move, Beta, Get_Current_Hash_Key(&position));
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
    TT.save(depth, Best.Score, Best, n, Get_Current_Hash_Key(&position));
    return alpha;
}
int Search::MateSearch(int alpha, int beta, int depth)
{
	if(depth <= 1)
    {
        return 0;
    }
    pos.Current_Turn ? Generate_White_Moves(false, &pos) : Generate_Black_Moves(false, &pos);
    if(pos.numlegalmoves == 0)
    {
        return (Is_Mate(&pos) / 10000);
    }
	Move move;
    for(int i = 0; i < pos.numlegalmoves; i++)
    {
        Nodes++;
        pos.Make_Move(move);
        int score = -MateSearch(-beta, -alpha, depth - 1);
        pos.Undo_Move(move);
        if(score >= beta)
        {
        	return beta;
        }
        if(score > alpha)
        {
            alpha = score;
        }
    }
    return alpha;
}

int Search::Get_Move_Score(Move& m)
{
	int capturedtype = m.C;
	int movedtype = m.P;
	return ((64 * capturedtype) - movedtype);
}


