/* vector_sse4.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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


#include <smmintrin.h>


//Index for shuffle must be constant integer - hide function with a define
vector_t vector_shuffle( const vector_t v, unsigned int mask )
{
	FOUNDATION_ASSERT_FAIL( "Unreachable code" );
	//return _mm_shuffle_ps( v, v, mask );
	return v;
}
#define vector_shuffle( v, mask ) _mm_shuffle_ps( v, v, mask )


vector_t vector( real x, real y, real z, real w )
{
	return _mm_setr_ps( x, y, z, w );
}


vector_t vector_aligned( const float32_aligned128_t* v )
{
	FOUNDATION_ASSERT_ALIGNMENT( v, 16 );
	return _mm_load_ps( v );
}


vector_t vector_unaligned( const float32_t* v )
{
	return _mm_loadu_ps( v );
}


vector_t vector_uniform( real v )
{
	return _mm_set_ps1( v );
}


vector_t vector_zero( void )
{
	return _mm_setzero_ps();
}


vector_t vector_one( void )
{
	return _mm_set1_ps( 1.0f );
}


vector_t vector_half( void )
{
	return _mm_set1_ps( 0.5f );
}


vector_t vector_two( void )
{
	return _mm_set1_ps( 2.0f );
}


vector_t vector_origo( void )
{
	static const float32_t ALIGN(16) origo[] = { 0, 0, 0, 1 };
	return vector_aligned( origo );
}


vector_t vector_xaxis( void )
{
	const vector_t v = _mm_set_ss( 1.0f );
	return _mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( v ), VECTOR_MASK_XYYX ) );
}


vector_t vector_yaxis( void )
{
	const vector_t v = _mm_set_ss( 1.0f );
	return _mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( v ), VECTOR_MASK_YXYX ) );
}


vector_t vector_zaxis( void )
{
	const vector_t v = _mm_set_ss( 1.0f );
	return _mm_castsi128_ps( _mm_shuffle_epi32( _mm_castps_si128( v ), VECTOR_MASK_YYXX ) );
}


vector_t vector_normalize( const vector_t v )
{
	return vector_mul( v, _mm_rsqrt_ps( _mm_dp_ps( v, v, 0xFF ) ) );
}


vector_t vector_normalize3( const vector_t v )
{
	return vector_mul( v, _mm_rsqrt_ps( _mm_dp_ps( v, v, 0x77 ) ) );
}


vector_t vector_dot( const vector_t v0, const vector_t v1 )
{
	return _mm_dp_ps( v0, v1, 0xFF );
}


vector_t vector_dot3( const vector_t v0, const vector_t v1 )
{
	return _mm_dp_ps( v0, v1, 0x77 );
}


vector_t vector_cross3( const vector_t v0, const vector_t v1 )
{
	vector_t v0yzx = vector_shuffle( v0, VECTOR_MASK_YZXW );
	vector_t v1yzx = vector_shuffle( v1, VECTOR_MASK_YZXW );
	vector_t v0zxy = vector_shuffle( v0, VECTOR_MASK_ZXYW );
	vector_t v1zxy = vector_shuffle( v1, VECTOR_MASK_ZXYW );
#if FOUNDATION_ARCH_SSE4_FMA3
	vector_t interm = vector_mul( v0yzx, v1zxy );
	return _mm_fnmadd_ps( v0zxy, v1yzx, interm );
#else
	return vector_sub( vector_mul( v0yzx, v1zxy ), vector_mul( v0zxy, v1yzx ) );
#endif
}


vector_t vector_mul( const vector_t v0, const vector_t v1 )
{
	return _mm_mul_ps( v0, v1 );
}


vector_t vector_div( const vector_t v0, const vector_t v1 )
{
	return _mm_div_ps( v0, v1 );
}


vector_t vector_add( const vector_t v0, const vector_t v1 )
{
	return _mm_add_ps( v0, v1 );
}


vector_t vector_sub( const vector_t v0, const vector_t v1 )
{
	return _mm_sub_ps( v0, v1 );
}


vector_t vector_neg( const vector_t v )
{
	return _mm_sub_ps( _mm_setzero_ps(), v );
}


vector_t vector_muladd( const vector_t v0, const vector_t v1, const vector_t v2 )
{
#if FOUNDATION_ARCH_SSE4_FMA3
	return _mm_fmadd_ps( v0, v1, v2);
#else
	return vector_add( vector_mul( v0, v1 ), v2 );
#endif
}


vector_t vector_scale( const vector_t v, const real s )
{
	return _mm_mul_ps( v, _mm_set_ps1( s ) );
}


vector_t vector_lerp( const vector_t from, const vector_t to, const real factor )
{
	vector_t s = _mm_set1_ps( factor );
#if FOUNDATION_ARCH_SSE4_FMA3
	return _mm_fmadd_ps( to, s, _mm_fnmadd_ps( from, s, from ) );
#else
	return _mm_add_ps( _mm_mul_ps( s, to ), _mm_sub_ps( from, _mm_mul_ps( s, from ) ) );
#endif
}


vector_t vector_reflect( const vector_t v, const vector_t at )
{
	const vector_t ALIGN(16) two = _mm_set_ps1( 2.0f );
	vector_t normal = vector_normalize( at );
	vector_t double_proj = vector_mul( normal, vector_mul( _mm_dp_ps( normal, v, 0x77 ), two ) );
	return vector_sub( double_proj, v );
}


vector_t vector_length( const vector_t v )
{
	return _mm_sqrt_ss( _mm_dp_ps( v, v, 0xFF ) );
}


vector_t vector_length_fast( const vector_t v )
{
	return _mm_sqrt_ss( _mm_dp_ps( v, v, 0xFF ) );
}


vector_t vector_length_sqr( const vector_t v )
{
	return vector_dot( v, v );
}


vector_t vector_length3( const vector_t v )
{
	return _mm_sqrt_ss( _mm_dp_ps( v, v, 0x77 ) );
}


vector_t vector_length3_fast( const vector_t v )
{
	return _mm_sqrt_ss( _mm_dp_ps( v, v, 0x77 ) );
}


vector_t vector_length3_sqr( const vector_t v )
{
	return vector_dot3( v, v );
}


vector_t vector_min( const vector_t v0, const vector_t v1 )
{
	return _mm_min_ps( v0, v1 );
}


vector_t vector_max( const vector_t v0, const vector_t v1 )
{
	return _mm_max_ps( v0, v1 );
}


real vector_x( const vector_t v )
{
	return *(const float32_t*)&v;
}

real vector_y( const vector_t v )
{
	return *((const float32_t*)&v + 1);
}

real vector_z( const vector_t v )
{
	return *((const float32_t*)&v + 2);
}

real vector_w( const vector_t v )
{
	return *((const float32_t*)&v + 3);
}

real vector_component( const vector_t v, int c )
{
	FOUNDATION_ASSERT( ( c >= 0 ) && ( c < 4 ) );
	return *((const float32_t*)&v + c);
}


bool vector_equal( const vector_t v0, const vector_t v1 )
{
	return math_realeq( *(const float32_t*)&v0, *(const float32_t*)&v1, 100 ) && math_realeq( *((const float32_t*)&v0 + 1), *((const float32_t*)&v1 + 1), 100 ) && math_realeq( *((const float32_t*)&v0 + 2), *((const float32_t*)&v1 + 2), 100 ) && math_realeq( *((const float32_t*)&v0 + 3), *((const float32_t*)&v1 + 3), 100 );
}
