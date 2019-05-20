/* matrix_sse2.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform vector math library in C11 providing basic support data
 * types and functions to write applications and games in a platform-independent fashion. The latest
 * source code is always available at
 *
 * https://github.com/rampantpixels/vector_lib
 *
 * This library is built on top of the foundation library available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any
 * restrictions.
 *
 */

#ifndef VECTOR_HAVE_MATRIX_UNALIGNED

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_unaligned(const float32_t* FOUNDATION_RESTRICT m) {
	matrix_t mtx;
	mtx.row[0] = vector_unaligned(m);
	mtx.row[1] = vector_unaligned(m + 4);
	mtx.row[2] = vector_unaligned(m + 8);
	mtx.row[3] = vector_unaligned(m + 12);
	return mtx;
}
#define VECTOR_HAVE_MATRIX_UNALIGNED 1

#endif

#ifndef VECTOR_HAVE_MATRIX_TRANSPOSE

matrix_t FOUNDATION_PURECALL
matrix_transpose(const matrix_t m) {
	matrix_t mt = m;
	_MM_TRANSPOSE4_PS(mt.row[0], mt.row[1], mt.row[2], mt.row[3]);
	return mt;
}
#define VECTOR_HAVE_MATRIX_TRANSPOSE

#endif

#ifndef VECTOR_HAVE_MATRIX_MUL

matrix_t FOUNDATION_CONSTCALL
matrix_mul(const matrix_t m0, const matrix_t m1) {
	matrix_t ret;

	const vector_t m0_r0 = m0.row[0];
	const vector_t m0_r1 = m0.row[1];
	const vector_t m0_r2 = m0.row[2];
	const vector_t m0_r3 = m0.row[3];

	const vector_t m1_r0 = m1.row[0];
	vector_t r0 = vector_mul(vector_shuffle(m0_r0, VECTOR_MASK_XXXX), m1_r0);
	vector_t r1 = vector_mul(vector_shuffle(m0_r1, VECTOR_MASK_XXXX), m1_r0);
	vector_t r2 = vector_mul(vector_shuffle(m0_r2, VECTOR_MASK_XXXX), m1_r0);
	vector_t r3 = vector_mul(vector_shuffle(m0_r3, VECTOR_MASK_XXXX), m1_r0);

	const vector_t m1_r1 = m1.row[1];
	r0 = vector_muladd(vector_shuffle(m0_r0, VECTOR_MASK_YYYY), m1_r1, r0);
	r1 = vector_muladd(vector_shuffle(m0_r1, VECTOR_MASK_YYYY), m1_r1, r1);
	r2 = vector_muladd(vector_shuffle(m0_r2, VECTOR_MASK_YYYY), m1_r1, r2);
	r3 = vector_muladd(vector_shuffle(m0_r3, VECTOR_MASK_YYYY), m1_r1, r3);

	const vector_t m1_r2 = m1.row[2];
	r0 = vector_muladd(vector_shuffle(m0_r0, VECTOR_MASK_ZZZZ), m1_r2, r0);
	r1 = vector_muladd(vector_shuffle(m0_r1, VECTOR_MASK_ZZZZ), m1_r2, r1);
	r2 = vector_muladd(vector_shuffle(m0_r2, VECTOR_MASK_ZZZZ), m1_r2, r2);
	r3 = vector_muladd(vector_shuffle(m0_r3, VECTOR_MASK_ZZZZ), m1_r2, r3);

	const vector_t m1_r3 = m1.row[3];
	r0 = vector_muladd(vector_shuffle(m0_r0, VECTOR_MASK_WWWW), m1_r3, r0);
	r1 = vector_muladd(vector_shuffle(m0_r1, VECTOR_MASK_WWWW), m1_r3, r1);
	r2 = vector_muladd(vector_shuffle(m0_r2, VECTOR_MASK_WWWW), m1_r3, r2);
	r3 = vector_muladd(vector_shuffle(m0_r3, VECTOR_MASK_WWWW), m1_r3, r3);

	ret.row[0] = r0;
	ret.row[1] = r1;
	ret.row[2] = r2;
	ret.row[3] = r3;

	return ret;
}
#define VECTOR_HAVE_MATRIX_MUL

#endif

#include <vector/matrix_base.h>
