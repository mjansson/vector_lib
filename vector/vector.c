/* vector.c  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

#include <vector/vector.h>

static bool _vector_initialized = false;

int
vector_module_initialize(const vector_config_t config) {
	FOUNDATION_UNUSED(config);
	if (_vector_initialized)
		return 0;

	_vector_initialized = true;

	return 0;
}

void
vector_module_finalize(void) {
	_vector_initialized = false;
}

bool
vector_module_is_initialized(void) {
	return _vector_initialized;
}
