
#include "adjunct.h"

#include "cut.h"

Adjunct adjunctInst ( double x, double y, double z, double limit )
{
	Adjunct iinst ( adjunct, adjunct_s );

	nlcknl ( adjunct );

	adjunct -> x = x;
	adjunct -> vx = 0;
	adjunct -> ax = 0;

	adjunct -> y = y;

	adjunct -> z = z;
	adjunct -> vz = 0;
	adjunct -> az = GRAVITY;

	adjunct -> limit = limit;

	adjunct -> links = 0;

	sizeinst ( adjunct -> desc, adjunct_s, adjunct -> links );

	return adjunct;
}

void adjunctLink ( Adjunct adj, double x, double y, double z, double limit )
{
	nullck ( adj );

	Adjunct nlinst ( next, adjunctInst ( x, y, z, limit ) );

	nullck ( next );

	Adjunct * desc = adj -> desc;

	if ( desc == NULL )
	{
		adjunctClr ( next );
		return;
	}

	adj -> links ++;

	eqact ( desc, NULL, sizeinst ( desc, adjunct_s, adj -> links ) )

	else
	{
		Adjunct * tmp = realloc ( desc, adj -> links );
		neqact ( tmp, NULL, desc = tmp )
	}

	desc[ adj -> links - 1 ] = next;
	adj -> desc = desc;
}

void adjunctClr ( Adjunct adjunct )
{
	nullck ( adjunct );

	if ( adjunct -> desc != NULL )
	{
		for ( int ix = 0; ix < adjunct -> links; ix ++ )
		{
			adjunctClr ( adjunct -> desc[ ix ] );
		}

		free ( adjunct -> desc );
	}

	free ( adjunct );
}

void adjunctMove ( Adjunct adj )
{
	nullck ( adj );

	double dz = adj -> vz * TIME_SCALE;
	double dvz = adj -> az * TIME_SCALE;

	adj -> z += dz;
	adj -> vz += dvz;

	adj -> vz = min ( adj -> vz, TERMINAL );
	adj -> z = min ( adj -> z, WIN_VT );

	double dx = adj -> vx * TIME_SCALE; // Delta x
	double dvx = adj -> ax * TIME_SCALE; // Delta v in the x direction

	adj -> x += dx;
	adj -> vx += dvx;
}

void adjSetAcceleration ( Adjunct adj, Vecdir vd, double acc )
{
	nullck ( adj );

	int ndx = 0;

	if ( 0 < adj -> vx ) ndx = -1;
	else if ( adj -> vx < 0 ) ndx = 1;

	double friction = ndx * FRICTION;

	adj -> ax = ( vd.vx * acc ) + friction;
	adj -> az = ( vd.vz * acc ) + GRAVITY;
}

void adjunctDirect ( Adjunct adj, Vecdir vd, float dist )
{
	nullck ( adj );

	int dx = ( int ) ( vd.vx * dist );
	int dy = ( int ) ( vd.vy * dist );
	int dz = ( int ) ( vd.vz * dist );

	adj -> x += dx;
	adj -> y += dy;
	adj -> z += dz;

	nullck ( adj -> desc );

	foreach ( adj -> desc, adj -> links )
	{
		adjunctDirect ( adj -> desc[ ix ], vd, dist );
	}
}

static void moveTowards ( Adjunct adjDest, Adjunct adj )
{

}

double adjunctDistance ( Adjunct adj1, Adjunct adj2 )
{
	nulret ( adj1, 0.0 );
	nulret ( adj2, 0.0 );

	double dx = ( double ) adj1 -> x - ( double ) adj2 -> x;
	double dy = ( double ) adj1 -> y - ( double ) adj2 -> y;
	double dz = ( double ) adj1 -> z - ( double ) adj2 -> z;

	return pow ( ( pow ( dx, 2 ) + pow ( dy, 2 ) + pow ( dz, 2 ) ), 0.5 );
}