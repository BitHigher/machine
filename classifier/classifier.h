#ifndef CLASSIFIER_CLASSIFIER_H
#define CLASSIFIER_CLASSIFIER_H

#include "../structure/hfvector.h"
#include "../structure/hfmatrix.h"


class Classifier
{
public:
	Classifier();
	virtual ~Classifier();

	virtual void train(HFMatrix<double> *features, 
						HFVector<int> *labels) = 0;

protected:
	HFVector<double> w_;
	double bias_;
};


#endif /* CLASSIFIER_CLASSIFIER_H */
