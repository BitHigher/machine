#include "hfvector.h"
#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>


template<class T>
HFVector<T>::HFVector()
: vector(NULL), size(0)
{
	printf("DEFAULT");
}


template<class T>
HFVector<T>::HFVector(int size)
: size(size)
{
	vector = (T*)malloc(size*sizeof(T));
}

template<class T>
HFVector<T>::HFVector(T *v, int size): vector(v), size(size) {
}

template<class T>
HFVector<T>::~HFVector()
{
	printf("FREE %p\n", vector);
/*
	if(vector)
	{
		free(vector);
		
		printf("FREE %p\n", vector);
	}
	vector = NULL;
	size = 0;
*/
}

template<class T>
double HFVector<T>::dot(const double *v1, const double *v2, int size)
{
	double r = cblas_ddot(size, v1, 1, v2, 1);
	return r;
}

template class HFVector<int>;
template class HFVector<double>;
