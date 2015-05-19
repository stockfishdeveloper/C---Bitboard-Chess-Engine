using namespace std;
#include <cstdlib>//For random move generation
#include <ctime>//For random move generation
#include <iostream>
#include <fstream>//For writing the game to a text file
ofstream Dave("Rest.txt");
#include "magicmoves.c"//Pradu's Magic Bitboards
#include "Bitboard.h"
#include "MoveGen.h"
#include "MakeMove.h"

int main()
{
initmagicmoves();//Thanks, Pradu

while(true)//Keep making moves until one side loses or the game is a draw
{
Generate_White_Knight_Moves();//Generates White Knight moves
Generate_White_King_Moves();//Generates White King moves
Generate_White_Pawn_Moves();//Generates White Pawn moves
Generate_White_Rook_Moves();//Generates White Rook moves
Generate_White_Bishop_Moves();//Generates White Bishop moves
Generate_White_Queen_Moves();//Generates White Queen moves
MakeWhiteMove();//Plays White's moves out on the internal bitboards
Generate_Black_Knight_Moves();//Generates Black Knight moves
Generate_Black_King_Moves();//Generates Black King moves
Generate_Black_Pawn_Moves();//Generates Black Pawn moves
Generate_Black_Rook_Moves();//Generates Black Rook moves
Generate_Black_Bishop_Moves();//Generates Black Bishop moves
Generate_Black_Queen_Moves();//Generates Black Queen moves
MakeBlackMove();//Plays Black's moves out on the internal bitboards
}

//So that we can see the reult
    char f;
    cin >> f;

    return 0;

}
         
    

         
    
