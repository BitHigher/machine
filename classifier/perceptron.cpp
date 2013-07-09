#include "perceptron.h"
#include "../base/common.h"

Perceptron::Perceptron()
: learn_rate_(0.1), max_iter_(1000)
{
}

void Perceptron::train(HFMatrix<double> *features, HFVector<int> *labels)
{
	ASSERT(features->num_rows == labels->size);

}
