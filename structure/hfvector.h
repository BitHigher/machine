#ifndef STRUCTURE_HFVECTOR
#define STRUCTURE_HFVECTOR

template<class T>
class HFVector
{
public:
	HFVector();
	HFVector(int size);
	HFVector(T *v, int size);
	virtual ~HFVector();

	static double dot(const double *v1, const double *v2, int size);

public:
	T *vector;
	int size;
};


#endif /* STRUCTURE_HFVECTOR */
