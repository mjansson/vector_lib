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


vector_t vector( real x, real y, real z, real w )
{
	vector_t rv = { x, y, z, w };
	return rv;
}


vector_t vector_aligned( const float32_aligned128_t* RESTRICT v )
{
	return *(const vector_t*)v;
}


vector_t vector_unaligned( const float32_t* RESTRICT v )
{
	vector_t rv = { *v, *(v+1), *(v+2), *(v+3) };
	return rv;
}


vector_t vector_uniform( real v )
{
	vector_t rv = { v, v, v, v };
	return rv;
}


vector_t vector_zero( void )
{
	vector_t rv = { 0 };
	return rv;
}


vector_t vector_one( void )
{
	vector_t rv = { 1, 1, 1, 1 };
	return rv;
}


vector_t vector_half( void )
{
	vector_t rv = { 0.5, 0.5, 0.5, 0.5 };
	return rv;
}


vector_t vector_two( void )
{
	vector_t rv = { 2, 2, 2, 2 };
	return rv;
}


vector_t vector_origo( void )
{
	vector_t rv = { 0, 0, 0, 1 };
	return rv;
}


vector_t vector_xaxis( void )
{
	vector_t rv = { 1, 0, 0, 1 };
	return rv;
}


vector_t vector_yaxis( void )
{
	vector_t rv = { 0, 1, 0, 1 };
	return rv;
}


vector_t vector_zaxis( void )
{
	vector_t rv = { 0, 0, 1, 1 };
	return rv;
}


vector_t vector_normalize( const vector_t v )
{
	float32_t inv_length = math_rsqrt( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w );
	vector_t rv = v;
	rv.x *= inv_length;
	rv.y *= inv_length;
	rv.z *= inv_length;
	rv.w *= inv_length;
	return rv;
}


vector_t vector_normalize3( const vector_t v )
{
	float32_t inv_length = math_rsqrt( v.x*v.x + v.y*v.y + v.z*v.z );
	vector_t rv = v;
	rv.x *= inv_length;
	rv.y *= inv_length;
	rv.z *= inv_length;
	return rv;
}


vector_t vector_dot( const vector_t v0, const vector_t v1 )
{
	return vector_uniform( v0.x*v1.x + v0.y*v1.y + v0.z*v1.z + v0.w*v1.w );
}


vector_t vector_dot3( const vector_t v0, const vector_t v1 )
{
	return vector_uniform( v0.x*v1.x + v0.y*v1.y + v0.z*v1.z );
}


vector_t vector_cross3( const vector_t v0, const vector_t v1 )
{
	const vector_t v = { v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x, 1 };
	return v;
}


vector_t vector_mul( const vector_t v0, const vector_t v1 )
{
	const vector_t v = { v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w };
	return v;
}


vector_t vector_div( const vector_t v0, const vector_t v1 )
{
	const vector_t v = { v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w };
	return v;
}


vector_t vector_add( const vector_t v0, const vector_t v1 )
{
	const vector_t v = { v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w };
	return v;
}


vector_t vector_sub( const vector_t v0, const vector_t v1 )
{
	const vector_t v = { v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w };
	return v;
}


vector_t vector_neg( const vector_t v )
{
	const vector_t negv = { -v.x, -v.y, -v.z, -v.w };
	return negv;
}


vector_t vector_shuffle( const vector_t v, unsigned int mask )
{
	const float32_t* element = &v.x;
	const vector_t ret = {
		element[ ( mask >> 0 ) & 0x3 ],
		element[ ( mask >> 2 ) & 0x3 ],
		element[ ( mask >> 4 ) & 0x3 ],
		element[ ( mask >> 6 ) & 0x3 ]
	};
	return ret;
}


vector_t vector_scale( const vector_t v, const real s )
{
	vector_t rv = { v.x * s, v.y *s, v.z *s, v.w *s };
	return rv;
}


vector_t vector_lerp( const vector_t from, const vector_t to, const real factor )
{
	real factor_inv = REAL_C( 1.0 ) - factor;
	vector_t v = {
		from.x * factor_inv + to.x * factor,
		from.y * factor_inv + to.y * factor,
		from.z * factor_inv + to.z * factor,
		from.w * factor_inv + to.w * factor };
	return v;
}


vector_t vector_reflect( const vector_t v, const vector_t at )
{
	vector_t normal = vector_normalize( at );
	vector_t double_proj = vector_scale( normal, ( normal.x*v.x + normal.y*v.y + normal.z*v.z ) * 2.0f );
	return vector_sub( double_proj, v );
}


vector_t vector_length_fast( const vector_t v )
{
	return vector_length( v );
}


vector_t vector_length( const vector_t v )
{
	return vector_uniform( math_sqrt( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w ) );
}


vector_t vector_length_sqr( const vector_t v )
{
	return vector_uniform( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w );
}


vector_t vector_length3_fast( const vector_t v )
{
	return vector_length3( v );
}


vector_t vector_length3( const vector_t v )
{
	return vector_uniform( math_sqrt( v.x*v.x + v.y*v.y + v.z*v.z ) );
}


vector_t vector_length3_sqr( const vector_t v )
{
	return vector_uniform( v.x*v.x + v.y*v.y + v.z*v.z );
}


vector_t vector_min( const vector_t v0, const vector_t v1 )
{
	const vector_t v = { ( v0.x < v1.x ) ? v0.x : v1.x, ( v0.y < v1.y ) ? v0.y : v1.y, ( v0.z < v1.z ) ? v0.z : v1.z, ( v0.w < v1.w ) ? v0.w : v1.w };
	return v;
}


vector_t vector_max( const vector_t v0, const vector_t v1 )
{
	const vector_t v = { ( v0.x > v1.x ) ? v0.x : v1.x, ( v0.y > v1.y ) ? v0.y : v1.y, ( v0.z > v1.z ) ? v0.z : v1.z, ( v0.w > v1.w ) ? v0.w : v1.w };
	return v;
}


real vector_x( const vector_t v )
{
	return v.x;
}

real vector_y( const vector_t v )
{
	return v.y;
}

real vector_z( const vector_t v )
{
	return v.z;
}

real vector_w( const vector_t v )
{
	return v.w;
}

real vector_component( const vector_t v, int c )
{
	FOUNDATION_ASSERT( ( c >= 0 ) && ( c < 4 ) );
	return *((const float32_t*)&v + c);
}


bool vector_equal( const vector_t v0, const vector_t v1 )
{
	return math_realeq( v0.x, v1.x, 100 ) && math_realeq( v0.y, v1.y, 100 ) && math_realeq( v0.z, v1.z, 100 ) && math_realeq( v0.w, v1.w, 100 );
}
