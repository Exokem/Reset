
#ifndef _ADJUNCT_H
#define _ADJUNCT_H

#include "vecdir.h"
#include "linear.h"
#include "options.h"

typedef struct adjunct_s
{
	double x; ///< Horizontal
	double vx; ///< Horizontal Velocity
	double ax; ///< Horizontal Acceleration

	double y; ///< Depth

	double z; ///< Vertical
	double vz; ///< Vertical Velocity
	double az; ///< Vertical Acceleration
	double limit;
	size_t links;
	struct adjunct_s ** desc;
} * Adjunct;

Adjunct adjunctInst ( double, double, double, double );

void adjunctLink ( Adjunct, double, double, double, double );

void adjunctClr ( Adjunct );

void adjunctDirect ( Adjunct, Vecdir, float );

void adjunctMove ( Adjunct );

void adjSetAcceleration ( Adjunct, Vecdir, double );

double adjunctDistance ( Adjunct, Adjunct );

#endif