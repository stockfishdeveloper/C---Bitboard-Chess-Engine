using namespace std;
#include "Bitboard.h"
#include "Search.h"
#include "Eval.h"
#include "UCI.h"
#include "Thread.h"
#include "magicmoves.h"
#include "Endgame.h"
#include "TransTable.h"

int Search::Time_Allocation = 0;
bool Search::Searching = false;
Bitboard Search::Nodes = 0;
int Search::Depth = 0;
int Search::Seldepth = 0;
bool Search::STOP_SEARCHING_NOW = false;
bool Search::Current_Turn = false;

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
    int rootAlpha;
    rootAlpha = -100000;
    int rootBeta;
    rootBeta = 100000;
    const int MAXDEPTH = 60;
    int Plies_Searched = 0;
    LINE line;
    Move rootstack[100];
    int count = 0;
    int matemoves = 1000;
    for(int q = 1; q < MAXDEPTH; q++)
    {
    	output.lock();
		cout << "info depth " << q << endl;
        output.unlock();
    	/*if(q > 5)
    	{
    		rootAlpha = std::max(rootstack[q].Score - 18, -100000);
    		rootBeta = std::min(rootstack[q].Score + 18, 100000);
		}*/
        if(Current_Turn == true)
        {
            Time_Allocation = wtime;
            Depth = q;
            if(q == 1) Generate_White_Moves(false);
            Move wh;
            move = wh;
            wh.White_Temp_Move_Spacer = White_Move_Spacer;
            for(int h = 0; h < White_Move_Spacer; h++)
            {
            	if(q == 1)
                {
                    move.From = White_Move_From_Stack[h];
                    move.To = White_Move_To_Stack[h];
                    move.Move_Type = White_Move_Types[h];
                    rootstack[h] = move;
                    count++;
                }
            }
            for(int i = 0; i < White_Move_Spacer; i++)
            {
                Nodes++;
                move.From = White_Move_From_Stack[i];
                move.To = White_Move_To_Stack[i];
                move.Move_Type = White_Move_Types[i];
                if(White_Move_Spacer == 1)
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
                Make_White_Search_Move(move.From, move.To, move.Move_Type);
                int Temp_Move = SearchMin(rootAlpha, rootBeta, (q - 1), &line, true);
                (rootstack[i]).Score = Temp_Move;
                move.Undo_Move();
                if(Temp_Move < rootAlpha)
                {
                    rootAlpha -= 18;
                    continue;
                }
                if(Temp_Move > rootBeta)
                {
                    rootBeta += 18;
                    continue;
                }
                if(Temp_Move > rootAlpha)
                {
                    LINE* f = new LINE;
                    f->cmove = 0;
                    ::PVline = *f;
                    delete f;
                    ::PVline.argmove[0] = move;
                    ::PVline.score = Temp_Move;
                    ::PVline.cmove = line.cmove + 1;
                    memcpy(::PVline.argmove + 1, line.argmove, line.cmove * sizeof(Move));
                    Best = move;
                    Best.Score = Temp_Move;
                    rootAlpha = Temp_Move;
                }
                if(timer.Get_Time() >= (Search::Time_Allocation / 30))
        			{
            			Search::STOP_SEARCHING_NOW = true;
            			return Best;
        			}
            }

        }

        else
        {
        	Time_Allocation = btime;
            Depth = q;
            if(q == 1)
			{
				Generate_Black_Moves(false);
				Move bl;
            	move = bl;
				move.Black_Temp_Move_Spacer = Black_Move_Spacer;
				for(int h = 0; h < Black_Move_Spacer; h++)
            		{
            		move.From = Black_Move_From_Stack[h];
                    move.To = Black_Move_To_Stack[h];
                    move.Move_Type = Black_Move_Types[h];
                    rootstack[h] = move;
                    count++;
                	}
            }
            for(int i = 0; i < Black_Move_Spacer; i++)
            {
                Nodes++;
                move.From = Black_Move_From_Stack[i];
                move.To = Black_Move_To_Stack[i];
                move.Move_Type = Black_Move_Types[i];
                if(Black_Move_Spacer == 1)
                {
                    Best = move;
                    return Best;
                }
                if(q >= 2 && timer.Get_Time() > 1000)
                {
                    output.lock();
                    cout << "info currmove " << PlayerMoves[(move.Convert_Bitboard(move.From))] << PlayerMoves[(move.Convert_Bitboard(move.To))];
                    Log << "info currmove " << PlayerMoves[(move.Convert_Bitboard(move.From))] << PlayerMoves[(move.Convert_Bitboard(move.To))];
                    cout << " currmovenumber " << (i + 1) << endl;
                    Log << " currmovenumber " << (i + 1) << endl;
                    output.unlock();
                }
                Make_Black_Search_Move(move.From, move.To, move.Move_Type);
                int Temp_Move = SearchMax(rootAlpha, rootBeta, (q - 1), &line, true);
                (rootstack[i]).Score = Temp_Move;
                move.Undo_Move();
                if (Temp_Move < rootAlpha)
                {
                    rootAlpha -= 18;
                    continue;
                }
                if(Temp_Move > rootBeta)
                {
                    rootBeta += 18;
                    continue;
                }
                if(Temp_Move < rootBeta)
                {
                    LINE* f = new LINE;
                    f->cmove = 0;
                    ::PVline = *f;
                    delete f;
                    ::PVline.argmove[0] = move;
                    ::PVline.score = Temp_Move;
                    ::PVline.cmove = line.cmove + 1;
                    memcpy(::PVline.argmove + 1, line.argmove, line.cmove * sizeof(Move));
                    Best = move;
                    Best.Score = Temp_Move;
                    rootBeta = Temp_Move;
                }
                if(timer.Get_Time() >= (Search::Time_Allocation / 30))
        			{
            			Search::STOP_SEARCHING_NOW = true;
            			return Best;
        			}

            }

        }


		for(int i = 0; i < count; i++)
		{
			if((rootstack[i].From == Best.From) && (rootstack[i].To == Best.To))
				rootstack[i].Score += (Current_Turn ? 1000 : -1000);
			if((rootstack[i].Move_Type % 2) > 0)
				rootstack[i].Score += (Current_Turn ? 20 : -20);
			if((rootstack[i].Move_Type == 13) || (rootstack[i].Move_Type == 14))
				rootstack[i].Score += (Current_Turn ? 40 : -40);
			if(MVV_LVA(rootstack[i].Move_Type, rootstack[i].To, (Current_Turn ? true : false)))
			{
				rootstack[i].Score += (Current_Turn ? 50 : -50);
			}
		}
        Search::Order_Moves(rootstack, Current_Turn, count);
        for(int i = 0; i < count; i++)
        {
        	//cout << PlayerMoves[rootstack[i].Convert_Bitboard(rootstack[i].From)] << PlayerMoves[rootstack[i].Convert_Bitboard(rootstack[i].To)] << " " << rootstack[i].Score << endl;
        	rootstack[i].Score = 0;
            if(Current_Turn)
            {
                White_Move_From_Stack[i] = rootstack[i].From;
                White_Move_To_Stack[i] = rootstack[i].To;
                White_Move_Types[i] = rootstack[i].Move_Type;
                White_Move_Spacer = count;
            }
            else
            {
                Black_Move_From_Stack[i] = rootstack[i].From;
                Black_Move_To_Stack[i] = rootstack[i].To;
                Black_Move_Types[i] = rootstack[i].Move_Type;
                Black_Move_Spacer = count;
            }
        }
		
		output.lock();
		cout << "info multipv 1 depth " << q << " seldepth " << Search::Seldepth << " score ";
        Log << "<< info multipv 1 depth " << q << " seldepth " << Search::Seldepth << " score ";
        if(Best.Score == 10000)
        {
        	if(q + 1 < matemoves)
                {
                	cout << "mate " << (Current_Turn == true ? ((q + 1) / 2) : -((q + 1) / 2));
                    Log << "mate " << (Current_Turn == true ? ((q + 1) / 2) : -((q + 1) / 2));
                    matemoves = q + 1;
                }
            else
                {
                    cout << "mate " << (Current_Turn == true ? matemoves / 2 : -matemoves / 2);
                    Log << "mate " << (Current_Turn == true ? matemoves / 2 : -matemoves / 2);
                }
        }
        else if(Best.Score == -10000)
        {
        	if(q + 1 < matemoves)
                {
        			cout << "mate " << (Current_Turn == true ? -((q + 1) / 2) : ((q + 1) / 2));
        			Log << "mate " << (Current_Turn == true ? -((q + 1) / 2) : ((q + 1) / 2));
        			matemoves = q + 1;
        		}
        	else
                {
                    cout << "mate " << (Current_Turn == true ? -matemoves / 2 : matemoves / 2);
                    Log << "mate " << (Current_Turn == true ? -matemoves / 2 : matemoves / 2);
                }
    	}
        else
        {
        cout << "cp " << Current_Turn ? Best.Score : -Best.Score;
        Log << "cp " << Current_Turn ? Best.Score : -Best.Score;
    	}
        cout << " pv " << ::PVline.Output() << line.Output();
        Log << " pv " << ::PVline.Output() << line.Output();
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
        //rootAlpha = -100000;
    	//rootBeta = 100000;
    }

    return Best;
}

