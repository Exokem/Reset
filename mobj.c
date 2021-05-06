
#include "mobj.h"

Mrec defineMrec ( int x, int y, int w, int h )
{
	Mrec rec = NULL; 
	rec = malloc ( sizeof ( Mrec ) );

	if ( rec != NULL )
	{
		rec -> x = x;
		rec -> y = y;
		rec -> w = w;
		rec -> h = h;
	}

	return rec;
}

Mobj mobjInst ( char idn[ IDN_LIM ], Mrec rec, SDL_Surface * ( * binder ) ( char * ) )
{
	Mobj mobj = NULL;
	mobj = malloc ( sizeof ( Mobj ) );

	if ( mobj != NULL )
	{
		mobj -> ornt = DIR_AL;
		strcpy ( mobj -> idn, idn );
		
		mobj -> rec = NULL;
		mobj -> rec = rec;

		mobj -> mappings = NULL;
		HashMap mappings = NULL;
		mappings = mapBuild ( DIR_CRD, &chpHash, &strcmp );

		if ( binder != NULL )
		{
			for ( int dir = DIR_DV; dir < DIR_CRD; dir ++ )
			{
				// Create the resource identifier, attempt to load a resource.
				
				char resIdn[ IDN_LIM + 1 ];
				strcpy ( resIdn, idn );

				IINS ( mappings, dir, binder ( resIdn ) );
			}
		}

		mobj -> mappings = mappings;
	}

	return mobj;
}

/// Clearing function for Mobj structure instances. Do not call with other objects.

void mobjClr ( void * vpt )
{
	if ( vpt == NULL ) return;
	
	Mobj mobj = vpt;

	if ( mobj -> rec != NULL ) free ( mobj -> rec );

	// Mappings bind directions ( integral ) to SDL_Surfaces.
	// A clearing function for surfaces should not be required, surfaces should be managed
	// externally by a resource eater.

	if ( mobj -> mappings != NULL ) mapDestroy ( mobj -> mappings, NULL, NULL );

	free ( mobj );
}