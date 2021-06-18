
//#define SDL_MAIN_HANDLED

#include "RESET.h"

#undef main

/// Main Function

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
    RTILE tile = rtile_inst ( "grass" );

    VEC2U pos = { 0, 0 };
    VEC2U pos2 = { 63, 31 };

    rtilemap_set ( tilemap, tile, pos );
    rtilemap_set ( tilemap, tile, pos2 );

    RFOCUS focus = rfocus_inst ( F_LAYERED_TILEMAP );

    RLEVEL level = rlevel_inst ( 1 );
    level -> level_set [ 0 ] = tilemap;
    focus -> content.level = level;

    SDL_Event ev;

    VEC3I down = { 0, 20, 0 };

    while ( 1 )
    {
        if ( SDL_WaitEvent ( & ev ) )
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

            if ( ev.type == SDL_KEYDOWN )
            {
                if ( ev.key.keysym.sym == SDLK_s )
                {
                    rfocus_translate ( focus, down );
                }
            }
        }

        // SDL_SetRenderDrawColor ( display.renderer, 0, 0, 0, 255 );
        SDL_RenderClear ( display.renderer );

        rfocus_render_content ( focus, rrcon );

        SDL_RenderPresent ( display.renderer );
    }

    return 0;
}
