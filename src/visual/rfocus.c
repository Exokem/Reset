
#include "rfocus.h"

const VEC3D DEFAULT_RFOCUS_ANGLE = { 90.0, 90.0, 0.0 };
const VEC3I DEFAULT_RFOCUS_OFFSET = { 0, 0, 0 };

RFOCUS rfocus_inst ( FocusMode focus_mode )
{
    RFOCUS focus = inst ( rfocus_s );

    retnulv ( focus, NULL );

    focus -> focus_mode = focus_mode;
    focus -> angle = cpvec3 ( VEC3D, DEFAULT_RFOCUS_ANGLE );
    focus -> offset = cpvec3 ( VEC3I, DEFAULT_RFOCUS_OFFSET );

    return focus;
}

RFOCUS rfocus_vinst ( FocusMode focus_mode, VEC3D angle, VEC3I offset )
{
    RFOCUS focus = inst ( rfocus_s );

    retnulv ( focus, NULL );

    focus -> focus_mode = focus_mode;
    focus -> angle = angle;
    focus -> offset = offset;

    return focus;
}

void rfocus_render_content ( RFOCUS rfocus, RRCON rrcon )
{
    retnul ( rfocus );
    retnul ( rrcon );

    switch ( rfocus -> focus_mode )
    {
        case F_FLAT_TILEMAP:
        {
            retnul ( rfocus -> content.tilemap );


        }

        case F_LAYERED_TILEMAP:
        {
            retnul ( rfocus -> content.levelmap );


        }

    }
}

void rfocus_translate ( RFOCUS rfocus, VEC3I tvec )
{
    retnul ( rfocus );

    rfocus -> offset = addvec3 ( VEC3I, rfocus -> offset, tvec );
}

void rfocus_clr ( RFOCUS rfocus )
{
    retnul ( rfocus );

    switch ( rfocus -> focus_mode )
    {
        case F_FLAT_TILEMAP:
        {
            rtilemap_clr ( rfocus -> content.tilemap );
            break;
        }
        case F_LAYERED_TILEMAP:
        {
            rlevelmap_clr ( rfocus -> content.levelmap );
            break;
        }
    }

    free ( rfocus );
    rfocus = NULL;
}
