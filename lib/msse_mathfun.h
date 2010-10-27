/*
 * msse_mathfun.h
 *
 *  Created on: Apr 9, 2010
 *      Author: darek
 */

#ifndef MSSE_MATHFUN_H_
#define MSSE_MATHFUN_H_
#ifdef _MSC_VER /* visual c++ */
# define ALIGN16_BEG __declspec(align(16))
# define ALIGN16_END
#else /* gcc or icc */
# define ALIGN16_BEG
# define ALIGN16_END __attribute__((aligned(16)))
#endif

#include <xmmintrin.h>
# include <emmintrin.h>
typedef __m128 v4sf;  // vector of 4 float (sse1)
typedef __m128i v4si; // vector of 4 int (sse2)


/* declare some SSE constants -- why can't I figure a better way to do that? */
#define _PS_CONST(Name, Val)                                            \
  static const ALIGN16_BEG float _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PI32_CONST(Name, Val)                                            \
  static const ALIGN16_BEG int _pi32_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PS_CONST_TYPE(Name, Type, Val)                                 \
  static const ALIGN16_BEG Type _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }

#define nr_PI			(3.14159265358979323846)
_PS_CONST(1  , 1.0f);
_PS_CONST(0p5, 0.5f);
/* the smallest non denormalized float number */
_PS_CONST_TYPE(min_norm_pos, int, 0x00800000);
_PS_CONST_TYPE(mant_mask, int, 0x7f800000);
_PS_CONST_TYPE(inv_mant_mask, int, ~0x7f800000);

_PS_CONST_TYPE(sign_mask, int, 0x80000000);
_PS_CONST_TYPE(inv_sign_mask, int, ~0x80000000);

_PS_CONST(pi_4, (float)(nr_PI / 4.0));
_PS_CONST(pi_2, (float)(nr_PI / 2.0));
_PS_CONST(pi, (float)(nr_PI));


// for sin
_PS_CONST(4_pi, (float)(4.0 / nr_PI));
_PS_CONST(4_pixpi, (float)(-4.0 /(nr_PI * nr_PI)));
#ifdef EXTRA_PRECISION
_PS_CONST(0p225, 0.225f);
#endif

/// all input between -pi and pi is valid
v4sf sin_ps(v4sf x) {
	 v4sf y,z;
	 /* scale by 4/Pi */
	  y = _mm_mul_ps(x, *(v4sf*)_ps_4_pi);
	  /* take the absolute value */
	  z = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
	  z = _mm_mul_ps(x,z);
	  z = _mm_mul_ps(z, *(v4sf*)_ps_4_pixpi);
	  y = _mm_add_ps (y,z);
#ifdef EXTRA_PRECISION
	  z = _mm_and_ps(y, *(v4sf*)_ps_inv_sign_mask);
	  z = _mm_mul_ps(y,z);
	  z = _mm_sub_ps(z,y);
	  z = _mm_mul_ps(z, *(v4sf*)_ps_0p225);
	  y = _mm_add_ps (y,z);
#endif
	return (y);
}

// cos(x) = sin(x + pi/2)
v4sf cos_ps(v4sf x) {
	 v4sf y,z;
	 x = _mm_add_ps (x,*(v4sf*)_ps_pi_2);
	 y = x;
	 y = _mm_cmpnlt_ps(y,*(v4sf*)_ps_pi);
	 y = _mm_and_ps(y, *(v4sf*)_ps_pi_2);
	 x = _mm_sub_ps (x,y);
	 /* sin_ps */
	  y = _mm_mul_ps(x, *(v4sf*)_ps_4_pi);
	  /* take the absolute value */
	  z = _mm_and_ps(x, *(v4sf*)_ps_inv_sign_mask);
	  z = _mm_mul_ps(x,z);
	  z = _mm_mul_ps(z, *(v4sf*)_ps_4_pixpi);
	  y = _mm_add_ps (y,z);
#ifdef EXTRA_PRECISION
	  z = _mm_and_ps(y, *(v4sf*)_ps_inv_sign_mask);
	  z = _mm_mul_ps(y,z);
	  z = _mm_sub_ps(z,y);
	  z = _mm_mul_ps(z, *(v4sf*)_ps_0p225);
	  y = _mm_add_ps (y,z);
#endif
	return (y);
}

// EXP_PS http://www.musicdsp.org/showone.php?id=222
#ifdef EXTRA_PRECISION
	_PS_CONST(5, (float)(5.0));
	_PS_CONST(20, (float)(20.0));
	_PS_CONST(60, (float)(60.0));
	_PS_CONST(120, (float)(120.0));
	_PS_CONST(0008333, (float)(0.0083333333));
	v4sf exp_ps(v4sf x) {
	v4sf y;
	 y = _mm_add_ps(x, *(v4sf*)_ps_5);
	 y = _mm_mul_ps(y,x);
	 y = _mm_add_ps(y, *(v4sf*)_ps_20);
	 y = _mm_mul_ps(y,x);
	 y = _mm_add_ps(y, *(v4sf*)_ps_60);
	 y = _mm_mul_ps(y,x);
	 y = _mm_add_ps(y, *(v4sf*)_ps_120);
	 y = _mm_mul_ps(y,x);
	 y = _mm_add_ps(y, *(v4sf*)_ps_120);
	 y = _mm_mul_ps(y, *(v4sf*)_ps_0008333);
	 return (y);
	 }
#else
	  _PS_CONST(6, (float)(6.0));
	  _PS_CONST(3, (float)(3.0));
	  _PS_CONST(01666, (float)(0.16666666));

	 v4sf exp_ps(v4sf x) {
	 v4sf y;
	 y = _mm_add_ps(x, *(v4sf*)_ps_3);
	 y = _mm_mul_ps(y,x);
	 y = _mm_add_ps(y, *(v4sf*)_ps_6);
	 y = _mm_mul_ps(y,x);
	 y = _mm_add_ps(y, *(v4sf*)_ps_6);
	 y = _mm_mul_ps(y, *(v4sf*)_ps_01666);
	return (y);
	  }
#endif


_PS_CONST_TYPE(mask_abs, int, ~0x7fffffff);

	 /*
	 A tanh() function approximation :

	 tanh(x) ~ sign(x) * (1 - 1 / (1 + |x| + x^2 + a * x^4))

	 with a = 1 to save a mul (3.0 % max. relative error)
	 or a = 1.41645 to minimize the maximum relative error (1.7 %)
	 */
#ifdef EXTRA_PRECISION
	 _PS_CONST(1p416, 1.41645f);
#endif

	 v4sf   approx_tanh_ps (v4sf x)
	 {
	    const v4sf   xa = _mm_and_ps (*(v4sf*)_ps_mask_abs, x);
	    const v4sf   xs = _mm_andnot_ps (*(v4sf*)_ps_mask_abs, x);

	    const v4sf   x2 = _mm_mul_ps (x, x);
	    v4sf   x4 = _mm_mul_ps (x2, x2);
#ifdef EXTRA_PRECISION
	    x4 = _mm_mul_ps (x4, *(v4sf*)_ps_1p416);
#endif
	    const v4sf   poly = _mm_add_ps (_mm_add_ps (xa, x2), x4);
	    const v4sf   resa = _mm_div_ps (poly, _mm_add_ps (*(v4sf*)_ps_1, poly));
	    const v4sf   result = _mm_or_ps (resa, xs);

	    return (result);
	 }


#endif /* MSSE_MATHFUN_H_ */
