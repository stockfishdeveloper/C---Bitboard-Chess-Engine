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
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();

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
  	auto t1 = Time::now();
  	fsec fs = t1 - t0;
  	ms d = std::chrono::duration_cast<ms>(fs);    
 	 	
    cout << "time " << d.count() << " nodes " << nodes << " nps " << (1000 *(nodes / (d.count() + 1))) << endl;
    Log << "time " << d.count() << " nodes " << nodes << " nps " << (1000 *(nodes / (d.count() + 1))) << endl;
    if(d.count() >= (time_allocation / 20))
    {
    	Search::STOP_SEARCHING_NOW = true;
    	return;
	}
    Sleep(500);
  } 
}
