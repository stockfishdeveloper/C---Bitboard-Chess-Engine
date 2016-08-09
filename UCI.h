#ifndef UCI_H_INCLUDED
#define UCI_H_INCLUDED
using namespace std;
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <iostream>
#include "Search.h"
#include <chrono>
extern LINE PVline;
extern ofstream Log;
extern int CheckUci();
//extern int Compute_Time(auto before, auto after);
int MakeMove(Move&);
int Moves_Command();
int Parse_Moves(string First_Part, string Second_Part, string Promotion_Type);
int Parse_Moves(string First_Part, string Second_Part);
int Read_Fen(char Current_Square);
extern Bitboard Current_Rank;
extern string UciCommand;
extern int Time_Usage;
extern string Engine_Info();
void Uci_Pv(int depth, int seldepth, Move best, int* matemoves, int time, int nodes);
#endif
