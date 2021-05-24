
#ifndef _LINEAR_H
#define _LINEAR_H

#include <math.h>

#include "adjunct.h"

#define adjdx( adj1, adj2 ) adj1 -> x - adj2 -> x
#define adjdy( adj1, adj2 ) adj1 -> y - adj2 -> y
#define adjdz( adj1, adj2 ) adj1 -> z - adj2 -> z

#define max3( a, b, c ) max ( a, max ( b, c ) )

float distance ( Adjunct, Adjunct );

#endif