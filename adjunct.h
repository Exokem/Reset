
#ifndef _ADJUNCT_H
#define _ADJUNCT_H

#include "vecdir.h"

typedef struct adjunct_s
{
	int x; ///< Horizontal
	int y; ///< Depth
	int z; ///< Vertical
	float limit;
	size_t links;
	struct adjunct_s ** desc;
} * Adjunct;

Adjunct adjunctInst ( int, int, int, float );

void adjunctLink ( Adjunct, int, int, int, float );

void adjunctClr ( Adjunct );

void adjunctMove ( Adjunct, Vecdir, float );

#endif