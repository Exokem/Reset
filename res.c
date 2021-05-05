
#include "res.h"

SDL_Surface * importBMP ( Root container, char * path )
{
    SDL_Surface * bmp = NULL;
    bmp = SDL_LoadBMP(path);

    if ( bmp == NULL )
    {
        fprintf(stderr, "Failed to load bitmap resource [%s]: %s\n", path, SDL_GetError());
    }

    trackSurface ( container, bmp );

    return bmp;
}