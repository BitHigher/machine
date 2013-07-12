#include "kmeans.h"
#include "../base/common.h"
#include "../math/hfmath.h"
#include <memory.h>

KMeans::KMeans()
: distance_(NULL)
{
}

KMeans::~KMeans()
{
}

void KMeans::set_distance(Distance *distance)
{
	distance_ = distance;
}

void KMeans::cluster(HFMatrix<double> *vertices, int k)
{
	srand(time(0));
	ASSERT(vertices->num_cols >= k);
	ASSERT(distance_);
	int size = vertices->num_cols;
	int nfeat = vertices->num_rows;
	k_ = k;
	mus_.resize(nfeat, k_);
	weight_.resize(size);
	weight_.set_const(1.0);

	int *clusters = (int*)malloc(size*sizeof(int));
	double *weight_set = (double*)malloc(k_*sizeof(double));
	memset(weight_set, 0, k_*sizeof(double));

	// initiate the starting centers: mus_
	for(int i = 0; i < size; ++i)
	{
		double w = weight_.vector[i];
		int cl = HFMath::random(0, k-1);
		clusters[i] = cl; 
		weight_set[cl] += w;
		double *vec = vertices->get_column(i);

		for(int j = 0; j < nfeat; ++j)
			mus_(j, cl) += w*vec[j];
	}
	
	for(int i = 0; i < k_; ++i)
	{
		if(weight_set[i] == 0)
			continue;

		for(int j = 0; j < nfeat; ++j)
			mus_(j, i) /= weight_set[i];
	}

	mus_.display_matrix("Starting Centers");

	// apply assign and update steps alternatively
	bool stop = false;
	int iter = 0;
	distance_->set_right(*vertices);
	
	HFMatrix<double> old_mus;
	old_mus.copy(mus_);
	while(!stop)
	{
		printf("Iter: %d\n", iter++);

		distance_->set_left(mus_);
		distance_->distances();
		// recalculate centers: mus_
		mus_.set_const(0);
		memset(weight_set, 0, k_*sizeof(double));
		
		int cl = 0;
		double w = 0;
		double *vec = NULL;

		for(int i = 0; i < size; ++i)
		{
			w = weight_.vector[i];
			vec = vertices->get_column(i);
			// find the nearest mu
			cl = 0;
			for(int j = 1; j < k_; ++j)
			{
				if(distance_->result_(j,i) <
					distance_->result_(cl, i))
					cl = j;
			}

			for(int j = 0; j < nfeat; ++j)
			{
				mus_(j, cl) += w*vec[j];
			}
			weight_set[cl] += w;
		}

		// new centers
		for(int i = 0; i < k_; ++i)
		{
			if(weight_set[i] == 0)
				continue;

			for(int j = 0; j < nfeat; ++j)
				mus_(j, i) /= weight_set[i];
		
			printf("Center: %d numter: %lf\n", i, weight_set[i]);
		}
		distance_->set_left(mus_);

		mus_.display_matrix("Centers");
		
		if(iter >= 1000 || old_mus.equals(mus_))
			break;

		old_mus.copy(mus_);
	}

	free(clusters);
	free(weight_set);
}
