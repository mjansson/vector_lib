/* vector_fallback.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t
vector(const real x,const real y,const real z,const real w) {
	return (vector_t){x, y, z, w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_aligned(const float32_aligned128_t* FOUNDATION_RESTRICT v) {
	return *(const vector_t*)v;
}

static FOUNDATION_FORCEINLINE FOUNDATION_PURECALL vector_t
vector_unaligned(const float32_t* FOUNDATION_RESTRICT v) {
	vector_t rv = { *v, *(v + 1), *(v + 2), *(v + 3) };
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
	return (vector_t){v0.y* v1.z - v0.z * v1.y, v0.z* v1.x - v0.x * v1.z, v0.x* v1.y - v0.y * v1.x, 1};
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
	return (vector_t){
		element[(mask >> 0) & 0x3 ],
		element[(mask >> 2) & 0x3 ],
		element[(mask >> 4) & 0x3 ],
		element[(mask >> 6) & 0x3 ]
	};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t 
vector_scale(const vector_t v, const real s) {
	return (vector_t){v.x * s, v.y * s, v.z * s, v.w * s};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t 
vector_lerp(const vector_t from, const vector_t to, const real factor) {
	return (vector_t){
		from.x + (to.x - from.x)* factor,
		from.y + (to.y - from.y)* factor,
		from.z + (to.z - from.z)* factor,
		from.w + (to.w - from.w)* factor
	};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t 
vector_project(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize(at);
	const vector_t ndotv = vector_dot(normal, v);
	return (vector_t){
		normal.x * ndotv.x,
		normal.y * ndotv.y,
		normal.z * ndotv.z,
		normal.w* ndotv.w
	};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t 
vector_reflect(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize(at);
	const vector_t ndotv = vector_dot(normal, v);
	return (vector_t){
		(2.0f * (normal.x * ndotv.x)) - v.x,
		(2.0f * (normal.y * ndotv.y)) - v.y,
		(2.0f * (normal.z * ndotv.z)) - v.z,
		(2.0f * (normal.w * ndotv.w)) - v.w
	};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t 
vector_project3(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize3(at);
	const vector_t ndotv = vector_dot3(normal, v);
	return (vector_t){
		normal.x * ndotv.x,
		normal.y * ndotv.y,
		normal.z * ndotv.z,
		v.w
	};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t 
vector_reflect3(const vector_t v, const vector_t at) {
	const vector_t normal = vector_normalize3(at);
	const vector_t ndotv = vector_dot3(normal, v);
	return (vector_t){
		(2.0f * (normal.x * ndotv.x)) - v.x,
		(2.0f * (normal.y * ndotv.y)) - v.y,
		(2.0f * (normal.z * ndotv.z)) - v.z,
		v.w
	};
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
vector_min(const vector_t v0, const vector_t v1) {
	return (vector_t){(v0.x < v1.x) ? v0.x : v1.x, (v0.y < v1.y) ? v0.y : v1.y, (v0.z < v1.z) ? v0.z : v1.z, (v0.w < v1.w) ? v0.w : v1.w};
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL vector_t 
vector_max(const vector_t v0, const vector_t v1) {
	return (vector_t){(v0.x > v1.x) ? v0.x : v1.x, (v0.y > v1.y) ? v0.y : v1.y, (v0.z > v1.z) ? v0.z : v1.z, (v0.w > v1.w) ? v0.w : v1.w};
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
	FOUNDATION_ASSERT((c >= 0) && (c < 4));
	return *((const float32_t*)&v + c);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL bool 
vector_equal(const vector_t v0, const vector_t v1) {
	return math_real_eq(v0.x, v1.x, 100) && math_real_eq(v0.y, v1.y, 100) &&
	       math_real_eq(v0.z, v1.z, 100) && math_real_eq(v0.w, v1.w, 100);
}
