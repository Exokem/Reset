
#ifndef _MAP_H
#define _MAP_H

#define HASH( map, key ) map -> hash ( key, map -> limit );
#define RETR( map, index ) map -> entries[ index ];
#define INST( map, index, value ) map -> entries[ index ] = value;
#define CONT( map, key ) map -> entries[ HASH ( map, key ) ] != NULL;

/// Simple Insert: key, value only.
/// Incremented Insert: key, value, and increment for map expansion.
/// Memory-Conscious Insert: key, value, and memory clearing functions.

#define SINS( map, key, value ) mapIns ( map, key, value, NULL, NULL, DEFAULT_INCREMENT );
#define IINS( map, key, value, inc ) mapIns ( map, key, value, NULL, NULL, inc );
#define MINS( map, key, value, kclr, vclr ) mapIns ( map, key, value, kclr, vclr, DEFAULT_INCREMENT );

#define EQUIVALENT 0

#ifndef _TABLE_DEF

typedef struct 
{
	int limit;       ///< Size of the table ( current capacity ).
	int volume;      ///< Volume of the table ( used spaces ).

	int ** data;     ///< Integral array backing the table.
} * HashTable;

#endif

#ifndef _ENTRY_DEF

typedef struct 
{
	void * key;	     ///< Key of the entry.
	void * value;    ///< Generic value of the entry.
} * Entry;

#endif

#ifndef _MAP_DEF

typedef struct 
{
	int limit;       ///< Volume limit of the table.
	int volume;      ///< Volume of the table.
	
	int ( * hash ) ( void *, int ); ///< Hash function for the map.
	int ( * eq ) ( void *, void * );    ///< Key equivalence function.

	Entry * entries; ///< Array of entries - the content of the map.
} * HashMap;

#endif

HashMap mapBuild 
( 
	int limit,
	int ( * hash ) ( void *, int ),
	int ( * eq ) ( void *, void * )
);

void mapDestroy
(
	HashMap map,
	void ( * keyclr ) ( void * ),
	void ( * valclr ) ( void * )
);

void mapIns
(
	HashMap map, 
	void * key, void * value,
	void ( * keyclr ) ( void * ),
	void ( * valclr ) ( void * ),
	int increment
);

void * mapAcck
(
	HashMap map, 
	void * key
);

/// Remove an entry from the map by its index.

void * mapRemk
(
	HashMap map,
	void * key
);

/// Remove an entry from the map by its key.

void * mapRemi
(
	HashMap map,
	int index
);

void chpKeyclr 
( 
	char * chp 
);

int chpHash 
( 
	void * vpt, 
	int size 
);

#endif