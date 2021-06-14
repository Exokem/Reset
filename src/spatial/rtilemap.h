
/// rtilemap.h
///
/// Provides structures and functions suited to the management of tile based displays.

#ifndef _RTILEMAP_H
#define _RTILEMAP_H

#include "depn.h"
#include "rvector.h"
#include "rrcon.h"

// Default X dimension for static tilemaps.
#ifndef DEFAULT_SRTILEMAP_XDIM
#define DEFAULT_SRTILEMAP_XDIM 255
#endif // DEFAULT_RTILEMAP_XDIM

// Default Y dimension for static tilemaps.
#ifndef DEFAULT_SRTILEMAP_YDIM
#define DEFAULT_SRTILEMAP_YDIM 255
#endif // DEFAULT_RTILEMAP_YDIM

/// rtile_s
///
/// The data container for individual tiles in a tilemap.

typedef struct rtile_s
{
    char rkey [ RRCON_MAX_KEY + 1 ]; ///< The resource key for the tile graphic.
} * RTILE;

/// rtilemap_s
///
/// The data container for tilemaps. Tilemaps can be sized dynamically or statically.
/// All static tilemaps will have the same dimensions, but dynamic tilemaps may each
/// have unique dimensions.

typedef struct rtilemap_s
{
    size_t xdim, ydim; ///< Horizontal and vertical dimensions of the tilemap.
    int dynamic; ///< State indicator for whether the tilemap is dynamic or static.

    union tiles
    {
        RTILE st [ DEFAULT_SRTILEMAP_XDIM ] [ DEFAULT_SRTILEMAP_YDIM ]; ///< Static tile container.
        RTILE * dy; ///< Dynamic tile container.
    } tiles;

} * RTILEMAP;

/// rtilemap_dynamic
///
/// Produces a dynamic RTILEMAP with the specified horizontal and vertical dimensions.
/// All tile indices are initialized to NULL pointers.
///
/// @param The horizontal dimension of the RTILEMAP.
/// @param The vertical dimension of the RTILEMAP.
///
/// @return A dynamic RTILEMAP with unique dimensions.

RTILEMAP rtilemap_dynamic ( size_t, size_t );

/// rtilemap_static
///
/// Produces a static RTILEMAP with horizontal and vertical dimensions specified by
/// DEFAULT_SRTILEMAP_XDIM and DEFAULT_SRTILEMAP_YDIM, respectively.
/// All tile indices are initialized to NULL pointers.
///
/// @return A static RTILEMAP.

RTILEMAP rtilemap_static ( void );

/// rtile_inst
///
/// Produces an RTILE instance with the provided resource key.
/// Resource keys are assumed to be valid.
///
/// @param The resource key to be associated with the tile.
///
/// @return A new RTILE instance.

RTILE rtile_inst ( char * );

/// rtilemap_tile
///
/// Provides the RTILE at a specific coordinate in the provided RTILEMAP.
/// A NULL pointer may be returned when a tile has not been placed at the location
/// parametrically specified.
///
/// @param The RTILEMAP to receive the location query.
/// @param The VEC2I instance representing the location query.
///
/// @return A NULLABLE RTILE representing the located or empty tile.

RTILE rtilemap_tile ( RTILEMAP, VEC2I );

/// rtilemap_set
///
/// Updates the RTILE at a specific location in the provided RTILEMAP.
/// The RTILEMAP provided may not be NULL, but the RTILE provided is NULLABLE.
/// The values possessed by VEC2I must be within the bounds of the RTILEMAP.
/// This function will return the RTILE that has been replaced.
///
/// @param The RTILEMAP to update.
/// @param The RTILE replacing an existing RTILE.
/// @param The VEC2I representing the location of the RTILE to be replaced.
///
/// @return The RTILE previously located in the updated space.

RTILE rtilemap_set ( RTILEMAP, RTILE, VEC2I );

/// rtilemap_clr
///
/// Clears the contents of a provided RTILEMAP from active memory. This includes the
/// contents of all RTILE instances that a particular RTILEMAP contains.
///
/// @param The RTILEMAP to be cleared from memory.

void rtilemap_clr ( RTILEMAP );

#endif // _RTILEMAP_H
