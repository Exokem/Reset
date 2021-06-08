
#ifndef _MOBJ_H
#define _MOBJ_H

#include <SDL2/SDL.h>

#include "root.h"
#include "map.h"

#define SREC( mrec ) SDL_Rect ( mrec -> x, mrec -> y, mrec -> w, mrec -> h );

#define IDN_LIM 16
#define DIR_CRD 7

typedef enum 
{
	DIR_DV,     ///< Decreasing Vertical
	DIR_IV,     ///< Increasing Vertical
	DIR_DH,     ///< Decreasing Horizontal
	DIR_IH,     ///< Increasing Horizontal
	DIR_AXIS_H, ///< Horizontal Axis
	DIR_AXIS_V, ///< Vertical Axis
	DIR_AL      ///< All Directions
} Direction;

typedef struct mobj_s
{
	//int motive;          ///< Motive status - is this mobj movable.
	Direction ornt;      ///< Orientation direction.
	char idn[ IDN_LIM ]; ///< Identifier, limited to 16 characters.
	SDL_Rect rec;        ///< Bounding rectangle.
	HashMap mappings;    ///< Directional surface resource bindings.
} * Mobj;

/// <summary>
///		
/// </summary>
/// <param name="idn">The 16-character ( maximum ) identifier for the mobj.</param>
/// <param name="rec">The rectangular collision box for the mobj.</param>
/// <param name="binder">
///		The directional surface resource binder for this mobj. This function is responsible for
///		providing resource surfaces when provided a resource identifier.
/// </param>

Mobj mobjInst ( char idn[ IDN_LIM ], SDL_Rect rec, Root root );

void mobjClr ( Mobj mobj );

#endif