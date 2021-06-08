
#ifndef _LINEAR_H
#define _LINEAR_H

#include <math.h>

#define GRAVITY 10.0
#define TERMINAL 70.0
#define TIME_SCALE 0.006
#define FRICTION 2.0
#define MAX_VX 15.0

#define adjdx( adj1, adj2 ) adj1 -> x - adj2 -> x
#define adjdy( adj1, adj2 ) adj1 -> y - adj2 -> y
#define adjdz( adj1, adj2 ) adj1 -> z - adj2 -> z

#define max3( a, b, c ) max ( a, max ( b, c ) )

#endif