/* matrix_fallback.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
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

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_unaligned(const float32_t* FOUNDATION_RESTRICT m) {
	return *(const matrix_t*)m;
}
#define VECTOR_HAVE_MATRIX_UNALIGNED 1

#include <vector/matrix_base.h>
