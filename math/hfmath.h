#ifndef MATH_MATH_H
#define MATH_MATH_H

class HFMath
{
public:
	template<class T>
	static inline T max(T a, T b){
		return a>b?a:b;
	}

	template<class T>
	static inline T min(T a, T b){
		return a>b?b:a;
	}
};

#endif /* MATH_MATH_H */
