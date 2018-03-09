/* vector_base.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

#ifndef VECTOR_HAVE_VECTOR_ROTATE

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_rotate(const vector_t v, const matrix_t m) {
	return vector(
	           m.frow[0][0] * v.x + m.frow[1][0] * v.y + m.frow[2][0] * v.z,
	           m.frow[0][1] * v.x + m.frow[1][1] * v.y + m.frow[2][1] * v.z,
	           m.frow[0][2] * v.x + m.frow[1][2] * v.y + m.frow[2][2] * v.z,
	           v.w);
}
#define VECTOR_HAVE_VECTOR_ROTATE
#endif

#ifndef VECTOR_HAVE_VECTOR_TRANSFORM

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_transform(const vector_t v, const matrix_t m) {
	return vector(
	           m.frow[0][0] * v.x + m.frow[1][0] * v.y + m.frow[2][0] * v.z + m.frow[3][0] * v.w,
	           m.frow[0][1] * v.x + m.frow[1][1] * v.y + m.frow[2][1] * v.z + m.frow[3][1] * v.w,
	           m.frow[0][2] * v.x + m.frow[1][2] * v.y + m.frow[2][2] * v.z + m.frow[3][2] * v.w,
	           m.frow[0][3] * v.x + m.frow[1][3] * v.y + m.frow[2][3] * v.z + m.frow[3][3] * v.w);
}
#define VECTOR_HAVE_VECTOR_TRANSFORM
#endif
