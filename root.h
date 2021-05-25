
#ifndef _ROOT_H
#define _ROOT_H

#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "options.h"

#ifndef _DEFAULT_DIM_

#endif

/**
* A ResourceEater ( res_eat_s ) should be used to track dynamic resources.
* 
* The format of a ResourceEater should allow a variety of resources to be managed uniformly.
*/
typedef struct res_eat_s
{
	SDL_Surface ** surface_set; ///< The array of tracked SDL surfaces.
	size_t surfaces; ///< The number of tracked SDL surfaces.
} * ResourceEater; 

/**
* A Root ( root_s ) is the root structure for the program. 
* 
* This structure contains the SDL window, screen, and a ResourceEater for SDL resource management.
*/
typedef struct root_s
{
	SDL_Window * window; ///< The program window. 
	SDL_Surface * screen; ///< The program window surface.
	SDL_Renderer * renderer; ///< The program renderer.
	ResourceEater eater; ///< The resource eater for the program.
} * Root;

/// <summary>
/// The setup function provides a fully initialized Root. This includes all of the setup tasks
/// required for SDL. 
/// </summary>
Root setup ();

ResourceEater defineEater ();

void dismantleRoot ( Root root );

void terminateRoot ( Root root );

void trackSurface ( Root root, SDL_Surface * surface );

void eat ( ResourceEater eater );

#endif