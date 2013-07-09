#ifndef CLASSIFIER_PERCEPTRON_H
#define CLASSIFIER_PERCEPTRON_H

/*
 * Perceptron:
 *  y = +1 if w^Tx + b > 0
 *  y = -1 otherwise
 * 
 * 
 *
 */

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
