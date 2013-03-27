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


int main_initialize( void )
{
	int ret = 0;

	application_t application = {0};
	application.name = "maskgen";
	application.short_name = "maskgen";
	application.config_dir = "maskgen";
	application.flags = APPLICATION_UTILITY;

	log_enable_prefix( false );

	if( ( ret = foundation_initialize( memory_system_malloc(), application ) ) < 0 )
		return ret;

	config_set_int( HASH_FOUNDATION, HASH_TEMPORARY_MEMORY, 32 * 1024 );

	return 0;
}


int main_run( void* main_arg )
{
	const char element[4][2] = { "X", "Y", "Z", "W" };

	log_infof(
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
	
	 "#define VECTOR_MASK( x, y, z, w ) (((w) << 6) | ((z) << 4) | ((y) << 2) | ((x)))\n\n"

	 "/*! \\brief Vector shuffle masks\n"
	 "    Vector shuffle masks where the operation performed by\n"
	 "    v1 = vector_shuffle( v0, VECTOR_MASK_abcd )\n"
	 "    will be equal to\n"
	 "    v1.x = v0[a]\n"
	 "    v1.y = v0[b]\n"
	 "    v1.z = v0[c]\n"
	 "    v1.w = v0[d] */\n"
	 "typedef enum _vector_mask\n"
	 "{" );
		
	for( int e0 = 0; e0 < 4; ++e0 )
		for( int e1 = 0; e1 < 4; ++e1 )
			for( int e2 = 0; e2 < 4; ++e2 )
				for( int e3 = 0; e3 < 4; ++e3 )
					log_infof( "	VECTOR_MASK_%s%s%s%s = VECTOR_MASK( %d, %d, %d, %d ),", element[e0], element[e1], element[e2], element[e3], e0, e1, e2, e3 );

	log_infof( "} vector_mask_t;\n\n" );

	return 0;
}


void main_shutdown( void )
{
	foundation_shutdown();
}
