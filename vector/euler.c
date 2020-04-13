/* euler.c  -  Vector library  -  Public Domain  -  2013 Mattias Jansson
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

#include <vector/euler.h>
#include <vector/quaternion.h>

euler_angles_t
euler_angles(real rx, real ry, real rz, euler_angles_order_t order) {
	float32_aligned128_t v[4];
	v[0] = rx;
	v[1] = ry;
	v[2] = rz;
	*((uint32_t*)v + 3) = order;
	return vector_aligned(v);
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL unsigned int
euler_get_safe(unsigned int order) {
	static const unsigned int safe[] = {0, 1, 2, 0};
	return safe[order & 0x3];
}

static FOUNDATION_FORCEINLINE FOUNDATION_CONSTCALL unsigned int
euler_get_next(unsigned int order) {
	static const unsigned int next[] = {1, 2, 0, 1};
	return next[order & 0x3];
}

#define EULER_SPLICE_ORDER_DATA(order) \
	f = order & 0x1;                   \
	order >>= 1;                       \
	s = order & 0x1;                   \
	order >>= 1;                       \
	n = order & 0x1;                   \
	order >>= 1;                       \
	i = euler_get_safe(order);         \
	j = euler_get_next(i + n);         \
	k = euler_get_next(i + 1 - n)

quaternion_t
euler_angles_to_quaternion(const euler_angles_t angles) {
	// From http://etclab.mie.utoronto.ca/people/david_dir/GEMS/GEMS.html
	// https://web.archive.org/web/20101204012751/http://etclab.mie.utoronto.ca/people/david_dir/GEMS/GEMS.html
	uint32_t order = *((const uint32_t*)&angles + 3);
	real angle[3] = {vector_x(angles), vector_y(angles), vector_z(angles)};
	real ti, tj, th, ci, cj, ch, si, sj, sh, cc, cs, sc, ss;
	float32_aligned128_t q[4];
	unsigned int i, j, k, n, s, f;

	EULER_SPLICE_ORDER_DATA(order);

	if (f == VECTOR_EULER_ROTATEFRAME) {
		real t = angle[0];
		angle[0] = angle[2];
		angle[2] = t;
	}
	if (n == VECTOR_EULER_ODD)
		angle[1] = -angle[1];

	ti = angle[0] * 0.5f;
	tj = angle[1] * 0.5f;
	th = angle[2] * 0.5f;

	ci = math_cos(ti);
	cj = math_cos(tj);
	ch = math_cos(th);
	si = math_sin(ti);
	sj = math_sin(tj);
	sh = math_sin(th);

	cc = ci * ch;
	cs = ci * sh;
	sc = si * ch;
	ss = si * sh;

	if (s == VECTOR_EULER_REPEAT) {
		q[i] = cj * (cs + sc);
		q[j] = sj * (cc + ss);
		q[k] = sj * (cs - sc);
		q[3] = cj * (cc - ss);
	} else {
		q[i] = cj * sc - sj * cs;
		q[j] = cj * ss + sj * cc;
		q[k] = cj * cs - sj * sc;
		q[3] = cj * cc + sj * ss;
	}

	if (n == VECTOR_EULER_ODD)
		q[j] = -q[j];

	return quaternion_normalize(quaternion_aligned(q));
}

/*
euler_angles_t
euler_angles_from_quaterion(const quaternion_t q, euler_angles_order_t order) {
    uint32_t lorder = order;
    matrix_t mat = quaternion_to_matrix(q);

    //From http://etclab.mie.utoronto.ca/people/david_dir/GEMS/GEMS.html
    //https://web.archive.org/web/20101204012751/http://etclab.mie.utoronto.ca/people/david_dir/GEMS/GEMS.html
    int i,j,k,n,s,f;
    float32_aligned128_t angles[4];

    EULER_SPLICE_ORDER_DATA(lorder);

    if (s == VECTOR_EULER_REPEAT) {
        real sy = math_sqrt(mat.frow[j][i] * mat.frow[j][i] + mat.frow[k][i] * mat.frow[k][i]);

        if (!fltzero(sy)) {
            angles[0] = math_atan2(mat.frow[j][i],  mat.frow[k][i]);
            angles[1] = math_atan2(sy,              mat.frow[i][i]);
            angles[2] = math_atan2(mat.frow[i][j], -mat.frow[i][k]);
        }
        else {
            angles[0] = math_atan2(-mat.frow[k][j], mat.frow[j][j]);
            angles[1] = math_atan2(sy,              mat.frow[i][i]);
            angles[2] = 0.0f;
        }
    }
    else
    {
        real cy = math_sqrt(mat.frow[i][i] * mat.frow[i][i] + mat.frow[i][j] * mat.frow[i][j]);

        if (!fltzero(cy)) {
            angles[0] = math_atan2( mat.frow[j][k], mat.frow[k][k]);
            angles[1] = math_atan2(-mat.frow[i][k], cy            );
            angles[2] = math_atan2( mat.frow[i][j], mat.frow[i][i]);
        }
        else {
            angles[0] = math_atan2(-mat.frow[k][j], mat.frow[j][j]);
            angles[1] = math_atan2(-mat.frow[i][k], cy            );
            angles[2] = 0.0f;
        }
    }

    if (n == VECTOR_EULER_ODD) {
        angles[0] = -angles[0];
        angles[1] = -angles[1];
        angles[2] = -angles[2];
    }
    if (f == VECTOR_EULER_ROTATEFRAME) {
        real t = angles[0];
        angles[0] = angles[2];
        angles[2] = t;
    }

    return euler_angles(vector_aligned(angles), order);
}
*/
