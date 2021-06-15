
/// rvector.h
///
/// Includes various structures for the purpose of representing vectors with multiple
/// distinct dimensions in a compact manner.
///
/// Structures ending in 'I' contain signed integers, structures ending in 'D'
/// contain doubles, structures ending in 'U' contain unsigned integers.

#ifndef _RVECTOR_H
#define _RVECTOR_H

typedef struct int_vec2_s
{
    int a, b;
} VEC2I;

typedef struct uint_vec2_s
{
    size_t a, b;
} VEC2U;

typedef struct double_vec3_s
{
    double x, y, z;
} VEC3D;

typedef struct int_vec3_s
{
    int x, y, z;
} VEC3I;

#endif // _RVECTOR_H
