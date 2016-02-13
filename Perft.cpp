#include "Perft.h"
#include "Search.h"

int Root_Perft(int depth)
{
    int n_moves, i;
    Bitboard nodes = 0;

    if (depth == 0) return 1;
    Search::Current_Turn ? Generate_White_Moves() : Generate_Black_Moves();
    n_moves = Search::Current_Turn ? White_Move_Spacer : Black_Move_Spacer;
    Move move;
    for (i = 0; i < n_moves; i++)
    {

        Search::Current_Turn ? move.From = White_Move_From_Stack[i] : move.From = Black_Move_From_Stack[i];
        Search::Current_Turn ? move.To = White_Move_To_Stack[i] : move.To = Black_Move_To_Stack[i];
        Search::Current_Turn ? move.Move_Type = White_Move_Types[i] : move.Move_Type = Black_Move_Types[i];
        Search::Current_Turn ? move.White_Temp_Move_Spacer = White_Move_Spacer : move.Black_Temp_Move_Spacer = Black_Move_Spacer;

        if(Search::Current_Turn)
        {
            for(int h = 0; h < White_Move_Spacer; h++)
            {
                move.White_Temp_Move_From_Stack[h] = move.Convert_Bitboard(White_Move_From_Stack[h]);
                move.White_Temp_Move_To_Stack[h] = move.Convert_Bitboard(White_Move_To_Stack[h]);
                move.White_Temp_Move_Types[h] = White_Move_Types[h];
            }
        }
        else
        {
            for(int h = 0; h < Black_Move_Spacer; h++)
            {
                move.Black_Temp_Move_From_Stack[h] = move.Convert_Bitboard(Black_Move_From_Stack[h]);
                move.Black_Temp_Move_To_Stack[h] = move.Convert_Bitboard(Black_Move_To_Stack[h]);
                move.Black_Temp_Move_Types[h] = Black_Move_Types[h];
            }
        }
        Search::Current_Turn ? Search::Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]) : Search::Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
        for( int h = 0; h < 64; h++)
        {
            if(GeneralBoard[h] & move.From)
            {
                cout << PlayerMoves[h];
            }
        }
        for( int h = 0; h < 64; h++)
        {
            if(GeneralBoard[h] & move.To)
            {
                cout  << PlayerMoves[h] << ": ";
            }
        }
        int f = nodes;
        nodes += Perft(depth - 1);
        cout << nodes - f << endl;
        move.Undo_Move();
    }
    return nodes;

}
int Perft(int depth)
{
    int n_moves, i;
    Bitboard nodes = 0;

    if (depth == 0) return 1;
    Search::Current_Turn ? Generate_White_Moves() : Generate_Black_Moves();
    n_moves = Search::Current_Turn ? White_Move_Spacer : Black_Move_Spacer;
    //cout << "n_moves: " << n_moves << endl;
    for (i = 0; i < n_moves; i++)
    {
        Move move;
        Search::Current_Turn ? move.From = White_Move_From_Stack[i] : move.From = Black_Move_From_Stack[i];
        Search::Current_Turn ? move.To = White_Move_To_Stack[i] : move.To = Black_Move_To_Stack[i];
        Search::Current_Turn ? move.Move_Type = White_Move_Types[i] : move.Move_Type = Black_Move_Types[i];
        Search::Current_Turn ? move.White_Temp_Move_Spacer = White_Move_Spacer : move.Black_Temp_Move_Spacer = Black_Move_Spacer;
        if(Search::Current_Turn)
        {
            for(int h = 0; h < White_Move_Spacer; h++)
            {
                move.White_Temp_Move_From_Stack[h] = move.Convert_Bitboard(White_Move_From_Stack[h]);
                move.White_Temp_Move_To_Stack[h] = move.Convert_Bitboard(White_Move_To_Stack[h]);
                move.White_Temp_Move_Types[h] = White_Move_Types[h];
            }
        }
        else
        {
            for(int h = 0; h < Black_Move_Spacer; h++)
            {
                move.Black_Temp_Move_From_Stack[h] = move.Convert_Bitboard(Black_Move_From_Stack[h]);
                move.Black_Temp_Move_To_Stack[h] = move.Convert_Bitboard(Black_Move_To_Stack[h]);
                move.Black_Temp_Move_Types[h] = Black_Move_Types[h];
            }
        }
        Search::Current_Turn ? Search::Make_White_Search_Move(White_Move_From_Stack[i], White_Move_To_Stack[i], White_Move_Types[i]) : Search::Make_Black_Search_Move(Black_Move_From_Stack[i], Black_Move_To_Stack[i], Black_Move_Types[i]);
        nodes += Perft(depth - 1);
        move.Undo_Move();
    }
    return nodes;

}
