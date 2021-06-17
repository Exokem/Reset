
/// rconfig.h
///
/// Header containing definitions for various structures suited to the encapsulation
/// of configuration values.

#ifndef _RCONFIG_H
#define _RCONFIG_H

#define LIM_TITLE 128 ///< The default character limit for window titles.

/// win_cfg
///
/// Contains data for the configuration of windows, including dimensions and position
/// values. Titles are limited to LIM_TITLE characters.

typedef struct win_cfg
{
    int width;  ///< Window width ( px ).
    int height; ///< Window height ( px ).
    int x;      ///< Window x position ( px ).
    int y;      ///< Window y position ( px ).
    char title [ LIM_TITLE ];
} CFG_WIN;

#endif // _RCONFIG_H
