
#ifndef _PLANE_H
#define _PLANE_H

#include <stdlib.h>

#include "map.h"
#include "mobj.h"

typedef struct objset_s
{
	int volume;
	Mobj * objects;
} * Objset;

/// <summary>
/// The plane_s structure outlines a distinct layer in the program display.
/// 
/// Each plane has a certain depth field, which denotes how many distinct object display priorities
/// it contains. The object sets are stored in the objsets map, which indexes them against their
/// display priorities.
/// </summary>
typedef struct plane_s
{
	int depth; ///< The depth of a Plane ( how many object layers it contains ).
	HashMap objsets; ///< The map linking each object set to its priority.
} * Plane;

Plane planeInst ( int depth );

void planeClr ( Plane plane );

void placeObj ( Plane plane, Mobj mobj, int priority );

void objSetClr ( Objset objset );

#endif