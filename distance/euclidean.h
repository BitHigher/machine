#ifndef DISTANCE_EUCLIDEAN
#define DISTANCE_EUCLIDEAN

/**
 * Euclidean Distance.
 *
 * Calculate euclidean distance between vectors and matrices.
 *
 */

#include "distance.h"

class Euclidean : public Distance
{
public:
	virtual double distance(double *v1, double *v2, int size);
};

#endif /* DISTANCE_EUCLIDEAN */