int Search::SearchMax(int alpha, int beta, int depth, LINE * pline, bool donullmove)
{
    if(depth <= 1)
    {
        ++Nodes;
        pline->cmove = 0;
        return QuiesceMax(alpha, beta, pline, depth + 1);
    }
    LINE line;

    /*NULLMOVE PRUNING*******************************************************
    *************************************************************************
    *************************************************************************/
    /*if((Search::Is_Mate() != -10000) && (donullmove) && (depth > 3))
    {
        Search::Current_Turn = false;
        int Temp_Move = SearchMin(beta, beta - 1, depth - 3, &line, false);
        if(Temp_Move >= beta)
            {
                //cout << "NULL MOVE BETA CUTOFF!" << endl;
                Search::Current_Turn = true;
                return beta;
            }

    }
        Search::Current_Turn = true;*/
    /************************************************************************
    *************************************************************************
    *************************************************************************/
    Generate_White_Moves(false);
    Move move;
    if(White_Move_Spacer == 0)
    {
        alpha = Is_Mate();
        pline->score = alpha;
        pline->cmove = 0;
        return alpha;
	}
    for(int i = 0; i < White_Move_Spacer; i++)
    {
        Nodes++;
        move.From = White_Move_From_Stack[i];
        move.To = White_Move_To_Stack[i];
        move.Move_Type = White_Move_Types[i];
        Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]);
        int Temp_Move = SearchMin(alpha, beta, depth - 1, &line, (donullmove ? false : true));
        move.Undo_Move();
        if(Temp_Move >= beta)
        {
            return beta;
        }
        else if(Temp_Move > alpha)
        {
            pline->argmove[0] = move;
            pline->score = Temp_Move;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
            pline->cmove = line.cmove + 1;
            alpha = Temp_Move;
        }

    }

    return alpha;
}


