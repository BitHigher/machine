#ifndef DISTANCE_DISTANCE_H
#define DISTANCE_DISTANCE_H


class Distance
{
public:
	Distance();


	virtual double distance(double *v1, double *v2, int size) = 0;	
protected:
	static void* run_distance_thread(void *p);
};

#endif /* DISTANCE_DISTANCE_H */
