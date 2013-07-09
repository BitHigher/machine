#ifndef STRUCTURE_HFMATRIX
#define STRUCTURE_HFMATRIX

/*
#include "../io/saver.h"
#include "../io/loader.h"
*/

template<class T>
class HFMatrix
{
public:
	HFMatrix();
	HFMatrix(T *m, int nrows, int ncols);
//	void save(Saver &saver);
//	void load(Loader &loader);
	T* get_row(int index);

	static double* pinv(double *matrix, int rows, int cols);


public:
	int num_rows;
	int num_cols;
	T *matrix;
};

#endif /* STRUCTURE_HFMATRIX */
