using namespace std;
#include <cstdlib>//For random move generation
#include <ctime>//For random move generation
#include <iostream>
#include <fstream>//For writing the game to a text file
ofstream Log("Log.txt");
bool Current_Turn = true;
bool White_Turn = true;
#include "magicmoves.c"//Pradu's Magic Bitboards
#include "Bitboard.h"
#include "MoveGen.h"
#include "MakeMove.h"
#include "UCI.h"

int main()
{
initmagicmoves();//Thanks, Pradu
CheckUci();


    return 0;

}
         
    
