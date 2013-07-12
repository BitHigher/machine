#ifndef MATH_MATH_H
#define MATH_MATH_H

#include <math.h>
#include <time.h>
#include <stdlib.h>

class HFMath
{
public:
	template<class T>
	static inline T max(T a, T b)
	{
		return a>b?a:b;
	}

	template<class T>
	static inline T min(T a, T b)
	{
		return a>b?b:a;
	}

	template<class T>
	static inline T sign(T a)
	{
		if(a == 0)
			return 0;
		else return (a<0)? -1 : 1;
	}

	template<class T>
	static inline T square(T x)
	{
		return x*x;
	}

	template<class T>
	static inline T sqrt(T x)
	{
		return ::sqrt(x);
	}

	static inline double random()
	{
		return rand()/(RAND_MAX+1.0);
	}

	static inline int random(int min_val, int max_val)
	{
		int ret = min_val + (int)(max_val-min_val+1)*random();
		return ret;
	}
};

#endif /* MATH_MATH_H */
