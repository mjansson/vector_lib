/* matrix.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform vector math library in C11 providing basic support data
 * types and functions to write applications and games in a platform-independent fashion. The latest
 * source code is always available at
 *
 * https://github.com/rampantpixels/vector_lib
 *
 * This library is built on top of the foundation library available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any
 * restrictions.
 *
 */

#pragma once

/*! \file matrix.h
    Matrix math, row major where each element in one row of the matrix
    reside next to each other in memory. Matrix components are laid out like
      m00  m01  m02  m03  -- Row 0
      m10  m11  m12  m13  -- Row 1
      m20  m21  m22  m23  -- Row 2
      m30  m31  m32  m33  -- Row 3
    mapping to a two-dimensional C array with row as major array index like
      frow[0][0]  frow[0][1]  frow[0][2]  frow[0][3]  -- Row 0
      frow[1][0]  frow[1][1]  frow[1][2]  frow[1][3]  -- Row 1
      frow[2][0]  frow[2][1]  frow[2][2]  frow[2][3]  -- Row 2
      frow[3][0]  frow[3][1]  frow[3][2]  frow[3][3]  -- Row 3
    mapping to a flat C array like
      arr[0]  arr[1]  arr[2]  arr[3]   -- Row 0
      arr[4]  arr[5]  arr[6]  arr[7]   -- Row 1
      arr[8]  arr[9]  arr[10] arr[11]  -- Row 2
      arr[12] arr[13] arr[14] arr[15]  -- Row 3
    */

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

//! Create scaling matrix from vector
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_scaling(const vector_t scale);

//! Create scaling matrix from scalar values
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_scaling_scalar(float32_t x, float32_t y, float32_t z);

//! Create translation matrix from vector
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_translation(const vector_t translation);

//! Create translation matrix from scalar values
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_translation_scalar(float32_t x, float32_t y, float32_t z);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_transpose(const matrix_t m);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_mul(const matrix_t m0, const matrix_t m1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_add(const matrix_t m0, const matrix_t m1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_sub(const matrix_t m0, const matrix_t m1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
matrix_get_translation(const matrix_t m);

#if VECTOR_IMPLEMENTATION_SSE4
#include <vector/matrix_sse4.h>
#elif VECTOR_IMPLEMENTATION_SSE3
#include <vector/matrix_sse3.h>
#elif VECTOR_IMPLEMENTATION_SSE2
#include <vector/matrix_sse2.h>
#elif VECTOR_IMPLEMENTATION_NEON
#include <vector/matrix_neon.h>
#else
#include <vector/matrix_fallback.h>
#endif
