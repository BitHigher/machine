#include "perceptron.h"
#include "../base/common.h"
#include "../math/hfmath.h"

Perceptron::Perceptron()
: learn_rate_(0.1), max_iter_(1000)
{
}

void Perceptron::train(HFMatrix<double> *features, HFVector<int> *labels)
{
	ASSERT(features->num_cols == labels->size);	
	int nfeat = features->num_rows;
	int size = features->num_cols;

	// initiate w and b
	w_ = HFVector<double>(nfeat);
	bias_ = 0;
	for(int i = 0; i < nfeat; ++i)
		w_.vector[i] = 1.0/nfeat;


	int error_count = 1;
	int iter = 0;
	while(error_count && iter < max_iter_)
	{
		error_count = 0;
		for(int i = 0; i < size; ++i)
		{
			double *col = features->get_column(i);
			double y = HFVector<double>::dot(col, w_.vector, nfeat) + bias_;
			double error = labels->vector[i] - HFMath::sign<double>(y);
			if(error)
			{
				error_count += 1;
				bias_ += learn_rate_ * labels->vector[i];
				for(int j = 0; j < nfeat; ++j)
				{
					w_.vector[j] += learn_rate_ * (error) * col[j];
				}
				w_.display_vector("Weight");
			}	
		}

		iter++;
	}
	
	if(!error_count)
		printf("Perceptron converged after %d iterations\n", iter);
	else
		printf("Perceptron did not converge after %d iterations\n", max_iter_);

	w_.display_vector("Weight");
	printf("Bias: %lf\n", bias_);
}
