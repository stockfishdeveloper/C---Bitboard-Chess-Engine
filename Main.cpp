using namespace std;
#include <iostream>
#include "magicmoves.c"//Pradu's Magic Bitboards
#include "UCI.h"

int main()
	{
		initmagicmoves();//Thanks, Pradu 
		cout << "Chess, a chess engine by\nDavid Cimbalista\nCopyright (c) 2015" << endl;
		CheckUci(); //Main command loop
    	return 0;
	}
         
