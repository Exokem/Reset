
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

/// surface_entry_s
///
/// Surface entries are indexed by RRCON structures.

typedef struct surface_entry_s
{
    char key [ RRCON_MAX_KEY ]; ///< The key associated with this entry.
    SDL_Surface * surface;      ///< The surface resource imported to this entry.
} * SFEntry;

/// rrcon_s
///
/// The main RRCON structure.

typedef struct rrcon_s
{
    size_t sf_entry_size;  ///< The current RRCON size ( number of imported resources ).
    size_t sf_entry_limit; ///< The current resources limit.
    SFEntry * sf_entries; ///< The set of indexed surface resource entries.
} * RRCON;

/// rrcon_inst
///
/// Produces a pointer to a new RRCON instance.
///
/// The sf_entry_size of the instance will be set to 0, the sf_entry_limit will be
/// set to RRCON_SF_DEFAULT * RRCON_SF_INCREMENT, and sf_entries will be allocated to
/// the size of sf_entry_limit * size_SFEntry. All elements contained by sf_entries
/// are thereafter nullified.
///
/// @return A pointer to a new RRCON instance.

RRCON rrcon_inst ();

/// rrcon_import_sf
///
/// Attempts to import a specified resource into the provided RRCON.
///
/// Resource names should include file extensions, but should not include preceding
/// directories. As long as the resource exists in a directory that has been
/// registered with the resource provider, it should be imported successfully.
///
/// @param The RRCON to house an imported resource.
/// @param The key assigned to an imported resource.
/// @param The specific name of the resource that will be imported.

void rrcon_import_sf ( RRCON, char *, char * );

/// rrcon_clr
///
/// Clears the provided RRCON structure from memory. This function will also liberate
/// the entire contents of an RRCON structure.
///
/// @param The RRCON structure to be cleared from active memory.

void rrcon_clr ( RRCON );

/// rrcon_retrieve_sf
///
/// Attempts to retrieve an imported surface resource from a specified key.
///
/// This function may return NULL when the key provided has not been assigned to any
/// resource.
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

#endif // _RRCON_H
