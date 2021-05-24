
#include "adjunct.h"
#include "linear.h"
#include "cut.h"

Adjunct adjunctInst ( int x, int y, int z, float limit )
{
	Adjunct iinst ( adjunct, adjunct_s );

	nlcknl ( adjunct );

	adjunct -> x = x;
	adjunct -> y = y;
	adjunct -> z = z;
	adjunct -> limit = limit;

	adjunct -> links = 0;

	sizeinst ( adjunct -> desc, adjunct_s, adjunct -> links );

	return adjunct;
}

void adjunctLink ( Adjunct adj, int x, int y, int z, float limit )
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

void adjunctMove ( Adjunct adj, Vecdir vd, float dist )
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
		adjunctMove ( adj -> desc[ ix ], vd, dist );
	}
}

static void moveTowards ( Adjunct adjDest, Adjunct adj )
{

}