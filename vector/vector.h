/* vector.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

/*! \file math/vector.h
    Vector math */

#include <vector/types.h>
#include <vector/mask.h>

#include <foundation/math.h>


//! Load unaligned
static FORCEINLINE CONSTCALL vector_t   vector( const real x, const real y, const real z, const real w );

//! Load unaligned
static FORCEINLINE PURECALL  vector_t   vector_unaligned( const float32_t* RESTRICT v );

//! Load aligned (16-byte alignment)
static FORCEINLINE PURECALL  vector_t   vector_aligned( const float32_aligned128_t* RESTRICT v );

//! Load aligned (16-byte alignment) single uniform
static FORCEINLINE CONSTCALL vector_t   vector_uniform( const real v );

//! Load predefined vectors
static FORCEINLINE CONSTCALL vector_t   vector_zero( void );  // [ 0, 0, 0, 0 ]
static FORCEINLINE CONSTCALL vector_t   vector_one( void );   // [ 1, 1, 1, 1 ]
static FORCEINLINE CONSTCALL vector_t   vector_half( void );  // [ 0.5, 0.5, 0.5, 0.5 ]
static FORCEINLINE CONSTCALL vector_t   vector_two( void );   // [ 2, 2, 2, 2 ]
static FORCEINLINE CONSTCALL vector_t   vector_origo( void ); // [ 0, 0, 0, 1 ]
static FORCEINLINE CONSTCALL vector_t   vector_xaxis( void ); // [ 1, 0, 0, 1 ]
static FORCEINLINE CONSTCALL vector_t   vector_yaxis( void ); // [ 0, 1, 0, 1 ]
static FORCEINLINE CONSTCALL vector_t   vector_zaxis( void ); // [ 0, 0, 1, 1 ]

static FORCEINLINE CONSTCALL vector_t   vector_normalize( const vector_t v );
static FORCEINLINE CONSTCALL vector_t   vector_normalize3( const vector_t v );

static FORCEINLINE CONSTCALL vector_t   vector_dot( const vector_t v0, const vector_t v1 );
static FORCEINLINE CONSTCALL vector_t   vector_dot3( const vector_t v0, const vector_t v1 );

static FORCEINLINE CONSTCALL vector_t   vector_cross3( const vector_t v0, const vector_t v1 );

static FORCEINLINE CONSTCALL vector_t   vector_mul( const vector_t v0, const vector_t v1 );
static FORCEINLINE CONSTCALL vector_t   vector_div( const vector_t v0, const vector_t v1 );
static FORCEINLINE CONSTCALL vector_t   vector_add( const vector_t v0, const vector_t v1 );
static FORCEINLINE CONSTCALL vector_t   vector_sub( const vector_t v0, const vector_t v1 );
static FORCEINLINE CONSTCALL vector_t   vector_neg( const vector_t v );

static FORCEINLINE CONSTCALL vector_t   vector_shuffle( const vector_t v, const unsigned int mask );
static FORCEINLINE CONSTCALL vector_t   vector_scale( const vector_t v, const real s );
static FORCEINLINE CONSTCALL vector_t   vector_lerp( const vector_t from, const vector_t to, const real factor );
static FORCEINLINE CONSTCALL vector_t   vector_reflect( const vector_t v, const vector_t at );

static FORCEINLINE CONSTCALL vector_t   vector_length( const vector_t v );
static FORCEINLINE CONSTCALL vector_t   vector_length_fast( const vector_t v );
static FORCEINLINE CONSTCALL vector_t   vector_length_sqr( const vector_t v );
static FORCEINLINE CONSTCALL vector_t   vector_length3( const vector_t v );
static FORCEINLINE CONSTCALL vector_t   vector_length3_fast( const vector_t v );
static FORCEINLINE CONSTCALL vector_t   vector_length3_sqr( const vector_t v );

static FORCEINLINE CONSTCALL vector_t   vector_min( const vector_t v0, const vector_t v1 );
static FORCEINLINE CONSTCALL vector_t   vector_max( const vector_t v0, const vector_t v1 );

static FORCEINLINE CONSTCALL real       vector_x( const vector_t v );
static FORCEINLINE CONSTCALL real       vector_y( const vector_t v );
static FORCEINLINE CONSTCALL real       vector_z( const vector_t v );
static FORCEINLINE CONSTCALL real       vector_w( const vector_t v );
static FORCEINLINE CONSTCALL real       vector_component( const vector_t v, int c );

static FORCEINLINE CONSTCALL bool       vector_equal( const vector_t v0, const vector_t v1 );


#define VECTOR_IMPLEMENTATION_SSE4 0
#define VECTOR_IMPLEMENTATION_SSE3 0
#define VECTOR_IMPLEMENTATION_SSE2 0
#define VECTOR_IMPLEMENTATION_NEON 0
#define VECTOR_IMPLEMENTATION_FALLBACK 0


#if FOUNDATION_ARCH_SSE4
#  include <vector/vector_sse4.h>
#  undef  VECTOR_IMPLEMENTATION_SSE4
#  define VECTOR_IMPLEMENTATION_SSE4 1
#elif FOUNDATION_ARCH_SSE3
#  include <vector/vector_sse3.h>
#  undef  VECTOR_IMPLEMENTATION_SSE3
#  define VECTOR_IMPLEMENTATION_SSE3 1
#elif FOUNDATION_ARCH_SSE2
#  include <vector/vector_sse2.h>
#  undef  VECTOR_IMPLEMENTATION_SSE2
#  define VECTOR_IMPLEMENTATION_SSE2 1
#elif FOUNDATION_ARCH_NEON
#  include <vector/vector_neon.h>
#  undef  VECTOR_IMPLEMENTATION_NEON
#  define VECTOR_IMPLEMENTATION_NEON 1
#else
#  include <vector/vector_fallback.h>
#  undef  VECTOR_IMPLEMENTATION_FALLBACK
#  define VECTOR_IMPLEMENTATION_FALLBACK 1
#endif
