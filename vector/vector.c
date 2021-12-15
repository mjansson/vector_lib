/* vector.c  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
 *
 * This library provides a cross-platform vector math library in C11 providing basic support data types and
 * functions to write applications and games in a platform-independent fashion. The latest source code is
 * always available at
 *
 * https://github.com/mjansson/vector_lib
 *
 * This library is built on top of the foundation library available at
 *
 * https://github.com/mjansson/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.
 *
 */

#include <vector/vector.h>

static bool vector_initialized;

int
vector_module_initialize(const vector_config_t config) {
	FOUNDATION_UNUSED(config);
	if (vector_initialized)
		return 0;

	vector_initialized = true;

	return 0;
}

void
vector_module_finalize(void) {
	vector_initialized = false;
}

bool
vector_module_is_initialized(void) {
	return vector_initialized;
}

string_t
string_from_vector(char* buffer, size_t capacity, const vector_t v) {
	return string_format(buffer, capacity,
	                     STRING_CONST("(%.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ", %.6" PRIreal ")"),
	                     (double)vector_x(v), (double)vector_y(v), (double)vector_z(v), (double)vector_w(v));
}

string_const_t
string_from_vector_static(const vector_t v) {
	string_t buffer = string_thread_buffer();
	return string_to_const(string_from_vector(buffer.str, buffer.length, v));
}
