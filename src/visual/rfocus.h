
#ifndef _RFOCUS_H
#define _RFOCUS_H

#include "depn.h"
#include "rrcon.h"
#include "rvector.h"
#include "rtilemap.h"
#include "rlevelmap.h"

typedef enum rfocus_mode_e
{
    F_FLAT_TILEMAP, F_LAYERED_TILEMAP
} FocusMode;

typedef struct rfocus_s
{
    FocusMode focus_mode;

    VEC3D angle;
    VEC3I offset;

    union content
    {
        RTILEMAP tilemap;
        RLEVELMAP levelmap;
    } content;

} * RFOCUS;

RFOCUS rfocus_inst ( FocusMode );

RFOCUS rfocus_vinst ( FocusMode, VEC3D, VEC3I );

void rfocus_render_content ( RFOCUS, RRCON );

void rfocus_translate ( RFOCUS, VEC3I );

void rfocus_clr ( RFOCUS );

#endif // _RFOCUS_H
