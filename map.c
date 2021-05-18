
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "map.h"

#ifndef _DEFAULT_INCREMENT_DEF

#define DEFAULT_INCREMENT 10

#endif

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

HashMap mapInst 
( 
	int limit, 
	int ( * hash ) ( void *, int ),
	int ( * eq ) ( void *, void * )
)
{
	if ( limit == 0 ) return NULL;

	HashMap map = NULL;
	map = malloc ( sizeof ( HashMap ) );

	if ( map != NULL )
	{
		map -> limit = limit;
		map -> volume = 0;
		map -> hash = hash;
		map -> eq = eq;

		map -> entries = NULL;
		Entry * entries = malloc ( limit * sizeof ( Entry ) );

		if ( entries != NULL )
		{
			for ( int ix = 0; ix < limit; ix ++ )
			{			
				entries[ ix ] = NULL;
			}

			map -> entries = entries;
		}
	}

	return map;
}

void mapClr
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

void mapInsert 
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
		entry -> key = NULL;
		entry -> value = NULL;

		entry -> key = key;
		entry -> value = value;

		int index = HASH ( map, key );

		Entry exis = NULL;

		if ( map -> volume != 0 )
		{
			exis = RETRV ( map, index );
		}

		if ( exis == NULL )
		{
			map -> entries[ index ] = entry;
		}

		else if ( map -> eq != NULL )
		{
			if ( map -> eq ( key, exis -> key ) == EQUIVALENT )
			{
				// Keys are equivalent, overwrite entry.

				entryClr ( exis, keyclr, valclr );

				INSRT ( map, index, entry );
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
						Entry en = RETRV ( map, ix );

						void * key = en -> key;
						int newix = map -> hash ( key, limit );

						adjent[ newix ] = en;
					}

					free ( map -> entries );

					map -> entries = adjent;
				}
			}
		}

		map -> volume ++;
	}
}

void * mapAcck
(
	HashMap map, void * key
)
{
	if ( map == NULL ) return NULL;

	int ix = HASH ( map, key );

	if ( map -> limit <= ix ) return NULL;

	Entry en = map -> entries[ ix ];

	if ( en == NULL ) return NULL;

	return en -> value;
}

void * mapRemk
(
	HashMap map, void * key
)
{
	if ( map == NULL || key == NULL ) return NULL;

	int ix = HASH ( map, key );
	void * value = map -> entries[ ix ];

	map -> entries[ ix ] = NULL;

	return value;
}

void chpKeyclr ( char * chp )
{
	if ( chp != NULL ) {
		free ( chp );
		chp = NULL;
	}
}

int chpHash ( char * chp, int size )
{
	if ( chp == NULL ) return 0;

	size_t len = strlen ( chp );
	int ix = 0;
	int mx = 1;
	unsigned int sum = 0;
	
	do 
	{
		sum += chp[ ix ++ ] * mx;

		if ( ix % 4 == 0 ) mx = 1;
		else mx *= 256;
	} 
	while ( ix < len );

	return sum % size;
}

int intHash ( int * value, int size )
{
	return * value % size;
}

int intCmp ( int * a, int * b )
{
	return ( * a ) - ( * b );
}