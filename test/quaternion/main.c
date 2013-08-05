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
#undef  FOUNDATION_ARCH_SSE2
#define FOUNDATION_ARCH_SSE2 0
//#undef  FOUNDATION_ARCH_NEON
//#define FOUNDATION_ARCH_NEON 0

#include <vector/quaternion.h>


real vector_test_difference( const vector_t v0, const vector_t v1 )
{
	return ( math_abs( vector_x( v0 ) - vector_x( v1 ) ) +
			 math_abs( vector_y( v0 ) - vector_y( v1 ) ) +
			 math_abs( vector_z( v0 ) - vector_z( v1 ) ) +
			 math_abs( vector_w( v0 ) - vector_w( v1 ) ) );
}


#define EXPECT_VECTOREQ( var, expect ) do { if( !vector_equal( (var), (expect) ) ) { log_warnf( WARNING_SUSPICIOUS, "Test failed, %s != %s vector (at %s:%u): (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ") (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ")", FOUNDATION_PREPROCESSOR_TOSTRING(var), FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__, (real)vector_x((var)), (real)vector_y((var)), (real)vector_z((var)), (real)vector_w((var)), (real)vector_x((expect)), (real)vector_y((expect)), (real)vector_z((expect)), (real)vector_w((expect)) ); return FAILED_TEST; } } while(0)
#define EXPECT_VECTORALMOSTEQ( var, expect ) do { real diff = vector_test_difference( (var), (expect) ); if( diff > 0.0075f ) { log_warnf( WARNING_SUSPICIOUS, "Test failed, %s != %s vector (at %s:%u): (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ") (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ") diff %.6" STRING_FORMAT_REAL, FOUNDATION_PREPROCESSOR_TOSTRING(var), FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__, (real)vector_x((var)), (real)vector_y((var)), (real)vector_z((var)), (real)vector_w((var)), (real)vector_x((expect)), (real)vector_y((expect)), (real)vector_z((expect)), (real)vector_w((expect)), diff ); return FAILED_TEST; } } while(0)


application_t test_quaternion_application( void )
{
	application_t app = {0};
	app.name = "Quaternion tests";
	app.short_name = "test_quaternion";
	app.config_dir = "test_quaternion";
	app.flags = APPLICATION_UTILITY;
	return app;
}


int test_quaternion_initialize( void )
{
	return 0;
}


void test_quaternion_shutdown( void )
{
}


DECLARE_TEST( quaternion, construct )
{
	quaternion_t q;

	q = quaternion_zero();
	EXPECT_VECTOREQ( q, vector_zero() );

	q = quaternion_identity();
	EXPECT_VECTOREQ( q, vector( 0, 0, 0, 1 ) );

	float32_t unaligned[] = { 1, -2, 3, -4 };

	q = quaternion_unaligned( unaligned );
	EXPECT_VECTOREQ( q, vector( 1, -2, 3, -4 ) );

	ALIGN(16) float32_t aligned[] = { 1, -2, 3, -4 };

	q = quaternion_aligned( aligned );
	EXPECT_VECTOREQ( q, vector( 1, -2, 3, -4 ) );
	
	return 0;
}


void test_quaternion_declare( void )
{
#if FOUNDATION_ARCH_SSE4
	log_infof( "Using SSE4 implementation" );
#elif FOUNDATION_ARCH_SSE3
	log_infof( "Using SSE3 implementation" );
#elif FOUNDATION_ARCH_SSE2
	log_infof( "Using SSE2 implementation" );
#elif FOUNDATION_ARCH_NEON
	log_infof( "Using NEON implementation" );
#else
	log_infof( "Using fallback implementation" );
#endif

	ADD_TEST( quaternion, construct );
}


test_suite_t test_quaternion_suite = {
	test_quaternion_application,
	test_quaternion_declare,
	test_quaternion_initialize,
	test_quaternion_shutdown
};


#if FOUNDATION_PLATFORM_ANDROID

int test_quaternion_run( void )
{
	test_suite = test_quaternion_suite;
	return test_run_all();
}

#else

test_suite_t test_suite_define( void )
{
	return test_quaternion_suite;
}

#endif
