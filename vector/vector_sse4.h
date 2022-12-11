/* vector_sse4.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
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

#include <smmintrin.h>

// Index for shuffle must be constant integer - hide function with a define
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle(const vector_t v, unsigned int mask) {
	FOUNDATION_ASSERT_FAIL("Unreachable code");
	FOUNDATION_UNUSED(mask);
	// return _mm_shuffle_ps(v, v, mask);
	return v;
}
#define vector_shuffle(v, mask) _mm_shuffle_ps(v, v, mask)

// Index for shuffle must be constant integer - hide function with a define
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle2(const vector_t v0, const vector_t v1, const unsigned int mask) {
	FOUNDATION_ASSERT_FAIL("Unreachable code");
	FOUNDATION_UNUSED(v1);
	FOUNDATION_UNUSED(mask);
	return v0;
}
#define vector_shuffle2(v0, v1, mask) _mm_shuffle_ps(v0, v1, mask)

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector(real x, real y, real z, real w) {
	return _mm_setr_ps(x, y, z, w);
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_aligned(const float32_aligned128_t* v) {
	FOUNDATION_ASSERT_ALIGNMENT(v, 16);
	return _mm_load_ps(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_unaligned(const float32_t* v) {
	return _mm_loadu_ps(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_uniform(real v) {
	return _mm_set_ps1(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zero(void) {
	return _mm_setzero_ps();
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_one(void) {
	return _mm_set1_ps(1.0f);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_half(void) {
	return _mm_set1_ps(0.5f);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_two(void) {
	return _mm_set1_ps(2.0f);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_origo(void) {
	const float32_aligned128_t origo[] = {0, 0, 0, 1};
	return vector_aligned(origo);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_xaxis(void) {
	const vector_t v = _mm_set_ss(1.0f);
	return _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v), VECTOR_MASK_XYYX));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_yaxis(void) {
	const vector_t v = _mm_set_ss(1.0f);
	return _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v), VECTOR_MASK_YXYX));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zaxis(void) {
	const vector_t v = _mm_set_ss(1.0f);
	return _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v), VECTOR_MASK_YYXX));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize(const vector_t v) {
	return vector_div(v, _mm_sqrt_ps(_mm_dp_ps(v, v, 0xFF)));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize3(const vector_t v) {
	return vector_div(v, _mm_sqrt_ps(_mm_dp_ps(v, v, 0x77)));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot(const vector_t v0, const vector_t v1) {
	return _mm_dp_ps(v0, v1, 0xFF);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot3(const vector_t v0, const vector_t v1) {
	return _mm_dp_ps(v0, v1, 0x77);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_cross3(const vector_t v0, const vector_t v1) {
	vector_t v0yzx = vector_shuffle(v0, VECTOR_MASK_YZXW);
	vector_t v1yzx = vector_shuffle(v1, VECTOR_MASK_YZXW);
	vector_t v0zxy = vector_shuffle(v0, VECTOR_MASK_ZXYW);
	vector_t v1zxy = vector_shuffle(v1, VECTOR_MASK_ZXYW);
#if FOUNDATION_ARCH_SSE4_FMA3
	vector_t interm = vector_mul(v0yzx, v1zxy);
	return _mm_fnmadd_ps(v0zxy, v1yzx, interm);
#else
	return vector_sub(vector_mul(v0yzx, v1zxy), vector_mul(v0zxy, v1yzx));
#endif
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_mul(const vector_t v0, const vector_t v1) {
	return _mm_mul_ps(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_div(const vector_t v0, const vector_t v1) {
	return _mm_div_ps(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_add(const vector_t v0, const vector_t v1) {
	return _mm_add_ps(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_add_triple(const vector_t v0, const vector_t v1, const vector_t v2) {
	return _mm_add_ps(_mm_add_ps(v0, v1), v2);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sub(const vector_t v0, const vector_t v1) {
	return _mm_sub_ps(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_neg(const vector_t v) {
	return _mm_sub_ps(_mm_setzero_ps(), v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_muladd(const vector_t v0, const vector_t v1, const vector_t v2) {
#if FOUNDATION_ARCH_SSE4_FMA3
	return _mm_fmadd_ps(v0, v1, v2);
#else
	return vector_add(vector_mul(v0, v1), v2);
#endif
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_scale(const vector_t v, const real s) {
	return _mm_mul_ps(v, _mm_set_ps1(s));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_lerp(const vector_t from, const vector_t to, const real factor) {
	vector_t s = _mm_set1_ps(factor);
#if FOUNDATION_ARCH_SSE4_FMA3
	return _mm_fmadd_ps(to, s, _mm_fnmadd_ps(from, s, from));
#else
	return _mm_add_ps(_mm_mul_ps(s, to), _mm_sub_ps(from, _mm_mul_ps(s, from)));
#endif
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_project(const vector_t v, const vector_t at) {
	vector_t normal = vector_normalize(at);
	return vector_mul(normal, vector_dot(normal, v));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_reflect(const vector_t v, const vector_t at) {
	const vector_t two = vector_two();
	const vector_t normal = vector_normalize(at);
	const vector_t double_proj = vector_mul(normal, vector_mul(vector_dot(normal, v), two));
	return vector_sub(double_proj, v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_project3(const vector_t v, const vector_t at) {
	const vector_t normal = vector_div(at, _mm_sqrt_ps(vector_dot3(at, at)));
	const vector_t result = vector_mul(normal, vector_dot3(normal, v));
	return _mm_blend_ps(result, v, 8);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_reflect3(const vector_t v, const vector_t at) {
	const vector_t two = vector_two();
	const vector_t normal = vector_normalize3(at);
	const vector_t double_proj = vector_mul(normal, vector_mul(vector_dot3(normal, v), two));
	const vector_t result = vector_sub(double_proj, v);
	return _mm_blend_ps(result, v, 8);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length(const vector_t v) {
	const vector_t vsqrt = _mm_sqrt_ss(_mm_dp_ps(v, v, 0xFF));
	return vector_shuffle(vsqrt, VECTOR_MASK_XXXX);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_fast(const vector_t v) {
	const vector_t vsqrt = _mm_sqrt_ss(_mm_dp_ps(v, v, 0xFF));
	return vector_shuffle(vsqrt, VECTOR_MASK_XXXX);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_sqr(const vector_t v) {
	return vector_dot(v, v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3(const vector_t v) {
	const vector_t vsqrt = _mm_sqrt_ss(_mm_dp_ps(v, v, 0x77));
	return vector_shuffle(vsqrt, VECTOR_MASK_XXXX);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_fast(const vector_t v) {
	const vector_t vsqrt = _mm_sqrt_ss(_mm_dp_ps(v, v, 0x77));
	return vector_shuffle(vsqrt, VECTOR_MASK_XXXX);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_sqr(const vector_t v) {
	return vector_dot3(v, v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sqrt(const vector_t v) {
	return _mm_sqrt_ps(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_min(const vector_t v0, const vector_t v1) {
	return _mm_min_ps(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_max(const vector_t v0, const vector_t v1) {
	return _mm_max_ps(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_abs(const vector_t v) {
	return _mm_and_ps(_mm_castsi128_ps(_mm_srli_epi32(_mm_set1_epi32(-1), 1)), v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_x(const vector_t v) {
	return *(const float32_t*)&v;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_y(const vector_t v) {
	return *((const float32_t*)&v + 1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_z(const vector_t v) {
	return *((const float32_t*)&v + 2);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_w(const vector_t v) {
	return *((const float32_t*)&v + 3);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_component(const vector_t v, int c) {
	FOUNDATION_ASSERT((c >= 0) && (c < 4));
	return *((const float32_t*)&v + c);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_set_component(const vector_t v, int c, real val) {
	FOUNDATION_ASSERT((c >= 0) && (c < 4));
	vector_t vmod = v;
	*((float32_t*)&vmod + c) = val;
	return vmod;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_zero(void) {
	return _mm_setzero_si128();
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_one(void) {
	return _mm_set1_epi32(1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_x(const vectori_t v) {
	return *(const int32_t*)&v;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_y(const vectori_t v) {
	return *((const int32_t*)&v + 1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_z(const vectori_t v) {
	return *((const int32_t*)&v + 2);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_w(const vectori_t v) {
	return *((const int32_t*)&v + 3);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_component(const vectori_t v, int c) {
	return ((const int32_t*)&v)[c];
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_and(const vectori_t v0, const vectori_t v1) {
	return _mm_and_si128(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_or(const vectori_t v0, const vectori_t v1) {
	return _mm_or_si128(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_equal(const vector_t v0, const vector_t v1) {
	return _mm_castps_si128(_mm_cmpeq_ps(v0, v1));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_lequal(const vector_t v0, const vector_t v1) {
	return _mm_castps_si128(_mm_cmple_ps(v0, v1));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_less(const vector_t v0, const vector_t v1) {
	return _mm_castps_si128(_mm_cmplt_ps(v0, v1));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_gequal(const vector_t v0, const vector_t v1) {
	return _mm_castps_si128(_mm_cmpge_ps(v0, v1));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_greater(const vector_t v0, const vector_t v1) {
	return _mm_castps_si128(_mm_cmpgt_ps(v0, v1));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_rotate(const vector_t v, const matrix_t m) {
	vector_t vr;
	vr = vector_mul(m.row[0], vector_shuffle(v, VECTOR_MASK_XXXX));
	vr = vector_muladd(m.row[1], vector_shuffle(v, VECTOR_MASK_YYYY), vr);
	vr = vector_muladd(m.row[2], vector_shuffle(v, VECTOR_MASK_ZZZZ), vr);

	const vector_t splice = _mm_shuffle_ps(vr, v, VECTOR_MASK_ZZWW);
	return _mm_shuffle_ps(vr, splice, VECTOR_MASK_XYXW);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_transform(const vector_t v, const matrix_t m) {
	vector_t vr;
	vr = vector_mul(m.row[0], vector_shuffle(v, VECTOR_MASK_XXXX));
	vr = vector_muladd(m.row[1], vector_shuffle(v, VECTOR_MASK_YYYY), vr);
	vr = vector_muladd(m.row[2], vector_shuffle(v, VECTOR_MASK_ZZZZ), vr);
	return vector_muladd(m.row[3], vector_shuffle(v, VECTOR_MASK_WWWW), vr);
}
