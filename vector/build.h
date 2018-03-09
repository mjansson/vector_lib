/* build.h  -  Vector library build setup  -  Public Domain  -  2015 Mattias Jansson / Rampant Pixels
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

#include <foundation/platform.h>

#if defined(VECTOR_COMPILE) && VECTOR_COMPILE
#  ifdef __cplusplus
#  define VECTOR_EXTERN extern "C"
#  define VECTOR_API extern "C"
#  else
#  define VECTOR_EXTERN extern
#  define VECTOR_API extern
#  endif
#else
#  ifdef __cplusplus
#  define VECTOR_EXTERN extern "C"
#  define VECTOR_API extern "C"
#  else
#  define VECTOR_EXTERN extern
#  define VECTOR_API extern
#  endif
#endif

#if FOUNDATION_ARCH_SSE4
#  undef FOUNDATION_ARCH_SSE4
#  define FOUNDATION_ARCH_SSE4 0
#endif
#if FOUNDATION_ARCH_SSE3
#  undef FOUNDATION_ARCH_SSE3
#  define FOUNDATION_ARCH_SSE3 0
#endif
#if FOUNDATION_ARCH_SSE2
#  undef FOUNDATION_ARCH_SSE2
#  define FOUNDATION_ARCH_SSE2 0
#endif
