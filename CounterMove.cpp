#include "CounterMove.h"
int CounterMove[30][64][64];
void InitCounterMove() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 64; j++) {
			for (int k = 0; k < 64; k++) {
				CounterMove[i][j][k] = 0;
			}
		}
	}
}
