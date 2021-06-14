
#ifndef _RFOCUS_H
#define _RFOCUS_H

#include "depn.h"
#include "rvector.h"

typedef struct rfocus_s
{
    // TODO: field for what it is looking at
    // TODO: field for display mode ( tile-based, 3D, etc. )

    VEC3D angles;
    VEC3I offsets;

} * RFOCUS;

RFOCUS rfocus_inst ( VEC3D, VEC3I );

#endif // _RFOCUS_H
