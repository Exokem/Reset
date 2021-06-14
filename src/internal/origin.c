
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

    RRCON rrcon = rrcon_inst ();
    register_directory ( "tile" );
    rrcon_import_sf ( rrcon, "grass", "grass.png" );

    RTILEMAP tilemap = rtilemap_static ();
    RTILE tile = rtile_inst ( "grass" );

    VEC2I pos = { 0, 0 };
    VEC2I pos2 = { 63, 63 };

    rtilemap_set ( tilemap, tile, pos );
    rtilemap_set ( tilemap, tile, pos2 );

    // SDL_Surface * grass = rrcon_retrieve_sf ( rrcon, "grass" );

    // if ( grass == NULL ) printf ("Invalid surface\n");

    // SDL_Texture * grass_texture = SDL_CreateTextureFromSurface ( display.renderer, grass );

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

        forv ( tilemap -> xdim, ix ) forv ( tilemap -> ydim, iy )
        {
            VEC2I vector = { ix, iy };

            RTILE rtile = rtilemap_tile ( tilemap, vector );

            if ( rtile )
            {
                SDL_Surface * surface = rrcon_retrieve_sf ( rrcon, rtile -> rkey );

                if ( surface )
                {
                    SDL_Texture * texture = SDL_CreateTextureFromSurface ( display.renderer, surface );
                    SDL_Rect destination = { 16 * ix, 16 * iy, 16, 16 };
                    SDL_RenderCopy ( display.renderer, texture, NULL, &destination );
                }
            }
        }

        // SDL_RenderCopy ( display.renderer, grass_texture, NULL, NULL );
        SDL_RenderPresent ( display.renderer );
    }

    return 0;
}
