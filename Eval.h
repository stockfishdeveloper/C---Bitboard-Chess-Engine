#ifndef _Eval_H_Included_
#define _Eval_H_Included_
#include "Position.h"
namespace Eval
{
const int Evaluate_Position(Position* position);
int Lazy_Eval(Position* position);
extern const int WNpsqt[64];
extern const int BNpsqt[64];
extern const int WPpsqt[64];
extern const int BPpsqt[64];
extern const int WKpsqt[64];
extern const int BKpsqt[64];
extern const int WBpsqt[64];
extern const int BBpsqt[64];
}
#endif
