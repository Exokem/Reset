
#include "depn.h"
#include "rsetup.h"
#include "rrcon.h"
#include "provider.h"
#include "rfocus.h"
#include "rvector.h"
#include "rtilemap.h"

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

    RTILEMAP tilemap = rtilemap_static ();
    RTILE tile = rtile_inst ( "grass" );

    VEC2U pos = { 0, 0 };
    VEC2U pos2 = { 63, 63 };

    rtilemap_set ( tilemap, tile, pos );
    rtilemap_set ( tilemap, tile, pos2 );

    SDL_Event ev;

    while ( 1 )
    {
        if ( SDL_WaitEvent ( &ev ) )
        {
            if ( ev.type == SDL_QUIT )
            {
                rrcon_clr ( rrcon );

                SDL_DestroyRenderer ( display.renderer );
                SDL_DestroyWindow ( display.window );
                SDL_Quit ();
                IMG_Quit ();

                return EXIT_SUCCESS;
            }
        }

        // SDL_SetRenderDrawColor ( display.renderer, 0, 0, 0, 255 );
        SDL_RenderClear ( display.renderer );

        SDL_Surface * surface = NULL;
        SDL_Texture * texture = NULL;

        forv ( tilemap -> xdim, ix ) forv ( tilemap -> ydim, iy )
        {
            VEC2U vector = { ix, iy };

            RTILE rtile = rtilemap_tile ( tilemap, vector );

            if ( rtile )
            {
                if ( rrcon -> res_type == SURFACE )
                {
                    surface = rrcon_retrieve_sf ( rrcon, rtile -> rkey );

                    ifnnul ( surface )
                    {
                        texture = SDL_CreateTextureFromSurface ( display.renderer, surface );
                    }
                }

                else if ( rrcon -> res_type == TEXTURE )
                {
                    texture = rrcon_retrieve_tx ( rrcon, rtile -> rkey );
                }

                ifnnul ( texture )
                {
                    SDL_Rect destination = { 16 * ix, 16 * iy, 16, 16 };
                    SDL_RenderCopy ( display.renderer, texture, NULL, &destination );
                }

                surface = NULL;
                texture = NULL;
            }
        }

        SDL_RenderPresent ( display.renderer );
    }

    return 0;
}
