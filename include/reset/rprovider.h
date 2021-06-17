
/// rprovider.h
///
/// The Resource Provider includes functions suited to the location of resources and
/// management of valid resource directories.

#ifndef _RPROVIDER_H
#define _RPROVIDER_H

#define RPROVIDER_INDEX_DEFAULT 8   ///< The default directory limit.
#define RPROVIDER_INDEX_INCREMENT 2 ///< The default directory limit increment.

#include "depn.h"

/// rprovider_init
///
/// Initializes the Resource Provider. This includes tasks such as initializing the
/// directory set and any other related states.

void rprovider_init ( void );

/// register_directory
///
/// Registers a specified directory with the Resource Provider.
///
/// If the directory index is full, it will be resized automatically.
/// If the Resource Provider has not been initialized, it will be initialized
/// automatically before registering the directory provided.
///
/// Directory names may be formatted with subfolders, but slashes should be used only
/// between subfolders and not at either end of the string.
///
/// Directories must exist within the resources directory at the root of the program.
///
/// @param The name of the directory to register.

void register_directory ( char * );

/// locate_resource_sf
///
/// Attempts to locate a specific named resource as an SDL_Surface.
///
/// This function attempts to discover the specified resource by searching for it in
/// each registered resource directory.
///
/// The return value of this function may be NULL whenever the parameters are invalid,
/// or when the named resource could not be found in any registered directory.
///
/// @param The specific name of the resource to be located.
///
/// @return A NULLABLE SDL_Surface pointer representing the located or missing resource.

SDL_Surface * locate_resource_sf ( char * );

/// locate_resource_tx
///
/// Attempts to locate a specific named resource as an SDL_Texture.
///
/// This function attempts to discover the specified resource by searching for it in
/// each registered resource directory.
///
/// The return value of this function may be NULL whenever the parameters are invalid,
/// or when the named resource could not be found in any registered directory.
///
/// An SDL_Renderer instance is required for the creation of SDL_Texture instances.
///
/// @param The SDL_Renderer used for texture operations.
/// @param The specific name of the resource to be located.
///
/// @return A NULLABLE SDL_Texture pointer representing the located or missing resource.

SDL_Texture * locate_resource_tx ( SDL_Renderer *, char * );

#endif // _RPROVIDER_H
