
#ifndef _RRCON_H
#define _RRCON_H

#include "depn.h"

#ifndef RRCON_SF_DEFAULT
#define RRCON_SF_DEFAULT 1 ///< Increments built into new RRCON structures.
#endif // RRCON_SF_DEFAULT

#ifndef RRCON_SF_INCREMENT
#define RRCON_SF_INCREMENT 8 ///< Default increment quantity.
#endif // RRCON_INCREMENT

#ifndef RRCON_MAX_KEY
#define RRCON_MAX_KEY 63
#endif // RRCON_MAX_KEY

typedef struct surface_entry_s
{
    char key [ RRCON_MAX_KEY ];
    SDL_Surface * surface;
} SFEntry;

typedef struct rrcon_s
{
    size_t sf_entry_size;
    size_t sf_entry_limit;
    SFEntry ** sf_entries;
} Rrcon;

Rrcon * rrcon_inst ();

void rrcon_import_sf ( Rrcon *, char *, char * );

void rrcon_clr ( Rrcon * );

SDL_Surface * rrcon_retrieve_sf ( Rrcon *, char * );

#endif // _RRCON_H
