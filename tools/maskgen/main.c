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

#include <foundation/foundation.h>
#include <vector/vector.h>

int main_initialize(void) {
	int ret = 0;

	application_t application = {0};
	memset(&application, 0, sizeof(application));
	application.name = string_const(STRING_CONST("Vector mask generator"));
	application.short_name = string_const(STRING_CONST("maskgen"));
	application.company = string_const(STRING_CONST("Rampant Pixels"));
	application.version = vector_module_version();
	application.flags = APPLICATION_UTILITY;

	log_enable_prefix(false);

	foundation_config_t config;
	memset(&config, 0, sizeof(config));

	if ((ret = foundation_initialize(memory_system_malloc(), application, config)) < 0)
		return ret;

	return 0;
}

int main_run(void* main_arg) {
	const char element[4][2] = { "X", "Y", "Z", "W" };
	FOUNDATION_UNUSED(main_arg);

	log_set_suppress(HASH_TOOL, ERRORLEVEL_DEBUG);

	log_info(HASH_TOOL, STRING_CONST(
	             "/* mask.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels\n"
	             " *\n"
	             " * This library provides a cross-platform vector math library in C11 providing basic support data types and\n"
	             " * functions to write applications and games in a platform-independent fashion. The latest source code is\n"
	             " * always available at\n"
	             " *\n"
	             " * https://github.com/rampantpixels/vector_lib\n"
	             " *\n"
	             " * This library is built on top of the foundation library available at\n"
	             " *\n"
	             " * https://github.com/rampantpixels/foundation_lib\n"
	             " *\n"
	             " * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.\n"
	             " *\n"
	             "*/\n\n"

	             "#pragma once\n\n"

	             "/*! \\file math/mask.h\n"
	             "    Vector mask definitions */\n\n"

	             "#include <vector/types.h>\n\n"

	             "#define VECTOR_MASK(x, y, z, w) (((w) << 6) | ((z) << 4) | ((y) << 2) | ((x)))\n\n"

	             "/* Vector shuffle masks where the operation performed by\n"
	             "   v1 = vector_shuffle(v0, VECTOR_MASK_abcd)\n"
	             "   will be equal to\n"
	             "   v1.x = v0[a]\n"
	             "   v1.y = v0[b]\n"
	             "   v1.z = v0[c]\n"
	             "   v1.w = v0[d] */\n"));

	for (int e0 = 0; e0 < 4; ++e0)
		for (int e1 = 0; e1 < 4; ++e1)
			for (int e2 = 0; e2 < 4; ++e2)
				for (int e3 = 0; e3 < 4; ++e3)
					log_infof(HASH_TOOL, STRING_CONST("#define VECTOR_MASK_%s%s%s%s VECTOR_MASK(%d, %d, %d, %d)"),
						element[e0], element[e1], element[e2], element[e3], e0, e1, e2, e3);

	return 0;
}

void main_finalize(void) {
	foundation_finalize();
}
