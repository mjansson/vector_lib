/* matrix.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform vector math library in C11 providing basic support data types and
 * functions to write applications and games in a platform-independent fashion. The latest source code is
 * always available at
 *
 * https://github.com/rampantpixels/vector_lib
 *
 * This library is built on top of the foundation library available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.
 *
*/

#pragma once

/*! \file matrix.h
    Matrix math, row major (matrix row elements reside next to each
    other in memory), treating vectors as row vectors. Rotation matrix
    axes in matrix rows for efficient vector transform operations. */

#include <vector/types.h>
#include <vector/mask.h>
#include <vector/vector.h>

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_zero(void);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_identity(void);

//! Load unaligned
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_unaligned(const float32_t* FOUNDATION_RESTRICT m);

//! Load aligned (16-byte alignment)
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_aligned(const float32_aligned128_t* FOUNDATION_RESTRICT m);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_from_quaternion(const quaternion_t q);

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_transpose(const matrix_t m);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_mul(const matrix_t m0, const matrix_t m1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_add(const matrix_t m0, const matrix_t m1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_sub(const matrix_t m0, const matrix_t m1);

//! Treat vectors as row vectors, which puts axes in rows in matrix
//                 [ m00 m01 m02 m03 ]
// [ vx vy vz vw ] [ m10 m11 m12 m13 ] = [ m00*vx + m10*vy + m20*vz + m30*vw, m01*vx ... ]
//                 [ m20 m21 m22 m23 ]
//                 [ m30 m31 m32 m33 ]
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
matrix_rotate(const matrix_t m, const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
matrix_transform(const matrix_t m, const vector_t v);

#if FOUNDATION_ARCH_SSE4
#  include <vector/matrix_sse4.h>
#elif FOUNDATION_ARCH_SSE3
#  include <vector/matrix_sse3.h>
#elif FOUNDATION_ARCH_SSE2
#  include <vector/matrix_sse2.h>
#elif FOUNDATION_ARCH_NEON
#  include <vector/matrix_neon.h>
#else
#  include <vector/matrix_fallback.h>
#endif

