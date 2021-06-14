
#ifndef _RCONFIG_H
#define _RCONFIG_H

#define LIM_TITLE 128

/// The win_cfg ( CFG_WIN ) structure contains data for the configuration
/// of windows.

typedef struct win_cfg
{
    int width;
    int height;
    int x;
    int y;
    char title[LIM_TITLE];
} CFG_WIN;

#endif // _RCONFIG_H
