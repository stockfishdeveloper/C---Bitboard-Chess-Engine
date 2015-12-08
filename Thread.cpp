#include "tinythread.h"
#include "Search.h"
#include "Thread.h"
#include "UCI.h"
#include <chrono>
#include <iostream>
#include <windows.h>

using namespace std;
using namespace tthread;

int nodes = 0;
int movenum = 0;
bool turn = false;
int f;
// This is the child thread function

void Runthread(void * aArg)
{
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();

  while(Searching)
  {
  	LINE pvline = PVline;
  	cout << "info multipv 1 depth " << Depth << " seldepth " << Seldepth << " score cp " << pvline.score * 100 << " pv ";
  	Log << "<< " << "info multipv 1 depth " << Depth << " seldepth " << Seldepth << " score cp " << pvline.score * 100 << " pv ";
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
 	float temporary = (Nodes / d.count());
 	
    cout << "time " << d.count() << " nodes " << Nodes << " nps " << (1000 *(Nodes / (d.count() + 1))) << endl;
    Log << "time " << d.count() << " nodes " << Nodes << " nps " << (1000 *(Nodes / (d.count() + 1))) << endl;
    if(d.count() >= (Time_Allocation / 20))
    {
    	STOP_SEARCHING_NOW = true;
	}
    Sleep(500);
  } 
}
