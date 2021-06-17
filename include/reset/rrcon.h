
/// rrcon.h
///
/// The Reset Resource Container is designed to manage resources with reduced overall
/// overhead. Resources that are imported using an RRCON are stored in an array whose
/// indices are determined by hashing the registry key provided for the resource.
///
/// As a result, it is easier to access imported resources ( simply using the key )
/// and clearing all imported resources from memory can be accomplished using a
/// single function call.

#ifndef _RRCON_H
#define _RRCON_H

#include "depn.h"

// The default surface increment count. This value will be multiplied by the increment
// amount ( RRCON_SF_INCREMENT ) when the initial capacity of an RRCON is determined.
#ifndef RRCON_SF_DEFAULT
#define RRCON_SF_DEFAULT 1
#endif // RRCON_SF_DEFAULT

// The default surface increment amount. This value specifies how many resource spaces
// will be added when an RRCON reaches its capacity.
#ifndef RRCON_SF_INCREMENT
#define RRCON_SF_INCREMENT 8
#endif // RRCON_INCREMENT

// The default maximum size of keys used ( number of characters ).
#ifndef RRCON_MAX_KEY
#define RRCON_MAX_KEY 63
#endif // RRCON_MAX_KEY

typedef enum rrcon_resource_type_e
{
    SURFACE, TEXTURE
} ResourceType;

/// surface_entry_s
///
/// Surface entries are indexed by RRCON structures.

typedef struct surface_entry_s
{
    char key [ RRCON_MAX_KEY ]; ///< The key associated with this entry.
    SDL_Surface * surface;      ///< The surface resource imported to this entry.
} * SFEntry;

/// texture_entry_s
///
/// Texture entries are indexed by RRCON structures.

typedef struct texture_entry_s
{
    char key [ RRCON_MAX_KEY ]; ///< The key associated with this entry.
    SDL_Texture * texture;      ///< The texture resource imported to this entry.
} * TXEntry;

/// rrcon_s
///
/// The main RRCON structure.

typedef struct rrcon_s
{
    ResourceType res_type; ///< The type of resource that the RRCON manages.

    size_t entry_size;  ///< The current RRCON size ( number of imported resources ).
    size_t entry_limit; ///< The current resource limit.

    SDL_Renderer * renderer; ///< The renderer required for SDL_Texture operations.

    union entries
    {
        SFEntry * sf; ///< The set of indexed surface resource entries.
        TXEntry * tx; ///< The set of indexed texture resource entries.
    } entries;

} * RRCON;

/// rrcon_inst
///
/// Produces a pointer to a new RRCON instance.
///
/// The SDL_Renderer argument is required to be NONNULL only when the ResourceType
/// will be TEXTURE. Various operations with SDL_Texture instances require access to
/// a renderer, whereas SDL_Surface instances do not.
///
/// The ResourceType argument specifies the type of RRCON that will be created. An
/// RRCON instance can only accept resources of the type it is initialized with.
///
/// The sf_entry_size of the instance will be set to 0, the sf_entry_limit will be
/// set to RRCON_SF_DEFAULT * RRCON_SF_INCREMENT, and sf_entries will be allocated to
/// the size of sf_entry_limit * size_SFEntry. All elements contained by sf_entries
/// are thereafter nullified.
///
/// @param The conditionally NULLABLE SDL_Renderer required for SDL_Texture operations.
/// @param The type of resource that the initialized RRCON will handle.
///
/// @return A pointer to a new RRCON instance.

RRCON rrcon_inst ( SDL_Renderer *, ResourceType );

/// rrcon_retrieve_sf
///
/// Attempts to retrieve an imported surface resource from a specified key.
///
/// This function may return NULL when the key provided has not been assigned to any
/// resource.
///
/// This function will return NULL when the RRCON provided has ResourceType TEXTURE.
///
/// This function may produce a NONNULL value when the key provided has not been
/// assigned to any resource in any case where the current RRCON limit is small and
/// the key provided is similar to the key originally used to import a resource.
///
/// No operation may occur when either parameter is provided a NULL pointer.
///
/// @param The RRCON instance to query for the provided key.
/// @param The key ( char * ) used as the query value.
///
/// @return A NULLABLE SDL_Surface pointer representing the resolved surface resource.

SDL_Surface * rrcon_retrieve_sf ( RRCON, char * );

/// rrcon_retrieve_tx
///
/// Attempts to retrieve an imported texture resource from a specified key.
///
/// This function may return NULL when the key provided has not been assigned to any
/// resource.
///
/// This function will return NULL when the RRCON provided has ResourceType SURFACE.
///
/// This function may produce a NONNULL value when the key provided has not been
/// assigned to any resource in any case where the current RRCON limit is small and
/// the key provided is similar to the key originally used to import a resource.
///
/// No operation may occur when either parameter is provided a NULL pointer.
///
/// @param The RRCON instance to query for the provided key.
/// @param The key ( char * ) used as the query value.
///
/// @return A NULLABLE SDL_Texture pointer representing the resolved texture resource.

SDL_Texture * rrcon_retrieve_tx ( RRCON, char * );

/// rrcon_retrieve
///
/// A generic function for retrieving SDL_Texture pointers from RRCONs of any type.
///
/// @param The RRCON that will receive a resource query.
/// @param The resource key.
///
/// @return A NULLABLE SDL_Texture pointer representing the resolved texture resource.

SDL_Texture * rrcon_retrieve ( RRCON, char * );

/// rrcon_import
///
/// Attempts to import a specified resource into the provided RRCON. The type of
/// resource imported is automatically determined based on the ResourceType field in
/// the provided RRCON.
///
/// Resource names should include file extensions, but should not include preceding
/// directories. As long as the resource exists in a directory that has been
/// registered with the resource provider, it should be imported successfully.
///
/// @param The RRCON to house an imported resource.
/// @param The key assigned to an imported resource.
/// @param The specific name of the resource that will be imported.

void rrcon_import ( RRCON, char *, char * );

/// rrcon_clr
///
/// Clears the provided RRCON structure from memory. This function will also liberate
/// the entire contents of an RRCON structure.
///
/// @param The RRCON structure to be cleared from active memory.

void rrcon_clr ( RRCON );

#endif // _RRCON_H
