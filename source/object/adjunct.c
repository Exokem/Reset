
#include "adjunct.h"

#include "cut.h"

Adjunct adjunctInst ( double x, double y, double z, double limit )
{
	Adjunct iinst ( adjunct, adjunct_s );

	nlcknl ( adjunct );

	adjunct -> motion_x = 0;

	adjunct -> mass = 1; // kg

	adjunct -> pos_x = x;
	adjunct -> vel_x = 0;
	adjunct -> acc_x = 0;
	adjunct -> force_x = 0;

	adjunct -> y = y;

	adjunct -> pos_z = z;
	adjunct -> vel_z = 0;
	adjunct -> acc_z = 0;
	adjunct -> force_z = GRAVITY * adjunct -> mass;

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
		for ( size_t ix = 0; ix < adjunct -> links; ix ++ )
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

	double dz = adj -> vel_z * TIME_SCALE;
	double dvz = adj -> acc_z * TIME_SCALE;

	adj -> pos_z += dz;
	adj -> vel_z += dvz;

	adj -> vel_z = min ( adj -> vel_z, TERMINAL );
	adj -> pos_z = min ( adj -> pos_z, WIN_VT );

	double dx = adj -> vel_x * TIME_SCALE; // Delta x
	double dvx = adj -> acc_x * TIME_SCALE; // Delta v in the x direction
	double fx = - adj -> motion_x * FRICTION * TIME_SCALE;

	double vx = adj -> vel_x + dvx;

	if ( vx == 0 ) fx = 0;

	if ( 0 < vx && vx + fx < 0 ) vx = 0;
	else if ( vx < 0 && 0 < vx + fx ) vx = 0;
	else vx += fx;

	printf ( "velocity: %f\nacceleration: %f\nfriction: %f\n", adj -> vel_x, dvx, fx );

	adj -> pos_x += dx;
	adj -> vel_x = vx;

	nullck ( adj -> desc );

	foreach ( adj -> desc, adj -> links )
	{
		Adjunct next = adj -> desc[ ix ];
		
		if ( next )
		{
			adjunctMove ( next );
		}
	}
}

void adjSetAcceleration ( Adjunct adj, Vecdir vd, double acc )
{
	nullck ( adj );

	if ( 0 < adj -> vel_x ) adj -> motion_x = 1;
	else if ( adj -> vel_x < 0 ) adj -> motion_x = -1;

	// double friction = ndx * FRICTION;

	adj -> acc_x = vd.vx * acc;
	adj -> acc_z = ( vd.vz * acc ) + GRAVITY;

	// if ( MAX_VX <= adj -> vx ) adj -> ax = friction;
}

void adjSetForce ( Adjunct adj, Vecdir vd, double force )
{
	adj -> force_x = vd.vx * force;
	adj -> force_z = vd.vz * force;
}

static void moveTowards ( Adjunct adjDest, Adjunct adj )
{

}

double adjunctDistance ( Adjunct adj1, Adjunct adj2 )
{
	nulret ( adj1, 0.0 );
	nulret ( adj2, 0.0 );

	double dx = ( double ) adj1 -> pos_x - ( double ) adj2 -> pos_x;
	double dy = ( double ) adj1 -> y - ( double ) adj2 -> y;
	double dz = ( double ) adj1 -> pos_z - ( double ) adj2 -> pos_z;

	return pow ( ( pow ( dx, 2 ) + pow ( dy, 2 ) + pow ( dz, 2 ) ), 0.5 );
}