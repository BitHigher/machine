#ifndef STRUCTURE_HFMATRIX
#define STRUCTURE_HFMATRIX

#include "../io/saver.h"
#include "../io/loader.h"

template<class T>
class HFMatrix
{
public:
	HFMatrix();
	HFMatrix(T *m, int nrows, int ncols);
	HFMatrix(Loader &loader);
	
	void save(Saver &saver);
	void load(Loader &loader);
	T* get_column(int index);
	
	void resize(int rows, int cols);
	void set_const(T val);

	static double* pinv(double *matrix, int rows, int cols);

	inline T& operator()(int row, int col)
	{
		return matrix[col*num_rows + row];
	}

	// compare pointer
	bool operator==(const HFMatrix<T> &that) const;
	// compare content
	bool equals(const HFMatrix<T> &that) const;
	
	void copy(const HFMatrix<T> &that);


	void display_matrix(const char *desc="Matix");
public:
	int num_rows;
	int num_cols;
	T *matrix;
};

#endif /* STRUCTURE_HFMATRIX */
