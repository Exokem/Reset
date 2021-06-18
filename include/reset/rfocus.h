
/// rfocus.h
///
/// Focus structures pertain to the rendering of specific content segments. A given
/// focus may be translated to adjust the position of its rendered contents. In many
/// respects, a focus is like the camera for a program.

#ifndef _RFOCUS_H
#define _RFOCUS_H

#include "depn.h"
#include "rrcon.h"
#include "rvector.h"
#include "rtilemap.h"
#include "rlevel.h"

/// rfocus_mode_e
///
/// Enumerated values for the possible focus modes.

typedef enum rfocus_mode_e
{
    F_FLAT_TILEMAP,   ///< The focus will use a single tilemap.
    F_LAYERED_TILEMAP ///< The focus will use multiple layered tilemaps ( RLEVELMAP ).
} FocusMode;

/// rfocus_s
///
/// The RFOCUS structure represents the viewport of the program. It is responsible
/// for managing the different menus and displays that a program might have.

typedef struct rfocus_s
{
    FocusMode focus_mode; ///< The type of display that is currently displayed

    VEC3D angle;  ///< The current angle vector of the view.
    VEC3I offset; ///< The offset vector for content displayed withing the view.

    union content
    {
        RTILEMAP tilemap;   ///< RTILEMAP is used by any F_FLAT_TILEMAP RFOCUS.
        RLEVEL level; ///< RLEVELMAP is used by any F_LAYERED_TILEMAP RFOCUS.
    } content;

} * RFOCUS;

/// rfocus_inst
///
/// Provides a new RFOCUS instance, initialized with the specified FocusMode.
/// The angle and offset fields of the instance may be populated with default values.
///
/// @param The FocusMode of the RFOCUS.
///
/// @return An RFOCUS instance.

RFOCUS rfocus_inst ( FocusMode );

/// rfocus_vinst
///
/// Provides a new RFOCUS instance, initialized with the specified FocusMode, as well
/// as the provided angle and offset vectors.
///
/// @param The FocusMode of the RFOCUS.
/// @param The initial angle vector of the RFOCUS.
/// @param The initial offset vector of the RFOCUS.
///
/// @return An RFOCUS instance.

RFOCUS rfocus_vinst ( FocusMode, VEC3D, VEC3I );

/// rfocus_render_content
///
/// Renders the current content of the provided RFOCUS, using data provided by an
/// RRCON.
///
/// @param The RFOCUS whose content will be rendered.
/// @param The RRCON containing relevant resource and rendering data.

void rfocus_render_content ( RFOCUS, RRCON );

/// rfocus_translate
///
/// Translates the provided RFOCUS using a translation vector. The vector of
/// translation must be signed and integral.
///
/// @param The RFOCUS to be translated.
/// @param The VEC3I containing axis translation quantities.

void rfocus_translate ( RFOCUS, VEC3I );

/// rfocus_clr
///
/// Clears the provided RFOCUS from active memory. The current contents of the RFOCUS
/// must be cleared separately if that is the desired effect.
///
/// @param The RFOCUS to be cleared.

void rfocus_clr ( RFOCUS );

#endif // _RFOCUS_H
