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

#include <vector/quaternion.h>

#define EXPECT_VECTOREQ( var, expect ) do { if( !vector_equal((var), (expect) )) { log_warnf(HASH_TEST, WARNING_SUSPICIOUS, STRING_CONST("Test failed, %s != %s vector (at %s:%u): (%.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ") (%.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ")"), FOUNDATION_PREPROCESSOR_TOSTRING(var), FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__, (real)vector_x((var)), (real)vector_y((var)), (real)vector_z((var)), (real)vector_w((var)), (real)vector_x((expect)), (real)vector_y((expect)), (real)vector_z((expect)), (real)vector_w((expect)) ); return FAILED_TEST; } } while(0)
#define EXPECT_VECTORALMOSTEQ( var, expect ) do { real diff = vector_test_difference((var), (expect)); if( diff > 0.0075f ) { log_warnf(HASH_TEST, WARNING_SUSPICIOUS, STRING_CONST("Test failed, %s != %s vector (at %s:%u): (%.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ") (%.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ") diff %.6" PRIreal), FOUNDATION_PREPROCESSOR_TOSTRING(var), FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__, (real)vector_x((var)), (real)vector_y((var)), (real)vector_z((var)), (real)vector_w((var)), (real)vector_x((expect)), (real)vector_y((expect)), (real)vector_z((expect)), (real)vector_w((expect)), diff ); return FAILED_TEST; } } while(0)

static application_t
test_quaternion_application(void) {
	application_t app = {0};
	app.name = string_const(STRING_CONST("Quaternion tests"));
	app.short_name = string_const(STRING_CONST("test_quaternion"));
	app.config_dir = string_const(STRING_CONST("test_quaternion"));
	app.version = vector_module_version();
	app.flags = APPLICATION_UTILITY;
	return app;
}

static memory_system_t
test_quaternion_memory_system(void) {
	return memory_system_malloc();
}

static foundation_config_t
test_quaternion_config(void) {
	foundation_config_t config;
	memset(&config, 0, sizeof(config));
	return config;
}

static int
test_quaternion_initialize(void) {
	vector_config_t config;
	memset(&config, 0, sizeof(config));
	return vector_module_initialize(config);
}

static void
test_quaternion_finalize(void) {
	vector_module_finalize();
}

DECLARE_TEST(quaternion, construct) {
	quaternion_t q;
	float32_t unaligned[] = { 1, -2, 3, -4 };
	VECTOR_ALIGN float32_t aligned[] = { 1, -2, 3, -4 };

	q = quaternion_zero();
	EXPECT_VECTOREQ(q, vector_zero());

	q = quaternion_identity();
	EXPECT_VECTOREQ(q, vector(0, 0, 0, 1));

	q = quaternion_unaligned(unaligned);
	EXPECT_VECTOREQ(q, vector(1, -2, 3, -4));

	q = quaternion_aligned(aligned);
	EXPECT_VECTOREQ(q, vector(1, -2, 3, -4));

	return 0;
}

static void
test_quaternion_declare(void) {
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

	ADD_TEST(quaternion, construct);
}

test_suite_t test_quaternion_suite = {
	test_quaternion_application,
	test_quaternion_memory_system,
	test_quaternion_config,
	test_quaternion_declare,
	test_quaternion_initialize,
	test_quaternion_finalize
};

#if BUILD_MONOLITHIC

int
test_quaternion_run(void);

int
test_quaternion_run(void) {
	test_suite = test_quaternion_suite;
	return test_run_all();
}

#else

test_suite_t
test_suite_define(void);

test_suite_t
test_suite_define(void) {
	return test_quaternion_suite;
}

#endif
