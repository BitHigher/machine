#include "lda.h"
#include "../base/common.h"
#include "../math/hfmath.h"
#include <stdlib.h>
#include <cblas.h>
#include <lapacke.h>

LDA::LDA()
{
}

void LDA::train(HFMatrix<double> *features, 
					HFVector<int> *labels)
{
	print_matrix("Features", features->num_rows, features->num_cols,
					features->matrix, features->num_rows);
	
	ASSERT(features->num_cols == labels->size);
	int size = features->num_cols;
	int nfeat = features->num_rows;

	int num_neg = 0;
	int num_pos = 0;

	int *negs = (int*)malloc(size*sizeof(int));
	int *poss = (int*)malloc(size*sizeof(int));

	for(int i = 0; i < size; ++i)
	{
		if(labels->vector[i] == 1)
			poss[num_pos++] = i;
		else // -1
			negs[num_neg++] = i;
	}

	ASSERT(num_neg >= 0 && num_pos > 0);
	
	double *neg_mean = (double*)malloc(nfeat*sizeof(double));
	double *pos_mean = (double*)malloc(nfeat*sizeof(double));
	double *scatter = (double*)malloc(nfeat*nfeat*sizeof(double));
	double *buffer = (double*)malloc(nfeat*sizeof(double)*
									HFMath::max(num_neg, num_pos));

	/*
	 * buffer stores vectors of negative features
	 * or positive features
	 *
	 */
	
	for(int i = 0; i < num_pos; ++i)
	{
		double *row = features->get_column(poss[i]);
		for(int j = 0; j < nfeat; ++j)
		{
			pos_mean[j] += row[j];
			buffer[nfeat*i+j] = row[j];
		}
	}

	for(int i = 0; i < nfeat; ++i)
		pos_mean[i] /= num_pos;
	
	for(int i = 0; i < num_pos; ++i)
	{
		for(int j = 0; j < nfeat; ++j)
			buffer[i*nfeat+j] -= pos_mean[j];
	}

	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, 
				nfeat, nfeat, num_pos, 1.0, buffer, nfeat,
				buffer, nfeat, 0, scatter, nfeat);


	for(int i = 0; i < num_neg; ++i)
	{
		double *row = features->get_column(negs[i]);
		for(int j = 0; j < nfeat; ++j)
		{
			neg_mean[j] += row[j];
			buffer[i*nfeat+j] = row[j];
		}
	}

	for(int i = 0; i < nfeat; ++i)
		neg_mean[i] /= num_neg;
	for(int i = 0; i < num_neg; ++i)
	{
		for(int j = 0; j < nfeat; ++j)
			buffer[i*nfeat+j] -= neg_mean[j];
	}


	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, 
				nfeat, nfeat, num_neg, 1.0, buffer, nfeat,
				buffer, nfeat, 1.0, scatter, nfeat);

	/* 
	 * S_w = (X_1-m_1)(X_1-m_1)^T + (X_2-m_2)(X_2-m_2)^T
	 * S_b = (m_1-m_2)*(m_1-m_2)^T
	 *
	 * w = S_w^-1(m_1 - m_2) 
	 *
	 */	

	print_matrix("scatter", nfeat, nfeat, scatter, nfeat);
	
	double *inv_scatter = HFMatrix<double>::pinv(scatter, nfeat,nfeat);

	double *w_pos = (double*)malloc(nfeat*sizeof(double));
	double *w_neg = (double*)malloc(nfeat*sizeof(double));


	print_matrix("inverse scatter", nfeat, nfeat, inv_scatter, nfeat);
	cblas_dsymv(CblasColMajor, CblasUpper, nfeat, 1.0, inv_scatter, nfeat,
				pos_mean, 1, 0.0, w_pos, 1);
	cblas_dsymv(CblasColMajor, CblasUpper, nfeat, 1.0, inv_scatter, nfeat,
				neg_mean, 1, 0.0, w_neg, 1);

	printf("BEFORE\n");
	w_ = HFVector<double>(nfeat);
	printf("w_: %p\n", w_.vector);
	for(int i = 0; i < nfeat; ++i)
		w_.vector[i] = w_pos[i] - w_neg[i];

	bias_ = 0.5*(HFVector<double>::dot(w_neg, neg_mean, nfeat) -
				 HFVector<double>::dot(w_pos, pos_mean, nfeat));

	print_matrix("Weight", 1, nfeat, w_.vector, 1);
	printf("Bias: %lf\n", bias_);

	// free memory
	free(negs);
	free(poss);

	free(pos_mean);
	free(neg_mean);
	free(scatter);
	free(buffer);
	
	free(inv_scatter);
	free(w_pos);
	free(w_neg);
}
