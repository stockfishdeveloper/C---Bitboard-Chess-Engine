using namespace std;
#include "Zobrist.h"
#include "magicmoves.c"//Pradu's Magic Bitboards
#include "UCI.h"

int main()
{
    initmagicmoves();//Thanks, Pradu
    Engine_Info();
    cout << "\nA chess engine by David Cimbalista\nCopyright (c) 2015" << endl;
    CheckUci(); //Main command loop
    return 0;
}


