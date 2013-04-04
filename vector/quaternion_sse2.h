/* quaternion_sse2.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

quaternion_t quaternion_conjugate( const quaternion_t q )
{
	const vector_t qneg = vector_neg( q );
	const vector_t splice = _mm_shuffle_ps( qneg, q, VECTOR_MASK_ZZWW );
	return _mm_shuffle_ps( qneg, splice, VECTOR_MASK_XYXZ );
}
#define VECTOR_HAVE_QUATERNION_CONJUGATE 1

#endif


#ifndef VECTOR_HAVE_QUATERNION_INVERSE

quaternion_t quaternion_inverse( const quaternion_t q )
{
	const vector_t norm = vector_length_sqr( q );
	const vector_t inv_norm = vector_div( vector_one(), norm );
	const vector_t r = vector_mul( q, inv_norm );
	const vector_t rneg = vector_neg( r );
	const vector_t splice = _mm_shuffle_ps( rneg, r, VECTOR_MASK_ZZWW );
	return _mm_shuffle_ps( rneg, splice, VECTOR_MASK_XYXZ );
}
#define VECTOR_HAVE_QUATERNION_INVERSE 1

#endif


#include <vector/quaternion_base.h>
