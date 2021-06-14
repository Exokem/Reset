
#ifndef _RSETUP_H
#define _RSETUP_H

#include "depn.h"
#include "rconfig.h"
#include "rdata.h"

void r_sdlset ();

SDL_Window * r_winset ( CFG_WIN );

DATA_WIN r_dispset ( CFG_WIN );

#endif // _RSETUP_H
