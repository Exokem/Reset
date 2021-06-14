
#ifndef _PROVIDER_H
#define _PROVIDER_H

#define PROVIDER_INDEX_DEFAULT 8
#define PROVIDER_INDEX_INCREMENT 2

#include "depn.h"

void provider_init ( void );

void register_directory ( char * );

SDL_Surface * locate_resource ( char * );

#endif // _PROVIDER_H
