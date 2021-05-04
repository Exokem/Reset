
#include "root.h"

static SDL_Window * windowSetup ( int width, int height )
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
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
        SDL_WINDOW_SHOWN
    );

    if ( window == NULL )
    {
        fprintf(stderr, "Window creation failure: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return window;
}

Root setup ()
{
	Root root = malloc ( sizeof ( Root ) );

    if ( root == NULL ) return NULL;

	root -> window = NULL;
    root -> screen = NULL; 
    root -> eater = NULL;
    root -> terminated = 0;

    root -> window = windowSetup ( WIN_HZ, WIN_VT );
    root -> screen = SDL_GetWindowSurface ( root -> window );
    root -> eater = defineEater();

    return root;
}

ResourceEater defineEater ()
{
    ResourceEater eater = NULL;

    eater = malloc ( sizeof ( ResourceEater ) );

    if ( eater == NULL ) return NULL;

    eater -> surface_set = NULL;
    eater -> surface_set = malloc ( 0 );
    eater -> surfaces = 0;

    return eater;
}

void dismantleRoot ( Root root )
{
	if ( root == NULL ) return;
	if ( root -> window != NULL ) SDL_DestroyWindow ( root -> window );
	if ( root -> screen != NULL ) SDL_FreeSurface ( root -> screen );
	if ( root -> eater != NULL ) eat ( root -> eater );

	// free ( root -> eater ); why is this a problem? 

	root -> window = NULL;
	root -> screen = NULL;
	root -> eater = NULL;
    root -> terminated = 1;
}

void flagTermination ( Root root )
{
    root -> terminated = 2;
}

void terminateRoot ( Root root )
{
    dismantleRoot ( root );

    SDL_Quit();
}

void trackSurface ( Root root, SDL_Surface * surface )
{
    ResourceEater eater = root -> eater;

    if ( eater == NULL ) 
    {
        fprintf ( stderr, "Attempted to track resource with NULL eater.\n" );
        return;
    }

    SDL_Surface ** set = eater -> surface_set;

    if ( set == NULL )
    {
        fprintf ( stderr, "Attempted to track resource with malformed eater.\n");
        return;
    }

    SDL_Surface ** checker;

    checker = realloc 
    (
        set, 
        sizeof ( set ) + sizeof ( SDL_Surface )
    );

    if ( checker != NULL )
    {
        eater -> surface_set = checker;
    }

    eater -> surface_set[ eater -> surfaces ] = surface;
    eater -> surfaces ++;
}

void eat ( ResourceEater eater )
{
    if ( eater == NULL ) return;

    if ( eater -> surface_set != NULL ) 
    {
        for ( size_t ix = 0; ix < eater -> surfaces; ix ++)
        {
            SDL_Surface * surface = NULL;
            surface = eater -> surface_set[ ix ];

            printf ( "Attempting to free surface set index %zu.\n", ix );

            if ( surface != NULL )
            {
                SDL_FreeSurface ( surface );
                surface = NULL;
                eater -> surface_set[ ix ] = NULL;
            }
        }

        free ( eater -> surface_set );
    }

    eater -> surface_set = NULL;

    printf ( "Resource Eater terminated.\n" );
}