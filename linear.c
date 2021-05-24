
#include "linear.h"
#include "cut.h"

float distance ( Adjunct adj1, Adjunct adj2 )
{
	nullck ( adj1 );
	nullck ( adj2 );

	float dx = adj1 -> x - adj2 -> x;
	float dy = adj1 -> y - adj2 -> y;
	float dz = adj1 -> z - adj2 -> z;

	return pow ( ( pow ( dx, 2 ) + pow ( dy, 2 ) + pow ( dz, 2 ) ), 0.5 );
}