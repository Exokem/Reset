
/// rdata.h
///
/// Header containing definitions of various structures suited to data encapsulation
/// for specific cases.

#ifndef _RDATA_H
#define _RDATA_H

/// win_data_s
///
/// Encapsulates various fields relevant to the operation of a window.

typedef struct win_data_s
{
    SDL_Window * window;     ///< The SDL2 window reference.
    SDL_Renderer * renderer; ///< The SDL2 renderer associated with the window.
} DATA_WIN;

#endif // _RDATA_H
