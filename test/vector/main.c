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


real vector_test_difference( const vector_t v0, const vector_t v1 )
{
	return ( math_abs( vector_x( v0 ) - vector_x( v1 ) ) +
			 math_abs( vector_y( v0 ) - vector_y( v1 ) ) +
			 math_abs( vector_z( v0 ) - vector_z( v1 ) ) +
			 math_abs( vector_w( v0 ) - vector_w( v1 ) ) );
}


#define EXPECT_VECTOREQ( var, expect ) do { if( !vector_equal( (var), (expect) ) ) { log_warnf( WARNING_SUSPICIOUS, "Test failed, %s != %s vector (at %s:%u): (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ") (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ")", FOUNDATION_PREPROCESSOR_TOSTRING(var), FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__, (real)vector_x((var)), (real)vector_y((var)), (real)vector_z((var)), (real)vector_w((var)), (real)vector_x((expect)), (real)vector_y((expect)), (real)vector_z((expect)), (real)vector_w((expect)) ); return FAILED_TEST; } } while(0)
#define EXPECT_VECTORALMOSTEQ( var, expect ) do { real diff = vector_test_difference( (var), (expect) ); if( diff > 0.005f ) { log_warnf( WARNING_SUSPICIOUS, "Test failed, %s != %s vector (at %s:%u): (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ") (%.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ", %.6" STRING_FORMAT_REAL ") diff %.6" STRING_FORMAT_REAL, FOUNDATION_PREPROCESSOR_TOSTRING(var), FOUNDATION_PREPROCESSOR_TOSTRING(expect), __FILE__, __LINE__, (real)vector_x((var)), (real)vector_y((var)), (real)vector_z((var)), (real)vector_w((var)), (real)vector_x((expect)), (real)vector_y((expect)), (real)vector_z((expect)), (real)vector_w((expect)), diff ); return FAILED_TEST; } } while(0)


application_t test_application( void )
{
	application_t app = {0};
	app.name = "Vector tests";
	app.short_name = "test_vector";
	app.config_dir = "test_vector";
	app.flags = APPLICATION_UTILITY;
	return app;
}


DECLARE_TEST( vector, construct )
{
	vector_t vec;
	float32_t unaligned[4] = { 3, 2, 1, 0 };
	ALIGN(16) float32_t aligned[4] = { 0, 1, 2, 3 };
	
	vec = vector( REAL_C(0.0), REAL_C(1.0), REAL_C(2.0), REAL_C(3.0) );	
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(3.0) );

	vec = vector_unaligned( unaligned );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.0) );

	vec = vector_aligned( aligned );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(3.0) );

	vec = vector_uniform( REAL_C(4.0) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(4.0) );

	vec = vector_zero();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.0) );

	vec = vector_one();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );

	vec = vector_half();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.5) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.5) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.5) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.5) );

	vec = vector_two();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(2.0) );

	vec = vector_origo();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );

	vec = vector_xaxis();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );

	vec = vector_yaxis();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );

	vec = vector_zaxis();
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );
	
	return 0;
}


