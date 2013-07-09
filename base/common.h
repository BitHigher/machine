/*
 * common functions
 *
 */

#ifndef BASE_COMMON_H
#define BASE_COMMON_H

#include <stdio.h>
#include <stdlib.h>

#if !defined(HF_UNLIKELY)
#if __GNUC__ >= 3
#define HF_UNLIKELY(expr) __builtin_expect(expr, 0)
#else
#define HF_UNLIKELY(expr) expr
#endif
#endif

#define DIE(err) { \
	printf("[%s: line %d]: %s\n", __FILE__, __LINE__, err); \
	exit(-1);	\
}


#define ASSERT(x){	\
	if(HF_UNLIKELY(!(x))){ \
		printf("Assertion %s failed in file %s line %d\n", \
				#x, __FILE__, __LINE__);	\
		exit(-1); \
	}	\
}

void print_matrix(const char *desc, int m, int n, double *a, int lda);
#endif /* BASE_COMMON_H */
