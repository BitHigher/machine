#ifndef CLASSIFIER_PERCEPTRON_H
#define CLASSIFIER_PERCEPTRON_H

/**
 * Perceptron, an implementation of online perceptron.
 *
 * y = +1 if w^Tx + b > 0
 * y = -1 otherwise
 * 
 * Update Strategy: Gradient Descent
 *
 * h = w^Tx + b
 * J = 0.5*(h-y)^2
 * w = argmin_w J
 *
 * gradient = \frac{\delta J}{\delta w} = (h-y)*x
 *
 * error = h - y
 * w -= learn_rate * error * x
 * b += learn_rate + y
 * 
 * h is computed value and y is desired value
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
