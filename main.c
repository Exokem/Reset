
#include "res.h"
#include "mobj.h"

int main ( int argc, char * argv[] ) 
{
    // The window contains the surface.

    Root root = NULL;
    root = setup ();

    SDL_Window * window = NULL;
    window = root -> window;

    SDL_Surface * screenSurface = NULL; 
    screenSurface = root -> screen;

    Mobj player = NULL;
    SDL_Rect player_rec = { 0, 0, 16, 16 };
    player = mobjInst ( "controlled", player_rec, root );

    SDL_Surface * player_icon = mapAcck ( player -> mappings, "0" );

    SDL_Event ev;

    while ( !root -> terminated )
    {
        while ( SDL_PollEvent ( &ev ) )
        {
            if ( ev.type == SDL_QUIT )
            {
                terminateRoot ( root );
                return EXIT_SUCCESS;
            }
        }

        SDL_FillRect ( screenSurface, NULL, SDL_MapRGB ( screenSurface -> format, 0x00, 0x00, 0x00 ) );

        if ( player_icon != NULL )
        {
            SDL_BlitSurface ( player_icon, NULL, screenSurface, NULL );
        }

        //if ( character != NULL )
        //{
        //    //SDL_BlitSurface ( character, NULL, screenSurface, NULL );
        //}

        SDL_UpdateWindowSurface ( window );
    }

    return EXIT_SUCCESS;
}