int Search::SearchMin(int alpha, int beta, int depth, LINE * pline, bool donullmove)
{
    if(depth <= 1)
    {
        ++Nodes;
        pline->cmove = 0;
        return QuiesceMin(alpha, beta, pline, depth + 1);
    }
    LINE line;
    /*NULLMOVE PRUNING*******************************************************
    *************************************************************************
    *************************************************************************/
    /*if((Search::Is_Mate() != 10000) && (donullmove) && (depth > 3))
    {
        Search::Current_Turn = true;
        int Temp_Move = SearchMax(alpha, alpha + 1, depth - 3, &line, false);
        if(Temp_Move <= alpha)
            {
                //cout << "NULL MOVE ALPHA CUTTOFF!" << endl;
                Search::Current_Turn = false;
                return alpha;
            }
    }
        Search::Current_Turn = false;*/
    /************************************************************************
    *************************************************************************
    *************************************************************************/

    Generate_Black_Moves(false);
    Move move;
    if(Black_Move_Spacer == 0)
    {
        beta = Is_Mate();
        pline->score = beta;
        pline->cmove = 0;
        return beta;
    }

    for(int i = 0; i < Black_Move_Spacer; i++)
    {
    	move.From = Black_Move_From_Stack[i];
        move.To = Black_Move_To_Stack[i];
        move.Move_Type = Black_Move_Types[i];
        Nodes++;
        Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
        int Temp_Move = SearchMax(alpha, beta, depth - 1, &line, (donullmove ? false : true));
        move.Undo_Move();
        if(Temp_Move <= alpha)
        {
            return alpha;
        }
        else if(Temp_Move < beta)
        {
            pline->argmove[0] = move;
            pline->score = Temp_Move;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
            pline->cmove = line.cmove + 1;
            beta = Temp_Move;
        }
	}
	return beta;

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
    for(int t = 0; t < 100; t++)
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
    for(int t = 0; t < 100; t++)
    {
        Black_Move_From_Stack[t] = 0;//Clear the move from stack
        Black_Move_To_Stack[t] = 0;//Clear the move to stack
        Black_Move_Types[t] = 0;//Clear the move types associated with the moves
    }
    Black_Move_Spacer = 0;

    Search::Current_Turn  = true;
    return 0;

}

