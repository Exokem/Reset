
#include <string.h>

#include "rrcon.h"
#include "rprovider.h"

/// hash_str
///
/// Hashes the provided key into an index based on the limit specified.
/// Key character lengths are limited by RRCON_MAX_KEY.
///
/// @param limit    The index limit.
/// @param key      The key to be hashed.
///
/// @return The resultant index.

static size_t hash_str ( size_t limit, char * key )
{
    retnulv ( key, 0 );

    size_t size = RRCON_MAX_KEY + 1;
    char lkey [ size ];

    snprintf ( lkey, RRCON_MAX_KEY, "%s", key );

    int mx = 1;
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
/// @param rrcon    The RRCON structure to be incremented.
///
/// @return 0 on failure, 1 on success.

static int rrcon_inc ( RRCON rrcon )
{
    retnulv ( rrcon, 0 );

    size_t size = rrcon -> entry_limit + RRCON_SF_INCREMENT;

    SFEntry * sf_adj = NULL;
    TXEntry * tx_adj = NULL;

    switch ( rrcon -> res_type )
    {
        case SURFACE:
        {
            sf_adj = minst ( surface_entry_s, size );
            retnulv ( sf_adj, 0 );

            fori ( size ) sf_adj [ ix ] = NULL;
            fori ( rrcon -> entry_limit )
            {
                SFEntry entry = rrcon -> entries.sf [ ix ];
                ifnnul ( entry )
                {
                    size_t index = hash_str ( size, entry -> key );
                    sf_adj [ index ] = entry;
                }
            }
        }

        case TEXTURE:
        {
            tx_adj = minst ( texture_entry_s, size );
            retnulv ( tx_adj, 0 );

            fori ( size ) tx_adj [ ix ] = NULL;
            fori ( rrcon -> entry_limit )
            {
                TXEntry entry = rrcon -> entries.tx [ ix ];
                ifnnul ( entry )
                {
                    size_t index = hash_str ( size, entry -> key );
                    tx_adj [ index ] = entry;
                }
            }
        }

        default: return 0;
    }

    ifnnul ( sf_adj )
    {
        free ( rrcon -> entries.sf );
        rrcon -> entries.sf = sf_adj;
    }

    else ifnnul ( tx_adj )
    {
        free ( rrcon -> entries.tx );
        rrcon -> entries.tx = tx_adj;
    }

    return 1;
}

RRCON rrcon_inst ( SDL_Renderer * renderer, ResourceType resv )
{
    if ( resv == TEXTURE && renderer == NULL ) return NULL;

    RRCON rrcon = inst ( rrcon_s );

    retnulv ( rrcon, NULL );

    size_t size = RRCON_SF_DEFAULT * RRCON_SF_INCREMENT;

    rrcon -> entry_size = 0;
    rrcon -> entry_limit = size;
    rrcon -> renderer = renderer;
    rrcon -> res_type = resv;

    if ( resv == SURFACE )
    {
        rrcon -> entries.sf = minst ( surface_entry_s, size );
        rrcon -> entries.tx = NULL;

        ifnul ( rrcon -> entries.sf )
        {
            free ( rrcon );
            return NULL;
        }

        fori ( size ) rrcon -> entries.sf [ ix ] = NULL;
    }

    else
    {
        rrcon -> entries.sf = NULL;
        rrcon -> entries.tx = minst ( texture_entry_s, size );

        ifnul ( rrcon -> entries.tx )
        {
            free ( rrcon );
            return NULL;
        }

        fori ( size ) rrcon -> entries.tx [ ix ] = NULL;
    }

    return rrcon;
}

/// Similar but nonequal keys may resolve to the same indices.
/// NULL pointers are not usable for either parameter.

SDL_Surface * rrcon_retrieve_sf ( RRCON rrcon, char * key )
{
    retnulv ( rrcon, NULL );
    retnulv ( key, NULL );

    if ( rrcon -> res_type == TEXTURE ) return NULL;

    size_t index = hash_str ( rrcon -> entry_limit, key );

    SFEntry entry = rrcon -> entries.sf [ index ];

    if ( entry == NULL )
    {
        fprintf ( stderr, "Could not resolve entry for resource key '%s'\n", key );
        return NULL;
    }

//    fprintf ( stderr, "Resolved index '%u' for resource key '%s'\n", index, key );

    return entry -> surface;
}

SDL_Texture * rrcon_retrieve_tx ( RRCON rrcon, char * key )
{
    retnulv ( rrcon, NULL );
    retnulv ( key, NULL );

    if ( rrcon -> res_type == SURFACE ) return NULL;

    size_t index = hash_str ( rrcon -> entry_limit, key );

    TXEntry entry = rrcon -> entries.tx [ index ];

    if ( entry == NULL )
    {
        fprintf ( stderr, "Could not resolve entry for resource key '%s'\n", key );
        return NULL;
    }

//    fprintf ( stderr, "Resolved index '%u' for resource key '%s'\n", index, key );

    return entry -> texture;
}

SDL_Texture * rrcon_retrieve ( RRCON rrcon, char * key )
{
    retnulv ( rrcon, NULL );
    retnulv ( key, NULL );

    SDL_Texture * texture = NULL;

    if ( rrcon -> res_type == SURFACE )
    {
        SDL_Surface * surface = rrcon_retrieve_sf ( rrcon, key );

        texture = SDL_CreateTextureFromSurface ( rrcon -> renderer, surface );

        SDL_FreeSurface ( surface );
    }

    else if ( rrcon -> res_type == TEXTURE )
    {
        texture = rrcon_retrieve_tx ( rrcon, key );
    }

    return texture;
}

void rrcon_import ( RRCON rrcon, char * key, char * path )
{
    retnul ( rrcon );
    retnul ( key );
    retnul ( path );

    SFEntry sf_entry = NULL;
    TXEntry tx_entry = NULL;

    switch ( rrcon -> res_type )
    {
        case SURFACE:
        {
            // Load resource as SDL_Surface

            SDL_Surface * surface = locate_resource_sf ( path );

            ifnnul ( surface )
            {
                sf_entry = inst ( surface_entry_s );
                ifnul ( sf_entry ) { SDL_FreeSurface ( surface ); return; }

                snprintf ( sf_entry -> key, RRCON_MAX_KEY, "%s", key );
                sf_entry -> surface = surface;
            }

            break;
        }

        case TEXTURE:
        {
            // Load resource as SDL_Texture

            SDL_Texture * texture = locate_resource_tx ( rrcon -> renderer, path );

            ifnnul ( texture )
            {
                tx_entry = inst ( texture_entry_s );
                ifnul ( tx_entry ) { SDL_DestroyTexture ( texture ); return; }

                snprintf ( tx_entry -> key, RRCON_MAX_KEY, "%s", key );
                tx_entry -> texture = texture;
            }

            break;
        }

        default:
        {
            // Display warning output

            fprintf
            (
                stderr,
                "Failed to import resource for invalid ResourceType: %d",
                rrcon -> res_type
            );

            return;
        }
    }

    fprintf
    (
        stderr,
        "Found valid ResourceType '%d' for RRCON import operation.\n",
        rrcon -> res_type
    );

    if ( rrcon -> entry_size == rrcon -> entry_limit && !rrcon_inc ( rrcon ) ) return;

    size_t index = hash_str ( rrcon -> entry_limit, key );

    fprintf ( stderr, "Designated index '%zu' for imported resource '%s'\n", index, path );

    ifnnul ( sf_entry )
    {
        ifnul ( rrcon -> entries.sf [ index ] ) rrcon -> entry_size ++;
        rrcon -> entries.sf [ index ] = sf_entry;
    }

    else ifnnul ( tx_entry )
    {
        ifnul ( rrcon -> entries.tx [ index ] ) rrcon -> entry_size ++;
        rrcon -> entries.tx [ index ] = tx_entry;
    }
}

/// Clears the contents of a provided RRCON from memory.

void rrcon_clr ( RRCON rrcon )
{
    retnul ( rrcon );

    fori ( rrcon -> entry_limit )
    {
        if ( rrcon -> res_type == SURFACE && rrcon -> entries.sf != NULL )
        {
            SFEntry entry = rrcon -> entries.sf [ ix ];
            if ( entry != NULL )
            {
                SDL_FreeSurface ( entry -> surface );
                free ( entry );
            }
        }

        else if ( rrcon -> res_type == TEXTURE && rrcon -> entries.tx != NULL )
        {
            TXEntry entry = rrcon -> entries.tx [ ix ];
            ifnnul ( entry )
            {
                SDL_DestroyTexture ( entry -> texture );
                free ( entry );
            }
        }
    }

    free ( rrcon );
    rrcon = NULL;
}
