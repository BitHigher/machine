#include "euclidean.h"
#include "../math/hfmath.h"


double Euclidean::distance(double *v1, double *v2, int size)
{
	double result = 0;
	for(int i = 0; i < size; ++i)
		result += HFMath::square(v1[i]-v2[i]);

	return HFMath::sqrt(result);
}
