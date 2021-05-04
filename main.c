#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "res_eat.h"

const int S_WIDTH = 1920;
const int S_HEIGHT = 1080;

static SDL_Window * initialize ()
{
    // Attempt to initialize SDL and a window. Failures will shut down the program.
    
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf ( stderr, "SDL initialization failure: %s\n", SDL_GetError () );
        exit ( EXIT_FAILURE );
    }

    SDL_Window * window = NULL;
    window = SDL_CreateWindow
    (
        "Windsor 0", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_WIDTH, S_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if ( window == NULL )
    {
        fprintf(stderr, "Window creation failure: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return window;
}

static void terminate ( SDL_Window * window )
{
    SDL_DestroyWindow ( window );
    SDL_Quit ();
}

static SDL_Surface * importBMP ( char * path )
{
    SDL_Surface * bmp = NULL;
    bmp = SDL_LoadBMP(path);

    if ( bmp == NULL )
    {
        fprintf(stderr, "Failed to load bitmap resource [%s]: %s\n", path, SDL_GetError());
        return NULL;
    }

    return bmp;
}

int main ( int argc, char * argv[] ) 
{
    // The window contains the surface.

    SDL_Window * window = NULL;
    window = initialize ();

    SDL_Surface * screenSurface = NULL; 
    screenSurface = SDL_GetWindowSurface ( window );
    
    ResourceEater resourceEater = NULL;
    resourceEater = defineEater ();

    SDL_Surface * character = NULL;
    character = importBMP ( "character.bmp" );

    trackSurfaceResource ( resourceEater, character );

    SDL_FillRect ( screenSurface, NULL, SDL_MapRGB ( screenSurface -> format, 0x00, 0x00, 0x00 ) );

    if ( character != NULL )
    {
        SDL_BlitSurface ( character, NULL, screenSurface, NULL );
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

    terminate ( window );
    eat ( resourceEater );

    return EXIT_SUCCESS;
}