
#include "rlevel.h"

RLEVEL rlevel_inst ( size_t levels )
{
    RLEVEL level = inst ( rlevel_s );

    retnulv ( level, NULL );

    level -> levels = levels;
    level -> level_set = minst ( rtilemap_s, levels );

    ifnul ( level -> level_set )
    {
        free ( level );
        return NULL;
    }

    fori ( levels ) level -> level_set [ ix ] = NULL;

    return level;
}

RTILEMAP rlevel_tilemap ( RLEVEL level, size_t index )
{
    retnulv ( level, NULL );
    if ( level -> levels <= index ) return NULL;

    return level -> level_set [ index ];
}

RTILE rlevel_tile ( RLEVEL level, size_t index, VEC2U vector )
{
    retnulv ( level, NULL );

    RTILEMAP tilemap = rlevel_tilemap ( level, index );
    retnulv ( level, NULL );

    return rtilemap_tile ( tilemap, vector );
}

RTILE rlevel_set ( RLEVEL level, size_t index, RTILE tile, VEC2U vector )
{
    retnulv ( level, NULL );

    RTILEMAP tilemap = rlevel_tilemap ( level, index );

    retnulv ( tilemap, NULL );

    RTILE prev = rlevel_tile ( level, index, vector );

    rtilemap_set ( tilemap, tile, vector );

    return prev;
}

void rlevel_render_levels ( RLEVEL level, RRCON rrcon, VEC2I offset, double scale )
{
    retnul ( level );
    retnul ( rrcon );

    fori ( level -> levels )
    {
        rtilemap_render_tiles ( level -> level_set [ ix ], rrcon, offset, scale );
    }
}

void rlevel_clr ( RLEVEL level )
{
    retnul ( level );

    ifnnul ( level -> level_set )
    {
        fori ( level -> levels )
        {
            rtilemap_clr ( level -> level_set [ ix ] );
        }
    }

    free ( level );
    level = NULL;
}
