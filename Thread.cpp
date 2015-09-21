#include "tinythread.h"
#include "Thread.h"
#include "Search.h"
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
  while(!Done_Searching)
  {
      cout << "info nodes " << Nodes <<  endl;
      Sleep(100);
  } 
}
