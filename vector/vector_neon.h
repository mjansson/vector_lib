/* vector_neon.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
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

#if FOUNDATION_COMPILER_CLANG
#pragma clang diagnostic push
#if __has_warning("-Wvector-conversion")
#pragma clang diagnostic ignored "-Wvector-conversion"
#endif
#endif

// Index for shuffle must be constant integer - hide function with a define
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle(const vector_t v, const unsigned int mask) {
	FOUNDATION_ASSERT_FAIL("Unreachable code");
	FOUNDATION_UNUSED(mask);
	return v;
}
#define vector_shuffle(v, mask)                                                 \
	__extension__({                                                             \
		float32x4_t ret;                                                        \
		ret = vmovq_n_f32(vgetq_lane_f32((v), (mask)&0x3));                     \
		ret = vsetq_lane_f32(vgetq_lane_f32((v), ((mask) >> 2) & 0x3), ret, 1); \
		ret = vsetq_lane_f32(vgetq_lane_f32((v), ((mask) >> 4) & 0x3), ret, 2); \
		ret = vsetq_lane_f32(vgetq_lane_f32((v), ((mask) >> 6) & 0x3), ret, 3); \
		ret;                                                                    \
	})

// Index for shuffle must be constant integer - hide function with a define
static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle2(const vector_t v0, const vector_t v1, const unsigned int mask) {
	FOUNDATION_ASSERT_FAIL("Unreachable code");
	FOUNDATION_UNUSED(v1);
	FOUNDATION_UNUSED(mask);
	return v0;
}
#define vector_shuffle2(v0, v1, mask)                                            \
	__extension__({                                                              \
		vector_t ret;                                                            \
		ret = vmovq_n_f32(vgetq_lane_f32((v0), (mask)&0x3));                     \
		ret = vsetq_lane_f32(vgetq_lane_f32((v0), ((mask) >> 2) & 0x3), ret, 1); \
		ret = vsetq_lane_f32(vgetq_lane_f32((v1), ((mask) >> 4) & 0x3), ret, 2); \
		ret = vsetq_lane_f32(vgetq_lane_f32((v1), ((mask) >> 6) & 0x3), ret, 3); \
		ret;                                                                     \
	})

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector(const real x, const real y, const real z, const real w) {
	vector_arr_t data = {x, y, z, w};
	return vld1q_f32(data);
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_aligned(const float32_aligned128_t* FOUNDATION_RESTRICT v) {
	FOUNDATION_ASSERT_ALIGNMENT(v, 16);
	return vld1q_f32(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_unaligned(const float32_t* FOUNDATION_RESTRICT v) {
	return vld1q_f32(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_uniform(const real v) {
	return vdupq_n_f32(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zero(void) {
	return vdupq_n_f32(0);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_one(void) {
	return vdupq_n_f32(1.0f);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_half(void) {
	return vdupq_n_f32(0.5f);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_two(void) {
	return vdupq_n_f32(2.0f);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_origo(void) {
	vector_arr_t data = {0, 0, 0, 1};
	return vld1q_f32(data);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_xaxis(void) {
	vector_arr_t data = {1, 0, 0, 1};
	return vld1q_f32(data);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_yaxis(void) {
	vector_arr_t data = {0, 1, 0, 1};
	return vld1q_f32(data);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zaxis(void) {
	vector_arr_t data = {0, 0, 1, 1};
	return vld1q_f32(data);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize(const vector_t v) {
	return vector_div(v, vector_sqrt(vector_dot(v, v)));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize3(const vector_t v) {
	// Shuffle to preserve w component of input vector
	const vector_t norm = vector_div(v, vector_sqrt(vector_dot3(v, v)));
	const vector_t splice = vector_shuffle2(norm, v, VECTOR_MASK_ZZWW);
	return vector_shuffle2(norm, splice, VECTOR_MASK_XYXW);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot(const vector_t v0, const vector_t v1) {
	const vector_t r = vector_mul(v0, v1);
#if defined(__aarch64__)
	const vector_t rp = vpaddq_f32(r, r);
	return vpaddq_f32(rp, rp);
#else
	const float32x2_t low = vpadd_f32(vget_low_f32(r), vget_low_f32(r));
	const float32x2_t high = vpadd_f32(vget_high_f32(r), vget_high_f32(r));
	const float32x2_t sum = vadd_f32(low, high);
	return vreinterpretq_m128_f32(vdupq_n_f32(vgetq_lane_f32(sum, 0)));
#endif
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot3(const vector_t v0, const vector_t v1) {
	const vector_t r = vector_mul(v0, v1);
	float32x2_t low = vpadd_f32(vget_low_f32(r), vget_low_f32(r));
	low = vadd_f32(low, vget_high_f32(r));
	return vdupq_n_f32(vget_lane_f32(low, 0));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_cross3(const vector_t v0, const vector_t v1) {
	vector_t v0yzx = vector_shuffle(v0, VECTOR_MASK_YZXW);
	vector_t v1yzx = vector_shuffle(v1, VECTOR_MASK_YZXW);
	vector_t v0zxy = vector_shuffle(v0, VECTOR_MASK_ZXYW);
	vector_t v1zxy = vector_shuffle(v1, VECTOR_MASK_ZXYW);
	return vector_sub(vector_mul(v0yzx, v1zxy), vector_mul(v0zxy, v1yzx));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_mul(const vector_t v0, const vector_t v1) {
	return vmulq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_div(const vector_t v0, const vector_t v1) {
	return vdivq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_add(const vector_t v0, const vector_t v1) {
	return vaddq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_add_triple(const vector_t v0, const vector_t v1, const vector_t v2) {
	return vaddq_f32(vaddq_f32(v0, v1), v2);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sub(const vector_t v0, const vector_t v1) {
	return vsubq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_neg(const vector_t v) {
	return vsubq_f32(vdupq_n_f32(0), v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_muladd(const vector_t v0, const vector_t v1, const vector_t v2) {
#if defined(__aarch64__)
	return vfmaq_f32(v2, v1, v0);
#else
	return vector_add(vector_mul(v0, v1), v2);
#endif
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_scale(const vector_t v, const real s) {
	return vector_mul(v, vector_uniform(s));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_lerp(const vector_t from, const vector_t to, const real factor) {
	vector_t s = vector_uniform(factor);
	return vector_add(vector_mul(s, to), vector_sub(from, vector_mul(s, from)));
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
	// Shuffle to preserve w component of input vector
	const vector_t normal = vector_div(at, vector_sqrt(vector_dot3(at, at)));
	const vector_t result = vector_mul(normal, vector_dot3(normal, v));
	const vector_t splice = vector_shuffle2(result, v, VECTOR_MASK_ZZWW);
	return vector_shuffle2(result, splice, VECTOR_MASK_XYXW);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_reflect3(const vector_t v, const vector_t at) {
	// Shuffle to preserve w component of input vector
	const vector_t two = vector_two();
	const vector_t normal = vector_normalize3(at);
	const vector_t double_proj = vector_mul(normal, vector_mul(vector_dot3(normal, v), two));
	const vector_t result = vector_sub(double_proj, v);
	const vector_t splice = vector_shuffle2(result, v, VECTOR_MASK_ZZWW);
	return vector_shuffle2(result, splice, VECTOR_MASK_XYXW);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length(const vector_t v) {
	return vector_sqrt(vector_dot(v, v));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_fast(const vector_t v) {
	return vector_sqrt(vector_dot(v, v));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_sqr(const vector_t v) {
	return vector_dot(v, v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3(const vector_t v) {
	return vector_sqrt(vector_dot3(v, v));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_fast(const vector_t v) {
	return vector_sqrt(vector_dot3(v, v));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_sqr(const vector_t v) {
	return vector_dot3(v, v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sqrt(const vector_t v) {
	return vsqrtq_f32(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_min(const vector_t v0, const vector_t v1) {
	return vminq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_max(const vector_t v0, const vector_t v1) {
	return vmaxq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_abs(const vector_t v) {
	return vabsq_f32(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_x(const vector_t v) {
	return vgetq_lane_f32(v, 0);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_y(const vector_t v) {
	return vgetq_lane_f32(v, 1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_z(const vector_t v) {
	return vgetq_lane_f32(v, 2);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_w(const vector_t v) {
	return vgetq_lane_f32(v, 3);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_component(const vector_t v, int c) {
	return *((const float32_t*)&v + c);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_set_component(const vector_t v, int c, real val) {
	vector_t vmod = v;
	*((float32_t*)&vmod + c) = val;
	return vmod;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_zero(void) {
	return vdupq_n_s32(0);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_one(void) {
	return vdupq_n_s32(1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_x(const vectori_t v) {
	return vgetq_lane_s32(v, 0);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_y(const vectori_t v) {
	return vgetq_lane_s32(v, 1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_z(const vectori_t v) {
	return vgetq_lane_s32(v, 2);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_w(const vectori_t v) {
	return vgetq_lane_s32(v, 3);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_component(const vectori_t v, int c) {
	return ((const int32_t*)&v)[c];
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_and(const vectori_t v0, const vectori_t v1) {
	return vandq_s32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_or(const vectori_t v0, const vectori_t v1) {
	return vorrq_s32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_equal(const vector_t v0, const vector_t v1) {
	return vceqq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_lequal(const vector_t v0, const vector_t v1) {
	return vcleq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_less(const vector_t v0, const vector_t v1) {
	return vcltq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_gequal(const vector_t v0, const vector_t v1) {
	return vcgeq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_greater(const vector_t v0, const vector_t v1) {
	return vcgtq_f32(v0, v1);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_rotate(const vector_t v, const matrix_t m) {
	vector_t vr;
	vr = vector_mul(m.row[0], vector_shuffle(v, VECTOR_MASK_XXXX));
	vr = vector_muladd(m.row[1], vector_shuffle(v, VECTOR_MASK_YYYY), vr);
	vr = vector_muladd(m.row[2], vector_shuffle(v, VECTOR_MASK_ZZZZ), vr);

	const vector_t splice = vector_shuffle2(vr, v, VECTOR_MASK_ZZWW);
	return vector_shuffle2(vr, splice, VECTOR_MASK_XYXW);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_transform(const vector_t v, const matrix_t m) {
	vector_t vr;
	vr = vector_mul(m.row[0], vector_shuffle(v, VECTOR_MASK_XXXX));
	vr = vector_muladd(m.row[1], vector_shuffle(v, VECTOR_MASK_YYYY), vr);
	vr = vector_muladd(m.row[2], vector_shuffle(v, VECTOR_MASK_ZZZZ), vr);
	return vector_muladd(m.row[3], vector_shuffle(v, VECTOR_MASK_WWWW), vr);
}

#if FOUNDATION_COMPILER_CLANG
#pragma clang diagnostic pop
#endif
