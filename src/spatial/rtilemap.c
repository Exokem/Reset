
#include "rtilemap.h"

/// linearize_vector
///
/// Converts a two-dimensional vector position into a linear coordinate based on the
/// dimensions of a known RTILEMAP.
///
/// @param vector   The VEC2I to be linearized.
/// @param tilemap  The RTILEMAP used as the basis for linearization.
///
/// @return The linear index produced.

static size_t linearize_vector ( RTILEMAP tilemap, VEC2U vector )
{
    retnulv ( tilemap, 0 );

    return vector.b + ( vector.a * tilemap -> xdim );
}

static VEC2U delinearize_vector ( RTILEMAP tilemap, size_t index )
{
    return ( VEC2U ) { .b = index % tilemap -> xdim, .a = ( int ) ( index / tilemap -> xdim ) };
}

/// Dynamic RTILEMAPs may be simply resized without affecting their content. If the
/// goal would involve a shift rather than simple expansion ( expanding outwards in
/// all directions versus the two frontier directions ), the process is more complex.

RTILEMAP rtilemap_dynamic ( size_t xdim, size_t ydim )
{
    RTILEMAP tilemap = inst ( rtilemap_s );

    retnulv ( tilemap, NULL );

    tilemap -> dynamic = 1;

    tilemap -> xdim = xdim;
    tilemap -> ydim = ydim;

    size_t size = xdim * ydim;

    tilemap -> size = size;
    tilemap -> tiles.dy = minst ( rtile_s, size );

    retnulv ( tilemap -> tiles.dy, NULL );

    fori ( size )
    {
        tilemap -> tiles.dy [ ix ] = NULL;
    }

    return tilemap;
}

/// Static RTILEMAPs cannot be resized, and will all occupy the same dimensions.

RTILEMAP rtilemap_static ( void )
{
    RTILEMAP tilemap = inst ( rtilemap_s );
    retnulv ( tilemap, NULL );

    tilemap -> dynamic = 0;
    tilemap -> xdim = DEFAULT_SRTILEMAP_XDIM;
    tilemap -> ydim = DEFAULT_SRTILEMAP_YDIM;
    tilemap -> tiles.dy = NULL;
    tilemap -> size = tilemap -> xdim * tilemap -> ydim;

    forv ( tilemap -> xdim, ix ) forv ( tilemap -> ydim, iy )
    {
        tilemap -> tiles.st [ ix ] [ iy ] = NULL;
    }

    return tilemap;
}

/// RTILE instances can be created using unregistered resource keys.

RTILE rtile_inst ( char * key )
{
    RTILE tile = inst ( rtile_s );
    retnulv ( tile, NULL );

    strncpy ( tile -> rkey, key, RRCON_MAX_KEY );

    return tile;
}

/// NULL is returned for empty tiles, NULL RTILEMAPs, and out-of-bounds vectors.

RTILE rtilemap_tile ( RTILEMAP tilemap, VEC2U vector )
{
    retnulv ( tilemap, NULL );

    if ( tilemap -> xdim <= vector.a || tilemap -> ydim <= vector.b ) return NULL;

    if ( tilemap -> dynamic )
    {
        RTILE * dynamics = tilemap -> tiles.dy;
        retnulv ( dynamics, NULL );

        size_t index = linearize_vector ( tilemap, vector );
        return dynamics [ index ];
    }

    else
    {
        return tilemap -> tiles.st [ vector.a ] [ vector.b ];
    }
}

/// NULL is returned for replacements of empty spaces, out-of-bounds vectors, and NULL
/// dynamic tile containers.

RTILE rtilemap_set ( RTILEMAP tilemap, RTILE tile, VEC2U vector )
{
    retnulv ( tilemap, NULL );

    if ( tilemap -> xdim <= vector.a || tilemap -> ydim <= vector.b ) return NULL;

    RTILE removed;

    if ( tilemap -> dynamic )
    {
        RTILE * dynamics = tilemap -> tiles.dy;
        retnulv ( dynamics, NULL );

        size_t index = linearize_vector ( tilemap, vector );
        removed = dynamics [ index ];
        dynamics [ index ] = tile;
    }

    else
    {
        removed = tilemap -> tiles.st [ vector.a ] [ vector.b ];
        tilemap -> tiles.st [ vector.a ] [ vector.b ] = tile;
    }

    return removed;
}

void rtilemap_render_tiles ( RTILEMAP tilemap, RRCON rrcon, VEC2I start, double scale )
{
    retnul ( tilemap );
    retnul ( rrcon );
    retnul ( rrcon -> renderer );

    int tiledim = ( int ) ( ( double ) DEFAULT_RTILEMAP_TILEDIM * scale );

    forv ( tilemap -> xdim, ix ) forv ( tilemap -> ydim, iy )
    {
        RTILE tile = NULL;
        VEC2U vec = { ix, iy };

        if ( !tilemap -> dynamic )
        {
            tile = tilemap -> tiles.st [ ix ] [ iy ];
        }

        else if ( tilemap -> tiles.dy )
        {
            size_t index = linearize_vector ( tilemap, vec );
            tile = tilemap -> tiles.dy [ index ];
        }

        ifnnul ( tile )
        {
            SDL_Texture * texture = rrcon_retrieve ( rrcon, tile -> rkey );

            ifnnul ( texture )
            {
                SDL_Rect dest =
                {
                    start.a + ( int ) ( vec.a * tiledim ),
                    start.b + ( int ) ( vec.b * tiledim ),
                    tiledim, tiledim
                };

                SDL_RenderCopy ( rrcon -> renderer, texture, NULL, &dest );
            }
        }
    }
}

/// While the RTILEMAP is cleared, its RTILEs are set to NULL to account for cases
/// where multiple RTILEMAPs might share RTILE instances.

void rtilemap_clr ( RTILEMAP tilemap )
{
    retnul ( tilemap );

    size_t size = tilemap -> xdim * tilemap -> ydim;

    RTILE tile = NULL;

    if ( tilemap -> dynamic )
    {
        RTILE * dynamics = tilemap -> tiles.dy;

        if ( dynamics )
        {
            fori ( size )
            {
                tile = dynamics [ ix ];

                if ( tile ) free ( tile );
                tile = NULL;
            }

            free ( dynamics );
        }
    }

    else
    {
        forv ( tilemap -> xdim, ix ) forv ( tilemap -> ydim, iy )
        {
            tile = tilemap -> tiles.st [ ix ] [ iy ];

            if ( tile ) free ( tile );
        }
    }

    free ( tilemap );
    tilemap = NULL;
}
