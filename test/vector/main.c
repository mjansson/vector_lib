/* main.c  -  Vector tests  -  Public Domain  -  2013 Mattias Jansson
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

#include <foundation/foundation.h>
#include <test/test.h>

// For testing specific implementations
//#undef  FOUNDATION_ARCH_SSE4
//#define FOUNDATION_ARCH_SSE4 0
//#undef  FOUNDATION_ARCH_SSE3
//#define FOUNDATION_ARCH_SSE3 0
//#undef  FOUNDATION_ARCH_SSE2
//#define FOUNDATION_ARCH_SSE2 0
//#undef  FOUNDATION_ARCH_NEON
//#define FOUNDATION_ARCH_NEON 0

#include <vector/vector.h>

#include "../test/vector.h"

static application_t
test_vector_application(void) {
	application_t app;
	memset(&app, 0, sizeof(app));
	app.name = string_const(STRING_CONST("Vector tests"));
	app.short_name = string_const(STRING_CONST("test_vector"));
	app.company = string_const(STRING_CONST(""));
	app.version = vector_module_version();
	app.exception_handler = test_exception_handler;
	app.flags = APPLICATION_UTILITY;
	return app;
}

static memory_system_t
test_vector_memory_system(void) {
	return memory_system_malloc();
}

static foundation_config_t
test_vector_config(void) {
	foundation_config_t config;
	memset(&config, 0, sizeof(config));
	return config;
}

static int
test_vector_initialize(void) {
	vector_config_t config;
	memset(&config, 0, sizeof(config));
	return vector_module_initialize(config);
}

static void
test_vector_finalize(void) {
	vector_module_finalize();
}

DECLARE_TEST(vector, construct) {
	vector_t vec;
	float32_t unaligned[4] = {3, 2, 1, 0};
	VECTOR_ALIGN float32_t aligned[4] = {0, 1, 2, 3};

	vec = vector(REAL_C(0.0), REAL_C(1.0), REAL_C(2.0), REAL_C(3.0));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(3.0));

	vec = vector_unaligned(unaligned);
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.0));

	vec = vector_aligned(aligned);
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(3.0));

	vec = vector_uniform(REAL_C(4.0));
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(4.0));

	vec = vector_zero();
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.0));

	vec = vector_one();
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_half();
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.5));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.5));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.5));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.5));

	vec = vector_two();
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(2.0));

	vec = vector_origo();
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_xaxis();
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_yaxis();
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_zaxis();
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	return 0;
}

DECLARE_TEST(vector, normalize) {
	vector_t vec;
	real ref;

	vec = vector_normalize(vector(1, 0, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(1, 0, 0, 0));

	vec = vector_normalize(vector(0, 1, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 1, 0, 0));

	vec = vector_normalize(vector(0, 0, 1, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 0, 1, 0));

	vec = vector_normalize(vector(0, 0, 0, 1));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 0, 0, 1));

	ref = math_sqrt(REAL_C(1.0) / REAL_C(4.0));
	vec = vector_normalize(vector(1, 1, 1, 1));
	EXPECT_VECTORALMOSTEQ(vec, vector(ref, ref, ref, ref));

	ref = math_sqrt(REAL_C(1.0) / REAL_C(4.0));
	vec = vector_normalize(vector(-1, 1, -1, 1));
	EXPECT_VECTORALMOSTEQ(vec, vector(-ref, ref, -ref, ref));

	ref = math_sqrt(REAL_C(158.0));
	vec = vector_normalize(vector(0, -3, 7, -10));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, -REAL_C(3.0) / ref, REAL_C(7.0) / ref, -REAL_C(10.0) / ref));

	vec = vector_normalize3(vector(1, 0, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(1, 0, 0, 0));

	vec = vector_normalize3(vector(0, 1, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 1, 0, 0));

	vec = vector_normalize3(vector(0, 0, 1, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 0, 1, 0));

	ref = math_sqrt(REAL_C(1.0) / REAL_C(3.0));
	vec = vector_normalize3(vector(1, 1, 1, 1));
	EXPECT_VECTORALMOSTEQ(vec, vector(ref, ref, ref, 1));

	ref = math_sqrt(REAL_C(1.0) / REAL_C(3.0));
	vec = vector_normalize3(vector(-1, 1, -1, 1));
	EXPECT_VECTORALMOSTEQ(vec, vector(-ref, ref, -ref, 1));

	ref = math_sqrt(REAL_C(58.0));
	vec = vector_normalize3(vector(0, -3, 7, -10));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, -REAL_C(3.0) / ref, REAL_C(7.0) / ref, -REAL_C(10.0)));

	return 0;
}

DECLARE_TEST(vector, dot) {
	vector_t vec;

	vec = vector_dot(vector_zero(), vector_one());
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.0));

	vec = vector_dot(vector_one(), vector_zero());
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.0));

	vec = vector_dot(vector_one(), vector_one());
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(4.0));

	vec = vector_dot(vector(1, 0, 0, 0), vector(2, 0, 0, 0));
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(2.0));

	vec = vector_dot(vector(-1, 1, -1, 1), vector(1, 1, -1, -1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.0));

	vec = vector_dot(vector(-3, 4, -5, 6), vector(0, 1, -1, -2));
	EXPECT_REALEQ(vector_x(vec), REAL_C(-3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(-3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(-3.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(-3.0));

	vec = vector_dot3(vector_zero(), vector_one());
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.0));

	vec = vector_dot3(vector_one(), vector_zero());
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(0.0));

	vec = vector_dot3(vector_one(), vector_one());
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(3.0));

	vec = vector_dot3(vector(-1, 1, -1, 1), vector(1, 1, -1, -1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_dot3(vector(-3, 4, -5, 6), vector(0, 1, -1, -2));
	EXPECT_REALEQ(vector_x(vec), REAL_C(9.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(9.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(9.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(9.0));

	return 0;
}

DECLARE_TEST(vector, cross) {
	vector_t vec;

	vec = vector_cross3(vector(0, 0, 0, 1), vector(1, 2, 3, 4));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	vec = vector_cross3(vector(1, 0, 0, 0), vector(1, 0, 0, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	vec = vector_cross3(vector(1, 0, 0, 1), vector(0, 1, 0, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));

	vec = vector_cross3(vector(1, 0, 0, 0), vector(0, 0, 1, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(-1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	vec = vector_cross3(vector(0, 1, 0, 1), vector(1, 0, 0, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(-1.0));

	vec = vector_cross3(vector(0, 1, 0, 0), vector(0, 1, 0, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	vec = vector_cross3(vector(0, 1, 0, 1), vector(0, 0, 1, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	vec = vector_cross3(vector(0, 0, 1, 0), vector(1, 0, 0, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	vec = vector_cross3(vector(0, 0, 1, 1), vector(0, 1, 0, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(-1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	vec = vector_cross3(vector(0, 0, 1, 0), vector(0, 0, 1, 1));
	EXPECT_REALEQ(vector_x(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(0.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(0.0));

	return 0;
}

DECLARE_TEST(vector, ops) {
	vector_t vec;

	vec = vector_mul(vector_one(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_mul(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_mul(vector_one(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_mul(vector_two(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_mul(vector_two(), vector_half());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_mul(vector(1, 2, 3, 4), vector(5, 6, 7, 8));
	EXPECT_VECTOREQ(vec, vector(5, 12, 21, 32));

	vec = vector_div(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_div(vector_one(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_div(vector_one(), vector_half());
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_div(vector(1, 2, 3, 4), vector(5, 6, 7, 8));
	EXPECT_VECTOREQ(vec, vector(REAL_C(1.0) / REAL_C(5.0), REAL_C(2.0) / REAL_C(6.0), REAL_C(3.0) / REAL_C(7.0),
	                            REAL_C(4.0) / REAL_C(8.0)));

	vec = vector_add(vector_zero(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_add(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_add(vector_one(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_add(vector_one(), vector_one());
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_add(vector(1, 2, 3, 4), vector(5, 6, 7, 8));
	EXPECT_VECTOREQ(vec, vector(6, 8, 10, 12));

	vec = vector_sub(vector_zero(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_sub(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector(-1, -1, -1, -1));

	vec = vector_sub(vector_one(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_sub(vector_one(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_sub(vector(1, -2, 3, -4), vector(-5, 6, -7, 8));
	EXPECT_VECTOREQ(vec, vector(6, -8, 10, -12));

	vec = vector_neg(vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_neg(vector_one());
	EXPECT_VECTOREQ(vec, vector(-1, -1, -1, -1));

	vec = vector_neg(vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(vec, vector(-1, 2, -3, 4));

	vec = vector_muladd(vector_one(), vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_muladd(vector_zero(), vector_one(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_muladd(vector_one(), vector_one(), vector_one());
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_muladd(vector_two(), vector_zero(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_muladd(vector_two(), vector_half(), vector_one());
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_muladd(vector(1, 2, 3, 4), vector(5, 6, 7, 8), vector(-1, -2, -3, -4));
	EXPECT_VECTOREQ(vec, vector(4, 10, 18, 28));

	vec = vector_sqrt(vector(4, 9, 16, 25));
	EXPECT_VECTOREQ(vec, vector(2, 3, 4, 5));

	return 0;
}

DECLARE_TEST(vector, shuffle) {
	vector_t in = vector(1, 2, 3, 4);
	vector_t in2 = vector(5, 6, 7, 8);
	vector_t vec;

	vec = vector_shuffle(in, VECTOR_MASK_XXXX);
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_shuffle(in, VECTOR_MASK_YYYY);
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(2.0));

	vec = vector_shuffle(in, VECTOR_MASK_ZZZZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(3.0));

	vec = vector_shuffle(in, VECTOR_MASK_WWWW);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(4.0));

	vec = vector_shuffle(in, VECTOR_MASK_XYZW);
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(4.0));

	vec = vector_shuffle(in, VECTOR_MASK_WZYX);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_shuffle(in, VECTOR_MASK_YXWZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(3.0));

	vec = vector_shuffle(in, VECTOR_MASK_ZWXY);
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(2.0));

	vec = vector_shuffle(in, VECTOR_MASK_ZZXX);
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(1.0));

	vec = vector_shuffle(in, VECTOR_MASK_YYZZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(3.0));

	vec = vector_shuffle(in, VECTOR_MASK_WXXW);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(4.0));

	vec = vector_shuffle(in, VECTOR_MASK_WYYZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(3.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_XXXX);
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(5.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(5.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_YYYY);
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(6.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(6.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_ZZZZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(7.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(7.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_WWWW);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(8.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(8.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_XYZW);
	EXPECT_REALEQ(vector_x(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(7.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(8.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_WZYX);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(6.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(5.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_YXWZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(8.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(7.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_ZWXY);
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(5.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(6.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_ZZXX);
	EXPECT_REALEQ(vector_x(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(3.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(5.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(5.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_YYZZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(7.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(7.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_WXXW);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(1.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(5.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(8.0));

	vec = vector_shuffle2(in, in2, VECTOR_MASK_WYYZ);
	EXPECT_REALEQ(vector_x(vec), REAL_C(4.0));
	EXPECT_REALEQ(vector_y(vec), REAL_C(2.0));
	EXPECT_REALEQ(vector_z(vec), REAL_C(6.0));
	EXPECT_REALEQ(vector_w(vec), REAL_C(7.0));

	return 0;
}

DECLARE_TEST(vector, util) {
	vector_t vec;

	vec = vector_scale(vector_zero(), 1);
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_scale(vector_one(), 1);
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_scale(vector_two(), 0);
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_scale(vector_two(), 1);
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_scale(vector_one(), 2);
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_scale(vector(1, 2, 3, 4), 5);
	EXPECT_VECTOREQ(vec, vector(5, 10, 15, 20));

	vec = vector_lerp(vector_zero(), vector_zero(), 0);
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_lerp(vector_zero(), vector_zero(), 1);
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_lerp(vector_zero(), vector_one(), 0);
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_lerp(vector_zero(), vector_one(), 1);
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_lerp(vector_one(), vector_one(), 1);
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_lerp(vector_one(), vector_one(), 10);
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_lerp(vector_zero(), vector_one(), 2);
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_lerp(vector_zero(), vector_one(), -1);
	EXPECT_VECTOREQ(vec, vector_uniform(-1));

	vec = vector_lerp(vector(1, -2, 3, -4), vector(11, -12, -13, 14), REAL_C(0.5));
	EXPECT_VECTOREQ(vec, vector(6, -7, -5, 5));

	vec = vector_project(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_project(vector_one(), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_one());

	vec = vector_project(vector_uniform(-1), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_uniform(-1));

	vec = vector_project(vector(1, 2, 3, 4), vector(2, 0, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(1, 0, 0, 0));

	vec = vector_project(vector(1, 2, 3, 4), vector(0, -3, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 2, 0, 0));

	vec = vector_project(vector(1, 2, 3, 4), vector(0, 0, 4, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 0, 3, 0));

	vec = vector_project(vector(1, 2, 3, 4), vector(0, 0, 0, -5));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 0, 0, 4));

	vec = vector_project(vector(1, 2, 3, 4), vector(0, 1, 0, 2));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 2, 0, 4));

	vec = vector_project3(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_project3(vector_one(), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_one());

	vec = vector_project3(vector_uniform(-1), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_uniform(-1));

	vec = vector_project3(vector(1, 2, 3, 4), vector(2, 0, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(1, 0, 0, 4));

	vec = vector_project3(vector(1, 2, 3, 4), vector(0, -3, 0, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 2, 0, 4));

	vec = vector_project3(vector(1, 2, 3, 4), vector(0, 0, 4, 0));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 0, 3, 4));

	vec = vector_project3(vector(1, 2, 3, 4), vector(0, 0, 0, -5));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 0, 0, 4));

	vec = vector_project3(vector(1, 2, 3, 4), vector(0, 1, 0, 2));
	EXPECT_VECTORALMOSTEQ(vec, vector(0, 2, 0, 4));

	vec = vector_reflect(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_reflect(vector_one(), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_one());

	vec = vector_reflect(vector_uniform(-1), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_uniform(-1));

	vec = vector_reflect(vector(1, 1, 0, 1), vector(0, 1, 0, 1));
	EXPECT_VECTORALMOSTEQ(vec, vector(-1, 1, 0, 1));

	vec = vector_reflect(vector(2, 3, 4, 5), vector(-2, -3, 0, -5));
	EXPECT_VECTORALMOSTEQ(vec, vector(2, 3, -4, 5));

	vec = vector_reflect3(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_reflect3(vector_one(), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_one());

	vec = vector_reflect3(vector_uniform(-1), vector_one());
	EXPECT_VECTORALMOSTEQ(vec, vector_uniform(-1));

	vec = vector_reflect3(vector(1, 1, 0, 1), vector(0, 1, 0, 1));
	EXPECT_VECTORALMOSTEQ(vec, vector(-1, 1, 0, 1));

	vec = vector_reflect3(vector(2, 3, 4, 5), vector(-2, -3, 0, -5));
	EXPECT_VECTORALMOSTEQ(vec, vector(2, 3, -4, 5));

	vec = vector_reflect3(vector(2, 3, 4, -5), vector(-2, -3, 0, 13));
	EXPECT_VECTORALMOSTEQ(vec, vector(2, 3, -4, -5));

	return 0;
}

DECLARE_TEST(vector, length) {
	vector_t vec;

	vec = vector_length(vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_length(vector_one());
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_length(vector_two());
	EXPECT_VECTOREQ(vec, vector_uniform(4));

	vec = vector_length(vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(vec, vector_uniform(math_sqrt(30)));

	vec = vector_length_fast(vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_length_fast(vector_one());
	EXPECT_VECTOREQ(vec, vector_two());

	vec = vector_length_fast(vector_two());
	EXPECT_VECTOREQ(vec, vector_uniform(4));

	vec = vector_length_fast(vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(vec, vector_uniform(math_sqrt(30)));

	vec = vector_length3(vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_length3(vector_one());
	EXPECT_VECTOREQ(vec, vector_uniform(REAL_SQRT3));

	vec = vector_length3(vector_two());
	EXPECT_VECTOREQ(vec, vector_uniform(math_sqrt(12)));

	vec = vector_length3(vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(vec, vector_uniform(math_sqrt(14)));

	vec = vector_length3_fast(vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_length3_fast(vector_one());
	EXPECT_VECTOREQ(vec, vector_uniform(REAL_SQRT3));

	vec = vector_length3_fast(vector_two());
	EXPECT_VECTOREQ(vec, vector_uniform(math_sqrt(12)));

	vec = vector_length3_fast(vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(vec, vector_uniform(math_sqrt(14)));

	vec = vector_length_sqr(vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_length_sqr(vector_one());
	EXPECT_VECTOREQ(vec, vector_uniform(4));

	vec = vector_length_sqr(vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(vec, vector_uniform(30));

	vec = vector_length3_sqr(vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_length3_sqr(vector_one());
	EXPECT_VECTOREQ(vec, vector_uniform(3));

	vec = vector_length3_sqr(vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(vec, vector_uniform(14));

	return 0;
}

DECLARE_TEST(vector, minmax) {
	vector_t vec;

	vec = vector_min(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = vector_min(vector_one(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_min(vector(1, 2, 3, 4), vector(2, -3, 4, -5));
	EXPECT_VECTOREQ(vec, vector(1, -3, 3, -5));

	vec = vector_max(vector_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_max(vector_one(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = vector_max(vector(1, 2, 3, 4), vector(2, -3, 4, -5));
	EXPECT_VECTOREQ(vec, vector(2, 2, 4, 4));

	return 0;
}

DECLARE_TEST(vector, component) {
	EXPECT_REALEQ(vector_x(vector_zero()), 0);
	EXPECT_REALEQ(vector_y(vector_zero()), 0);
	EXPECT_REALEQ(vector_z(vector_zero()), 0);
	EXPECT_REALEQ(vector_w(vector_zero()), 0);

	EXPECT_REALEQ(vector_x(vector_one()), 1);
	EXPECT_REALEQ(vector_y(vector_one()), 1);
	EXPECT_REALEQ(vector_z(vector_one()), 1);
	EXPECT_REALEQ(vector_w(vector_one()), 1);

	EXPECT_REALEQ(vector_x(vector(1, -2, 3, -4)), 1);
	EXPECT_REALEQ(vector_y(vector(1, -2, 3, -4)), -2);
	EXPECT_REALEQ(vector_z(vector(1, -2, 3, -4)), 3);
	EXPECT_REALEQ(vector_w(vector(1, -2, 3, -4)), -4);

	EXPECT_REALEQ(vector_component(vector(1, -2, 3, -4), 0), 1);
	EXPECT_REALEQ(vector_component(vector(1, -2, 3, -4), 1), -2);
	EXPECT_REALEQ(vector_component(vector(1, -2, 3, -4), 2), 3);
	EXPECT_REALEQ(vector_component(vector(1, -2, 3, -4), 3), -4);

	return 0;
}

DECLARE_TEST(vector, equal) {
	EXPECT_VECTOREQ(vector_zero(), vector_zero());
	EXPECT_VECTOREQ(vector_one(), vector_one());
	EXPECT_VECTOREQ(vector_uniform(-5), vector_uniform(-5));
	EXPECT_VECTOREQ(vector(1, -2, 3, -4), vector(1, -2, 3, -4));

	EXPECT_VECTORNOTEQ(vector_zero(), vector_one());
	EXPECT_VECTORNOTEQ(vector_one(), vector_zero());
	EXPECT_VECTORNOTEQ(vector_uniform(-5), vector_uniform(5));
	EXPECT_VECTORNOTEQ(vector(1, -2, 3, -4), vector(1, 2, 3, -4));

	return 0;
}

static void
test_vector_declare(void) {
#if FOUNDATION_ARCH_SSE4
	log_info(HASH_TEST, STRING_CONST("Using SSE4 implementation"));
#elif FOUNDATION_ARCH_SSE3
	log_info(HASH_TEST, STRING_CONST("Using SSE3 implementation"));
#elif FOUNDATION_ARCH_SSE2
	log_info(HASH_TEST, STRING_CONST("Using SSE2 implementation"));
#elif FOUNDATION_ARCH_NEON
	log_info(HASH_TEST, STRING_CONST("Using NEON implementation"));
#else
	log_info(HASH_TEST, STRING_CONST("Using fallback implementation"));
#endif

	ADD_TEST(vector, construct);
	ADD_TEST(vector, normalize);
	ADD_TEST(vector, dot);
	ADD_TEST(vector, cross);
	ADD_TEST(vector, ops);
	ADD_TEST(vector, shuffle);
	ADD_TEST(vector, util);
	ADD_TEST(vector, length);
	ADD_TEST(vector, minmax);
	ADD_TEST(vector, component);
	ADD_TEST(vector, equal);
}

static test_suite_t test_vector_suite = {test_vector_application,
                                         test_vector_memory_system,
                                         test_vector_config,
                                         test_vector_declare,
                                         test_vector_initialize,
                                         test_vector_finalize,
                                         0};

#if BUILD_MONOLITHIC

int
test_vector_run(void);

int
test_vector_run(void) {
	test_suite = test_vector_suite;
	return test_run_all();
}

#else

test_suite_t
test_suite_define(void);

test_suite_t
test_suite_define(void) {
	return test_vector_suite;
}

#endif
