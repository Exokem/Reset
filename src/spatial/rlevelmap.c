
#include "rlevelmap.h"

RLEVELMAP rlevelmap_inst ( size_t levels )
{
    RLEVELMAP levelmap = inst ( rlevelmap_s );

    retnulv ( levelmap, NULL );

    levelmap -> levels = levels;
    levelmap -> level_set = minst ( rtilemap_s, levels );

    ifnul ( levelmap -> level_set )
    {
        free ( levelmap );
        return NULL;
    }

    fori ( levels ) levelmap -> level_set [ ix ] = NULL;

    return levelmap;
}

void rlevelmap_clr ( RLEVELMAP levelmap )
{
    retnul ( levelmap );

    ifnnul ( levelmap -> level_set )
    {
        fori ( levelmap -> levels )
        {
            rtilemap_clr ( levelmap -> level_set [ ix ] );
        }
    }

    free ( levelmap );
    levelmap = NULL;
}
