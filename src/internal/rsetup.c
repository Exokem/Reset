
#include "rsetup.h"

void r_sdlset ()
{
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf ( stderr, "SDL initialization failure: %s\n", SDL_GetError () );
        exit ( EXIT_FAILURE );
    }

    SDL_version compiled, linked;

    SDL_VERSION ( & compiled );
    SDL_GetVersion ( & linked );

    fprintf
    (
        stderr,
        "Initialized SDL2:\n\t"
        "Compilation version: %d.%d.%d\n\t"
        "Linked version: %d.%d.%d\n",
        compiled.major, compiled.minor, compiled.patch,
        linked.major, linked.minor, linked.patch
    );

    if ( IMG_Init ( IMG_INIT_PNG ) != IMG_INIT_PNG )
    {
        fprintf ( stderr, "SDL/IMG initialization failure: %s\n", SDL_GetError () );
        exit ( EXIT_FAILURE );
    }

    fprintf ( stderr, "Initialized SDL2/Image\n" );
}

SDL_Window * r_winset ( CFG_WIN window_cfg )
{
    SDL_Window * window = NULL;

    window = SDL_CreateWindow
    (
        window_cfg.title,
        window_cfg.x, window_cfg.y,
        window_cfg.width, window_cfg.height,
        SDL_WINDOW_SHOWN
    );

    if ( window == NULL ) fprintf ( stderr, "Failed to create window: %s\n", SDL_GetError () );

    return window;
}

DATA_WIN r_dispset ( CFG_WIN cfg )
{
    SDL_Window * window = r_winset ( cfg );

    DATA_WIN data =
    {
        window, SDL_CreateRenderer ( window, -1, SDL_RENDERER_ACCELERATED )
    };

    return data;
}
