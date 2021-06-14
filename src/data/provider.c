
#include "provider.h"

static short PROVIDER_INITIALIZED = 0;
static size_t REGISTERED_DIRECTORIES = 0;
static size_t INDEX_LIMIT = PROVIDER_INDEX_DEFAULT;
static char ** DIRECTORY_INDEX = NULL;
static const char * ROOT = "resources";

static SDL_Surface * load_resource ( const char * directory, char * resource )
{
    size_t size = strlen ( ROOT ) + 1 + strlen ( directory ) + 1 + strlen ( resource ) + 1;
    char path [ size ];

    snprintf ( path, size, "%s/%s/%s", ROOT, directory, resource );

    SDL_Surface * surface = IMG_Load ( path );

    fprintf
    (
        stderr,
        "Resource '%s' %s.\n",
        path,
        surface == NULL ? "could not be loaded" : "loaded successfully"
    );

    return surface;
}

void provider_init ( void )
{
    if ( PROVIDER_INITIALIZED ) return;

    DIRECTORY_INDEX = malloc ( PROVIDER_INDEX_DEFAULT * sizeof ( char * ) );
    REGISTERED_DIRECTORIES = 0;

    if ( DIRECTORY_INDEX == NULL )
    {
        fprintf
        (
            stderr,
            "Failed to initialize the resource provider\n"
        );

        exit ( EXIT_FAILURE );
    }

    PROVIDER_INITIALIZED = 1;

    fprintf ( stderr, "Initialized Resource Provider.\n" );
}

void register_directory ( char * directory )
{
    if ( !PROVIDER_INITIALIZED ) provider_init ();

    if ( REGISTERED_DIRECTORIES == INDEX_LIMIT )
    {
        size_t size = INDEX_LIMIT + PROVIDER_INDEX_INCREMENT;

        char ** tmp = realloc ( DIRECTORY_INDEX, size );

        if ( tmp == NULL )
        {
            fprintf ( stderr, "Failed to expand directory index\n" );
            return;
        }

        DIRECTORY_INDEX = tmp;
        INDEX_LIMIT = size;
    }

    DIRECTORY_INDEX [ REGISTERED_DIRECTORIES ] = directory;
    REGISTERED_DIRECTORIES ++;

    fprintf ( stderr, "Successfully registered directory '%s'\n", directory );
}

SDL_Surface * locate_resource ( char * resource )
{
    if ( !PROVIDER_INITIALIZED ) provider_init ();

    if ( REGISTERED_DIRECTORIES == 0 ) return NULL;

    retnulv ( resource, NULL );

    SDL_Surface * surface = NULL;

    fori ( REGISTERED_DIRECTORIES )
    {
        char * directory = DIRECTORY_INDEX [ ix ];

        if ( directory != NULL )
        {
            surface = load_resource ( directory, resource );
            if ( surface != NULL ) return surface;
        }
    }

    return NULL;
}
