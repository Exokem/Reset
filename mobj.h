
#include "root.h"

typedef enum 
{
	DIR_NY,     ///< Negative Y
	DIR_PY,     ///< Positive Y
	DIR_NX,     ///< Negative X
	DIR_PX,     ///< Positive X
	DIR_AXIS_X, ///< Horizontal Axis
	DIR_AXIS_Y, ///< Vertical Axis
	DIR_AL      ///< All Directions
} Direction;

typedef struct 
{
	Direction dir;
	SDL_Surface * img;

} * ImageMapping;

typedef struct 
{
	int motive;
	ImageMapping * mappings;
} * Mobj;