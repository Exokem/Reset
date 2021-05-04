#include <SDL2/SDL.h>

typedef struct res_eater_s
{
    SDL_Surface ** surface_set;
    int surfaces;
} * ResourceEater;

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

void trackSurfaceResource ( ResourceEater eater, SDL_Surface * surface )
{
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