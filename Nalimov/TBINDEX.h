#ifndef TBINDEX_H_
#define TBINDEX_H_
#define NEW
#define T41_INCLUDE
#define T33_INCLUDE
int IInitializeTb(const char *pszPath);
int IDescFindFromCounters(int *); 
int PfnIndCalcFun(int iTb, int side); 
int TbtProbeTable(int iTb, int side, unsigned long indOffset);
#endif
