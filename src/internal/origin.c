
#include "depn.h"
#include "rsetup.h"
#include "rrcon.h"
#include "provider.h"
#undef main

int main ( int argc, char ** argv )
{
    CFG_WIN cfg =
    {
        1920, 1080,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        "Reset"
    };

    r_sdlset(); // SDL2 module init

    DATA_WIN display = r_dispset ( cfg );

    Rrcon * rrcon = rrcon_inst ();
    register_directory ( "tile" );
    // rrcon_import_sf ( rrcon, "grass", "grass.png" );

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
        // SDL_RenderCopy ( display.renderer, grass_texture, NULL, NULL );
        SDL_RenderPresent ( display.renderer );
    }

    return 0;
}
