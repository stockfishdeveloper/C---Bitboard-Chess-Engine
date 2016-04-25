using namespace std;
#include "TransTable.h"
#include <iostream>
#include "magicmoves.c"//Pradu's Magic Bitboards
#include "UCI.h"

int main()
{
    initmagicmoves();//Thanks, Pradu
    cout << Engine_Info();
    cout << "\nA chess engine by David Cimbalista\nCopyright (c) 2015" << endl;
    //Init_Zobrist();
    #include "Nalimov\TBINDEX.h"
    char* f = "c:\\Tablebases";
    //cout << IInitializeTb(f) << endl;
    CheckUci(); //Main command loop
    return 0;
}


