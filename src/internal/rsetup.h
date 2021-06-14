
/// rsetup.h
///
/// Reset Setup
///
/// Generified setup functions for various elements in the display.

#ifndef _RSETUP_H
#define _RSETUP_H

#include "depn.h"    // Provides SDL includes.
#include "rconfig.h" // Provides CFG_WIN.
#include "rdata.h"   // Provides DATA_WIN.

/// r_sdlset
///
/// Attempts to initialize required libraries ( SDL2, SDL2\IMG ). Displays any errors
/// produced by a failure to initialize a library before causing the program to exit.

void r_sdlset ();

/// r_winset
///
/// Attempts to create an SDL window using a set of configuration parameters.
///
/// @param An instance of the window configuration structure CFG_WIN. @see rconfig.h.
///
/// @return A nullable SDL_Window pointer representing the created window.

SDL_Window * r_winset ( CFG_WIN );

/// r_dispset
///
/// Produces a window data structure using a window configuration.
/// Note: this function may not fail when the window cannot be created.
///
/// @param An instance of the window configuration structure CFG_WIN. @see rconfig.h.
///
/// @return An instance of the window data structure DATA_WIN @see rdata.h.

DATA_WIN r_dispset ( CFG_WIN );

#endif // _RSETUP_H
