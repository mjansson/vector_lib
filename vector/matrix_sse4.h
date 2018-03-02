/* matrix_sse4.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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


/*
#ifndef VECTOR_HAVE_MATRIX_MUL

matrix_t FOUNDATION_CONSTCALL
matrix_mul( const matrix_t m0, const matrix_t m1 )
{
	//For SSE4 dot+or we need to zero out initial memory
	matrix_t ret = matrix_zero();

	ret.row[0] = _mm_dp_ps( _v, m2._m[0], DP_PUTX_4F);
	ret.row[1] = _mm_or_ps( _rm[i], _mm_dp_ps(_v, m2._m[1], DP_PUTY_4F) );
	ret.row[2] = _mm_or_ps( _rm[i], _mm_dp_ps(_v, m2._m[2], DP_PUTZ_4F) );
	ret.row[3] = _mm_or_ps( _rm[i], _mm_dp_ps(_v, m2._m[3], DP_PUTW_4F) );

	return ret;
}

#define VECTOR_HAVE_MATRIX_MUL
#endif
*/


#include <vector/matrix_sse3.h>
