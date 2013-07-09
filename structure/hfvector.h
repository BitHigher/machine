#ifndef STRUCTURE_HFVECTOR
#define STRUCTURE_HFVECTOR

template<class T>
class HFVector
{
public:
	HFVector();
	HFVector(int size);
	HFVector(T *v, int size);
//	~HFVector();

public:
	T *vector;
	int size;
};


#endif /* STRUCTURE_HFVECTOR */
