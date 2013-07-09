#ifndef CLASSIFIER_LDA_H
#define CLASSIFIER_LDA_H

/*
 * PLDA: Pseudoinverse Linear Discriminant Analysis
 *
 * S_i = (X_i - m_i)(X_i - m_i)^T
 * S_w = S_1 + S_2
 * S_b = (m_1 - m_2)(m_1 - m_2)^T
 * 
 * According to Fisher Linear Discriminant, we have:
 * 
 * J(w) = \frac{w^T S_b w}{w^T S_w w}
 * w = argmax_w(J(w))
 * 
 * w = S_w^{-1}(m_1 - m_2)
 *
 * Because S_w may be irreversible, so we use pseudoinverse 
 * 
 * w = S_w^+ (m_1 - m_2)
 * b = 0.5*(m_2^T S_w^+ m_2 - m_1^T S_w^+ m_1)
 *
 */

#include "classifier.h"

class LDA : public Classifier
{
public:
	LDA();
	void train(HFMatrix<double> *features, HFVector<int> *labels);

};

#endif /* CLASSIFIER_LDA_H */
