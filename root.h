
#ifndef _ROOT_H
#define _ROOT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#ifndef _DEFAULT_DIM_

#define WIN_HZ 1920
#define WIN_VT 1080

#endif

typedef struct
{
	SDL_Surface ** surface_set;
	int surfaces;
} * ResourceEater;

typedef struct
{
	SDL_Window * window;
	SDL_Surface * screen;
	ResourceEater eater;
	int terminated;
} * Root;

Root setup ();

ResourceEater defineEater ();

void dismantleRoot ( Root root );

void terminateRoot ( Root root );

void trackSurface ( Root root, SDL_Surface * surface );

void eat ( ResourceEater eater );

#endif