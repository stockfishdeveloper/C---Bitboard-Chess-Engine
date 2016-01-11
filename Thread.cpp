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

void Runthread(void * aArg)
{
	Timer timer;
	timer.Start_Clock();
	while(Search::Searching)
  {
  	//Before copying the LINE we want to make sure we do not copy the LINE with corrupted data
  	//We must use a mutex
  	output.lock();
  	int depth = Search::Depth;
  	int seldepth = Search::Seldepth;
  	int nodes = Search::Nodes;
  	int time_allocation = Search::Time_Allocation;
  	LINE pvline = PVline;
  	output.unlock();
  	
  	cout << "info multipv 1 depth " << depth << " seldepth " << seldepth << " score cp " << pvline.score << " pv ";
  	Log << "<< " << "info multipv 1 depth " << depth << " seldepth " << seldepth << " score cp " << pvline.score << " pv ";
  	for(int i = 0; i < pvline.cmove; i++)
    {
    	for( int h = 0; h < 20; h++)
			{
        	if(GeneralBoard[h] & pvline.argmove[i].From)
        	{
        	cout << PlayerMoves[h];
        	Log << PlayerMoves[h];
        	}
        }
        	for( int h = 0; h < 20; h++)
        {
        	if(GeneralBoard[h] & pvline.argmove[i].To)
        	{
        	cout << PlayerMoves[h] << " ";
        	Log << PlayerMoves[h] << " ";
        	}
		}
	}
  	 	
    cout << "time " << timer.Stop_Clock() << " nodes " << nodes << " nps " << (1000 *(nodes / (timer.Stop_Clock() + 1))) << endl;
    Log << "time " << timer.Stop_Clock() << " nodes " << nodes << " nps " << (1000 *(nodes / (timer.Stop_Clock() + 1))) << endl;
    if(timer.Stop_Clock() >= (time_allocation / 20))
    {
    	Search::STOP_SEARCHING_NOW = true;
    	return;
	}
    Sleep(500);
  } 
}
