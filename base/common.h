/*
 * common functions
 *
 */

#ifndef BASE_COMMON_H
#define BASE_COMMON_H

#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#if !defined(HF_UNLIKELY)
#if __GNUC__ >= 3
#define HF_UNLIKELY(expr) __builtin_expect(expr, 0)
#else
#define HF_UNLIKELY(expr) expr
#endif
#endif

#define ASSERT(x){	\
	if(HF_UNLIKELY(!(x))){ \
		printf("\033[1;31m[FATAL]\033[0m" \
				":Assertion %s failed in file %s line %d\n", \
				#x, __FILE__, __LINE__);	\
		exit(-1); \
	}	\
}

void print_matrix(const char *desc, int m, int n, double *a, int lda);
#endif /* BASE_COMMON_H */
