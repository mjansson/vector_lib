/* quaternion_fallback.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

#ifndef VECTOR_HAVE_QUATERNION_CONJUGATE

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_conjugate(const quaternion_t q) {
	return vector(-q.x, -q.y, -q.z, q.w);
}

#define VECTOR_HAVE_QUATERNION_CONJUGATE
#endif

#ifndef VECTOR_HAVE_QUATERNION_INVERSE

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL quaternion_t
quaternion_inverse(const quaternion_t q) {
	quaternion_t r = q;
	const float32_t norm = 1.0f / vector_length_sqr(q).x;
	r.x *= -norm;
	r.y *= -norm;
	r.z *= -norm;
	r.w *=  norm;
	return r;
}

#define VECTOR_HAVE_QUATERNION_INVERSE 1
#endif

#include <vector/quaternion_base.h>
