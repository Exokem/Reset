
#ifndef _RLEVELMAP_H
#define _RLEVELMAP_H

#include "depn.h"
#include "rtilemap.h"

typedef struct rlevelmap_s
{
    size_t levels;

    RTILEMAP * level_set;

} * RLEVELMAP;

RLEVELMAP rlevelmap_inst ( size_t );

void rlevelmap_clr ( RLEVELMAP );

#endif // _RLAYERED_TILEMAP_H
