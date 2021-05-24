
#ifndef _KEYIN_H
#define _KEYIN_H

#include <SDL2/SDL_keyboard.h>

#include "vecdir.h"

Vecdir keyProcess ( SDL_Keycode );

Vecdir readKeyboardState ( int, const Uint8 * );

#endif