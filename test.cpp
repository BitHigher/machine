#include <stdio.h>
#include "structure/hfmatrix.h"
#include "classifier/lda.h"
#include "classifier/perceptron.h"

#include "base/config.h"
#include "base/parallel.h"
#include "distance/euclidean.h"

void test_distance()
{
	printf("[test euclidean]\n");


	double v1[3] = {1, 2, 3};
	double v2[3] = {3, 1, 5};
	
	Euclidean e;
	double result = e.distance(v1, v2, 3);

	printf("Result: %lf\n", result);
}


void test_parallel()
{
	printf("[test parallel]\n");

	Parallel p;
	int cpus = p.get_num_cpus();
	printf("CPUS: %d\n", cpus);
}

void test_kmeans()
{
	printf("[test kmeans]\n");

#if defined(LINUX)
	printf("LINUX\n");
#elif defined(DARWIN)
	printf("DARWIN\n");
#endif
}

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


	//HFMatrix<double> features(feats, 3, 10);
	Loader loader("data/hello_matrix");
	HFMatrix<double> features(loader);


	//HFVector<int> labels(lbls, 10);
	Loader loader2("data/hello_label");
	HFVector<int> labels(loader2);
	
	
	//Saver saver("data/hello_label");
	//labels.save(saver);

	//Saver saver("data/hello_matrix");
	//features.save(saver);

	LDA lda;	
	lda.train(&features, &labels);
}

void test_perceptron()
{
	printf("[test perceptron]\n");

	Loader loader("data/hello_matrix");
	HFMatrix<double> features(loader);
	
	Loader lblLoader("data/hello_label");
	HFVector<int> labels(lblLoader);

	Perceptron p;
	p.train(&features, &labels);
}

int main()
{
	// test_vector();
	// test_matrix();

	// test_lda();

	// test_perceptron();

	// test_kmeans();

	// test_parallel();

	test_distance();
}
