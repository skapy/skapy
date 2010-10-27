#ifndef MATH_VECTOR_H_
#define MATH_VECTOR_H_

#ifdef M_MATH /* my sse math lib */
#include "msse_mathfun.h"
#else /* from fr */
#include "sse_mathfun.h"
#endif

typedef ALIGN16_BEG union {
  float f[4];
  int i[4];
  v4sf  v;
} ALIGN16_END V4SF;


/*class vector_log_ps{
	V4SF *const v1, *const v2; // multiply these vectors
	public:
		// constructor copies the arguments into local storage
		vector_log_ps(V4SF *vec1, V4SF *vec2)
		: v1(vec1), v2(vec2) { }

		// overload () so it does a vector multiply
		void operator() (const blocked_range<size_t> &r) const {
			for(size_t i=r.begin(); i!=r.end(); i++)
				  v2[i].v= log_ps(v1[i].v);
		}
};
*/
class vector_exp_ps{
	V4SF *const v1, *const v2; // multiply these vectors
	public:
		// constructor copies the arguments into local storage
		vector_exp_ps(V4SF *vec1, V4SF *vec2)
		: v1(vec1), v2(vec2) { }

		// overload () so it does a vector multiply
		void operator() (const blocked_range<size_t> &r) const {
			for(size_t i=r.begin(); i!=r.end(); i++)
				  v2[i].v= exp_ps(v1[i].v);
		}
};

class vector_sin_ps{
	V4SF *const v1, *const v2; // multiply these vectors
	public:
		// constructor copies the arguments into local storage
		vector_sin_ps(V4SF *vec1, V4SF *vec2)
		: v1(vec1), v2(vec2) { }

		// overload () so it does a vector multiply
		void operator() (const blocked_range<size_t> &r) const {
			for(size_t i=r.begin(); i!=r.end(); i++)
				  v2[i].v= sin_ps(v1[i].v);
		}
};

class vector_cos_ps{
	V4SF *const v1, *const v2; // multiply these vectors
	public:
		// constructor copies the arguments into local storage
		vector_cos_ps(V4SF *vec1, V4SF *vec2)
		: v1(vec1), v2(vec2) { }

		// overload () so it does a vector multiply
		void operator() (const blocked_range<size_t> &r) const {
			for(size_t i=r.begin(); i!=r.end(); i++)
				  v2[i].v= cos_ps(v1[i].v);
		}
};
class vector_ps{
	V4SF *const v1, *const v2; // multiply these vectors
	public:
		// constructor copies the arguments into local storage
		vector_ps(V4SF *vec1, V4SF *vec2)
		: v1(vec1), v2(vec2) { }

		//void exp(V4SF *ec1) : v1(ec1) {

//		}
		// overload () so it does a vector multiply
		void operator() (const blocked_range<size_t> &r) const {
			for(size_t i=r.begin(); i!=r.end(); i++)
				  v2[i].v= cos_ps(v1[i].v);
		}
};

#endif /*MATH_VECTOR_H_*/
