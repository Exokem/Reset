
#ifndef _RLEVELMAP_H
#define _RLEVELMAP_H

#include "depn.h"
#include "rtilemap.h"

typedef struct rlevel_s
{
    size_t levels;

    RTILEMAP * level_set;

} * RLEVEL;

RLEVEL rlevel_inst ( size_t );

RTILEMAP rlevel_tilemap ( RLEVEL, size_t );

RTILE rlevel_tile ( RLEVEL, size_t, VEC2U );

RTILE rlevel_set ( RLEVEL, size_t, RTILE, VEC2U );

void rlevel_render_levels ( RLEVEL, RRCON, VEC2I, double );

void rlevel_clr ( RLEVEL );

#endif // _RLAYERED_TILEMAP_H
