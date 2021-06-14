
/// provider.h
///
/// The Resource Provider includes functions suited to the location of resources and
/// management of valid resource directories.

#ifndef _PROVIDER_H
#define _PROVIDER_H

#define PROVIDER_INDEX_DEFAULT 8   ///< The default directory limit.
#define PROVIDER_INDEX_INCREMENT 2 ///< The default directory limit increment.

#include "depn.h"

/// provider_init
///
/// Initializes the Resource Provider. This includes tasks such as initializing the
/// directory set and any other related states.

void provider_init ( void );

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

/// locate_resource
///
/// Attempts to locate a specific named resource.
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

SDL_Surface * locate_resource ( char * );

#endif // _PROVIDER_H
