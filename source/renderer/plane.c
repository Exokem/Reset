
#include "cut.h"
#include "plane.h"


Plane planeInst ( int depth )
{
	if ( depth <= 0 ) return NULL; 
	
	Plane plane = NULL;
	plane = inst ( plane_s );

	if ( plane == NULL ) return NULL;

	plane -> depth = depth;

	HashMap objsets = NULL;
	objsets = mapInst ( depth, &intHash, &intCmp );

	for ( int ix = 0; ix < depth; ix ++ )
	{
		Objset set = NULL;
		set = inst ( objset_s );

		if ( set != NULL )
		{
			int * key = NULL;
			key = malloc ( sizeof ( int ) );
			* key = ix;
			
			set -> volume = 0;
			set -> objects = NULL;
			set -> objects = malloc ( 0 );

			mapInsert ( objsets, key, set, &free, &objSetClr, 0 );
		}
	}

	return plane;
}

void objSetClr ( Objset objset )
{
	if ( objset == NULL ) return;

	Mobj * objects = objset -> objects;

	if ( objects != NULL )
	{
		for ( int ix = 0; ix < objset -> volume; ix ++ )
		{
			mobjClr ( objects[ ix ] );
		}

		free ( objects );
		objset -> objects = NULL;
	}

	free ( objset );
	objset = NULL;
}