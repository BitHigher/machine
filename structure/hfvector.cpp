#include "hfvector.h"
#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>
#include <iostream>

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
HFVector<T>::HFVector(T *v, int size)
: vector(v), size(size)
{
}

template<class T>
HFVector<T>::HFVector(Loader &loader)
{
	load(loader);
}

template<class T>
HFVector<T>::~HFVector()
{
	printf("Vector Destroy %p\n", vector);
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
void HFVector<T>::save(Saver &saver)
{
	saver.save_vector(vector, size);
}

template<class T>
void HFVector<T>::load(Loader &loader)
{
	loader.load_vector(vector, size);
}

template<class T>
double HFVector<T>::dot(const double *v1, const double *v2, int size)
{
	double r = cblas_ddot(size, v1, 1, v2, 1);
	return r;
}

template<class T>
void HFVector<T>::display_vector(const char *desc)
{
	std::cout << '\n' << desc << '\n' << '[';
	for(int i = 0; i < size-1; ++i)
		std::cout << vector[i] << ',';

	if(size > 0)
		std::cout << vector[size-1];

	std::cout << "]\n";
}

template class HFVector<int>;
template class HFVector<double>;