DECLARE_TEST( vector, normalize )
{
	vector_t vec;
	real ref;

	vec = vector_normalize( vector( 1, 0, 0, 0 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 1, 0, 0, 0 ) );
	
	vec = vector_normalize( vector( 0, 1, 0, 0 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 0, 1, 0, 0 ) );
	
	vec = vector_normalize( vector( 0, 0, 1, 0 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 0, 0, 1, 0 ) );
	
	vec = vector_normalize( vector( 0, 0, 0, 1 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 0, 0, 0, 1 ) );

	ref = math_sqrt( REAL_C(1.0) / REAL_C(4.0) );
	vec = vector_normalize( vector( 1, 1, 1, 1 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( ref, ref, ref, ref ) );

	ref = math_sqrt( REAL_C(1.0) / REAL_C(4.0) );
	vec = vector_normalize( vector( -1, 1, -1, 1 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( -ref, ref, -ref, ref ) );

	ref = math_sqrt( REAL_C(158.0) );
	vec = vector_normalize( vector( 0, -3, 7, -10 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 0, -REAL_C(3.0) / ref, REAL_C(7.0) / ref, -REAL_C(10.0) / ref ) );
	
	vec = vector_normalize3( vector( 1, 0, 0, 0 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 1, 0, 0, 0 ) );
	
	vec = vector_normalize3( vector( 0, 1, 0, 0 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 0, 1, 0, 0 ) );
	
	vec = vector_normalize3( vector( 0, 0, 1, 0 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 0, 0, 1, 0 ) );

	ref = math_sqrt( REAL_C(1.0) / REAL_C(3.0) );
	vec = vector_normalize3( vector( 1, 1, 1, 1 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( ref, ref, ref, 1 ) );

	ref = math_sqrt( REAL_C(1.0) / REAL_C(3.0) );
	vec = vector_normalize3( vector( -1, 1, -1, 1 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( -ref, ref, -ref, 1 ) );

	ref = math_sqrt( REAL_C(58.0) );
	vec = vector_normalize3( vector( 0, -3, 7, -10 ) );
	EXPECT_VECTORALMOSTEQ( vec, vector( 0, -REAL_C(3.0) / ref, REAL_C(7.0) / ref, -REAL_C(10.0) ) );
	
	return 0;
}


DECLARE_TEST( vector, dot )
{
	vector_t vec;
	
	vec = vector_dot( vector_zero(), vector_one() );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.0) );
	
	vec = vector_dot( vector_one(), vector_zero() );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.0) );
	
	vec = vector_dot( vector_one(), vector_one() );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(4.0) );
	
	vec = vector_dot( vector( 1, 0, 0, 0 ), vector( 2, 0, 0, 0 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(2.0) );
	
	vec = vector_dot( vector( -1, 1, -1, 1 ), vector( 1, 1, -1, -1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.0) );
	
	vec = vector_dot( vector( -3, 4, -5, 6 ), vector( 0, 1, -1, -2 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(-3.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(-3.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(-3.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(-3.0) );
	
	vec = vector_dot3( vector_zero(), vector_one() );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.0) );
	
	vec = vector_dot3( vector_one(), vector_zero() );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(0.0) );
	
	vec = vector_dot3( vector_one(), vector_one() );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(3.0) );
	
	vec = vector_dot3( vector( -1, 1, -1, 1 ), vector( 1, 1, -1, -1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );
	
	vec = vector_dot3( vector( -3, 4, -5, 6 ), vector( 0, 1, -1, -2 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(9.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(9.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(9.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(9.0) );
	
	return 0;
}


DECLARE_TEST( vector, cross )
{
	vector_t vec;
	
	vec = vector_cross3( vector( 0, 0, 0, 1 ), vector( 1, 2, 3, 4 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );

	vec = vector_cross3( vector( 1, 0, 0, 0 ), vector( 1, 0, 0, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );

	vec = vector_cross3( vector( 1, 0, 0, 1 ), vector( 0, 1, 0, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );

	vec = vector_cross3( vector( 1, 0, 0, 0 ), vector( 0, 0, 1, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(-1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );

	vec = vector_cross3( vector( 0, 1, 0, 1 ), vector( 1, 0, 0, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(-1.0) );

	vec = vector_cross3( vector( 0, 1, 0, 0 ), vector( 0, 1, 0, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );

	vec = vector_cross3( vector( 0, 1, 0, 1 ), vector( 0, 0, 1, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );

	vec = vector_cross3( vector( 0, 0, 1, 0 ), vector( 1, 0, 0, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );

	vec = vector_cross3( vector( 0, 0, 1, 1 ), vector( 0, 1, 0, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(-1.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );

	vec = vector_cross3( vector( 0, 0, 1, 0 ), vector( 0, 0, 1, 1 ) );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(0.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(0.0) );
	
	return 0;
}


DECLARE_TEST( vector, ops )
{
	vector_t vec;

	vec = vector_mul( vector_one(), vector_zero() );
	EXPECT_VECTOREQ( vec, vector_zero() );

	vec = vector_mul( vector_zero(), vector_one() );
	EXPECT_VECTOREQ( vec, vector_zero() );

	vec = vector_mul( vector_one(), vector_one() );
	EXPECT_VECTOREQ( vec, vector_one() );

	vec = vector_mul( vector_two(), vector_zero() );
	EXPECT_VECTOREQ( vec, vector_zero() );

	vec = vector_mul( vector_two(), vector_half() );
	EXPECT_VECTOREQ( vec, vector_one() );

	vec = vector_mul( vector( 1, 2, 3, 4 ), vector( 5, 6, 7, 8 ) );
	EXPECT_VECTOREQ( vec, vector( 5, 12, 21, 32 ) );

	vec = vector_div( vector_zero(), vector_one() );
	EXPECT_VECTOREQ( vec, vector_zero() );

	vec = vector_div( vector_one(), vector_one() );
	EXPECT_VECTOREQ( vec, vector_one() );

	vec = vector_div( vector_one(), vector_half() );
	EXPECT_VECTOREQ( vec, vector_two() );

	vec = vector_div( vector( 1, 2, 3, 4 ), vector( 5, 6, 7, 8 ) );
	EXPECT_VECTOREQ( vec, vector( REAL_C(1.0) / REAL_C(5.0), REAL_C(2.0) / REAL_C(6.0), REAL_C(3.0) / REAL_C(7.0), REAL_C(4.0) / REAL_C(8.0) ) );

	vec = vector_add( vector_zero(), vector_zero() );
	EXPECT_VECTOREQ( vec, vector_zero() );
	
	vec = vector_add( vector_zero(), vector_one() );
	EXPECT_VECTOREQ( vec, vector_one() );

	vec = vector_add( vector_one(), vector_zero() );
	EXPECT_VECTOREQ( vec, vector_one() );

	vec = vector_add( vector_one(), vector_one() );
	EXPECT_VECTOREQ( vec, vector_two() );

	vec = vector_add( vector( 1, 2, 3, 4 ), vector( 5, 6, 7, 8 ) );
	EXPECT_VECTOREQ( vec, vector( 6, 8, 10, 12 ) );

	vec = vector_sub( vector_zero(), vector_zero() );
	EXPECT_VECTOREQ( vec, vector_zero() );
	
	vec = vector_sub( vector_zero(), vector_one() );
	EXPECT_VECTOREQ( vec, vector( -1, -1, -1, -1 ) );

	vec = vector_sub( vector_one(), vector_zero() );
	EXPECT_VECTOREQ( vec, vector_one() );

	vec = vector_sub( vector_one(), vector_one() );
	EXPECT_VECTOREQ( vec, vector_zero() );

	vec = vector_sub( vector( 1, -2, 3, -4 ), vector( -5, 6, -7, 8 ) );
	EXPECT_VECTOREQ( vec, vector( 6, -8, 10, -12 ) );

	vec = vector_neg( vector_zero() );
	EXPECT_VECTOREQ( vec, vector_zero() );
	
	vec = vector_neg( vector_one() );
	EXPECT_VECTOREQ( vec, vector( -1, -1, -1, -1 ) );

	vec = vector_neg( vector( 1, -2, 3, -4 ) );
	EXPECT_VECTOREQ( vec, vector( -1, 2, -3, 4 ) );
	
	return 0;
}


DECLARE_TEST( vector, shuffle )
{
	vector_t in = vector( 1, 2, 3, 4 );
	vector_t vec;

	vec = vector_shuffle( in, VECTOR_MASK_XXXX );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );
	
	vec = vector_shuffle( in, VECTOR_MASK_YYYY );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(2.0) );
	
	vec = vector_shuffle( in, VECTOR_MASK_ZZZZ );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(3.0) );
	
	vec = vector_shuffle( in, VECTOR_MASK_WWWW );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(4.0) );
	
	vec = vector_shuffle( in, VECTOR_MASK_XYZW );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(4.0) );
	
	vec = vector_shuffle( in, VECTOR_MASK_WZYX );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );
	
	vec = vector_shuffle( in, VECTOR_MASK_YXWZ );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(3.0) );
	
	vec = vector_shuffle( in, VECTOR_MASK_ZWXY );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(2.0) );

	vec = vector_shuffle( in, VECTOR_MASK_ZZXX );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(1.0) );

	vec = vector_shuffle( in, VECTOR_MASK_YYZZ );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(3.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(3.0) );

	vec = vector_shuffle( in, VECTOR_MASK_WXXW );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(1.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(4.0) );

	vec = vector_shuffle( in, VECTOR_MASK_WYYZ );
	EXPECT_REALEQ( vector_x( vec ), REAL_C(4.0) );
	EXPECT_REALEQ( vector_y( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_z( vec ), REAL_C(2.0) );
	EXPECT_REALEQ( vector_w( vec ), REAL_C(3.0) );
	
	return 0;
}


DECLARE_TEST( vector, util )
{

	return 0;
}


DECLARE_TEST( vector, length )
{

	return 0;
}


DECLARE_TEST( vector, minmax )
{

	return 0;
}


DECLARE_TEST( vector, component )
{

	return 0;
}


DECLARE_TEST( vector, equal )
{

	return 0;
}


void test_declare( void )
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

	ADD_TEST( vector, construct );
	ADD_TEST( vector, normalize );
	ADD_TEST( vector, dot );
	ADD_TEST( vector, cross );
	ADD_TEST( vector, ops );
	ADD_TEST( vector, shuffle );
	ADD_TEST( vector, util );
	ADD_TEST( vector, length );
	ADD_TEST( vector, minmax );
	ADD_TEST( vector, component );
	ADD_TEST( vector, equal );
}

