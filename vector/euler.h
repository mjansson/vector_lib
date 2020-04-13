/* euler.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
 *
 * This library provides a cross-platform vector math library in C11 providing basic support data
 * types and functions to write applications and games in a platform-independent fashion. The latest
 * source code is always available at
 *
 * https://github.com/mjansson/vector_lib
 *
 * This library is built on top of the foundation library available at
 *
 * https://github.com/mjansson/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any
 * restrictions.
 *
 */

#pragma once

/*! \file euler.h
    Euler angles representation */

#include <foundation/platform.h>
#include <foundation/types.h>

#include <vector/types.h>

VECTOR_API euler_angles_t
euler_angles(real rx, real ry, real rz, euler_angles_order_t order);

VECTOR_API quaternion_t
euler_angles_to_quaternion(const euler_angles_t angles);

// VECTOR_API euler_angles_t
// euler_angles_from_quaternion(const quaternion_t q, euler_angles_order_t order);
