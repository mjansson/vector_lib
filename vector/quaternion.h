/* quaternion.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

/*! \file quaternion.h
Rotation abstraction using quaternions */

#include <vector/types.h>
#include <vector/mask.h>
#include <vector/vector.h>

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_zero(void);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_identity(void);

//! Load unaligned
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL quaternion_t
quaternion_unaligned(const float32_t* FOUNDATION_RESTRICT q);

//! Load aligned (16-byte alignment)
static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL quaternion_t
quaternion_aligned(const float32_aligned128_t* FOUNDATION_RESTRICT q);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_conjugate(const quaternion_t q);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_inverse(const quaternion_t q);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_neg(const quaternion_t q);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_normalize(const quaternion_t q);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_mul(const quaternion_t q0, const quaternion_t q1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_add(const quaternion_t q0, const quaternion_t q1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_sub(const quaternion_t q0, const quaternion_t q1);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_slerp(const quaternion_t q0, const quaternion_t q1, real factor);

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
quaternion_rotate(const quaternion_t q, const vector_t v);

#if FOUNDATION_ARCH_SSE4
#  include <vector/quaternion_sse4.h>
#elif FOUNDATION_ARCH_SSE3
#  include <vector/quaternion_sse3.h>
#elif FOUNDATION_ARCH_SSE2
#  include <vector/quaternion_sse2.h>
#elif FOUNDATION_ARCH_NEON
#  include <vector/quaternion_neon.h>
#else
#  include <vector/quaternion_fallback.h>
#endif