void Search::Order_Moves(Move* moves, bool Whites_Turn, int elements)
{
    Move stack[elements];
    Move sorted[elements];
    int best;
    int index = 0;
    int count = 0;
    for(int i = 0; i < elements; i++)
    {
        stack[i] = *(moves + i);
        sorted[i].Score = 0;
    }
    if(Whites_Turn)
    {
        best = -10000;
        for(int y = 0; y < elements; y++)
        {

            for(int i = 0; i < elements; i++)
            {
                if(stack[i].Score > best)
                {
                    best = stack[i].Score;
                    index = i;
                }
            }
            sorted[count++] = stack[index];
            stack[index].Score = -10000;
            best = -10000;
        }
    }
    else
    {
        best = 10000;
        for(int y = 0; y < elements; y++)
        {

            for(int i = 0; i < elements; i++)
            {
                if(stack[i].Score < best)
                {
                    best = stack[i].Score;
                    index = i;
                }
            }
            sorted[count++] = stack[index];
            stack[index].Score = 10000;
            best = 10000;
        }
    }
    for(int i = 0; i < elements; i++)
    {
    	*(moves + i) = sorted[i];
	}
    return;

}

Search::Is_Mate()
{
    if(Search::Current_Turn)
    {
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
            return -10000;
        if(RAttacks & (Black_Rooks))
            return -10000;
        if(QAttacks & (Black_Queens))
            return -10000;
        if(Knight_Lookup_Table[h] & Black_Knights)
            return -10000;
        if(King_Lookup_Table[h] & Black_King)
            return -10000;

        Bitboard Spare = Black_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare >> 7) & White_King)
            return -10000;

        Bitboard Spare2 = Black_Pawns;
        Spare2 |= H_Pawn_Mask;
        Spare2 ^= H_Pawn_Mask;
        if((Spare2 >> 9) & White_King)
            return -10000;

        Bitboard Black_Pawns5 = Black_Pawns;
        Black_Pawns5 |= A_Pawn_Mask;
        Black_Pawns5 ^= A_Pawn_Mask;
        Black_Pawns5 |= H_Pawn_Mask;
        Black_Pawns5 ^= H_Pawn_Mask;
        if(((Black_Pawns5 >> 7) | (Black_Pawns5 >> 9)) & White_King)
            return -10000;
    }

    else
    {
        int h = 0;
        for(int j = 0; j < 64; j++)
        {
            if(Black_King & GeneralBoard[j])//Get the index(0-63) of the black king
            {
                h = j;
                break;
            }
        }
        Bitboard BAttacks = Bmagic(h, (White_Pieces | Black_Pieces));
        Bitboard RAttacks = Rmagic(h, (White_Pieces | Black_Pieces));
        Bitboard QAttacks = Qmagic(h, (White_Pieces | Black_Pieces));

        if(BAttacks & (White_Bishops))
            return 10000;
        if(RAttacks & (White_Rooks))
            return 10000;
        if(QAttacks & (White_Queens))
            return 10000;
        if(Knight_Lookup_Table[h] & White_Knights)
            return 10000;
        if(King_Lookup_Table[h] & White_King)
            return 10000;

        Bitboard Spare = White_Pawns;
        Spare |= A_Pawn_Mask;
        Spare ^= A_Pawn_Mask;
        if((Spare << 9) & Black_King)
            return 10000;

        Bitboard Spare7 = White_Pawns;
        Spare7 |= H_Pawn_Mask;
        Spare7 ^= H_Pawn_Mask;
        if((Spare7 << 7) & Black_King)
            return 10000;

        Bitboard White_Pawns2 = 0;
        White_Pawns2 |= A_Pawn_Mask;
        White_Pawns2 ^= A_Pawn_Mask;
        White_Pawns2 |= H_Pawn_Mask;
        White_Pawns2 ^= H_Pawn_Mask;
        if(((White_Pawns << 7) | (White_Pawns << 9)) & GeneralBoard[h])
            return 10000;
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

int Search::QuiesceMax(int alpha, int beta, LINE * pline, int depth)
{
	int stand_pat = Eval::Evaluate_Position();
	Search::Seldepth = Search::Depth + (depth > Search::Seldepth ? depth : Search::Seldepth);
	Nodes++;
    if(stand_pat >= beta)
        return beta;
    if(alpha < stand_pat)
        alpha = stand_pat;
	Generate_White_Moves(true);
	if(White_Move_Spacer == 0)
    {
    	pline->cmove = 0;
    	Generate_White_Moves(false);
		if(White_Move_Spacer == 0)
		{
			if(Search::Is_Mate() != 0)
			return Search::Is_Mate();
			return 0;
		}
        return stand_pat;
    }
    Move move;
    LINE line;
    /*bool table[White_Move_Spacer];
    for(int i = 0; i < White_Move_Spacer; i++)
    {
    	if(MVV_LVA(White_Move_Types[i], White_Move_To_Stack[i], true))
    	table[i] = true;
    	else
    	table[i] = false;
	}*/
    for(int i = 0; i < White_Move_Spacer; i++)
    {
    	if(MVV_LVA(White_Move_Types[i], White_Move_To_Stack[i], true))
    	{
        Nodes++;
        move.From = White_Move_From_Stack[i];
        move.To = White_Move_To_Stack[i];
        move.Move_Type = White_Move_Types[i];
        Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]);
        int Temp_Move = QuiesceMin(alpha, beta, &line, depth + 1);
        move.Undo_Move();
        if(Temp_Move >= beta)
        {
            return beta;
        }

        else if(Temp_Move > alpha)
        {
        	pline->argmove[0] = move;
            pline->score = Temp_Move;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
            pline->cmove = line.cmove + 1;
            alpha = Temp_Move;
        }
    	}

    }
            
    return alpha;
}

