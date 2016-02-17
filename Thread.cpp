#include "Search.h"
#include "Thread.h"
#include "UCI.h"
#include <chrono>
#include <iostream>
#include <windows.h>

using namespace std;

int nodes = 0;
int movenum = 0;
bool turn = false;
int f;
mutex output;
// This is the child thread function
LINE pvline;
void Runthread(void * aArg)
{
    Timer timer;
    timer.Start_Clock();
    while(Search::Searching)
    {
        //Before copying the LINE we want to make sure we do not copy the LINE with corrupted data
        //We must use a mutex
        /*if(Search::Output_Pv == true)
        {
        output.lock();
        int depth = Search::Depth;
        int seldepth = Search::Seldepth;
        int nodes = Search::Nodes;
        int time_allocation = Search::Time_Allocation;
        pvline = ::PVline;
        cout << "info multipv 1 depth " << depth << " seldepth " << seldepth << " score cp " << pvline.score << " pv ";
        Log << "<< " << "info multipv 1 depth " << depth << " seldepth " << seldepth << " score cp " << pvline.score << " pv ";
        for(int i = 0; i < pvline.cmove; i++)
        {
        	for( int h = 0; h < 64; h++)
        		{
            	if(GeneralBoard[h] & pvline.argmove[i].From)
            	{
            	cout << PlayerMoves[h];
            	Log << PlayerMoves[h];
            	}
            }
            	for( int h = 0; h < 64; h++)
            {
            	if(GeneralBoard[h] & pvline.argmove[i].To)
            	{
            	cout << PlayerMoves[h] << " ";
            	Log << PlayerMoves[h] << " ";
            	}
        	}
        }

        cout << " time " << timer.Get_Time() << " nodes " << nodes << " nps " << (1000 *(nodes / (timer.Get_Time() + 1))) << endl;
        Log << " time " << timer.Get_Time() << " nodes " << nodes << " nps " << (1000 *(nodes / (timer.Get_Time() + 1))) << endl;
        output.unlock();
        }*/
        if(timer.Get_Time() >= (Search::Time_Allocation / 30))
        {
            Search::STOP_SEARCHING_NOW = true;
            return;
        }
        //Sleep(500);
    }
}
