/* main.c  -  Vector tests  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

#include <foundation/foundation.h>
#include <test/test.h>

//For testing specific implementations
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
test_matrix_application(void) {
	application_t app = {0};
	app.name = string_const(STRING_CONST("Matrix tests"));
	app.short_name = string_const(STRING_CONST("test_matrix"));
	app.config_dir = string_const(STRING_CONST("test_matrix"));
	app.version = vector_module_version();
	app.flags = APPLICATION_UTILITY;
	return app;
}

static memory_system_t
test_matrix_memory_system(void) {
	return memory_system_malloc();
}

static foundation_config_t
test_matrix_config(void) {
	foundation_config_t config;
	memset(&config, 0, sizeof(config));
	return config;
}

static int
test_matrix_initialize(void) {
	vector_config_t config;
	memset(&config, 0, sizeof(config));
	return vector_module_initialize(config);
}

static void test_matrix_finalize(void) {
	vector_module_finalize();
}

DECLARE_TEST(matrix, construct) {
	matrix_t mat;

	mat = matrix_zero();
	EXPECT_VECTOREQ(mat.row[0], vector_zero());
	EXPECT_VECTOREQ(mat.row[1], vector_zero());
	EXPECT_VECTOREQ(mat.row[2], vector_zero());
	EXPECT_VECTOREQ(mat.row[3], vector_zero());

	mat = matrix_identity();
	EXPECT_VECTOREQ(mat.row[0], vector(1, 0, 0, 0));
	EXPECT_VECTOREQ(mat.row[1], vector(0, 1, 0, 0));
	EXPECT_VECTOREQ(mat.row[2], vector(0, 0, 1, 0));
	EXPECT_VECTOREQ(mat.row[3], vector(0, 0, 0, 1));

	float32_t unaligned[] = {
		0,
		1, -2, 3, -4,
		-5, 6, -7, 8,
		9, 10, 11, 12,
		-13, -14, -15, -16
	};

	mat = matrix_unaligned(&unaligned[1]);
	EXPECT_VECTOREQ(mat.row[0], vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(mat.row[1], vector(-5, 6, -7, 8));
	EXPECT_VECTOREQ(mat.row[2], vector(9, 10, 11, 12));
	EXPECT_VECTOREQ(mat.row[3], vector(-13, -14, -15, -16));

	VECTOR_ALIGN float32_t aligned[] = {
		1, -2, 3, -4,
		-5, 6, -7, 8,
		9, 10, 11, 12,
		-13, -14, -15, -16
	};

	mat = matrix_aligned(aligned);
	EXPECT_VECTOREQ(mat.row[0], vector(1, -2, 3, -4));
	EXPECT_VECTOREQ(mat.row[1], vector(-5, 6, -7, 8));
	EXPECT_VECTOREQ(mat.row[2], vector(9, 10, 11, 12));
	EXPECT_VECTOREQ(mat.row[3], vector(-13, -14, -15, -16));

	return 0;
}

DECLARE_TEST(matrix, ops) {
	matrix_t mat;

	VECTOR_ALIGN float32_t aligned[] = {
		1, -2, 3, -4,
		-5, 6, -7, 8,
		9, 10, 11, 12,
		-13, -14, -15, -16
	};

	float32_t unaligned[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15
	};

	mat = matrix_transpose(matrix_aligned(aligned));
	EXPECT_VECTOREQ(mat.row[0], vector(1, -5, 9, -13));
	EXPECT_VECTOREQ(mat.row[1], vector(-2, 6, 10, -14));
	EXPECT_VECTOREQ(mat.row[2], vector(3, -7, 11, -15));
	EXPECT_VECTOREQ(mat.row[3], vector(-4, 8, 12, -16));

	mat = matrix_add(matrix_zero(), matrix_zero());
	EXPECT_VECTOREQ(mat.row[0], vector_zero());
	EXPECT_VECTOREQ(mat.row[1], vector_zero());
	EXPECT_VECTOREQ(mat.row[2], vector_zero());
	EXPECT_VECTOREQ(mat.row[3], vector_zero());

	mat = matrix_add(matrix_zero(), matrix_identity());
	EXPECT_VECTOREQ(mat.row[0], vector(1, 0, 0, 0));
	EXPECT_VECTOREQ(mat.row[1], vector(0, 1, 0, 0));
	EXPECT_VECTOREQ(mat.row[2], vector(0, 0, 1, 0));
	EXPECT_VECTOREQ(mat.row[3], vector(0, 0, 0, 1));

	mat = matrix_add(matrix_identity(), matrix_zero());
	EXPECT_VECTOREQ(mat.row[0], vector(1, 0, 0, 0));
	EXPECT_VECTOREQ(mat.row[1], vector(0, 1, 0, 0));
	EXPECT_VECTOREQ(mat.row[2], vector(0, 0, 1, 0));
	EXPECT_VECTOREQ(mat.row[3], vector(0, 0, 0, 1));

	mat = matrix_add(matrix_aligned(aligned), matrix_unaligned(unaligned));
	EXPECT_VECTOREQ(mat.row[0], vector(1, -1, 5, -1));
	EXPECT_VECTOREQ(mat.row[1], vector(-1, 11, -1, 15));
	EXPECT_VECTOREQ(mat.row[2], vector(17, 19, 21, 23));
	EXPECT_VECTOREQ(mat.row[3], vector(-1, -1, -1, -1));

	mat = matrix_add(matrix_aligned(aligned), matrix_transpose(matrix_aligned(aligned)));
	EXPECT_VECTOREQ(mat.row[0], vector(2, -7, 12, -17));
	EXPECT_VECTOREQ(mat.row[1], vector(-7, 12, 3, -6));
	EXPECT_VECTOREQ(mat.row[2], vector(12, 3, 22, -3));
	EXPECT_VECTOREQ(mat.row[3], vector(-17, -6, -3, -32));

	mat = matrix_sub(matrix_zero(), matrix_zero());
	EXPECT_VECTOREQ(mat.row[0], vector_zero());
	EXPECT_VECTOREQ(mat.row[1], vector_zero());
	EXPECT_VECTOREQ(mat.row[2], vector_zero());
	EXPECT_VECTOREQ(mat.row[3], vector_zero());

	mat = matrix_sub(matrix_zero(), matrix_identity());
	EXPECT_VECTOREQ(mat.row[0], vector(-1, 0, 0, 0));
	EXPECT_VECTOREQ(mat.row[1], vector(0, -1, 0, 0));
	EXPECT_VECTOREQ(mat.row[2], vector(0, 0, -1, 0));
	EXPECT_VECTOREQ(mat.row[3], vector(0, 0, 0, -1));

	mat = matrix_add(matrix_identity(), matrix_zero());
	EXPECT_VECTOREQ(mat.row[0], vector(1, 0, 0, 0));
	EXPECT_VECTOREQ(mat.row[1], vector(0, 1, 0, 0));
	EXPECT_VECTOREQ(mat.row[2], vector(0, 0, 1, 0));
	EXPECT_VECTOREQ(mat.row[3], vector(0, 0, 0, 1));

	mat = matrix_sub(matrix_aligned(aligned), matrix_unaligned(unaligned));
	EXPECT_VECTOREQ(mat.row[0], vector(1, -3, 1, -7));
	EXPECT_VECTOREQ(mat.row[1], vector(-9, 1, -13, 1));
	EXPECT_VECTOREQ(mat.row[2], vector(1, 1, 1, 1));
	EXPECT_VECTOREQ(mat.row[3], vector(-25, -27, -29, -31));

	mat = matrix_sub(matrix_aligned(aligned), matrix_transpose(matrix_aligned(aligned)));
	EXPECT_VECTOREQ(mat.row[0], vector(0,   3,   -6,  9));
	EXPECT_VECTOREQ(mat.row[1], vector(-3,   0,  -17, 22));
	EXPECT_VECTOREQ(mat.row[2], vector(6,  17,    0, 27));
	EXPECT_VECTOREQ(mat.row[3], vector(-9, -22,  -27,  0));

	mat = matrix_mul(matrix_zero(), matrix_zero());
	EXPECT_VECTOREQ(mat.row[0], vector_zero());
	EXPECT_VECTOREQ(mat.row[1], vector_zero());
	EXPECT_VECTOREQ(mat.row[2], vector_zero());
	EXPECT_VECTOREQ(mat.row[3], vector_zero());

	mat = matrix_mul(matrix_zero(), matrix_identity());
	EXPECT_VECTOREQ(mat.row[0], vector_zero());
	EXPECT_VECTOREQ(mat.row[1], vector_zero());
	EXPECT_VECTOREQ(mat.row[2], vector_zero());
	EXPECT_VECTOREQ(mat.row[3], vector_zero());

	mat = matrix_mul(matrix_identity(), matrix_zero());
	EXPECT_VECTOREQ(mat.row[0], vector_zero());
	EXPECT_VECTOREQ(mat.row[1], vector_zero());
	EXPECT_VECTOREQ(mat.row[2], vector_zero());
	EXPECT_VECTOREQ(mat.row[3], vector_zero());

	mat = matrix_mul(matrix_identity(), matrix_identity());
	EXPECT_VECTOREQ(mat.row[0], vector(1, 0, 0, 0));
	EXPECT_VECTOREQ(mat.row[1], vector(0, 1, 0, 0));
	EXPECT_VECTOREQ(mat.row[2], vector(0, 0, 1, 0));
	EXPECT_VECTOREQ(mat.row[3], vector(0, 0, 0, 1));

	mat = matrix_mul(matrix_aligned(aligned), matrix_unaligned(unaligned));
	EXPECT_VECTOREQ(mat.row[0], vector(-8 + 24 - 48, 1 - 10 + 27 - 4 * 13, 2 - 12 + 30 - 4 * 14,
	                                   3 - 14 + 33 - 4 * 15));
	EXPECT_VECTOREQ(mat.row[1], vector(6 * 4 - 7 * 8 + 8 * 12, -5 * 1 + 6 * 5 - 7 * 9 + 8 * 13,
	                                   -5 * 2 + 6 * 6 - 7 * 10 + 8 * 14, -5 * 3 + 6 * 7 - 7 * 11 + 8 * 15));
	EXPECT_VECTOREQ(mat.row[2], vector(10 * 4 + 11 * 8 + 12 * 12, 9 * 1 + 10 * 5 + 11 * 9 + 12 * 13,
	                                   9 * 2 + 10 * 6 + 11 * 10 + 12 * 14, 9 * 3 + 10 * 7 + 11 * 11 + 12 * 15));
	EXPECT_VECTOREQ(mat.row[3], vector(-14 * 4 - 15 * 8 - 16 * 12, -13 * 1 - 14 * 5 - 15 * 9 - 16 * 13,
	                                   -13 * 2 - 14 * 6 - 15 * 10 - 16 * 14, -13 * 3 - 14 * 7 - 15 * 11 - 16 * 15));

	return 0;
}


DECLARE_TEST(matrix, vec) {
	vector_t vec;

	VECTOR_ALIGN float32_t aligned_rotm[] = {
		0, 2, 0, 11,
		0, 0, 3, 12,
		1, 0, 0, 13,
		7, 8, 9, 10
	};

	VECTOR_ALIGN float32_t aligned_tformm[] = {
		0, 2, 0, 0,
		0, 0, 3, 0,
		1, 0, 0, 0,
		-1, 2, 5, 1
	};

	vec = matrix_rotate(matrix_zero(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = matrix_rotate(matrix_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector(0, 0, 0, 1));

	vec = matrix_rotate(matrix_identity(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = matrix_rotate(matrix_aligned(aligned_rotm), vector_xaxis());
	EXPECT_VECTOREQ(vec, vector(0, 2, 0, 1));

	vec = matrix_rotate(matrix_aligned(aligned_rotm), vector_yaxis());
	EXPECT_VECTOREQ(vec, vector(0, 0, 3, 1));

	vec = matrix_rotate(matrix_aligned(aligned_rotm), vector_zaxis());
	EXPECT_VECTOREQ(vec, vector(1, 0, 0, 1));

	vec = matrix_transform(matrix_zero(), vector_zero());
	EXPECT_VECTOREQ(vec, vector_zero());

	vec = matrix_transform(matrix_zero(), vector_one());
	EXPECT_VECTOREQ(vec, vector(0, 0, 0, 0));

	vec = matrix_transform(matrix_identity(), vector_one());
	EXPECT_VECTOREQ(vec, vector_one());

	vec = matrix_transform(matrix_aligned(aligned_tformm), vector_xaxis());
	EXPECT_VECTOREQ(vec, vector(-1, 4, 5, 1));

	vec = matrix_transform(matrix_aligned(aligned_tformm), vector_yaxis());
	EXPECT_VECTOREQ(vec, vector(-1, 2, 8, 1));

	vec = matrix_transform(matrix_aligned(aligned_tformm), vector_zaxis());
	EXPECT_VECTOREQ(vec, vector(0, 2, 5, 1));

	return 0;
}

static void
test_matrix_declare(void) {
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

	ADD_TEST(matrix, construct);
	ADD_TEST(matrix, ops);
	ADD_TEST(matrix, vec);
}

test_suite_t test_matrix_suite = {
	test_matrix_application,
	test_matrix_memory_system,
	test_matrix_config,
	test_matrix_declare,
	test_matrix_initialize,
	test_matrix_finalize
};

#if BUILD_MONOLITHIC

int
test_matrix_run(void);

int
test_matrix_run(void) {
	test_suite = test_matrix_suite;
	return test_run_all();
}

#else

test_suite_t
test_suite_define(void);

test_suite_t
test_suite_define(void) {
	return test_matrix_suite;
}

#endif