int Search::QuiesceMin(int alpha, int beta, LINE * pline, int depth)
{
	int stand_pat = Eval::Evaluate_Position();
	Search::Seldepth = Search::Depth + (depth > Search::Seldepth ? depth : Search::Seldepth);
	Nodes++;
    if( stand_pat <= alpha)
        return alpha;
    if(stand_pat < beta)
        beta = stand_pat;
	Generate_Black_Moves(true);
	if(Black_Move_Spacer == 0)
    {
    	pline->cmove = 0;
    	Generate_Black_Moves(false);
    	if(Black_Move_Spacer == 0)
		{
			if(Search::Is_Mate() != 0)
			return Search::Is_Mate();
			return 0;
		}
        return stand_pat;
    }
    Move move;
    LINE line;
    /*bool table[Black_Move_Spacer];
    for(int i = 0; i < Black_Move_Spacer; i++)
    {
    	if(MVV_LVA(Black_Move_Types[i], Black_Move_To_Stack[i], false))
    	table[i] = true;
    	else
    	table[i] = false;
	}*/
    for(int i = 0; i < Black_Move_Spacer; i++)
    {
    	if(MVV_LVA(Black_Move_Types[i], Black_Move_To_Stack[i], false))
    	{
        Nodes++;
        move.From = Black_Move_From_Stack[i];
        move.To = Black_Move_To_Stack[i];
        move.Move_Type = Black_Move_Types[i];
        Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
        int Temp_Move = QuiesceMax(alpha, beta, &line, depth + 1);
        move.Undo_Move();
        if(Temp_Move <= alpha)
        {
            return alpha;
        }

        else if(Temp_Move < beta)
        {
        	pline->argmove[0] = move;
            pline->score = Temp_Move;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
            pline->cmove = line.cmove + 1;
			beta = Temp_Move;
        }
    	}    

    }

    return beta;
}

bool Search::MVV_LVA(int& Move_Type, Bitboard& To, bool WhiteToMove)
{
	if(WhiteToMove)
	{
		switch(Move_Type)
		{
			case 1:
				return true;
			case 3:
				if(!(Black_Pawns & To))
				return true;
				else
				return false;
			case 5:
				if(!(Black_Pawns & To))
				return true;
				else
				return false;
			case 7:
				if(!((Black_Pawns | Black_Knights) & To))
				return true;	
				else
				return false;
			case 9:
				if(!((Black_Pawns | Black_Knights | Black_Rooks) & To))
				return true;	
				else
				return false;
			case 11:
				return true;
			default:
				return false;			
		}
	}
	else
	{
		switch(Move_Type)
		{
			case 1:
				return true;
			case 3:
				if(!(White_Pawns & To))
				return true;
				else
				return false;
			case 5:
				if(!(White_Pawns & To))
				return true;
				else
				return false;
			case 7:
				if(!((White_Pawns | White_Knights) & To))
				return true;	
				else
				return false;
			case 9:
				if(!((White_Pawns | White_Knights | White_Rooks) & To))
				return true;	
				else
				return false;
			case 11:
				return true;
			default:
				return false;				
		}
	}
}


