#ifndef CLASSIFIER_LDA_H
#define CLASSIFIER_LDA_H

#include "../structure/hfmatrix.h"
#include "../structure/hfvector.h"

class LDA
{
public:
	LDA();
	void train(HFMatrix<double> *features, HFVector<int> *labels);

private:
	double bias_;
	HFVector<double> w_;
};

#endif /* CLASSIFIER_LDA_H */
