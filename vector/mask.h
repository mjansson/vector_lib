/* mask.h  -  Vector library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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

/*! \file math/mask.h
    Vector mask definitions */

#include <vector/types.h>

#define VECTOR_MASK(x, y, z, w) (((w) << 6) | ((z) << 4) | ((y) << 2) | ((x)))

/*! \brief Vector shuffle masks
    Vector shuffle masks where the operation performed by
    v1 = vector_shuffle(v0, VECTOR_MASK_abcd)
    will be equal to
    v1.x = v0[a]
    v1.y = v0[b]
    v1.z = v0[c]
    v1.w = v0[d] */
typedef enum vector_mask_t
{
	VECTOR_MASK_XXXX = VECTOR_MASK( 0, 0, 0, 0 ),
	VECTOR_MASK_XXXY = VECTOR_MASK( 0, 0, 0, 1 ),
	VECTOR_MASK_XXXZ = VECTOR_MASK( 0, 0, 0, 2 ),
	VECTOR_MASK_XXXW = VECTOR_MASK( 0, 0, 0, 3 ),
	VECTOR_MASK_XXYX = VECTOR_MASK( 0, 0, 1, 0 ),
	VECTOR_MASK_XXYY = VECTOR_MASK( 0, 0, 1, 1 ),
	VECTOR_MASK_XXYZ = VECTOR_MASK( 0, 0, 1, 2 ),
	VECTOR_MASK_XXYW = VECTOR_MASK( 0, 0, 1, 3 ),
	VECTOR_MASK_XXZX = VECTOR_MASK( 0, 0, 2, 0 ),
	VECTOR_MASK_XXZY = VECTOR_MASK( 0, 0, 2, 1 ),
	VECTOR_MASK_XXZZ = VECTOR_MASK( 0, 0, 2, 2 ),
	VECTOR_MASK_XXZW = VECTOR_MASK( 0, 0, 2, 3 ),
	VECTOR_MASK_XXWX = VECTOR_MASK( 0, 0, 3, 0 ),
	VECTOR_MASK_XXWY = VECTOR_MASK( 0, 0, 3, 1 ),
	VECTOR_MASK_XXWZ = VECTOR_MASK( 0, 0, 3, 2 ),
	VECTOR_MASK_XXWW = VECTOR_MASK( 0, 0, 3, 3 ),
	VECTOR_MASK_XYXX = VECTOR_MASK( 0, 1, 0, 0 ),
	VECTOR_MASK_XYXY = VECTOR_MASK( 0, 1, 0, 1 ),
	VECTOR_MASK_XYXZ = VECTOR_MASK( 0, 1, 0, 2 ),
	VECTOR_MASK_XYXW = VECTOR_MASK( 0, 1, 0, 3 ),
	VECTOR_MASK_XYYX = VECTOR_MASK( 0, 1, 1, 0 ),
	VECTOR_MASK_XYYY = VECTOR_MASK( 0, 1, 1, 1 ),
	VECTOR_MASK_XYYZ = VECTOR_MASK( 0, 1, 1, 2 ),
	VECTOR_MASK_XYYW = VECTOR_MASK( 0, 1, 1, 3 ),
	VECTOR_MASK_XYZX = VECTOR_MASK( 0, 1, 2, 0 ),
	VECTOR_MASK_XYZY = VECTOR_MASK( 0, 1, 2, 1 ),
	VECTOR_MASK_XYZZ = VECTOR_MASK( 0, 1, 2, 2 ),
	VECTOR_MASK_XYZW = VECTOR_MASK( 0, 1, 2, 3 ),
	VECTOR_MASK_XYWX = VECTOR_MASK( 0, 1, 3, 0 ),
	VECTOR_MASK_XYWY = VECTOR_MASK( 0, 1, 3, 1 ),
	VECTOR_MASK_XYWZ = VECTOR_MASK( 0, 1, 3, 2 ),
	VECTOR_MASK_XYWW = VECTOR_MASK( 0, 1, 3, 3 ),
	VECTOR_MASK_XZXX = VECTOR_MASK( 0, 2, 0, 0 ),
	VECTOR_MASK_XZXY = VECTOR_MASK( 0, 2, 0, 1 ),
	VECTOR_MASK_XZXZ = VECTOR_MASK( 0, 2, 0, 2 ),
	VECTOR_MASK_XZXW = VECTOR_MASK( 0, 2, 0, 3 ),
	VECTOR_MASK_XZYX = VECTOR_MASK( 0, 2, 1, 0 ),
	VECTOR_MASK_XZYY = VECTOR_MASK( 0, 2, 1, 1 ),
	VECTOR_MASK_XZYZ = VECTOR_MASK( 0, 2, 1, 2 ),
	VECTOR_MASK_XZYW = VECTOR_MASK( 0, 2, 1, 3 ),
	VECTOR_MASK_XZZX = VECTOR_MASK( 0, 2, 2, 0 ),
	VECTOR_MASK_XZZY = VECTOR_MASK( 0, 2, 2, 1 ),
	VECTOR_MASK_XZZZ = VECTOR_MASK( 0, 2, 2, 2 ),
	VECTOR_MASK_XZZW = VECTOR_MASK( 0, 2, 2, 3 ),
	VECTOR_MASK_XZWX = VECTOR_MASK( 0, 2, 3, 0 ),
	VECTOR_MASK_XZWY = VECTOR_MASK( 0, 2, 3, 1 ),
	VECTOR_MASK_XZWZ = VECTOR_MASK( 0, 2, 3, 2 ),
	VECTOR_MASK_XZWW = VECTOR_MASK( 0, 2, 3, 3 ),
	VECTOR_MASK_XWXX = VECTOR_MASK( 0, 3, 0, 0 ),
	VECTOR_MASK_XWXY = VECTOR_MASK( 0, 3, 0, 1 ),
	VECTOR_MASK_XWXZ = VECTOR_MASK( 0, 3, 0, 2 ),
	VECTOR_MASK_XWXW = VECTOR_MASK( 0, 3, 0, 3 ),
	VECTOR_MASK_XWYX = VECTOR_MASK( 0, 3, 1, 0 ),
	VECTOR_MASK_XWYY = VECTOR_MASK( 0, 3, 1, 1 ),
	VECTOR_MASK_XWYZ = VECTOR_MASK( 0, 3, 1, 2 ),
	VECTOR_MASK_XWYW = VECTOR_MASK( 0, 3, 1, 3 ),
	VECTOR_MASK_XWZX = VECTOR_MASK( 0, 3, 2, 0 ),
	VECTOR_MASK_XWZY = VECTOR_MASK( 0, 3, 2, 1 ),
	VECTOR_MASK_XWZZ = VECTOR_MASK( 0, 3, 2, 2 ),
	VECTOR_MASK_XWZW = VECTOR_MASK( 0, 3, 2, 3 ),
	VECTOR_MASK_XWWX = VECTOR_MASK( 0, 3, 3, 0 ),
	VECTOR_MASK_XWWY = VECTOR_MASK( 0, 3, 3, 1 ),
	VECTOR_MASK_XWWZ = VECTOR_MASK( 0, 3, 3, 2 ),
	VECTOR_MASK_XWWW = VECTOR_MASK( 0, 3, 3, 3 ),
	VECTOR_MASK_YXXX = VECTOR_MASK( 1, 0, 0, 0 ),
	VECTOR_MASK_YXXY = VECTOR_MASK( 1, 0, 0, 1 ),
	VECTOR_MASK_YXXZ = VECTOR_MASK( 1, 0, 0, 2 ),
	VECTOR_MASK_YXXW = VECTOR_MASK( 1, 0, 0, 3 ),
	VECTOR_MASK_YXYX = VECTOR_MASK( 1, 0, 1, 0 ),
	VECTOR_MASK_YXYY = VECTOR_MASK( 1, 0, 1, 1 ),
	VECTOR_MASK_YXYZ = VECTOR_MASK( 1, 0, 1, 2 ),
	VECTOR_MASK_YXYW = VECTOR_MASK( 1, 0, 1, 3 ),
	VECTOR_MASK_YXZX = VECTOR_MASK( 1, 0, 2, 0 ),
	VECTOR_MASK_YXZY = VECTOR_MASK( 1, 0, 2, 1 ),
	VECTOR_MASK_YXZZ = VECTOR_MASK( 1, 0, 2, 2 ),
	VECTOR_MASK_YXZW = VECTOR_MASK( 1, 0, 2, 3 ),
	VECTOR_MASK_YXWX = VECTOR_MASK( 1, 0, 3, 0 ),
	VECTOR_MASK_YXWY = VECTOR_MASK( 1, 0, 3, 1 ),
	VECTOR_MASK_YXWZ = VECTOR_MASK( 1, 0, 3, 2 ),
	VECTOR_MASK_YXWW = VECTOR_MASK( 1, 0, 3, 3 ),
	VECTOR_MASK_YYXX = VECTOR_MASK( 1, 1, 0, 0 ),
	VECTOR_MASK_YYXY = VECTOR_MASK( 1, 1, 0, 1 ),
	VECTOR_MASK_YYXZ = VECTOR_MASK( 1, 1, 0, 2 ),
	VECTOR_MASK_YYXW = VECTOR_MASK( 1, 1, 0, 3 ),
	VECTOR_MASK_YYYX = VECTOR_MASK( 1, 1, 1, 0 ),
	VECTOR_MASK_YYYY = VECTOR_MASK( 1, 1, 1, 1 ),
	VECTOR_MASK_YYYZ = VECTOR_MASK( 1, 1, 1, 2 ),
	VECTOR_MASK_YYYW = VECTOR_MASK( 1, 1, 1, 3 ),
	VECTOR_MASK_YYZX = VECTOR_MASK( 1, 1, 2, 0 ),
	VECTOR_MASK_YYZY = VECTOR_MASK( 1, 1, 2, 1 ),
	VECTOR_MASK_YYZZ = VECTOR_MASK( 1, 1, 2, 2 ),
	VECTOR_MASK_YYZW = VECTOR_MASK( 1, 1, 2, 3 ),
	VECTOR_MASK_YYWX = VECTOR_MASK( 1, 1, 3, 0 ),
	VECTOR_MASK_YYWY = VECTOR_MASK( 1, 1, 3, 1 ),
	VECTOR_MASK_YYWZ = VECTOR_MASK( 1, 1, 3, 2 ),
	VECTOR_MASK_YYWW = VECTOR_MASK( 1, 1, 3, 3 ),
	VECTOR_MASK_YZXX = VECTOR_MASK( 1, 2, 0, 0 ),
	VECTOR_MASK_YZXY = VECTOR_MASK( 1, 2, 0, 1 ),
	VECTOR_MASK_YZXZ = VECTOR_MASK( 1, 2, 0, 2 ),
	VECTOR_MASK_YZXW = VECTOR_MASK( 1, 2, 0, 3 ),
	VECTOR_MASK_YZYX = VECTOR_MASK( 1, 2, 1, 0 ),
	VECTOR_MASK_YZYY = VECTOR_MASK( 1, 2, 1, 1 ),
	VECTOR_MASK_YZYZ = VECTOR_MASK( 1, 2, 1, 2 ),
	VECTOR_MASK_YZYW = VECTOR_MASK( 1, 2, 1, 3 ),
	VECTOR_MASK_YZZX = VECTOR_MASK( 1, 2, 2, 0 ),
	VECTOR_MASK_YZZY = VECTOR_MASK( 1, 2, 2, 1 ),
	VECTOR_MASK_YZZZ = VECTOR_MASK( 1, 2, 2, 2 ),
	VECTOR_MASK_YZZW = VECTOR_MASK( 1, 2, 2, 3 ),
	VECTOR_MASK_YZWX = VECTOR_MASK( 1, 2, 3, 0 ),
	VECTOR_MASK_YZWY = VECTOR_MASK( 1, 2, 3, 1 ),
	VECTOR_MASK_YZWZ = VECTOR_MASK( 1, 2, 3, 2 ),
	VECTOR_MASK_YZWW = VECTOR_MASK( 1, 2, 3, 3 ),
	VECTOR_MASK_YWXX = VECTOR_MASK( 1, 3, 0, 0 ),
	VECTOR_MASK_YWXY = VECTOR_MASK( 1, 3, 0, 1 ),
	VECTOR_MASK_YWXZ = VECTOR_MASK( 1, 3, 0, 2 ),
	VECTOR_MASK_YWXW = VECTOR_MASK( 1, 3, 0, 3 ),
	VECTOR_MASK_YWYX = VECTOR_MASK( 1, 3, 1, 0 ),
	VECTOR_MASK_YWYY = VECTOR_MASK( 1, 3, 1, 1 ),
	VECTOR_MASK_YWYZ = VECTOR_MASK( 1, 3, 1, 2 ),
	VECTOR_MASK_YWYW = VECTOR_MASK( 1, 3, 1, 3 ),
	VECTOR_MASK_YWZX = VECTOR_MASK( 1, 3, 2, 0 ),
	VECTOR_MASK_YWZY = VECTOR_MASK( 1, 3, 2, 1 ),
	VECTOR_MASK_YWZZ = VECTOR_MASK( 1, 3, 2, 2 ),
	VECTOR_MASK_YWZW = VECTOR_MASK( 1, 3, 2, 3 ),
	VECTOR_MASK_YWWX = VECTOR_MASK( 1, 3, 3, 0 ),
	VECTOR_MASK_YWWY = VECTOR_MASK( 1, 3, 3, 1 ),
	VECTOR_MASK_YWWZ = VECTOR_MASK( 1, 3, 3, 2 ),
	VECTOR_MASK_YWWW = VECTOR_MASK( 1, 3, 3, 3 ),
	VECTOR_MASK_ZXXX = VECTOR_MASK( 2, 0, 0, 0 ),
	VECTOR_MASK_ZXXY = VECTOR_MASK( 2, 0, 0, 1 ),
	VECTOR_MASK_ZXXZ = VECTOR_MASK( 2, 0, 0, 2 ),
	VECTOR_MASK_ZXXW = VECTOR_MASK( 2, 0, 0, 3 ),
	VECTOR_MASK_ZXYX = VECTOR_MASK( 2, 0, 1, 0 ),
	VECTOR_MASK_ZXYY = VECTOR_MASK( 2, 0, 1, 1 ),
	VECTOR_MASK_ZXYZ = VECTOR_MASK( 2, 0, 1, 2 ),
	VECTOR_MASK_ZXYW = VECTOR_MASK( 2, 0, 1, 3 ),
	VECTOR_MASK_ZXZX = VECTOR_MASK( 2, 0, 2, 0 ),
	VECTOR_MASK_ZXZY = VECTOR_MASK( 2, 0, 2, 1 ),
	VECTOR_MASK_ZXZZ = VECTOR_MASK( 2, 0, 2, 2 ),
	VECTOR_MASK_ZXZW = VECTOR_MASK( 2, 0, 2, 3 ),
	VECTOR_MASK_ZXWX = VECTOR_MASK( 2, 0, 3, 0 ),
	VECTOR_MASK_ZXWY = VECTOR_MASK( 2, 0, 3, 1 ),
	VECTOR_MASK_ZXWZ = VECTOR_MASK( 2, 0, 3, 2 ),
	VECTOR_MASK_ZXWW = VECTOR_MASK( 2, 0, 3, 3 ),
	VECTOR_MASK_ZYXX = VECTOR_MASK( 2, 1, 0, 0 ),
	VECTOR_MASK_ZYXY = VECTOR_MASK( 2, 1, 0, 1 ),
	VECTOR_MASK_ZYXZ = VECTOR_MASK( 2, 1, 0, 2 ),
	VECTOR_MASK_ZYXW = VECTOR_MASK( 2, 1, 0, 3 ),
	VECTOR_MASK_ZYYX = VECTOR_MASK( 2, 1, 1, 0 ),
	VECTOR_MASK_ZYYY = VECTOR_MASK( 2, 1, 1, 1 ),
	VECTOR_MASK_ZYYZ = VECTOR_MASK( 2, 1, 1, 2 ),
	VECTOR_MASK_ZYYW = VECTOR_MASK( 2, 1, 1, 3 ),
	VECTOR_MASK_ZYZX = VECTOR_MASK( 2, 1, 2, 0 ),
	VECTOR_MASK_ZYZY = VECTOR_MASK( 2, 1, 2, 1 ),
	VECTOR_MASK_ZYZZ = VECTOR_MASK( 2, 1, 2, 2 ),
	VECTOR_MASK_ZYZW = VECTOR_MASK( 2, 1, 2, 3 ),
	VECTOR_MASK_ZYWX = VECTOR_MASK( 2, 1, 3, 0 ),
	VECTOR_MASK_ZYWY = VECTOR_MASK( 2, 1, 3, 1 ),
	VECTOR_MASK_ZYWZ = VECTOR_MASK( 2, 1, 3, 2 ),
	VECTOR_MASK_ZYWW = VECTOR_MASK( 2, 1, 3, 3 ),
	VECTOR_MASK_ZZXX = VECTOR_MASK( 2, 2, 0, 0 ),
	VECTOR_MASK_ZZXY = VECTOR_MASK( 2, 2, 0, 1 ),
	VECTOR_MASK_ZZXZ = VECTOR_MASK( 2, 2, 0, 2 ),
	VECTOR_MASK_ZZXW = VECTOR_MASK( 2, 2, 0, 3 ),
	VECTOR_MASK_ZZYX = VECTOR_MASK( 2, 2, 1, 0 ),
	VECTOR_MASK_ZZYY = VECTOR_MASK( 2, 2, 1, 1 ),
	VECTOR_MASK_ZZYZ = VECTOR_MASK( 2, 2, 1, 2 ),
	VECTOR_MASK_ZZYW = VECTOR_MASK( 2, 2, 1, 3 ),
	VECTOR_MASK_ZZZX = VECTOR_MASK( 2, 2, 2, 0 ),
	VECTOR_MASK_ZZZY = VECTOR_MASK( 2, 2, 2, 1 ),
	VECTOR_MASK_ZZZZ = VECTOR_MASK( 2, 2, 2, 2 ),
	VECTOR_MASK_ZZZW = VECTOR_MASK( 2, 2, 2, 3 ),
	VECTOR_MASK_ZZWX = VECTOR_MASK( 2, 2, 3, 0 ),
	VECTOR_MASK_ZZWY = VECTOR_MASK( 2, 2, 3, 1 ),
	VECTOR_MASK_ZZWZ = VECTOR_MASK( 2, 2, 3, 2 ),
	VECTOR_MASK_ZZWW = VECTOR_MASK( 2, 2, 3, 3 ),
	VECTOR_MASK_ZWXX = VECTOR_MASK( 2, 3, 0, 0 ),
	VECTOR_MASK_ZWXY = VECTOR_MASK( 2, 3, 0, 1 ),
	VECTOR_MASK_ZWXZ = VECTOR_MASK( 2, 3, 0, 2 ),
	VECTOR_MASK_ZWXW = VECTOR_MASK( 2, 3, 0, 3 ),
	VECTOR_MASK_ZWYX = VECTOR_MASK( 2, 3, 1, 0 ),
	VECTOR_MASK_ZWYY = VECTOR_MASK( 2, 3, 1, 1 ),
	VECTOR_MASK_ZWYZ = VECTOR_MASK( 2, 3, 1, 2 ),
	VECTOR_MASK_ZWYW = VECTOR_MASK( 2, 3, 1, 3 ),
	VECTOR_MASK_ZWZX = VECTOR_MASK( 2, 3, 2, 0 ),
	VECTOR_MASK_ZWZY = VECTOR_MASK( 2, 3, 2, 1 ),
	VECTOR_MASK_ZWZZ = VECTOR_MASK( 2, 3, 2, 2 ),
	VECTOR_MASK_ZWZW = VECTOR_MASK( 2, 3, 2, 3 ),
	VECTOR_MASK_ZWWX = VECTOR_MASK( 2, 3, 3, 0 ),
	VECTOR_MASK_ZWWY = VECTOR_MASK( 2, 3, 3, 1 ),
	VECTOR_MASK_ZWWZ = VECTOR_MASK( 2, 3, 3, 2 ),
	VECTOR_MASK_ZWWW = VECTOR_MASK( 2, 3, 3, 3 ),
	VECTOR_MASK_WXXX = VECTOR_MASK( 3, 0, 0, 0 ),
	VECTOR_MASK_WXXY = VECTOR_MASK( 3, 0, 0, 1 ),
	VECTOR_MASK_WXXZ = VECTOR_MASK( 3, 0, 0, 2 ),
	VECTOR_MASK_WXXW = VECTOR_MASK( 3, 0, 0, 3 ),
	VECTOR_MASK_WXYX = VECTOR_MASK( 3, 0, 1, 0 ),
	VECTOR_MASK_WXYY = VECTOR_MASK( 3, 0, 1, 1 ),
	VECTOR_MASK_WXYZ = VECTOR_MASK( 3, 0, 1, 2 ),
	VECTOR_MASK_WXYW = VECTOR_MASK( 3, 0, 1, 3 ),
	VECTOR_MASK_WXZX = VECTOR_MASK( 3, 0, 2, 0 ),
	VECTOR_MASK_WXZY = VECTOR_MASK( 3, 0, 2, 1 ),
	VECTOR_MASK_WXZZ = VECTOR_MASK( 3, 0, 2, 2 ),
	VECTOR_MASK_WXZW = VECTOR_MASK( 3, 0, 2, 3 ),
	VECTOR_MASK_WXWX = VECTOR_MASK( 3, 0, 3, 0 ),
	VECTOR_MASK_WXWY = VECTOR_MASK( 3, 0, 3, 1 ),
	VECTOR_MASK_WXWZ = VECTOR_MASK( 3, 0, 3, 2 ),
	VECTOR_MASK_WXWW = VECTOR_MASK( 3, 0, 3, 3 ),
	VECTOR_MASK_WYXX = VECTOR_MASK( 3, 1, 0, 0 ),
	VECTOR_MASK_WYXY = VECTOR_MASK( 3, 1, 0, 1 ),
	VECTOR_MASK_WYXZ = VECTOR_MASK( 3, 1, 0, 2 ),
	VECTOR_MASK_WYXW = VECTOR_MASK( 3, 1, 0, 3 ),
	VECTOR_MASK_WYYX = VECTOR_MASK( 3, 1, 1, 0 ),
	VECTOR_MASK_WYYY = VECTOR_MASK( 3, 1, 1, 1 ),
	VECTOR_MASK_WYYZ = VECTOR_MASK( 3, 1, 1, 2 ),
	VECTOR_MASK_WYYW = VECTOR_MASK( 3, 1, 1, 3 ),
	VECTOR_MASK_WYZX = VECTOR_MASK( 3, 1, 2, 0 ),
	VECTOR_MASK_WYZY = VECTOR_MASK( 3, 1, 2, 1 ),
	VECTOR_MASK_WYZZ = VECTOR_MASK( 3, 1, 2, 2 ),
	VECTOR_MASK_WYZW = VECTOR_MASK( 3, 1, 2, 3 ),
	VECTOR_MASK_WYWX = VECTOR_MASK( 3, 1, 3, 0 ),
	VECTOR_MASK_WYWY = VECTOR_MASK( 3, 1, 3, 1 ),
	VECTOR_MASK_WYWZ = VECTOR_MASK( 3, 1, 3, 2 ),
	VECTOR_MASK_WYWW = VECTOR_MASK( 3, 1, 3, 3 ),
	VECTOR_MASK_WZXX = VECTOR_MASK( 3, 2, 0, 0 ),
	VECTOR_MASK_WZXY = VECTOR_MASK( 3, 2, 0, 1 ),
	VECTOR_MASK_WZXZ = VECTOR_MASK( 3, 2, 0, 2 ),
	VECTOR_MASK_WZXW = VECTOR_MASK( 3, 2, 0, 3 ),
	VECTOR_MASK_WZYX = VECTOR_MASK( 3, 2, 1, 0 ),
	VECTOR_MASK_WZYY = VECTOR_MASK( 3, 2, 1, 1 ),
	VECTOR_MASK_WZYZ = VECTOR_MASK( 3, 2, 1, 2 ),
	VECTOR_MASK_WZYW = VECTOR_MASK( 3, 2, 1, 3 ),
	VECTOR_MASK_WZZX = VECTOR_MASK( 3, 2, 2, 0 ),
	VECTOR_MASK_WZZY = VECTOR_MASK( 3, 2, 2, 1 ),
	VECTOR_MASK_WZZZ = VECTOR_MASK( 3, 2, 2, 2 ),
	VECTOR_MASK_WZZW = VECTOR_MASK( 3, 2, 2, 3 ),
	VECTOR_MASK_WZWX = VECTOR_MASK( 3, 2, 3, 0 ),
	VECTOR_MASK_WZWY = VECTOR_MASK( 3, 2, 3, 1 ),
	VECTOR_MASK_WZWZ = VECTOR_MASK( 3, 2, 3, 2 ),
	VECTOR_MASK_WZWW = VECTOR_MASK( 3, 2, 3, 3 ),
	VECTOR_MASK_WWXX = VECTOR_MASK( 3, 3, 0, 0 ),
	VECTOR_MASK_WWXY = VECTOR_MASK( 3, 3, 0, 1 ),
	VECTOR_MASK_WWXZ = VECTOR_MASK( 3, 3, 0, 2 ),
	VECTOR_MASK_WWXW = VECTOR_MASK( 3, 3, 0, 3 ),
	VECTOR_MASK_WWYX = VECTOR_MASK( 3, 3, 1, 0 ),
	VECTOR_MASK_WWYY = VECTOR_MASK( 3, 3, 1, 1 ),
	VECTOR_MASK_WWYZ = VECTOR_MASK( 3, 3, 1, 2 ),
	VECTOR_MASK_WWYW = VECTOR_MASK( 3, 3, 1, 3 ),
	VECTOR_MASK_WWZX = VECTOR_MASK( 3, 3, 2, 0 ),
	VECTOR_MASK_WWZY = VECTOR_MASK( 3, 3, 2, 1 ),
	VECTOR_MASK_WWZZ = VECTOR_MASK( 3, 3, 2, 2 ),
	VECTOR_MASK_WWZW = VECTOR_MASK( 3, 3, 2, 3 ),
	VECTOR_MASK_WWWX = VECTOR_MASK( 3, 3, 3, 0 ),
	VECTOR_MASK_WWWY = VECTOR_MASK( 3, 3, 3, 1 ),
	VECTOR_MASK_WWWZ = VECTOR_MASK( 3, 3, 3, 2 ),
	VECTOR_MASK_WWWW = VECTOR_MASK( 3, 3, 3, 3 ),
} vector_mask_t;

