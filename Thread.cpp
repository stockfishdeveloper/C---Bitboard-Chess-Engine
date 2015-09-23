#include "tinythread.h"
#include "Thread.h"
#include "Search.h"
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

  while(!Done_Searching)
  {
  	auto t1 = Time::now();
  	fsec fs = t1 - t0;
  	ms d = std::chrono::duration_cast<ms>(fs);    
 	float temporary = (Nodes / d.count());
 	
    cout << "info time " << d.count() << " nodes " << Nodes << " nps " << (1000 *(Nodes / (d.count() + 1))) << endl;
    Sleep(1000);
  } 
}
