/*
 * util_math.h
 *
 *  Created on: Oct 27, 2010
 *      Author: darek
 */

#ifndef UTIL_MATH_H_
#define UTIL_MATH_H_


#ifdef _MSC_VER /* visual c++ */
# define ALIGN16_BEG __declspec(align(16))
# define ALIGN16_END
#else /* gcc or icc */
# define ALIGN16_BEG
# define ALIGN16_END __attribute__((aligned(16)))
#endif

#include <xmmintrin.h>

/* __m128 is ugly to write */
typedef __m128 v4sf;  // vector of 4 float (sse1)

#ifdef USE_SSE2
#include <emmintrin.h>
typedef __m128i v4si; // vector of 4 int (sse2)
#else
typedef __m64 v2si;   // vector of 2 int (mmx)
#endif

/* declare some SSE constants -- why can't I figure a better way to do that? */
#define _PS_CONST(Name, Val)                                            \
  static const ALIGN16_BEG float _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PI32_CONST(Name, Val)                                            \
  static const ALIGN16_BEG int _pi32_##Name[4] ALIGN16_END = { Val, Val, Val, Val }
#define _PS_CONST_TYPE(Name, Type, Val)                                 \
  static const ALIGN16_BEG Type _ps_##Name[4] ALIGN16_END = { Val, Val, Val, Val }

_PS_CONST(1  , 1.0f);
_PS_CONST(0p5, 0.5f);
/* the smallest non denormalized float number */
_PS_CONST_TYPE(min_norm_pos, int, 0x00800000);
_PS_CONST_TYPE(mant_mask, int, 0x7f800000);
_PS_CONST_TYPE(inv_mant_mask, int, ~0x7f800000);

_PS_CONST_TYPE(sign_mask, int, 0x80000000);
_PS_CONST_TYPE(inv_sign_mask, int, ~0x80000000);
_PS_CONST_TYPE(mask_abs, int, ~0x7fffffff);

typedef ALIGN16_BEG union {
  float f[4];
  int i[4];
  v4sf  v;
} ALIGN16_END V4SF;


#endif /* UTIL_MATH_H_ */



