#include "hfvector.h"
#include<stdlib.h>

template<class T>
HFVector<T>::HFVector()
: vector(NULL), size(0)
{
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

/*
template<class T>
HFVector<T>::~HFVector()
{
	if(vector)
		free(vector);
	vector = NULL;
	size = 0;
}
*/

template class HFVector<int>;
template class HFVector<double>;
