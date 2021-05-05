
#include <stdlib.h>
#include <stdio.h>

#include "map.h"

#ifndef _DEFAULT_INCREMENT_DEF

#define DEFAULT_INCREMENT 10

#endif

/// Simple Insert: key, value only.
/// Incremented Insert: key, value, and increment for map expansion.
/// Memory-Conscious Insert: key, value, and memory clearing functions.

#define SINS( map, key, value ) mapIns ( map, key, value, NULL, NULL, DEFAULT_INCREMENT );
#define IINS( map, key, value, inc ) mapIns ( map, key, value, NULL, NULL, inc );
#define MINS( map, key, value, kclr, vclr ) mapIns ( map, key, value, kclr, vclr, DEFAULT_INCREMENT );

static void entryClr 
( 
	Entry entry,
	void ( * keyclr ) ( void * ),
	void ( * valclr ) ( void * )
)
{
	if ( entry == NULL ) return;

	if ( keyclr != NULL ) keyclr ( entry -> key );
	if ( valclr != NULL ) valclr ( entry -> value );

	entry -> key = NULL;
	entry -> value = NULL;

	free ( entry );

	entry = NULL;
}

HashMap mapBuild 
( 
	int limit, 
	int ( * hash ) ( void *, int ),
	int ( * eq ) ( void *, void * )
)
{
	HashMap map = NULL;
	map = malloc ( sizeof ( HashMap ) );

	if ( map != NULL )
	{
		map -> limit = limit;
		map -> volume = 0;
		map -> hash = hash;
		map -> eq = eq;

		map -> entries = NULL;
		map -> entries = malloc ( sizeof ( Entry ) * limit );
	}

	return map;
}

void mapDestroy
(
	HashMap map,
	void ( * keyclr ) ( void * ),
	void ( * valclr ) ( void * )
)
{
	if ( map == NULL ) return;

	Entry * entries = map -> entries;

	if ( entries != NULL )
	{
		for ( int ix = 0; ix < map -> limit; ix ++ )
		{
			Entry entry = entries[ ix ];

			if ( entry != NULL ) entryClr ( entry, keyclr, valclr );

			entry = NULL;
			map -> entries[ ix ] = NULL;
		}

		free ( map -> entries );
		map -> entries = NULL;
	}

	map -> limit = 0;
	map -> volume = 0;
	map -> hash = NULL;
	map -> eq = NULL;

	free ( map );
	map = NULL;
}

void mapIns 
( 
	HashMap map, 
	void * key, void * value,
	void ( * keyclr ) ( void * ),
	void ( * valclr ) ( void * ),
	int increment
)
{
	if ( map == NULL || map -> hash == NULL ) return;
	
	if ( map -> volume == map -> limit )
	{
		fprintf ( stderr, "[map.c/mapINS]: Insertion failed; map is full.\n" );
		
		return;
	}

	Entry entry = NULL;
	entry = malloc ( sizeof ( Entry ) );

	if ( entry != NULL )
	{
		entry -> key = key;
		entry -> value = value;

		int index = HASH ( map, key );

		Entry exis = RETR ( map, index );

		if ( exis == NULL )
		{
			INST ( map, index, entry );
		}

		else if ( map -> eq != NULL )
		{
			if ( map -> eq ( key, exis -> key ) == EQUIVALENT )
			{
				// Keys are equivalent, overwrite entry.

				entryClr ( exis, keyclr, valclr );

				INST ( map, index, entry );
			}

			else if ( 0 < increment )
			{
				// Keys are different, resize map.

				int olm = map -> limit;
				int limit = olm + increment;

				Entry * adjent = NULL;
				adjent = malloc ( sizeof ( Entry ) * limit );				

				if ( adjent )
				{
					// Rehash entries, replace entry set.
					
					for ( int ix = 0; ix < olm; ix ++ )
					{
						Entry en = RETR ( map, ix );

						void * key = en -> key;
						int newix = map -> hash ( key, limit );

						adjent[ newix ] = en;
					}

					free ( map -> entries );

					map -> entries = adjent;
				}
			}
		}
	}
}

void * mapRemk
(
	HashMap map, void * key
)
{
	int ix = HASH ( map, key );
	void * value = map -> entries[ ix ];

	map -> entries[ ix ] = NULL;

	return value;
}