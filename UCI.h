#ifndef UCI_H_INCLUDED
#define UCI_H_INCLUDED
using namespace std;
#include <fstream>
#include "Search.h"
extern ofstream Log;
extern int CheckUci();
int MakeMove(Move&);
int Moves_Command();
int Parse_Moves(string First_Part, string Second_Part, string Promotion_Type);
int Parse_Moves(string First_Part, string Second_Part);
int Read_Fen(char Current_Square);
extern Bitboard Current_Rank;
extern string UciCommand;

#endif
