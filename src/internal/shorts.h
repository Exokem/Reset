
/// shorts.h
///
/// Contains shortcut macros to simplify repeated elements.

#ifndef _SHORTS_H
#define _SHORTS_H

// Dynamic structure instancing
#define inst( struct_id ) malloc ( sizeof ( struct struct_id ) );

// Dynamic structure array instancing
#define minst( struct_id, amount ) malloc ( sizeof ( struct struct_id ) * amount );

// Generic typed allocation
#define galloc( type ) malloc ( sizeof ( type ) );

// Generic typed array allocation
#define mxalloc( type, amount ) malloc ( sizeof ( type ) * amount );

// Array based increment
#define foreach( type, var, set, size ) for ( size_t ix = 0, type var = set [ ix ]; ix < size; var = set [ ++ ix ] )

// Simple incremented loop header for unsigned indices
#define fori( size ) for ( size_t ix = 0; ix < size; ix ++ )

// Simple incremented loop header for signed indices
#define forsi( size ) for ( int ix = 0; ix < size; ix ++ )

// Pointer dereference
#define deref( ptr, var ) var = * ptr;

// Array index access
#define ixget( ptr, ix ) ptr [ ix ];

// Void return null check
#define retnul( ptr ) if ( ptr == ( void * ) 0 ) return;

// Value return null check
#define retnulv( ptr, val ) if ( ptr == ( void * ) 0 ) return val;

#endif // _SHORTS_H
