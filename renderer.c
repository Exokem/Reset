
#include "renderer.h"
#include "cut.h"

void adjunctDebug ( Adjunct adj, SDL_Surface * surface )
{
	nullck ( adj );
	nullck ( surface );

	SDL_Rect rect = { .x = ( int ) adj -> x - 2, .y = ( int ) adj -> z - 2, .w = 5, .h = 5 };
	Uint32 color = SDL_MapRGB ( surface -> format, 255, 0, 0 );

	SDL_FillRect ( surface, &rect, color );

	nullck ( adj -> desc );
	foreach ( adj -> desc, adj -> links )
	{
		adjunctDebug ( adj -> desc[ ix ], surface );
	}
}

void adjDbg ( Adjunct adj, Root root )
{
	nullck ( adj );
	nullck ( root );

	int x = ( int ) adj -> x;
	int z = ( int ) adj -> z;

	SDL_Rect rect = { .x = x - 2, .y = z - 2, .w = 5, .h = 5 };
	SDL_Renderer * renderer = root -> renderer;

	nullck ( renderer );

	SDL_SetRenderDrawColor ( renderer, 255, 0, 0, 255 );
	SDL_RenderDrawRect ( root -> renderer, &rect );

	nullck ( adj -> desc );
	foreach ( adj -> desc, adj -> links )
	{
		Adjunct desc = adj -> desc[ ix ];

		SDL_RenderDrawLine ( renderer, x, z, ( int ) desc -> x, ( int ) desc -> z );
		adjDbg ( desc, root );
	}
}