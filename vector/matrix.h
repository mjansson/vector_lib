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

/*! \file math/matrix.h
    Matrix math */

#include <vector/types.h>
#include <vector/mask.h>

#include <foundation/math.h>


static FORCEINLINE CONSTCALL matrix_t   matrix_zero( void );

static FORCEINLINE CONSTCALL matrix_t   matrix_identity( void );

//! Load unaligned
static FORCEINLINE PURECALL  matrix_t   matrix_unaligned( const float32_t* RESTRICT m );

//! Load aligned (16-byte alignment)
static FORCEINLINE PURECALL  matrix_t   matrix_aligned( const float32_aligned128_t* RESTRICT m );

static FORCEINLINE PURECALL  matrix_t   matrix_transpose( const matrix_t m );

static FORCEINLINE CONSTCALL matrix_t   matrix_mul( const matrix_t m0, const matrix_t m1 );
static FORCEINLINE CONSTCALL matrix_t   matrix_add( const matrix_t m0, const matrix_t m1 );
static FORCEINLINE CONSTCALL matrix_t   matrix_sub( const matrix_t m0, const matrix_t m1 );

//! Treat vectors as column vectors
static FORCEINLINE CONSTCALL vector_t   matrix_rotate( const matrix_t m, const vector_t v );
static FORCEINLINE CONSTCALL vector_t   matrix_transform( const matrix_t m, const vector_t v );


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

