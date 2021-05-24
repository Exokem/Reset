
#include "keyin.h"
#include "cut.h"

SDL_Scancode AZK = SDL_SCANCODE_W;
SDL_Scancode DZK = SDL_SCANCODE_S;
SDL_Scancode AXK = SDL_SCANCODE_D;
SDL_Scancode DXK = SDL_SCANCODE_A;

Vecdir keyProcess ( SDL_Keycode key )
{
	eqret ( AZK, key, AZ );
	eqret ( DZK, key, DZ );
	eqret ( AXK, key, AX );
	eqret ( DXK, key, DX );

	return OO;
}

Vecdir readKeyboardState ( int size, const Uint8 * keyStates )
{
	Vecdir vd = OO;

	if ( AZK < size && keyStates[ AZK ] ) vd = vecdirSum ( vd, AZ );
	if ( DZK < size && keyStates[ DZK ] ) vd = vecdirSum ( vd, DZ );
	if ( AXK < size && keyStates[ AXK ] ) vd = vecdirSum ( vd, AX );
	if ( DXK < size && keyStates[ DXK ] ) vd = vecdirSum ( vd, DX );

	return vd;
}