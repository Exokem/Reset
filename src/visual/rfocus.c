
#include "rfocus.h"

RFOCUS rfocus_inst ( VEC3D angles, VEC3I offsets )
{
    RFOCUS focus = inst ( rfocus_s );

    retnulv ( focus, NULL );

    focus -> angles = angles;
    focus -> offsets = offsets;

    return focus;
}
