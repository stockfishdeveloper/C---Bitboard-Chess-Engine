using namespace std;
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
ofstream Dave("Rest.txt");
#include "magicmoves.c"
#include "Bitboard.h"
#include "MoveGen.h"
#include "MakeMove.h"

int main()
{
   
/*********************************REMEMBER! Create a function that after generating all types of moves uses a for loop to delete the Move_Stack! *****/
initmagicmoves();

while(true)
{
Generate_White_Knight_Moves();
Generate_White_King_Moves();
Generate_White_Pawn_Moves();
Generate_White_Rook_Moves();
Generate_White_Bishop_Moves();
Generate_White_Queen_Moves();
MakeWhiteMove();
Generate_Black_Knight_Moves();
Generate_Black_King_Moves();
Generate_Black_Pawn_Moves();
Generate_Black_Rook_Moves();
Generate_Black_Bishop_Moves();
Generate_Black_Queen_Moves();
MakeBlackMove();




//Dave << Black_Knights << endl;
//Dave << White_Knights << endl;
}

//cout << White_Pieces << endl;
//cout << Black_Pieces << endl;


    char f;
    cin >> f;

    return 0;

}
         
    
