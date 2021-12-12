/* vector_fallback.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
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
#if __has_warning("-Wfloat-equal")
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif
#endif

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector(const real x, const real y, const real z, const real w) {
	return (vector_t){x, y, z, w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_aligned(const float32_aligned128_t* FOUNDATION_RESTRICT v) {
	return *(const vector_t*)v;
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_unaligned(const float32_t* FOUNDATION_RESTRICT v) {
	vector_t rv = {*v, *(v + 1), *(v + 2), *(v + 3)};
	return rv;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_uniform(const real v) {
	return (vector_t){v, v, v, v};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zero(void) {
	return (vector_t){0, 0, 0, 0};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_one(void) {
	return (vector_t){1, 1, 1, 1};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_half(void) {
	return (vector_t){0.5f, 0.5f, 0.5f, 0.5f};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_two(void) {
	return (vector_t){2, 2, 2, 2};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_origo(void) {
	return (vector_t){0, 0, 0, 1};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_xaxis(void) {
	return (vector_t){1, 0, 0, 1};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_yaxis(void) {
	return (vector_t){0, 1, 0, 1};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_zaxis(void) {
	return (vector_t){0, 0, 1, 1};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize(const vector_t v) {
	float32_t inv_length = math_rsqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	vector_t rv = v;
	rv.x *= inv_length;
	rv.y *= inv_length;
	rv.z *= inv_length;
	rv.w *= inv_length;
	return rv;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_normalize3(const vector_t v) {
	float32_t inv_length = math_rsqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	vector_t rv = v;
	rv.x *= inv_length;
	rv.y *= inv_length;
	rv.z *= inv_length;
	return rv;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot(const vector_t v0, const vector_t v1) {
	return vector_uniform(v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_dot3(const vector_t v0, const vector_t v1) {
	return vector_uniform(v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_cross3(const vector_t v0, const vector_t v1) {
	return (vector_t){v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x, 1};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_mul(const vector_t v0, const vector_t v1) {
	return (vector_t){v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_div(const vector_t v0, const vector_t v1) {
	return (vector_t){v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_add(const vector_t v0, const vector_t v1) {
	return (vector_t){v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sub(const vector_t v0, const vector_t v1) {
	return (vector_t){v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_neg(const vector_t v) {
	return (vector_t){-v.x, -v.y, -v.z, -v.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_muladd(const vector_t v0, const vector_t v1, const vector_t v2) {
	return vector_add(vector_mul(v0, v1), v2);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle(const vector_t v, const unsigned int mask) {
	const float32_t* element = &v.x;
	return (vector_t){element[(mask >> 0) & 0x3], element[(mask >> 2) & 0x3], element[(mask >> 4) & 0x3],
	                  element[(mask >> 6) & 0x3]};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_shuffle2(const vector_t v0, const vector_t v1, const unsigned int mask) {
	const float32_t* element0 = &v0.x;
	const float32_t* element1 = &v1.x;
	return (vector_t){element0[(mask >> 0) & 0x3], element0[(mask >> 2) & 0x3], element1[(mask >> 4) & 0x3],
	                  element1[(mask >> 6) & 0x3]};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_scale(const vector_t v, const real s) {
	return (vector_t){v.x * s, v.y * s, v.z * s, v.w * s};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_lerp(const vector_t from, const vector_t to, const real factor) {
	return (vector_t){from.x + (to.x - from.x) * factor, from.y + (to.y - from.y) * factor,
	                  from.z + (to.z - from.z) * factor, from.w + (to.w - from.w) * factor};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_project(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize(at);
	const vector_t ndotv = vector_dot(normal, v);
	return (vector_t){normal.x * ndotv.x, normal.y * ndotv.y, normal.z * ndotv.z, normal.w * ndotv.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_reflect(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize(at);
	const vector_t ndotv = vector_dot(normal, v);
	return (vector_t){(2.0f * (normal.x * ndotv.x)) - v.x, (2.0f * (normal.y * ndotv.y)) - v.y,
	                  (2.0f * (normal.z * ndotv.z)) - v.z, (2.0f * (normal.w * ndotv.w)) - v.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_project3(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize3(at);
	const vector_t ndotv = vector_dot3(normal, v);
	return (vector_t){normal.x * ndotv.x, normal.y * ndotv.y, normal.z * ndotv.z, v.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_reflect3(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize3(at);
	const vector_t ndotv = vector_dot3(normal, v);
	return (vector_t){(2.0f * (normal.x * ndotv.x)) - v.x, (2.0f * (normal.y * ndotv.y)) - v.y,
	                  (2.0f * (normal.z * ndotv.z)) - v.z, v.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_fast(const vector_t v) {
	return vector_length(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length(const vector_t v) {
	return vector_uniform(math_sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length_sqr(const vector_t v) {
	return vector_uniform(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_fast(const vector_t v) {
	return vector_length3(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3(const vector_t v) {
	return vector_uniform(math_sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_length3_sqr(const vector_t v) {
	return vector_uniform(v.x * v.x + v.y * v.y + v.z * v.z);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_sqrt(const vector_t v) {
	return vector(math_sqrt(v.x), math_sqrt(v.y), math_sqrt(v.z), math_sqrt(v.w));
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_min(const vector_t v0, const vector_t v1) {
	return (vector_t){(v0.x < v1.x) ? v0.x : v1.x, (v0.y < v1.y) ? v0.y : v1.y, (v0.z < v1.z) ? v0.z : v1.z,
	                  (v0.w < v1.w) ? v0.w : v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_max(const vector_t v0, const vector_t v1) {
	return (vector_t){(v0.x > v1.x) ? v0.x : v1.x, (v0.y > v1.y) ? v0.y : v1.y, (v0.z > v1.z) ? v0.z : v1.z,
	                  (v0.w > v1.w) ? v0.w : v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_abs(const vector_t v) {
	return (vector_t){math_abs(v.x), math_abs(v.y), math_abs(v.z), math_abs(v.w)};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_x(const vector_t v) {
	return v.x;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_y(const vector_t v) {
	return v.y;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_z(const vector_t v) {
	return v.z;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL real
vector_w(const vector_t v) {
	return v.w;
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
	return (vectori_t){0, 0, 0, 0};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vectori_one(void) {
	return (vectori_t){1, 1, 1, 1};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_x(const vectori_t v) {
	return v.x;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_y(const vectori_t v) {
	return v.x;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_z(const vectori_t v) {
	return v.x;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_w(const vectori_t v) {
	return v.x;
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL int32_t
vectori_component(const vectori_t v, int c) {
	return *((const int32_t*)&v + c);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_equal(const vector_t v0, const vector_t v1) {
	return (vectori_t){v0.x == v1.x, v0.y == v1.y, v0.z == v1.z, v0.w == v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_lequal(const vector_t v0, const vector_t v1) {
	return (vectori_t){v0.x <= v1.x, v0.y <= v1.y, v0.z <= v1.z, v0.w <= v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_less(const vector_t v0, const vector_t v1) {
	return (vectori_t){v0.x < v1.x, v0.y < v1.y, v0.z < v1.z, v0.w < v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_gequal(const vector_t v0, const vector_t v1) {
	return (vectori_t){v0.x >= v1.x, v0.y >= v1.y, v0.z >= v1.z, v0.w >= v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vectori_t
vector_greater(const vector_t v0, const vector_t v1) {
	return (vectori_t){v0.x > v1.x, v0.y > v1.y, v0.z > v1.z, v0.w > v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_rotate(const vector_t v, const matrix_t m) {
	return vector((m.frow[0][0] * v.x) + (m.frow[1][0] * v.y) + (m.frow[2][0] * v.z),
	              (m.frow[0][1] * v.x) + (m.frow[1][1] * v.y) + (m.frow[2][1] * v.z),
	              (m.frow[0][2] * v.x) + (m.frow[1][2] * v.y) + (m.frow[2][2] * v.z), v.w);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector_transform(const vector_t v, const matrix_t m) {
	return vector((m.frow[0][0] * v.x) + (m.frow[1][0] * v.y) + (m.frow[2][0] * v.z) + (m.frow[3][0] * v.w),
	              (m.frow[0][1] * v.x) + (m.frow[1][1] * v.y) + (m.frow[2][1] * v.z) + (m.frow[3][1] * v.w),
	              (m.frow[0][2] * v.x) + (m.frow[1][2] * v.y) + (m.frow[2][2] * v.z) + (m.frow[3][2] * v.w),
	              (m.frow[0][3] * v.x) + (m.frow[1][3] * v.y) + (m.frow[2][3] * v.z) + (m.frow[3][3] * v.w));
}

#if FOUNDATION_COMPILER_CLANG
#pragma clang diagnostic pop
#endif
