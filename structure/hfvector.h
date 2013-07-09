#ifndef STRUCTURE_HFVECTOR
#define STRUCTURE_HFVECTOR

#include "../io/loader.h"
#include "../io/saver.h"

template<class T>
class HFVector
{
public:
	HFVector();
	HFVector(int size);
	HFVector(T *v, int size);
	HFVector(Loader &loader);
	
	virtual ~HFVector();

	void load(Loader &loader);
	void save(Saver &saver);

	static double dot(const double *v1, const double *v2, int size);
	
	void display_vector(const char *desc = "Vector");
public:
	T *vector;
	int size;
};


#endif /* STRUCTURE_HFVECTOR */
