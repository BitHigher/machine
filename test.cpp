#include <stdio.h>
#include "structure/hfmatrix.h"
#include "classifier/lda.h"
#include "classifier/perceptron.h"

#include <cblas.h>

void test_vector()
{
	printf("[test vector]\n");
	
	double v1[3] = {1, 2, 3};
	double v2[3] = {4, 5, 6};

	double r = HFVector<double>::dot(v1, v2, 3);
	printf("DOT: %lf\n", r);
}

void test_matrix()
{
	printf("[test matrix]\n");

	//double m[3*2] = {1,2,3,4,5,6};
	//double m[2*2] = {1,2,3,4};
	//double m[1*2] = {1,2};
	double m[3*3] = {219.58, 209.42, 217.75, 
					 209.42, 217.58, 213.25,
					 217.75, 213.25, 222.25};


	double *pinv = HFMatrix<double>::pinv(m, 3, 3);

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
			printf("%lf ", pinv[j*3+i]);
		printf("\n");
	}
}

void test_lda()
{
	printf("[test lda]\n");
	
	double feats[3*10] = {1,2,3,4,5,6,7,8,9,3,5,7,5,3,7,
						  11,12,13,14,15,16,17,18,19,
						  13,15,17,15,13,17};
	int lbls[10] = {-1, -1, 1, 1, -1, 1, 1, 1, -1, 1};


	HFMatrix<double> features(feats, 10, 3);
	HFVector<int> labels(lbls, 10);

	Saver saver("hello_matrix");
	features.save(saver);

	LDA lda;	
	lda.train(&features, &labels);
}

void test_perceptron()
{
	printf("[test perceptron]\n");
}

int main()
{
	// test_vector();
	// test_matrix();

	test_lda();
}
