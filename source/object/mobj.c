
#include "mobj.h"
#include "res.h"

Mobj mobjInst ( char idn[ IDN_LIM ], SDL_Rect rec, Root root )
{
	Mobj mobj = NULL;
	mobj = malloc ( sizeof ( struct mobj_s ) );

	if ( mobj != NULL )
	{
		mobj -> ornt = DIR_AL;
		strcpy_s ( mobj -> idn, IDN_LIM, idn );

		mobj -> rec = rec;

		mobj -> mappings = NULL;
		HashMap mappings = NULL;
		mappings = mapInst ( DIR_CRD, &chpHash, &strcmp );

		if ( root != NULL )
		{
			for ( int dir = DIR_DV; dir < DIR_CRD; dir ++ )
			{
				// Create the resource identifier, attempt to load a resource.
				
				char resIdn[ IDN_LIM + 6 ];
				sprintf_s ( resIdn, IDN_LIM + 6, "%s_%d.bmp", idn, dir );

				SDL_Surface * surface = importAsset ( root, resIdn );

				if ( surface != NULL )
				{
					char ukey[ 16 ];
					sprintf_s ( ukey, 16, "%d", dir );

					IINS ( mappings, ukey, surface, 0 );
				}
			}
		}

		mobj -> mappings = mappings;
	}

	return mobj;
}

/// Clearing function for Mobj structure instances. Do not call with other objects.

void mobjClr ( Mobj mobj )
{
	if ( mobj == NULL ) return;

	// Mappings bind directions ( integral ) to SDL_Surfaces.
	// A clearing function for surfaces should not be required, surfaces should be managed
	// externally by a resource eater.

	if ( mobj -> mappings != NULL ) mapClr ( mobj -> mappings, NULL, NULL );

	free ( mobj );
	mobj = NULL;
}