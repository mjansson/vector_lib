/* vector.h  -  Vector tests  -  Public Domain  -  2013 Mattias Jansson
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

#pragma once

#include <foundation/foundation.h>
#include <test/test.h>
#include <vector/vector.h>

VECTOR_API real
vector_test_difference(const vector_t v0, const vector_t v1);

VECTOR_API real
vector_test_difference(const vector_t v0, const vector_t v1) {
	return (math_abs(vector_x(v0) - vector_x(v1)) + math_abs(vector_y(v0) - vector_y(v1)) +
	        math_abs(vector_z(v0) - vector_z(v1)) + math_abs(vector_w(v0) - vector_w(v1)));
}

#define EXPECT_VECTOREQ(var, expect)                                                      \
	do {                                                                                  \
		if (!vector_equal((var), (expect))) {                                             \
			char buffer[2][64];                                                           \
			string_t vstr[2];                                                             \
			vstr[0] = string_from_vector(buffer[0], sizeof(buffer[0]), (var));            \
			vstr[1] = string_from_vector(buffer[1], sizeof(buffer[1]), (expect));         \
			log_warnf(HASH_TEST, WARNING_SUSPICIOUS,                                      \
			          STRING_CONST("Test failed, %s != %s vector (at %s:%u): %.*s %.*s"), \
			          FOUNDATION_PREPROCESSOR_TOSTRING(var),                              \
			          FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__,       \
			          STRING_FORMAT(vstr[0]), STRING_FORMAT(vstr[1]));                    \
			return FAILED_TEST;                                                           \
		}                                                                                 \
	} while (0)

#define EXPECT_VECTORALMOSTEQ(var, expect)                                                 \
	do {                                                                                   \
		real diff = vector_test_difference((var), (expect));                               \
		if (diff > 0.0075f) {                                                              \
			char buffer[2][64];                                                            \
			string_t vstr[2];                                                              \
			vstr[0] = string_from_vector(buffer[0], sizeof(buffer[0]), (var));             \
			vstr[1] = string_from_vector(buffer[1], sizeof(buffer[1]), (expect));          \
			log_warnf(HASH_TEST, WARNING_SUSPICIOUS,                                       \
			          STRING_CONST("Test failed, %s !~= %s vector (at %s:%u): %.*s %.*s"), \
			          FOUNDATION_PREPROCESSOR_TOSTRING(var),                               \
			          FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__,        \
			          STRING_FORMAT(vstr[0]), STRING_FORMAT(vstr[1]));                     \
			return FAILED_TEST;                                                            \
		}                                                                                  \
	} while (0)
