
#include "provider.h"

// State indicator for the initialization status of the Resource Provider.
static short PROVIDER_INITIALIZED = 0;

// The running counter for registered directories.
static size_t REGISTERED_DIRECTORIES = 0;

// The current limit for the total number of registered directories.
static size_t INDEX_LIMIT = PROVIDER_INDEX_DEFAULT;

// The index of registered directories, with INDEX_LIMIT indices.
static char ** DIRECTORY_INDEX = NULL;

// The root directory for all resources.
static const char * ROOT = "resources";

/// load_resource
///
/// Loads the specified resource from the specified directory, which is assumed to
/// exist as a subdirectory in ROOT.
///
/// @param directory    The subdirectory in ROOT whose contents will be queried.
/// @param resource     The named resource query.
///
/// @return A NULLABLE SDL_Surface pointer, the located or missing resource.

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

/// Initializes the resource provider by allocating the directory index. The field
/// PROVIDER_INITIALIZED ensures that this function only runs once.
/// If this function failes to allocate the directory index, the program will exit.

void provider_init ( void )
{
    if ( PROVIDER_INITIALIZED ) return;

    DIRECTORY_INDEX = malloc ( PROVIDER_INDEX_DEFAULT * sizeof ( char * ) );
    REGISTERED_DIRECTORIES = 0;

    if ( DIRECTORY_INDEX == NULL )
    {
        fprintf ( stderr, "Failed to initialize the resource provider\n" );
        exit ( EXIT_FAILURE );
    }

    PROVIDER_INITIALIZED = 1;

    fprintf ( stderr, "Initialized Resource Provider.\n" );
}

/// Registers a directory by inserting it into the last open index in the directory
/// index. The index is resized if necessary.

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

/// Searches all registered directories for the named resource.

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
