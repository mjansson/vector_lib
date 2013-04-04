/* matrix_sse2.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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



#ifndef VECTOR_HAVE_MATRIX_TRANSPOSE

matrix_t matrix_transpose( const matrix_t m )
{
	matrix_t mt = m;
	_MM_TRANSPOSE4_PS( mt.row[0], mt.row[1], mt.row[2], mt.row[3] );
	return mt;
}
#define VECTOR_HAVE_MATRIX_TRANSPOSE

#endif

#ifndef VECTOR_HAVE_MATRIX_MUL

matrix_t matrix_mul( const matrix_t m0, const matrix_t m1 )
{
	matrix_t ret;

	const vector_t m0_r0 = m0.row[0];
	const vector_t m0_r1 = m0.row[1];
	const vector_t m0_r2 = m0.row[2];
	const vector_t m0_r3 = m0.row[3];

	const vector_t m1_r0 = m1.row[0];
	vector_t r0 = vector_mul( vector_shuffle( m0_r0, VECTOR_MASK_XXXX ), m1_r0 );
	vector_t r1 = vector_mul( vector_shuffle( m0_r1, VECTOR_MASK_XXXX ), m1_r0 );
	vector_t r2 = vector_mul( vector_shuffle( m0_r2, VECTOR_MASK_XXXX ), m1_r0 );
	vector_t r3 = vector_mul( vector_shuffle( m0_r3, VECTOR_MASK_XXXX ), m1_r0 );

	const vector_t m1_r1 = m1.row[1];
	r0 = vector_muladd( vector_shuffle( m0_r0, VECTOR_MASK_YYYY ), m1_r1, r0 );
	r1 = vector_muladd( vector_shuffle( m0_r1, VECTOR_MASK_YYYY ), m1_r1, r1 );
	r2 = vector_muladd( vector_shuffle( m0_r2, VECTOR_MASK_YYYY ), m1_r1, r2 );
	r3 = vector_muladd( vector_shuffle( m0_r3, VECTOR_MASK_YYYY ), m1_r1, r3 );

	const vector_t m1_r2 = m1.row[2];
	r0 = vector_muladd( vector_shuffle( m0_r0, VECTOR_MASK_ZZZZ ), m1_r2, r0 );
	r1 = vector_muladd( vector_shuffle( m0_r1, VECTOR_MASK_ZZZZ ), m1_r2, r1 );
	r2 = vector_muladd( vector_shuffle( m0_r2, VECTOR_MASK_ZZZZ ), m1_r2, r2 );
	r3 = vector_muladd( vector_shuffle( m0_r3, VECTOR_MASK_ZZZZ ), m1_r2, r3 );

	const vector_t m1_r3 = m1.row[3];
	r0 = vector_muladd( vector_shuffle( m0_r0, VECTOR_MASK_WWWW ), m1_r3, r0 );
	r1 = vector_muladd( vector_shuffle( m0_r1, VECTOR_MASK_WWWW ), m1_r3, r1 );
	r2 = vector_muladd( vector_shuffle( m0_r2, VECTOR_MASK_WWWW ), m1_r3, r2 );
	r3 = vector_muladd( vector_shuffle( m0_r3, VECTOR_MASK_WWWW ), m1_r3, r3 );

	ret.row[0] = r0;
	ret.row[1] = r1;
	ret.row[2] = r2;
	ret.row[3] = r3;
	
	return ret;
}
#define VECTOR_HAVE_MATRIX_MUL

#endif

#ifndef VECTOR_HAVE_MATRIX_ROTATE

vector_t matrix_rotate( const matrix_t m, const vector_t v )
{
	vector_t vr;
	vr = vector_mul( m.row[0], vector_shuffle( v, VECTOR_MASK_XXXX ) );
	vr = vector_muladd( m.row[1], vector_shuffle( v, VECTOR_MASK_YYYY ), vr );
	vr = vector_muladd( m.row[2], vector_shuffle( v, VECTOR_MASK_ZZZZ ), vr );

	const vector_t splice = _mm_shuffle_ps( vr, v, VECTOR_MASK_ZZWW );
	return _mm_shuffle_ps( vr, splice, VECTOR_MASK_XYXW );
}
#define VECTOR_HAVE_MATRIX_ROTATE

#endif

#ifndef VECTOR_HAVE_MATRIX_TRANSFORM

vector_t matrix_transform( const matrix_t m, const vector_t v )
{
	vector_t vr;
	vr = vector_mul( m.row[0], vector_shuffle( v, VECTOR_MASK_XXXX ) );
	vr = vector_muladd( m.row[1], vector_shuffle( v, VECTOR_MASK_YYYY ), vr );
	vr = vector_muladd( m.row[2], vector_shuffle( v, VECTOR_MASK_ZZZZ ), vr );
	return vector_muladd( m.row[3], vector_shuffle( v, VECTOR_MASK_WWWW ), vr );
}
#define VECTOR_HAVE_MATRIX_TRANSFORM

#endif


#include <vector/matrix_base.h>
