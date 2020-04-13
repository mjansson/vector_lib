/* matrix_base.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
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

#ifndef VECTOR_HAVE_MATRIX_ZERO

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_zero(void) {
	static const FOUNDATION_ALIGN(16) float32_t _zero_matrix[16] = {0};
	return matrix_aligned(_zero_matrix);
}

#endif

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

#endif

#ifndef VECTOR_HAVE_MATRIX_ALIGNED

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_aligned(const float32_aligned128_t* FOUNDATION_RESTRICT m) {
	return *(const matrix_t*)m;
}

#endif

#ifndef VECTOR_HAVE_MATRIX_IDENTITY

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_identity(void) {
	static const FOUNDATION_ALIGN(16) float32_t _identity_matrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	return matrix_aligned(_identity_matrix);
}

#endif

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_scaling(const vector_t scale) {
	return matrix_scaling_scalar(vector_component(scale, 0), vector_component(scale, 1), vector_component(scale, 2));
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_scaling_scalar(float32_t x, float32_t y, float32_t z) {
	FOUNDATION_ALIGN(16)
	float32_t aligned[16] = {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
	return matrix_aligned(aligned);
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_translation(const vector_t translation) {
	matrix_t mtx = matrix_identity();
	mtx.row[3] = vector_set_component(translation, 3, REAL_C(1.0));
	return mtx;
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
matrix_get_translation(const matrix_t m) {
	return m.row[3];
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL matrix_t
matrix_translation_scalar(float32_t x, float32_t y, float32_t z) {
	FOUNDATION_ALIGN(16)
	float32_t aligned[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1};
	return matrix_aligned(aligned);
}

#ifndef VECTOR_HAVE_MATRIX_TRANSPOSE

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_transpose(const matrix_t m) {
	matrix_t mt;
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			mt.frow[row][col] = m.frow[col][row];
	return mt;
}

#endif

#ifndef VECTOR_HAVE_MATRIX_MUL

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_mul(const matrix_t m0, const matrix_t m1) {
	matrix_t r;
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			r.frow[row][col] = m0.frow[row][0] * m1.frow[0][col] + m0.frow[row][1] * m1.frow[1][col] +
			                   m0.frow[row][2] * m1.frow[2][col] + m0.frow[row][3] * m1.frow[3][col];
	return r;
}

#endif

#ifndef VECTOR_HAVE_MATRIX_ADD

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_add(const matrix_t m0, const matrix_t m1) {
	matrix_t r;
	r.row[0] = vector_add(m0.row[0], m1.row[0]);
	r.row[1] = vector_add(m0.row[1], m1.row[1]);
	r.row[2] = vector_add(m0.row[2], m1.row[2]);
	r.row[3] = vector_add(m0.row[3], m1.row[3]);
	return r;
}

#endif

#ifndef VECTOR_HAVE_MATRIX_SUB

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_sub(const matrix_t m0, const matrix_t m1) {
	matrix_t r;
	r.row[0] = vector_sub(m0.row[0], m1.row[0]);
	r.row[1] = vector_sub(m0.row[1], m1.row[1]);
	r.row[2] = vector_sub(m0.row[2], m1.row[2]);
	r.row[3] = vector_sub(m0.row[3], m1.row[3]);
	return r;
}

#endif

#ifndef VECTOR_HAVE_MATRIX_FROM_QUATERNION

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL matrix_t
matrix_from_quaternion(const quaternion_t q) {
	matrix_t mat;

	float32_t x = vector_x(q);
	float32_t y = vector_y(q);
	float32_t z = vector_z(q);
	float32_t w = vector_w(q);
	float32_t tx = 2.0f * x;
	float32_t ty = 2.0f * y;
	float32_t tz = 2.0f * z;
	float32_t tsx = tx * w;
	float32_t tsy = ty * w;
	float32_t tsz = tz * w;
	float32_t txx = tx * x;
	float32_t txy = ty * x;
	float32_t txz = tz * x;
	float32_t tyy = ty * y;
	float32_t tyz = tz * y;
	float32_t tzz = tz * z;

	mat.frow[0][0] = 1.0f - (tyy + tzz);
	mat.frow[1][0] = txy - tsz;
	mat.frow[2][0] = txz + tsy;
	mat.frow[3][0] = 0;

	mat.frow[0][1] = txy + tsz;
	mat.frow[1][1] = 1.0f - (txx + tzz);
	mat.frow[2][1] = tyz - tsx;
	mat.frow[3][1] = 0;

	mat.frow[0][2] = txz - tsy;
	mat.frow[1][2] = tyz + tsx;
	mat.frow[2][2] = 1.0f - (txx + tyy);
	mat.frow[3][2] = 0;

	mat.frow[0][3] = 0;
	mat.frow[1][3] = 0;
	mat.frow[2][3] = 0;
	mat.frow[3][3] = 1;

	return mat;
}

#endif

#undef VECTOR_HAVE_MATRIX_ZERO
#undef VECTOR_HAVE_MATRIX_IDENTITY
#undef VECTOR_HAVE_MATRIX_UNALIGNED
#undef VECTOR_HAVE_MATRIX_ALIGNED
#undef VECTOR_HAVE_MATRIX_TRANSPOSE
#undef VECTOR_HAVE_MATRIX_MUL
#undef VECTOR_HAVE_MATRIX_ADD
#undef VECTOR_HAVE_MATRIX_SUB
#undef VECTOR_HAVE_MATRIX_FROM_QUATERNION
