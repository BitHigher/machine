#ifndef CLASSIFIER_LDA_H
#define CLASSIFIER_LDA_H

#include "classifier.h"

class LDA : public Classifier
{
public:
	LDA();
	void train(HFMatrix<double> *features, HFVector<int> *labels);

};

#endif /* CLASSIFIER_LDA_H */
