
#ifndef _MAP_H
#define _MAP_H

#define HASH( map, key ) map -> hash ( key, map -> limit );
#define RETRV( map, index ) map -> entries[ index ];
#define INSRT( map, index, value ) map -> entries[ index ] = value;
#define CONTS( map, key ) map -> entries[ HASH ( map, key ) ] != NULL;

/// Simple Insert: key, value only.
/// Incremented Insert: key, value, and increment for map expansion.
/// Memory-Conscious Insert: key, value, and memory clearing functions.

#define SINS( map, key, value ) mapInsert ( map, key, value, NULL, NULL, DEFAULT_INCREMENT );
#define IINS( map, key, value, inc ) mapInsert ( map, key, value, NULL, NULL, inc );
#define MINS( map, key, value, kclr, vclr ) mapInsert ( map, key, value, kclr, vclr, DEFAULT_INCREMENT );

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

typedef struct entry_s
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

HashMap mapInst 
( 
	int limit,
	int ( * hash ) ( void *, int ),
	int ( * eq ) ( void *, void * )
);

void mapClr
(
	HashMap map,
	void ( * keyclr ) ( void * ),
	void ( * valclr ) ( void * )
);

void mapInsert
(
	HashMap map, 
	void * key, 
	void * value,
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

/// Key clearing function for dynamically allocated char pointers.
/// DO NOT use with statically allocated char pointers.

void chpKeyclr 
( 
	char * chp 
);

/// Hash function for char pointer keys.
/// Applies a power multiplier to character values 4 bytes at a time to expand the range of
/// produced indices.

int chpHash 
( 
	void * vpt, 
	int size 
);

int intHash
(
	int * value, 
	int size
);

int intCmp
(
	int * a, 
	int * b
);

#endif