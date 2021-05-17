
#ifndef _ROOT_H
#define _ROOT_H



#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef _DEFAULT_DIM_

#define WIN_HZ 1920
#define WIN_VT 1080

#endif

typedef struct res_eat_s
{
	SDL_Surface ** surface_set;
	size_t surfaces;
} * ResourceEater;

typedef struct root_s
{
	SDL_Window * window;
	SDL_Surface * screen;
	ResourceEater eater;
} * Root;

Root setup ();

ResourceEater defineEater ();

void dismantleRoot ( Root root );

void terminateRoot ( Root root );

void trackSurface ( Root root, SDL_Surface * surface );

void eat ( ResourceEater eater );

#endif