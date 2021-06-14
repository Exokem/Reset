
#ifndef _SHORTS_H
#define _SHORTS_H

#define inst( struct_id ) malloc ( sizeof ( struct struct_id ) ); ///< Dynamic structure instancing
#define minst( struct_id, amount ) malloc ( sizeof ( struct struct_id ) * amount );

#define galloc( type ) malloc ( sizeof ( type ) );
#define mxalloc( type, amount ) malloc ( sizeof ( type ) * amount );

#define foreach( type, var, set, size ) for ( size_t ix = 0, type var = set [ ix ]; ix < size; var = set [ ++ ix ] )
#define fori( size ) for ( size_t ix = 0; ix < size; ix ++ )

#define deref( ptr, var ) var = * ptr;

#define ixget( ptr, ix ) ptr [ ix ];

#define retnul( ptr ) if ( ptr == ( void * ) 0 ) return;
#define retnulv( ptr, val ) if ( ptr == ( void * ) 0 ) return val;

#endif // _SHORTS_H
