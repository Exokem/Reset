
#include "res.h"

int main ( int argc, char * argv[] ) 
{
    // The window contains the surface.

    Root root = NULL;
    root = setup ();

    SDL_Window * window = NULL;
    window = root -> window;

    SDL_Surface * screenSurface = NULL; 
    screenSurface = root -> screen;

    SDL_Surface * character = NULL;
    character = importBMP ( root, "character.bmp" );

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

        if ( character != NULL )
        {
            SDL_BlitSurface ( character, NULL, screenSurface, NULL );
        }

        SDL_UpdateWindowSurface ( window );
    }

    return EXIT_SUCCESS;
}