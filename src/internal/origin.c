
#include "depn.h"
#include "rsetup.h"
#include "rrcon.h"
#include "provider.h"
#include "rfocus.h"
#include "rvector.h"
#include "rtilemap.h"
#include "rlevelmap.h"

#undef main

int main ( int argc, char ** argv )
{
    fprintf ( stderr, "Received %d argument%s:\n", argc, argc == 1 ? "" : "s" );

    forsi ( argc ) fprintf ( stderr, "\t%s\n", argv [ ix ] );

    CFG_WIN cfg =
    {
        1920, 1080,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        "Reset"
    };

    r_sdlset(); // SDL2 module init

    DATA_WIN display = r_dispset ( cfg );

    RRCON rrcon = rrcon_inst ( display.renderer, TEXTURE );
    register_directory ( "tile" );
    rrcon_import ( rrcon, "grass", "grass.png" );

    RTILEMAP tilemap = rtilemap_static ( );
//    RTILEMAP tilemap = rtilemap_dynamic ( 72, 72 );
    RTILE tile = rtile_inst ( "grass" );

    VEC2U pos = { 0, 0 };
    VEC2U pos2 = { 63, 31 };

    rtilemap_set ( tilemap, tile, pos );
    rtilemap_set ( tilemap, tile, pos2 );

//    RFOCUS focus = rfocus_inst ( F_FLAT_TILEMAP );
//
//    focus -> tilemap = tilemap;

    VEC2I tilemap_start = { 30, 0 };

    SDL_Event ev;

    while ( 1 )
    {
        if ( SDL_WaitEvent ( &ev ) )
        {
            if ( ev.type == SDL_QUIT )
            {
//                rrcon_clr ( rrcon );

                SDL_DestroyRenderer ( display.renderer );
                SDL_DestroyWindow ( display.window );
                SDL_Quit ();
                IMG_Quit ();

                return EXIT_SUCCESS;
            }
        }

        // SDL_SetRenderDrawColor ( display.renderer, 0, 0, 0, 255 );
        SDL_RenderClear ( display.renderer );

        rtilemap_render_tiles ( tilemap, rrcon, tilemap_start, 1.0 );

        SDL_RenderPresent ( display.renderer );
    }

    return 0;
}
