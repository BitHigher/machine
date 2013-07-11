#ifndef DISTANCE_DISTANCE_H
#define DISTANCE_DISTANCE_H

#include "../structure/hfmatrix.h"
#include "../base/common.h"
#include "../base/parallel.h"

class Distance
{
public:
	Distance();
	Distance(HFMatrix<double> left, HFMatrix<double> right);

	void set_left(HFMatrix<double> left);
	void set_right(HFMatrix<double> right);
	double distance(int i, int j);
	void distances();

	virtual double distance(double *v1, double *v2, int size) = 0;	


protected:
	static void* run_distance_thread(void *p);

protected:
	HFMatrix<double> left_;
	HFMatrix<double> right_;

public: // TODO result_ should be protected
	HFMatrix<double> result_;
};

#endif /* DISTANCE_DISTANCE_H */
