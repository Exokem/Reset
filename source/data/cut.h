#ifndef _CUT_H
#define _CUT_H

#include <stdlib.h>

#define inst( struct_id ) malloc ( sizeof ( struct struct_id ) )
#define iinst( instance, struct_id ) instance = ( ( void * ) 0 );\
			instance = inst ( struct_id )
#define setm( instance, field ) instance -> field = field
#define setd( instance, field, value ) instance -> field = value
#define nullck( ptr ) if ( ptr == NULL ) return
#define nlcknl( ptr ) if ( ptr == NULL ) return NULL
#define nlinst( instance, value ) instance = NULL;\
			instance = value

#define eqret( val1, val2, retval ) if ( val1 == val2 ) return retval
#define eqact( val1, val2, act ) if ( val1 == val2 ) { act; }
#define neqact( val1, val2, act ) if ( val1 != val2 ) { act; }
#define sizeinst( inst, stid, amt ) inst = NULL;\
			inst = malloc ( sizeof ( struct stid ) * amt )
#define foreach( set, size ) for ( size_t ix = 0; ix < size; ix ++ )

#define nulret( val, ret ) if ( val == NULL ) { return ret; }

#endif