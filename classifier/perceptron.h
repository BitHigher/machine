#ifndef CLASSIFIER_PERCEPTRON_H
#define CLASSIFIER_PERCEPTRON_H

#include "classifier.h"

class Perceptron: public Classifier
{
public:
	Perceptron();

	void train(HFMatrix<double> *features, HFVector<int> *labels);

protected:
	double learn_rate_;
	int max_iter_;
};

#endif /* CLASSIFIER_PERCEPTRON_H */
