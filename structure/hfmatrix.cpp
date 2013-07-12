#include "hfmatrix.h"
#include "../base/common.h"
#include "../math/hfmath.h"

#include <iostream>
#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>


/** test print matrix **/
void print_matrix(const char *desc, int m, int n, double *a, int lda)
{
	int i, j;
	printf("\n %s\n", desc);
	for(i = 0; i < m; ++i)
	{
		for(j = 0; j < n; ++j)
			printf(" %6.6f", a[i+j*lda]);
		printf("\n");
	}
}

template<class T>
HFMatrix<T>::HFMatrix()
: matrix(NULL), num_rows(0), num_cols(0)
{
}

template<class T>
HFMatrix<T>::HFMatrix(T *m, int nrows, int ncols)
: matrix(m), num_rows(nrows), num_cols(ncols)
{
}

template<class T>
HFMatrix<T>::HFMatrix(Loader &loader)
{
	load(loader);
}

template<class T>
void HFMatrix<T>::save(Saver &saver)
{
	saver.save_matrix(matrix, num_rows, num_cols);
}

template<class T>
void HFMatrix<T>::load(Loader &loader)
{
	loader.load_matrix(matrix, num_rows, num_cols);
}

template<class T>
T* HFMatrix<T>::get_column(int index)
{
	ASSERT(index >= 0 && index < num_cols);
	return matrix+(index*num_rows);
}

/*
 * pseudo inverse of matrix 
 */
template<class T>
double* HFMatrix<T>::pinv(double *matrix, int rows, int cols)
{
	lapack_int m, n, lda, ldu, ldvt, info;
	char jobu = 'A';
	char jobvt = 'A';
	m = rows;
	n = cols;
	lda = rows;
	ldu = rows;
	ldvt = cols;
	int ssize = HFMath::min(m, n);

	double *s = (double*)malloc(sizeof(double)*ssize);
	double *u = (double*)malloc(sizeof(double)*m*m);
	double *vt = (double*)malloc(sizeof(double)*n*n);
	double *sb = (double*)malloc(sizeof(double)*(ssize-1));

	info = LAPACKE_dgesvd(LAPACK_COL_MAJOR, jobu, jobvt, m, n, 
						matrix, lda, s, u, ldu, vt, ldvt, sb);

	ASSERT(info == 0);

	print_matrix("Singular values", 1, n, s, 1);
	print_matrix("Left singular vectors(stored columnwise)", m, n, u, ldu);
	print_matrix("Left singular vectors(stored rowwise)", n, n, vt, ldvt);



	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < ssize; ++j)
			vt[i*n+j] = vt[i*n+j]/s[j];
	
	}

	double *result = (double*)malloc(m*n*sizeof(double));
	cblas_dgemm(CblasColMajor, CblasTrans, CblasTrans, n, m,
				n, 1.0, vt, ldvt, u, ldu, 0, result, n);

	

	free(s);
	free(u);
	free(vt);
	free(sb);

	return result;
}

template<class T>
void HFMatrix<T>::resize(int rows, int cols)
{
	if(rows*cols == num_rows*num_cols)
	{
		num_rows = rows;
		num_cols = cols;
	}
	else
	{
		num_rows = num_cols = 0;
		if(matrix)
			free(matrix);	
		matrix = (T*)malloc(rows*cols*sizeof(T));
		num_rows = rows;
	}	num_cols = cols;
}


template<class T>
void HFMatrix<T>::display_matrix(const char *desc)
{
	std::cout << "\n" << desc << ":\n[";
	int i, j;
	for(i = 0; i < num_rows-1; ++i)
	{
		std::cout << '[';
		for(j = 0; j < num_cols-1; ++j)
			std::cout << matrix[j*num_rows+i] << ',';
		if(num_cols > 0)
			std::cout << matrix[j*num_rows+i];
		std::cout << "],\n";
	}

	if(num_rows > 0)
	{
		std::cout << '[';
		for(j = 0; j < num_cols-1; ++j)
			std::cout << matrix[j*num_rows+i] << ',';
		if(num_cols > 0)
			std::cout << matrix[j*num_rows+i];
		std::cout << "]";
	}
	
	std::cout << "]\n";
}

template<class T>
void HFMatrix<T>::set_const(T val)
{
	for(int i = 0; i < num_rows*num_cols; ++i)
		matrix[i] = val;
}

// allowed difference +/- 0.0001
template<class T>
bool HFMatrix<T>::equals(const HFMatrix<T> &that) const
{
	if((num_rows != that.num_rows) ||
		(num_cols != that.num_cols))
		return false;

	double diff = 0;
	double threshold = 0; // 0.0001;
	for(int i = 0; i < num_rows*num_cols; ++i)
	{
		diff = matrix[i] - that.matrix[i];
		if(diff > threshold || diff < -threshold)
			return false;
	}

	return true;
}

template<class T>
bool HFMatrix<T>::operator==(const HFMatrix<T> &that) const
{
	return ((num_rows == that.num_rows) &&
			(num_cols == that.num_cols) &&
			(matrix == that.matrix));
}

template<class T>
void HFMatrix<T>::copy(const HFMatrix<T> &that)
{
	resize(that.num_rows, that.num_cols);
	for(int i = 0; i < num_rows*num_cols; ++i)
		matrix[i] = that.matrix[i];
}

template class HFMatrix<double>;
