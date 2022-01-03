/* vector.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
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

/*! \file vector.h
    Vector math */

#include <vector/types.h>
#include <vector/mask.h>

VECTOR_API int
vector_module_initialize(const vector_config_t config);

VECTOR_API void
vector_module_finalize(void);

VECTOR_API bool
vector_module_is_initialized(void);

VECTOR_API version_t
vector_module_version(void);

//! Load unaligned
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector(const real x, const real y, const real z, const real w);

//! Load unaligned
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_unaligned(const float32_t* FOUNDATION_RESTRICT v);

//! Load aligned (16-byte alignment)
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_aligned(const float32_aligned128_t* FOUNDATION_RESTRICT v);

//! Load single uniform
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_uniform(const real v);

//! Load predefined vectors
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zero(void);  // [ 0, 0, 0, 0 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_one(void);  // [ 1, 1, 1, 1 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_half(void);  // [ 0.5, 0.5, 0.5, 0.5 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_two(void);  // [ 2, 2, 2, 2 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_origo(void);  // [ 0, 0, 0, 1 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_xaxis(void);  // [ 1, 0, 0, 1 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_yaxis(void);  // [ 0, 1, 0, 1 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zaxis(void);  // [ 0, 0, 1, 1 ]

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize3(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot3(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_cross3(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_mul(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_div(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_add(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sub(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_neg(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_muladd(const vector_t v0, const vector_t v1, const vector_t v2);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle(const vector_t v, const unsigned int mask);

// Shuffle two components from each vector into final result
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle2(const vector_t v0, const vector_t v1, const unsigned int mask);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_scale(const vector_t v, const real s);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_lerp(const vector_t from, const vector_t to, const real factor);

//! Project and reflect on non-normalized vector (will call normalize internally)
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_project(const vector_t v, const vector_t at);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_reflect(const vector_t v, const vector_t at);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_project3(const vector_t v, const vector_t at);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_reflect3(const vector_t v, const vector_t at);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_fast(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_sqr(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_fast(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_sqr(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sqrt(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_min(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_max(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_abs(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_x(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_y(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_z(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_w(const vector_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_component(const vector_t v, int c);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_set_component(const vector_t v, int c, real val);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_equal(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_lequal(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_less(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_gequal(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_greater(const vector_t v0, const vector_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_zero(void);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_one(void);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_x(const vectori_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_y(const vectori_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_z(const vectori_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_w(const vectori_t v);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_component(const vectori_t v, int c);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_and(const vectori_t v0, const vectori_t v1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_or(const vectori_t v0, const vectori_t v1);

//! Treat vectors as row vectors, which puts axes in rows in matrix
//                 [ m00 m01 m02 --- ]
// [ vx vy vz vw ] [ m10 m11 m12 --- ] = [ m00*vx + m10*vy + m20*vz, m01*vx ..., ..., vw ]
//                 [ m20 m21 m22 --- ]
//                 [ --- --- --- --- ]
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_rotate(const vector_t v, const matrix_t m);

//! Treat vectors as row vectors, which puts axes in rows in matrix
//                 [ m00 m01 m02 m03 ]
// [ vx vy vz vw ] [ m10 m11 m12 m13 ] = [ m00*vx + m10*vy + m20*vz + m30*vw, m01*vx ..., ..., ... ]
//                 [ m20 m21 m22 m23 ]
//                 [ m30 m31 m32 m33 ]
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_transform(const vector_t v, const matrix_t m);

VECTOR_API string_t
string_from_vector(char* buffer, size_t capacity, const vector_t v);

VECTOR_API string_const_t
string_from_vector_static(const vector_t v);

#if VECTOR_IMPLEMENTATION_SSE4
#include <vector/vector_sse4.h>
#elif VECTOR_IMPLEMENTATION_SSE3
#include <vector/vector_sse3.h>
#elif VECTOR_IMPLEMENTATION_SSE2
#include <vector/vector_sse2.h>
#elif VECTOR_IMPLEMENTATION_NEON
#include <vector/vector_neon.h>
#else
#include <vector/vector_fallback.h>
#endif

#include <vector/quaternion.h>
#include <vector/matrix.h>
#include <vector/euler.h>
