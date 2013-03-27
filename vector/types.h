/* types.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

#pragma once

/*! \file types.h
    Vector math types */

#include <foundation/platform.h>
#include <foundation/math.h>

#if FOUNDATION_ARCH_SSE4 || FOUNDATION_ARCH_SSE3 || FOUNDATION_ARCH_SSE2

#include <emmintrin.h>

#if FOUNDATION_COMPILER_GCC || FOUNDATION_COMPILER_CLANG
typedef __m128 vector_t ALIGN(16);
#else
typedef ALIGN(16) __m128 vector_t;
#endif

#else

typedef ALIGN(16) struct _vector
{
	float32_t          x;
	float32_t          y;
	float32_t          z;
	float32_t          w;
} vector_t;

#endif

//! Row-major matrix
typedef union _matrix
{
	ALIGN(16) struct _matrix_component
	{
		float32_t m00, m01, m02, m03; //Row
		float32_t m10, m11, m12, m13;
		float32_t m20, m21, m22, m23;
		float32_t m30, m31, m32, m33;
	} comp;
	ALIGN(16) float32_t arr[16];
	ALIGN(16) float32_t frow[4][4]; // frow[Column][Row]
	vector_t            row[4];
} matrix_t;

typedef vector_t quaternion_t;

typedef struct _dual_quaternion
{
	quaternion_t   q[2];
} dual_quaternion_t;

typedef struct _transform
{
	quaternion_t   rotation;
	vector_t       translation;  //Scale in w component
} transform_t;

#define VECTOR_MATH_GETEULERORDER( i, p, r, f ) ( ( ( ( ( ( i << 1 ) + p ) << 1 ) + r ) << 1 ) + f )

#define VECTOR_MATH_EULER_STATICFRAME    0
#define VECTOR_MATH_EULER_ROTATEFRAME    1
#define VECTOR_MATH_EULER_NOREPEAT       0
#define VECTOR_MATH_EULER_REPEAT         1
#define VECTOR_MATH_EULER_EVEN           0
#define VECTOR_MATH_EULER_ODD            1

/*! \brief Order identifiers

    Order identifiers describing the order and method of which the rotations
    are applied. The three upper-case letters denote the axes on which the rotations
    are applied, and the lower-case letter denote if it is a static frame or rotating
    frame of reference (if each consecutive rotation are applied in the unrotated
    coordinate system - 's', or in the rotated coordinate system - 'r')

    The default order is XYZs */
typedef enum _euler_angles_order
{
	EULER_DEFAULTORDER         = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_STATICFRAME ),

	EULER_XYZs                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_STATICFRAME ),
	EULER_XYXs                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_STATICFRAME ),
	EULER_XZYs                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_STATICFRAME ),
	EULER_XZXs                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_STATICFRAME ),
	EULER_YZXs                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_STATICFRAME ),
	EULER_YZYs                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_STATICFRAME ),
	EULER_YXZs                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_STATICFRAME ),
	EULER_YXYs                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_STATICFRAME ),
	EULER_ZXYs                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_STATICFRAME ),
	EULER_ZXZs                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_STATICFRAME ),
	EULER_ZYXs                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_STATICFRAME ),
	EULER_ZYZs                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_STATICFRAME ),

	EULER_ZYXr                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_XYXr                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_YZXr                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_XZXr                 = VECTOR_MATH_GETEULERORDER( 0, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_XZYr                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_YZYr                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_ZXYr                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_YXYr                 = VECTOR_MATH_GETEULERORDER( 1, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_YXZr                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_ZXZr                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_EVEN, VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_XYZr                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_NOREPEAT, VECTOR_MATH_EULER_ROTATEFRAME ),
	EULER_ZYZr                 = VECTOR_MATH_GETEULERORDER( 2, VECTOR_MATH_EULER_ODD,  VECTOR_MATH_EULER_REPEAT,   VECTOR_MATH_EULER_ROTATEFRAME )
} euler_angles_order_t;

typedef struct _euler_angles
{
	vector_t       angles;
	uint32_t       order;
} euler_angles_t;

typedef ALIGN(16) float32_t float32_aligned128_t;

FOUNDATION_COMPILETIME_ASSERT( sizeof( vector_t ) == sizeof( float32_t )*4, _assert_vector_size );
FOUNDATION_COMPILETIME_ASSERT( sizeof( matrix_t ) == sizeof( float32_t )*16, _assert_matrix_size );
FOUNDATION_COMPILETIME_ASSERT( sizeof( transform_t ) == sizeof( float32_t )*8, _assert_transform_size );

