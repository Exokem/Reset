
#include <string.h>

#include "rrcon.h"
#include "provider.h"

static size_t hash_str ( size_t limit, char * key )
{
    retnulv ( key, 0 );

    size_t size = RRCON_MAX_KEY + 1;
    char lkey [ size ];

    strncpy ( lkey, key, RRCON_MAX_KEY );

    int mx = 1; // Index, multiplier
    unsigned int sum = 0;
    size_t len = strlen ( lkey );

    fori ( len )
    {
        sum += lkey [ ix ] * mx;

        if ( ix % 4 == 0 ) mx = 1;
        else mx *= 256;
    }

    return sum % limit;
}

/// rrcon_inc
///
/// Attempts to dynamically increment the capacity of a provided RRCON structure.
///
/// @param Rrcon    The RRCON structure to be incremented.
///
/// @return         0 on failure, 1 on success.

static int rrcon_inc ( Rrcon * rrcon )
{
    retnulv ( rrcon, 0 );

    size_t size = rrcon -> sf_entry_limit + RRCON_SF_INCREMENT;
    SFEntry ** adjusted = minst ( surface_entry_s, size ); // Allocate new expanded entry set.

    retnulv ( adjusted, 0 );

    fori ( rrcon -> sf_entry_limit ) // Rehash contents.
    {
        SFEntry * entry = ixget ( rrcon -> sf_entries, ix );

        if ( entry != NULL )
        {
            size_t index = hash_str ( size, entry -> key );
            adjusted [ index ] = entry;
        }
    }

    free ( rrcon -> sf_entries );
    rrcon -> sf_entries = adjusted;

    return 1;
}

Rrcon * rrcon_inst ()
{
    Rrcon * rrcon = inst ( rrcon_s );

    retnulv ( rrcon, NULL );

    size_t size = RRCON_SF_DEFAULT * RRCON_SF_INCREMENT;

    rrcon -> sf_entry_size = 0;
    rrcon -> sf_entry_limit = size;
    rrcon -> sf_entries = mxalloc ( SDL_Surface, size );

    if ( rrcon -> sf_entries == NULL )
    {
        free ( rrcon );
        return NULL;
    }

    fori ( RRCON_SF_INCREMENT )
    {
        rrcon -> sf_entries [ ix ] = NULL;
    }

    return rrcon;
}

/// Imports a resource with the provided path into the provided RRCON.

void rrcon_import_sf ( Rrcon * pt_rrcon, char * key, char * path )
{
    retnul ( path ); // Cannot load resources from invalid paths.
    retnul ( pt_rrcon );

    SDL_Surface * surface = locate_resource ( path );

    Rrcon deref ( pt_rrcon, rrcon );

    if ( surface == NULL ) fprintf
    (
        stderr,
        "Resource '%s' could not be loaded: %s\n",
        path, IMG_GetError ()
    );

    else
    {
        if ( rrcon.sf_entry_size == rrcon.sf_entry_limit )
        {
            if ( !rrcon_inc ( pt_rrcon ) )
            {
                SDL_FreeSurface ( surface );
                return;
            }
        }

        SFEntry * entry = inst ( surface_entry_s );
        strncpy ( entry -> key, key, RRCON_MAX_KEY );
        entry -> surface = surface;

        size_t index = hash_str ( pt_rrcon -> sf_entry_limit, key );

        fprintf ( stderr, "Designated index '%u' for imported resource '%s'\n", index, path );

        pt_rrcon -> sf_entries [ index ] = entry;
        pt_rrcon -> sf_entry_size ++;
    }
}

/// Clears the contents of a provided RRCON from memory.

void rrcon_clr ( Rrcon * pt_rrcon )
{
    retnul ( pt_rrcon );

    // Rrcon deref ( pt_rrcon, rrcon );

    // TODO: Clear all resources

    free ( pt_rrcon );
}

SDL_Surface * rrcon_retrieve_sf ( Rrcon * rrcon, char * key )
{
    retnulv ( rrcon, NULL );
    retnulv ( key, NULL );

    size_t index = hash_str ( rrcon -> sf_entry_limit, key );

    SFEntry * entry = rrcon -> sf_entries [ index ];

    if ( entry == NULL )
    {
        fprintf ( stderr, "Could not resolve entry for resource key '%s'\n", key );
        return;
    }

    fprintf ( stderr, "Resolved index '%u' for resource key '%s'\n", index, key );

    return entry -> surface;
}
