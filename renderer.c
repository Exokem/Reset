
#include "renderer.h"
#include "cut.h"

void adjunctDebug ( Adjunct adj, SDL_Surface * surface )
{
	nullck ( adj );
	nullck ( surface );

	SDL_Rect rect = { .x = adj -> x - 2, .y = adj -> z - 2, .w = 4, .h = 4 };
	Uint32 color = SDL_MapRGB ( surface -> format, 255, 0, 0 );

	SDL_FillRect ( surface, &rect, color );

	nullck ( adj -> desc );
	foreach ( adj -> desc, adj -> links )
	{
		adjunctDebug ( adj -> desc[ ix ], surface );
	}
}