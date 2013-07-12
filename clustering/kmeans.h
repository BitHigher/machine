#ifndef CLUSTERING_KMEANS_H
#define CLUSTERING_KMEANS_H

/**
 * KMeans implements the simple kmeans algorithm.
 *
 * Two Steps:
 * 
 * Step 1: Assignment
 * c(x) = argmin_{c \in \{1,2,...,k\}} ||x - \mu_c||^2
 * 
 *
 * Step 2: Update
 * \mu_i = \frac{1}{|\{x:c(x)=i\}|} \sum_{x:c(x)=i} x  
 *
 *
 * c(x) is the cluster which x belongs to
 * \mu_i is the center of cluster i
 *
 */

#include "../structure/hfvector.h"
#include "../structure/hfmatrix.h"
#include "../distance/distance.h"

class KMeans
{
public:
	KMeans();
	virtual ~KMeans();
	void set_distance(Distance *distance);

	void cluster(HFMatrix<double> *vertices, int k);
private:
	HFMatrix<double> mus_;
	int k_;
	HFVector<double> weight_;
	
	Distance *distance_;
};

#endif /* CLUSTERING_KMEANS_H */
