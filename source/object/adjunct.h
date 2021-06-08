
#ifndef _ADJUNCT_H
#define _ADJUNCT_H

#include "vecdir.h"
#include "linear.h"
#include "options.h"

typedef struct adjunct_s
{
	int motion_x;

	double mass;

	double pos_x; ///< Horizontal
	double vel_x; ///< Horizontal Velocity
	double acc_x; ///< Horizontal Acceleration
	double force_x; ///< Horizontal Net Force

	double y; ///< Depth

	double pos_z; ///< Vertical
	double vel_z; ///< Vertical Velocity
	double acc_z; ///< Vertical Acceleration
	double force_z; ///< Vertical Net Force
	double limit;

	size_t links;

	struct adjunct_s ** desc;
} * Adjunct;

Adjunct adjunctInst ( double, double, double, double );

void adjunctLink ( Adjunct, double, double, double, double );

void adjunctClr ( Adjunct );

void adjunctMove ( Adjunct );

void adjSetAcceleration ( Adjunct, Vecdir, double );

void adjSetForce ( Adjunct, Vecdir, double );

double adjunctDistance ( Adjunct, Adjunct );

#endif